To implement the "Best Practice" we discussed, we will use **FastAPI**. This script demonstrates how to issue a secure, `HttpOnly` cookie and how to verify it in subsequent requests.

### 1. The Secure Token Issuer

In this setup, the JWT is stored in a cookie that is invisible to JavaScript (XSS protection) and restricted to your domain (CSRF protection).

```python
from fastapi import FastAPI, Response, Request, HTTPException, Depends
from datetime import datetime, timedelta
import jwt

# Security Configuration
SECRET_KEY = "your-ultra-secure-secret" # In production, use a Secret Manager
ALGORITHM = "HS256"
COOKIE_NAME = "access_token"

app = FastAPI()

def create_access_token(data: dict):
    to_encode = data.copy()
    expire = datetime.utcnow() + timedelta(minutes=15)
    to_encode.update({"exp": expire})
    return jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)

@app.post("/login")
async def login(response: Response):
    # 1. Create the token
    token = create_access_token(data={"sub": "sourabh_j"})

    # 2. Set the cookie with Best Practice settings
    response.set_cookie(
        key=COOKIE_NAME,
        value=token,
        httponly=True,   # Prevents XSS: JavaScript cannot read this
        max_age=900,     # 15 minutes
        expires=900,
        samesite="lax",  # Prevents CSRF: Won't be sent on cross-site requests
        secure=True,     # Only sent over HTTPS
    )
    return {"message": "Logged in successfully"}

```

---

### 2. The Verification Middleware

This part of the script acts as a "Gatekeeper." It extracts the token from the cookie and validates it.

```python
def get_current_user(request: Request):
    # 1. Extract token from the secure cookie
    token = request.cookies.get(COOKIE_NAME)
    
    if not token:
        raise HTTPException(status_code=401, detail="Not authenticated")

    # 2. Anti-CSRF Check (Optional but recommended)
    # Check for a custom header that an attacker's <form> cannot set
    if not request.headers.get("X-Requested-With"):
        raise HTTPException(status_code=403, detail="CSRF Protect: Missing Header")

    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        return payload
    except jwt.ExpiredSignatureError:
        raise HTTPException(status_code=401, detail="Token expired")
    except jwt.InvalidTokenError:
        raise HTTPException(status_code=401, detail="Invalid token")

@app.get("/me")
async def read_users_me(current_user: dict = Depends(get_current_user)):
    return {"user": current_user["sub"], "status": "Token is valid and secure"}

```

---

### How this protects your CrossFit Platform:

1. **XSS Protection:** Even if an attacker manages to inject a `<script>` into your workout comments section, `document.cookie` will return an empty string for your `access_token`. The attacker cannot steal the session.
2. **CSRF Protection:**
* By setting `samesite="lax"`, the browser will not attach the cookie if an attacker tries to trigger a request from a different website.
* By checking for `X-Requested-With`, you ensure the request came from your **React** frontend (which uses `fetch` or `axios`) and not a hidden HTML `<form>` on a malicious site.


3. **Integrity:** The `jwt.decode` step ensures that if the user tries to manually edit their `sub` or `role` in the cookie, the signature will fail.

### Testing Tip

When testing this locally on Chrome or Firefox, the `secure=True` flag might prevent the cookie from being set if you are using `http://localhost` instead of `https`. For local development, you can temporarily set `secure=False`.

To implement the "Form Side" of anti-CSRF protection, you need to include a unique token in your HTML that the browser will send back during a `POST` request.

Since you are using a decoupled setup (React frontend and FastAPI backend), there are two ways to do this. The **Double Submit Cookie** method is the most popular for modern SPAs (Single Page Applications).

### 1. The Backend (FastAPI)

The backend needs to generate a separate, non-HttpOnly cookie that the frontend can actually read.

```python
import secrets
from fastapi import FastAPI, Response

app = FastAPI()

@app.get("/get-csrf-token")
def get_csrf_token(response: Response):
    # Generate a random string
    token = secrets.token_hex(32)
    
    # This cookie is NOT HttpOnly so React can read it
    response.set_cookie(
        key="csrf_token", 
        value=token, 
        samesite="lax",
        secure=True # Set to False for local localhost testing
    )
    return {"detail": "CSRF cookie set"}

```

---

### 2. The Frontend (React)

In React, you need to read that cookie and attach it to a custom header. An attacker’s site cannot do this because the **Same-Origin Policy (SOP)** prevents a different domain from reading your cookies.

```javascript
import axios from 'axios';

// Helper function to get a specific cookie by name
const getCookie = (name) => {
  const value = `; ${document.cookie}`;
  const parts = value.split(`; ${name}=`);
  if (parts.length === 2) return parts.pop().split(';').shift();
};

const submitWorkout = async (workoutData) => {
  const csrfToken = getCookie('csrf_token');

  try {
    const response = await axios.post('/api/workout', workoutData, {
      headers: {
        // Send the token in a custom header
        'X-CSRF-Token': csrfToken,
        'X-Requested-With': 'XMLHttpRequest'
      },
      // Ensure cookies (including your HttpOnly JWT) are sent
      withCredentials: true 
    });
    console.log("Workout saved:", response.data);
  } catch (error) {
    console.error("Security check failed:", error);
  }
};

```

---

### 3. The Form Side (Traditional HTML)

If you were using a traditional server-side rendered form (like Jinja2 or Thymeleaf), you would embed the token directly into a hidden input field.

```html
<form action="/update-profile" method="POST">
    <!-- The server generates this value for each session -->
    <input type="hidden" name="csrf_token" value="5f31dcae89b...abc">
    
    <label>New Display Name:</label>
    <input type="text" name="display_name">
    <button type="submit">Update</button>
</form>

```

---

### How this completes the "Security Circle"

When the request hits your server, your backend code (as shown in the previous Python example) performs these checks:

1. **Does the JWT Cookie exist?** (Confirms the user is logged in).
2. **Does the `X-CSRF-Token` header exist?** (Confirms the request came from your code).
3. **Does the Header match the CSRF Cookie?** (Confirms the request wasn't forged).

### Why the attacker fails:

* An attacker can trigger a `POST` request to your backend from their own site (CSRF).
* The browser **will** send the `access_token` (JWT) cookie automatically.
* **HOWEVER**, the attacker cannot read the `csrf_token` cookie from their site to put it into the `X-CSRF-Token` header.
* Your backend sees the missing header and rejects the request with a **403 Forbidden**.

Does this help clarify how the "frontend" and "backend" cooperate to block the forgery?