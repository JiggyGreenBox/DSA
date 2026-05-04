To set up a professional-grade HTTP GET and POST endpoint on Ubuntu, the modern industry standard is to use **Spring Initializr** to bootstrap a Spring Boot project.

Here is the quickest way to get a REST API running from scratch.

---

## 1. Generate the Project

You don't need to manually create folders. Use the web-based generator:

1. Go to [start.spring.io](https://start.spring.io/).
2. **Project:** Maven
3. **Language:** Java
4. **Dependencies:** Search for and add **"Spring Web"**.
5. Click **Generate**. This downloads a `.zip` file.

Unzip it on your Ubuntu system:

```bash
unzip demo.zip -d my-api
cd my-api

```

---

## 2. Create the Controller (The Code)

Navigate to `src/main/java/com/example/demo/` and create a file named `ApiController.java`.

Since you know C++, notice the **Annotations** (`@`). These are like "compiler directives" that tell Spring to handle the low-level socket networking for you.  
```sh
touch ApiController.java
```

```java
package com.example.demo;

import org.springframework.web.bind.annotation.*;
import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping("/api") // Base path
public class ApiController {

    // GET Endpoint: http://localhost:8080/api/hello
    @GetMapping("/hello")
    public String sayHello() {
        return "Hello from Ubuntu!";
    }

    // POST Endpoint: http://localhost:8080/api/data
    // Accepts JSON like: {"name": "User"}
    @PostMapping("/data")
    public Map<String, String> processData(@RequestBody Map<String, String> payload) {
        String name = payload.getOrDefault("name", "Unknown");
        
        Map<String, String> response = new HashMap<>();
        response.put("status", "Success");
        response.put("message", "Processed " + name);
        return response; // Spring automatically converts this Map to JSON
    }
}

```

---

## 3. Run the Server

Spring Boot projects come with a "wrapper" script (`mvnw`) so you don't even need to install Maven separately.

1. **Grant execution permission:**
```bash
chmod +x mvnw

```


2. **Start the app:**
```bash
./mvnw spring-boot:run

```


Wait for the log: `Started DemoApplication in X seconds (process started on port 8080)`.

---

## 4. Test the Endpoints

Open a second terminal window to test your "server" using `curl`.

**Test GET:**

```bash
curl http://localhost:8080/api/hello

```

**Test POST:**

```bash
curl -X POST http://localhost:8080/api/data \
     -H "Content-Type: application/json" \
     -d '{"name": "C++ Developer"}'

```

---

## Summary for C++ Perspective

In C++, creating an HTTP server usually involves linking a library like `Boost.Asio` or `Pistache` and manually parsing strings.

* **Spring Web** handles the multi-threading and socket listening.
* **Jackson** (bundled library) handles the JSON parsing/serialization automatically.
* **Port 8080** is the default for Spring Boot (this is configurable in `application.properties`).

Would you like me to show you how to connect this POST endpoint to a simple database so your data persists after a restart?