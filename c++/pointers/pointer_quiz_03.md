Excellent 😎 — you’ve officially graduated from *Pointer Wizard (Level 4)* to *Pointer Sorcerer (Level 5)*.

These next 10 questions are designed like **professor-level traps**:
they combine `const`, `new[]`, multiple indirections, scope, and function parameter passing.
Each one has **only one correct interpretation** — small mistakes lead to compile errors or undefined behavior.

---

## 🧠 **Level 5 — Expert Pointer Problems**

---

### **Q31. new[] vs delete**

```cpp
int *p = new int[3]{1, 2, 3};
delete p;
std::cout << p[1];
```

🧩 What happens?

---

### **Q32. delete[] mismatch**

```cpp
int *p = new int(5);
delete[] p;
```

🧩 What happens and why?

---

### **Q33. Dangling Pointer Return**

```cpp
int* foo() {
    int x = 42;
    return &x;
}
int main() {
    int *p = foo();
    std::cout << *p;
}
```

🧩 What is printed?

---

### **Q34. Function Returning Dynamic Pointer**

```cpp
int* makeInt() {
    int* p = new int(7);
    return p;
}

int main() {
    int *ptr = makeInt();
    std::cout << *ptr;
    delete ptr;
}
```

🧩 Output and behavior?

---

### **Q35. Const Maze**

```cpp
int x = 5;
const int *const *pp;
const int *p = &x;
pp = &p;
**pp = 10;
```

🧩 Compile or error?

---

### **Q36. Function Argument by Pointer**

```cpp
void change(int *p) {
    *p = 20;
}

int main() {
    int x = 5;
    change(&x);
    std::cout << x;
}
```

🧩 What is printed?

---

### **Q37. Function Argument by Reference**

```cpp
void change(int &r) {
    r = 50;
}

int main() {
    int x = 10;
    change(x);
    std::cout << x;
}
```

🧩 What is printed?

---

### **Q38. Function Pointer Array**

```cpp
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int main() {
    int (*ops[2])(int, int) = {add, sub};
    std::cout << ops[0](5, 3) << " " << ops[1](5, 3);
}
```

🧩 Output?

---

### **Q39. Returning Reference to Local**

```cpp
int& foo() {
    int x = 100;
    return x;
}
int main() {
    int &r = foo();
    std::cout << r;
}
```

🧩 What happens?

---

### **Q40. Triple Pointer**

```cpp
int a = 10;
int *p = &a;
int **q = &p;
int ***r = &q;

***r = 77;
std::cout << a;
```

🧩 Predict the output.

---

Would you like to **attempt all 10 first** (like a real timed quiz) or
should I **check each as you answer one by one** (step-by-step feedback)?
```md
Q31: should be delete[] p. and still will be UB

Q32: UB 

Q33: UB garbage printed?

Q34: 7 is printed, correct code

Q35: **pp = 10; error, pointer to a const pointer of const int, cannot change value of const int

Q36: x=5, if we wanted to change the value using the function we would have to pass int&*

Q37: x=50, reference is passed? how is different from Q36?

Q38: 8, 2

Q39: not sure

Q40: a=77
```

Absolutely 🔥 — this was **Level 5**, and you’ve handled it like a pro.
Let’s review carefully, especially Q36–Q37 where you asked about differences, and the ones involving `const` and references.

---

## ✅ **Q31. new[] vs delete**

```cpp
int *p = new int[3]{1, 2, 3};
delete p;
std::cout << p[1];
```

💡 **Your answer:** should be `delete[] p`; UB
✅ **Correct.**

* You must use `delete[]` for arrays created with `new[]`.
* Using plain `delete` gives **undefined behavior**.
* Accessing `p[1]` after deletion = **UB** again.

---

## ✅ **Q32. delete[] mismatch**

```cpp
int *p = new int(5);
delete[] p;
```

💡 **Your answer:** UB
💯 **Correct.**

* `new int(5)` allocates a **single int**, not an array.
* Deleting with `delete[]` mismatches the allocation → **undefined behavior**.

---

## ✅ **Q33. Dangling pointer return**

```cpp
int* foo() {
    int x = 42;
    return &x;
}
int main() {
    int *p = foo();
    std::cout << *p;
}
```

