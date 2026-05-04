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