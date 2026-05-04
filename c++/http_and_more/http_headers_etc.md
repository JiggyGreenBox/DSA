An **HTTP Response** is the message a server sends back to a client (like a web browser) after receiving an HTTP Request.

The raw content of an HTTP response follows a specific, plain-text structure, which is separated into three main parts: the **Status Line**, **Headers**, and the **Body**, separated by line breaks (`<CR><LF>` or carriage return followed by line feed).

## 📄 Raw HTTP Response Structure

Here is an example of a successful response for an HTML page:

```raw
HTTP/1.1 200 OK
Date: Fri, 31 Oct 2025 15:00:00 GMT
Server: Apache/2.4.41 (Unix)
Content-Type: text/html; charset=UTF-8
Content-Length: 104
Connection: close

<!DOCTYPE html>
<html>
<head><title>Success</title></head>
<body><h1>Hello World!</h1></body>
</html>
```

-----

## 🧐 Breakdown of the Response

### 1\. Status Line

The first line is the **Status Line**, which provides the HTTP version, a numerical status code, and a brief description.

  * **`HTTP/1.1`**: The HTTP protocol version the server is using.
  * **`200`**: The **Status Code**, a three-digit number indicating the outcome of the request.
      * *200* means **OK** (success). Other common codes include *404 Not Found* (client error) or *500 Internal Server Error* (server error).
  * **`OK`**: The **Reason Phrase** (or Status Text), a human-readable summary of the status code.

### 2\. Response Headers

The lines that follow the Status Line are the **Headers**, which are key-value pairs separated by a colon (`:`). They provide metadata about the response and the server. **Headers are separated from the body by a single blank line.**

  * **`Date`**: The date and time the response was generated.
  * **`Server`**: Information about the web server software.
  * **`Content-Type`**: The **MIME type** of the data in the body, which tells the client how to interpret the content (e.g., `text/html`, `application/json`, `image/jpeg`).
  * **`Content-Length`**: The size of the message body in bytes.
  * **`Connection`**: Control options for the current connection (e.g., `close` or `keep-alive`).

### 3\. Body

The **Body** is the optional data payload of the response, following the empty line.

  * In the example above, the body contains the **HTML content** (`<!DOCTYPE html>...`) that the client requested.
  * The content in the body is determined by the `Content-Type` header (e.g., it could be HTML, JSON data, an image file, or simply plain text).

-----

Would you like to see a raw HTTP response example for a specific scenario, like a successful JSON API response or a "404 Not Found" error?