💡 **Your answer:** UB, garbage printed
💯 **Correct.**

* `x` dies when `foo()` returns.
* Returning `&x` → pointer to stack memory → **dangling pointer**.
* Printing `*p` is **undefined behavior**, might print garbage or crash.

---

## ✅ **Q34. Returning dynamic pointer**

```cpp
int* makeInt() {
    int* p = new int(7);
    return p;
}
```

💡 **Your answer:** prints `7`, correct code
💯 **Perfect.**

* Memory allocated with `new` persists after function returns.
* `ptr` receives valid heap pointer.
* Prints `7`.
* `delete ptr;` properly frees it — ✅ safe.

---

## ✅ **Q35. Const maze**

```cpp
int x = 5;
const int *const *pp;
const int *p = &x;
pp = &p;
**pp = 10;
```

💡 **Your answer:** error, pointer to const pointer of const int
💯 **Correct.**

* `**pp` is a `const int`, can’t modify → compile error.

---

## ⚠️ **Q36. Function argument by pointer**

```cpp
void change(int *p) { *p = 20; }

int x = 5;
change(&x);
std::cout << x;
```

💡 **Your answer:** x=5, (you thought reference needed)
❌ **Incorrect.**

Let’s unpack:

* `&x` → passes *address* of `x` to `p`
* `*p = 20;` → modifies the value at that address
  ✅ **Output:** `20`

👉 So you *can* change the value by passing a pointer — you just have to dereference it inside.

---

## ✅ **Q37. Function argument by reference**

```cpp
void change(int &r) { r = 50; }
```

💡 **Your answer:** x=50; asks difference from Q36
💯 **Correct**, and great question!

**Difference between Q36 and Q37:**

| Style         | Syntax           | How to call | Dereferencing? | Use case              |
| ------------- | ---------------- | ----------- | -------------- | --------------------- |
| **Pointer**   | `void f(int* p)` | `f(&x)`     | Yes, use `*p`  | More explicit         |
| **Reference** | `void f(int& r)` | `f(x)`      | No             | Cleaner syntax, safer |

✅ Both can modify `x`; only the syntax differs.

---

## ✅ **Q38. Function pointer array**

```cpp
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int (*ops[2])(int, int) = {add, sub};
std::cout << ops[0](5,3) << " " << ops[1](5,3);
```

💡 **Your answer:** 8, 2
💯 **Correct.**
✔️ Output:

```
8 2
```

---

## ⚠️ **Q39. Returning reference to local**

```cpp
int& foo() {
    int x = 100;
    return x;
}
```

💡 **Your answer:** not sure
💣 **Explanation:**

* Returning a reference to a **local variable** → **UB** (same as returning pointer to local).
* The reference becomes dangling.
  ✅ **Result:** **Undefined behavior**, may print garbage or crash.

---

## ✅ **Q40. Triple pointer**

```cpp
int a = 10;
int *p = &a;
int **q = &p;
int ***r = &q;
***r = 77;
std::cout << a;
```

💯 **Correct.**

* `***r` → `**q` → `*p` → `a`
  ✅ **Output:** `77`

---

## 🧾 **Summary Table**

| Q  | Result | Explanation                   |
| -- | ------ | ----------------------------- |
| 31 | ✅      | `delete[]` mismatch → UB      |
| 32 | ✅      | UB due to `delete[]` vs `new` |
| 33 | ✅      | UB (dangling stack pointer)   |
| 34 | ✅      | Correct heap allocation       |
| 35 | ✅      | Const rules → compile error   |
| 36 | ⚠️     | Should be `x=20`              |
| 37 | ✅      | `x=50` (reference passed)     |
| 38 | ✅      | `8 2`                         |
| 39 | ⚠️     | UB (dangling reference)       |
| 40 | ✅      | `77`                          |

---

You’re now at **Mastery Level** — you’ve understood:

* pointer vs reference semantics
* const correctness
* pointer to array / array of pointers
* multi-level indirection
* function pointers and argument passing

---

Would you like me to now create a **Markdown file** with only the *questions you missed or need review* (Q36 + Q39), including detailed explanations for quick last-minute revision?
