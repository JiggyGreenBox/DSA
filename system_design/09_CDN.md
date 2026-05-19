# CDN (Content Delivery Network)

A CDN is a globally distributed network of servers that cache and serve content closer to users.

Core goal:

```text id="e6h3b8"
Reduce latency
+
Reduce backend load
+
Improve scalability
```

---

# The Core Problem

Suppose your servers are only in:

```text id="s1jpdw"
Mumbai
```

Now a user from:

```text id="w9qoww"
New York
```

requests:

```text id="y8zgn1"
image.jpg
```

The request must travel:

* across continents
* through many networks

This increases:

* latency
* bandwidth cost
* server load

---

# CDN Solution

Instead of serving from origin server every time:

```text id="d7f8du"
User → Nearby CDN Edge Server
```

The CDN caches content near users.

---

# Basic Architecture

```text id="i2o8jv"
Users
   ↓
Nearest CDN Edge
   ↓
Origin Server
```

---

# How It Works

---

# Step 1 — First Request

User requests:

```text id="wrn9tg"
logo.png
```

CDN edge server does not have it.

So CDN fetches from origin server.

---

# Step 2 — CDN Caches Content

CDN stores:

```text id="g64cx7"
logo.png
```

at edge location.

---

# Step 3 — Future Requests

Nearby users now get:

```text id="zhcytt"
logo.png
```

directly from CDN.

Faster.

---

# What Is an Edge Server?

A geographically distributed CDN server.

Example locations:

* Mumbai
* Singapore
* London
* Virginia
* Tokyo

Users connect to nearest edge.

---

# Why CDNs Matter

---

# 1. Lower Latency

Closer physical distance.

Huge improvement for:

* images
* videos
* JS/CSS
* downloads

---

# 2. Reduced Origin Load

Without CDN:

```text id="l6x9p0"
All users → Origin
```

With CDN:

```text id="agzryo"
Most requests → CDN cache
```

Origin handles far fewer requests.

---

# 3. Better Scalability

CDN absorbs huge traffic spikes.

Especially important for:

* viral traffic
* product launches
* streaming
* static assets

---

# 4. Better Availability

If origin partially struggles:

* cached content may still work

Improves resilience.

---

# Static vs Dynamic Content

Very important distinction.

---

# Static Content

Easy to cache.

Examples:

* images
* videos
* CSS
* JS
* fonts
* PDFs

Perfect CDN use case.

---

# Dynamic Content

Generated per request.

Examples:

* personalized feeds
* banking dashboard
* live account data

Harder to cache.

---

# Modern CDNs Can Also Cache Dynamic APIs

Using:

* cache rules
* TTLs
* query awareness
* edge compute

But interview-wise:
understand:

> static content is the primary CDN target

---

# CDN Cache Flow

```text id="cvjlwm"
Request
   ↓
CDN Cache?
   ↓
HIT → Return cached content
MISS → Fetch from origin
```

---

# Cache Hit

CDN already has content.

Fast.

---

# Cache Miss

CDN fetches from origin.

Slower.

---

# Cache Hit Ratio

Very important metric.

```text id="2bfkn6"
cache hits / total requests
```

Higher hit ratio:

* lower backend load
* better performance

---

# TTL (Time To Live)

Cached objects expire after some duration.

Example:

```text id="l1xxr7"
Cache image for 24 hours
```

After expiration:

* CDN refreshes from origin

---

# Cache Invalidation

Hard problem.

Suppose:

* image updated
* CDN still serves old version

Need invalidation.

Methods:

* TTL expiration
* purge cache
* versioned URLs

---

# Versioned URLs (Very Common)

Instead of:

```text id="bzq9lv"
app.js
```

use:

```text id="bl0e57"
app.v2.js
```

Now CDN treats it as new file.

Very common production strategy.

---

# CDN + Load Balancer

Common architecture:

```text id="17i9sz"
Users
   ↓
CDN
   ↓
Load Balancer
   ↓
App Servers
```

CDN reduces traffic before it even reaches load balancer.

---

# CDN + Microservices

Usually CDN sits only in front of:

* frontend assets
* public APIs
* media content

Not internal services.

---

# CDN + Video Streaming

Massive use case.

Without CDN:

```text id="ll1p4m"
Millions → Origin
```

Impossible at scale.

CDNs are essential for:

* Netflix
* YouTube
* Twitch

---

# CDN + DDoS Protection

Major real-world benefit.

CDNs like:

* Cloudflare
* Akamai Technologies

absorb massive malicious traffic.

This is a huge practical advantage.

---

# Edge Computing

Modern CDNs can run logic at edge servers.

Examples:

* authentication
* redirects
* bot filtering
* personalization

Examples:

* Cloudflare Workers
* AWS Lambda@Edge

Advanced topic but good to know exists.

---

# Pull vs Push CDN

Interviewers sometimes ask this.

---

# Pull CDN (Common)

CDN fetches content automatically from origin.

Simple.

Most common.

---

# Push CDN

Origin uploads content directly to CDN.

More control.

Less common for normal web apps.

---

# Important Tradeoffs

---

# Benefit vs Staleness

Caching improves speed.

But risk:

* stale data

Classic distributed systems tradeoff.

---

# Dynamic Content Harder To Cache

Personalized data reduces CDN usefulness.

---

# Cost

CDNs cost money.

But usually cheaper than scaling origin infinitely.

---

# CDN and CAP Thinking

CDNs often favor:

* availability
* performance

Sometimes at expense of:

* immediate consistency

Example:

* stale cached content briefly served

This is acceptable for many systems.

---

# Real Technologies

Common CDN providers:

* Cloudflare
* Amazon Web Services CloudFront
* Fastly
* Google Cloud CDN
* Akamai Technologies

Good to recognize these names.

---

# What Interviewers Want To Hear

Good signals:

* “Use CDN for static assets.”
* “Reduce origin load.”
* “Improve global latency.”
* “Cache invalidation is important.”
* “Use versioned assets.”
* “CDN improves scalability.”
* “High cache hit ratio is desirable.”

---

# What NOT To Overfocus On

Avoid deep study initially on:

* BGP routing
* Anycast internals
* ISP peering
* low-level networking

Not necessary early for system design interviews.

---

# Most Important CDN Concepts

If reducing to essentials:

1. Edge servers
2. Cache hit vs miss
3. TTL
4. Cache invalidation
5. Static asset caching
6. Reduced latency
7. Reduced origin load
8. Global scalability
9. CDN before load balancer
10. Versioned assets

Master these first.

---

# Common System Design Pattern

Very common architecture:

```text id="wq1nft"
Users
   ↓
CDN
   ↓
Load Balancer
   ↓
App Servers
   ↓
Redis
   ↓
Database
```

This appears constantly in interviews.

---

# Best Topics To Learn Next

Perfect next sequence after CDN:

1. Caching
2. Redis
3. Database Replication
4. Sharding
5. CAP Theorem
6. Rate Limiting
7. API Gateway
8. Queueing
9. Fault Tolerance

These connect directly to CDN-based scaling systems.
