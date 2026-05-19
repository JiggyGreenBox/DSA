To implement idempotency in a web service, we usually use **Redis** because it is extremely fast and supports "atomic" operations (operations that happen all at once, preventing race conditions).

In this example, we'll use a **FastAPI** style approach. The logic is: "Try to claim this request ID. If I can't, it means we've already processed it."

### The Logic Flow

---

### Python Code Example

This script uses `redis-py`. It simulates a payment process where we only want to charge the user once, even if the function is called multiple times with the same `request_id`.

```python
import redis
import uuid
import time

# Connect to local Redis
r = redis.Redis(host='localhost', port=6379, decode_responses=True)

def process_payment(request_id, amount, user_id):
    """
    Simulates a payment that is protected by an Idempotency Key.
    """
    # 1. Generate a unique key for Redis
    idempotency_key = f"payment:{request_id}"

    # 2. ATOMIC CHECK: 'nx=True' means "Set if Not Exists"
    # We set an expiry (ex=3600) so the key eventually clears out of Redis
    is_new_request = r.set(idempotency_key, "PROCESSING", nx=True, ex=3600)

    if not is_new_request:
        # 3. If the key exists, check if it's still processing or finished
        status = r.get(idempotency_key)
        if status == "PROCESSING":
            return {"status": "error", "message": "Request is already being handled"}
        else:
            return {"status": "success", "message": "Duplicate request: Payment already confirmed", "data": status}

    # --- START CRITICAL BUSINESS LOGIC ---
    try:
        print(f"Processing unique payment of ${amount} for user {user_id}...")
        
        # Simulate network delay/processing
        time.sleep(2) 
        
        # Actual logic: charge_credit_card(user_id, amount)
        transaction_result = f"TXN_{uuid.uuid4().hex[:8].upper()}"
        
        # 4. Update the key with the actual result
        r.set(idempotency_key, transaction_result, ex=3600)
        
        return {"status": "success", "message": "Payment processed", "txn_id": transaction_result}
    
    except Exception as e:
        # If the actual logic fails, delete the key so the user can try again
        r.delete(idempotency_key)
        return {"status": "error", "message": str(e)}

# --- TESTING THE BEHAVIOR ---

# Unique Request ID (The client should generate this)
shared_request_id = "client_req_999"

# First Attempt: Should succeed
print("Attempt 1:", process_payment(shared_request_id, 50.0, "user_1"))

# Second Attempt (Immediate Retry): Should recognize it as a duplicate
print("Attempt 2:", process_payment(shared_request_id, 50.0, "user_1"))

```

### Why this works for Interviews:

1. **Atomic `SET NX`:** You aren't doing a `get` followed by a `set`. Doing them as two separate steps creates a "Race Condition" where two requests could both see "None" and both proceed to charge the user. `SET NX` combines them into one operation.
2. **State Management:** The code handles three states: **New** (proceed), **Processing** (tell the client to wait), and **Completed** (return the cached result).
3. **The "Cleanup" on Failure:** Note the `except` block. If your database or payment gateway crashes, you **must** delete the idempotency key; otherwise, the user will be "locked out" and unable to pay even if they try with a valid request later.