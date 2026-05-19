To illustrate this, we will use an **Asymmetric (RS256)** approach. This is the industry standard for microservices because it follows the "Principle of Least Privilege": only one service can "mint" tokens, while everyone else can only "check" them.

### The Architecture Roles

1. **Identity Service (The Issuer):** Holds the **Private Key**. It authenticates users and generates the JWT.
2. **Order/Workout Service (The Validator):** Holds the **Public Key**. it receives the JWT from the user and verifies it.

---

### Step 1: Generate the RSA Key Pair

First, you need a pair of keys. You can generate these using `cryptography` in Python.

```python
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization

# Generate Private Key
private_key = rsa.generate_private_key(public_exponent=65537, key_size=2048)
private_pem = private_key.private_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PrivateFormat.PKCS8,
    encryption_algorithm=serialization.NoEncryption()
)

# Generate Public Key
public_key = private_key.public_key()
public_pem = public_key.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

with open("private.pem", "wb") as f: f.write(private_pem)
with open("public.pem", "wb") as f: f.write(public_pem)

```

---

### Step 2: Identity Service (Create the Token)

This service uses the **Private Key** to sign the payload.

```python
import jwt # pip install PyJWT
import datetime

# Load the private key
with open("private.pem", "rb") as f:
    private_key_data = f.read()

def create_token(user_id):
    payload = {
        "sub": user_id,
        "role": "admin",
        "iat": datetime.datetime.utcnow(),
        "exp": datetime.datetime.utcnow() + datetime.timedelta(hours=1)
    }
    # Sign using RS256
    token = jwt.encode(payload, private_key_data, algorithm="RS256")
    return token

print(f"Generated JWT: {create_token('user_123')}")

```

---

### Step 3: Other Microservices (Verify the Token)

The Workout Service doesn't need the private key. It only needs the **Public Key** to ensure the token hasn't been tampered with.

```python
import jwt

# Load the public key
with open("public.pem", "rb") as f:
    public_key_data = f.read()

def verify_token(token):
    try:
        # Verify using the Public Key
        decoded_payload = jwt.decode(token, public_key_data, algorithms=["RS256"])
        print("✅ Token is valid!")
        return decoded_payload
    except jwt.ExpiredSignatureError:
        print("❌ Token has expired.")
    except jwt.InvalidTokenError:
        print("❌ Invalid token signature.")

# Example Usage
# verify_token("PASTE_TOKEN_HERE")

```

---

### Key Takeaways for your System Design mindset:

* **Security:** If your "Workout Service" is compromised, the hacker only finds the `public.pem`. They can see the users' IDs, but they **cannot** create a fake token to gain admin access.
* **Performance:** The Validator service does not need to make an API call back to the Identity Service to check the token. It does the math locally using the public key. This is why JWT is so fast for scaling.
* **Key Rotation:** In a real-world scenario, you wouldn't store these as files. You would use a **Secret Manager** (AWS KMS, HashiCorp Vault) and serve the Public Key via a **JWKS** (JSON Web Key Set) endpoint so services can update their keys automatically.
---
### Refresh Tokens
| Token         | Purpose               |
| ------------- | --------------------- |
| Access Token  | Access APIs           |
| Refresh Token | Get new access tokens |
---
| Token         | Storage                |
| ------------- | ---------------------- |
| Access Token  | Memory                 |
| Refresh Token | HttpOnly Secure Cookie |
---
| Token         | Expiry  |
| ------------- | ------- |
| Access Token  | 15 min  |
| Refresh Token | 30 days |
