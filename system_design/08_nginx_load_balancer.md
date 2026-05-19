For your LLD practice or your CrossFit platform, using **Nginx** as a load balancer on Ubuntu is a high-performance, industry-standard choice. In this setup, Nginx acts as a **Reverse Proxy**, receiving requests and distributing them to your backend servers (like your FastAPI or Java instances).

### 1. Basic Architecture

In this scenario, Nginx sits at the front, and your application instances sit behind it in a private network.

---

### 2. Configuration Example

On Ubuntu, your configuration usually lives in `/etc/nginx/conf.d/load_balancer.conf` or `/etc/nginx/sites-available/default`.

```nginx
# 1. Define the group of backend servers
upstream backend_servers {
    # Round Robin is the default
    server 10.0.0.1:8000; # App Server 1
    server 10.0.0.2:8000; # App Server 2
    server 10.0.0.3:8000; # App Server 3
    
    # Optional: Weighted Round Robin
    # server 10.0.0.4:8000 weight=3; 
}

server {
    listen 80;
    server_name api.yourdomain.com;

    location / {
        # 2. Forward requests to the upstream group
        proxy_pass http://backend_servers;

        # 3. Essential Headers for System Design
        # Ensures the backend knows the real IP of the user, not the LB's IP
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;

        # 4. Timeouts (Preventing the "Slowloris" or hanging connections)
        proxy_connect_timeout 5s;
        proxy_send_timeout 10s;
        proxy_read_timeout 10s;
    }
}

```

---

### 3. Key Settings for Interviews

#### A. Choosing the Algorithm

You can modify the `upstream` block to change how Nginx picks a server:

* **Least Connections:** `upstream { least_conn; server ... }` — Best if some requests take longer to process (e.g., generating an X-ray report vs. fetching a user profile).
* **IP Hash:** `upstream { ip_hash; server ... }` — Ensures a user from the same IP always hits the same server. Useful if you haven't moved your session data to Redis yet.

#### B. Health Checks (Passive)

Nginx's open-source version uses "Passive" health checks. You can configure it to stop sending traffic to a server if it fails a certain number of times:

```nginx
upstream backend_servers {
    server 10.0.0.1:8000 max_fails=3 fail_timeout=30s;
}

```

If the server fails 3 times within 30 seconds, Nginx marks it as "down" for the next 30 seconds.

---

### 4. SSL Termination (Standard Practice)

In a production setup, you should handle SSL at Nginx so your FastAPI/Java apps don't waste CPU cycles on encryption.

```nginx
server {
    listen 443 ssl;
    ssl_certificate /etc/letsencrypt/live/api.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/api.com/privkey.pem;

    location / {
        proxy_pass http://backend_servers;
    }
}

```

---

### 5. Testing the Setup

Once you save the file, always run the syntax check before restarting:

```bash
sudo nginx -t
sudo systemctl restart nginx

```

**Senior IC Tip:** When discussing this in an interview, mention that you'd use **Keepalive** connections in the upstream block. By keeping a pool of connections open between Nginx and your backends, you avoid the "TCP Handshake" overhead for every single request, which significantly reduces latency.

Are you planning to run these backend servers as Docker containers on your Ubuntu machine, or are they separate physical/virtual instances?

In a standard production environment, **SSL Termination** is the process where the Load Balancer (Nginx) handles the heavy lifting of encrypting and decrypting data, allowing your backend microservices to focus purely on business logic.

To understand why this is important, we have to look at the "Handshake" and the "CPU cost."

---

## 1. How SSL/TLS Termination Works

When a user visits your CrossFit platform via `https://`, a complex "handshake" occurs to establish a secure connection.

1. **The Handshake:** The browser and Nginx negotiate encryption keys. This involves mathematically expensive operations (asymmetric cryptography).
2. **Termination:** Nginx decrypts the incoming request. It then forwards the "plain" HTTP request over your **private, internal network** to your FastAPI or Java service.
3. **The Response:** Your service sends a plain response back to Nginx. Nginx encrypts it and sends it back to the user's browser.

---

## 2. Why do we terminate at the Load Balancer?

### A. Performance (CPU Offloading)

Encrypting and decrypting packets is CPU-intensive. If you have 10 microservices all handling their own SSL, you are wasting a significant portion of your cluster's total CPU power. By centralizing this at Nginx, you can optimize Nginx for cryptography and let your apps run "lean."

### B. Simplified Certificate Management

Imagine you have 50 microservices. If you don't terminate at the gateway/LB, you have to install and renew SSL certificates (like Let's Encrypt) on **all 50 servers**.
With SSL Termination, you only manage the certificate in **one place**: the Nginx configuration.

### C. Inspection and Routing (L7)

If the traffic is encrypted all the way to the app, the Load Balancer can't "see" inside the request. It wouldn't be able to look at the URL path (e.g., `/api/workouts`) or the Headers to make routing decisions. Termination allows Nginx to read the request and route it intelligently.

---

## 3. The Security Trade-off: Termination vs. Passthrough

In an interview, you might be asked: *"Isn't it insecure to send plain text from Nginx to the backend?"*

* **SSL Termination:** Traffic is plain text *inside* your private network (VPC). This is standard for 90% of web apps because the private network is isolated from the internet.
* **SSL Passthrough:** Nginx passes the encrypted bits directly to the backend without looking at them.
* **Use Case:** High-security environments (Banking, Healthcare) where even internal admins shouldn't be able to "sniff" traffic on the internal wire.
* **Downside:** No L7 routing, and every backend server needs its own certificate.



---

## 4. Setting it up in Nginx

For your Ubuntu setup, once you've pointed your domain to your IP, you would typically use **Certbot** to get a free certificate. It automatically updates your Nginx file to look like this:

```nginx
server {
    listen 443 ssl; # Listen on the HTTPS port
    server_name api.crossfit-app.com;

    # Paths to your certificate files
    ssl_certificate /etc/letsencrypt/live/api.crossfit-app.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/api.crossfit-app.com/privkey.pem;

    # Recommended Security Settings
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers HIGH:!aNULL:!MD5;

    location / {
        proxy_pass http://backend_servers; # Internal traffic is HTTP
        proxy_set_header X-Forwarded-Proto https; # Tell the app the user used HTTPS
    }
}

```

---

## 5. Senior Interview Tip: "X-Forwarded-Proto"

When you terminate SSL, your FastAPI app thinks it's receiving a regular `http` request. If your app generates links (like a password reset link), it might accidentally create them as `http://` instead of `https://`.

To fix this, you must tell Nginx to add the header `proxy_set_header X-Forwarded-Proto $scheme;`. This tells the backend: *"Hey, the user actually connected via HTTPS, I just decrypted it for you."*

Does this clear up the mystery of why we stop the "S" in HTTPS at the Nginx layer?

In a standard Nginx setup on Ubuntu, changing the algorithm is as simple as adding a single directive to your `upstream` block. By default, Nginx uses **Round Robin**, but you can shift to more sophisticated methods depending on your system's needs.

## 1. Changing the Algorithm

You define the strategy inside the `upstream` context in your configuration file (usually `/etc/nginx/conf.d/load_balancer.conf`).

### A. Round Robin (Default)

No extra keyword is needed. Nginx simply passes requests to servers in order: 1, 2, 3, then back to 1.

```nginx
upstream backend_servers {
    server 10.0.0.1:8000;
    server 10.0.0.2:8000;
}

```

### B. Least Connections (`least_conn`)

This sends the next request to the server with the fewest active connections. It is ideal for "long-lived" requests (like a heavy C++ data processing task or a large file download).

```nginx
upstream backend_servers {
    least_conn; # Add this line
    server 10.0.0.1:8000;
    server 10.0.0.2:8000;
}

```

### C. IP Hash (`ip_hash`)

This uses the client's IP address to determine which server gets the request. This ensures a user is "stuck" to a specific server, which is helpful if you are using local in-memory sessions instead of a centralized Redis store.

```nginx
upstream backend_servers {
    ip_hash; # Add this line
    server 10.0.0.1:8000;
    server 10.0.0.2:8000;
}

```

### D. Weighted Round Robin (`weight`)

If one of your servers has more RAM or a faster CPU, you can tell Nginx to send it more traffic.

```nginx
upstream backend_servers {
    server 10.0.0.1:8000 weight=3; # Gets 3x more traffic
    server 10.0.0.2:8000 weight=1;
}

```

---

## 2. How do we know which server gets the request?

In an interview, you'll be asked how to verify your distribution. You can do this in three ways:

### A. The "X-Backend-Server" Header (Best for Debugging)

You can configure Nginx to "tag" the response with the identity of the server that handled it. This is extremely useful during development.

In your `server` block:

```nginx
location / {
    proxy_pass http://backend_servers;
    # This adds a header to the response you see in the Browser Network Tab
    add_header X-Backend-Server $upstream_addr;
}

```

When you check the **Network Tab** in your browser, you will see a header like `X-Backend-Server: 10.0.0.2:8000`.

### B. Nginx Access Logs

Nginx keeps a record of every request. You can customize the log format to show the `upstream_addr`.
Check your logs with:

```bash
tail -f /var/log/nginx/access.log

```

You will see which internal IP was hit for every incoming request.

### C. Application-Level Logging

In your **FastAPI** or **Java** code, you can print the server's hostname or IP to the console whenever a request is received.

```python
import socket
print(f"Request handled by: {socket.gethostname()}")

```

---

## 3. Which one should you choose for your project?

* **For your CrossFit Platform:** If you are running multiple instances of a Python/FastAPI backend on one Ubuntu machine, **Round Robin** is perfectly fine.
* **For your X-ray Tool:** If processing an image takes a long time, **Least Connections** is better. It ensures that if Server A is busy crunching numbers on a heavy X-ray, the next user gets sent to the idle Server B.

**Pro-Tip for NVIDIA Interviews:** If they ask about scaling, mention **Consistent Hashing**. Unlike standard IP Hash (which breaks if you add a third server), Consistent Hashing minimizes the number of keys that need to be remapped when the server cluster size changes. Nginx Plus supports this natively, but for the open-source version, you often use the `hash $remote_addr consistent;` directive.