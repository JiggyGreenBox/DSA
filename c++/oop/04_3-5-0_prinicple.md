The C++ compiler automatically provides (or implicitly defines) several special member functions for a class if you don't declare them yourself. These are often called the **"Rule of Zero/Three/Five"** functions, as they manage the lifecycle of an object.

The default functions provided are:

---

## 1. Default Constructor

* **Signature:** `ClassName()`
* **When Provided:** If the class declares **no other constructors** (user-defined or deleted).
* **Purpose:** Initializes the object.
    * It **value-initializes** the base classes and members. For primitive types (like `int`, `float`), value initialization means they are typically initialized to zero (or the closest equivalent).

## 2. Destructor

* **Signature:** `~ClassName()`
* **When Provided:** Always, unless you explicitly declare it as deleted.
* **Purpose:** Cleans up the object when it goes out of scope.
    * The implicitly defined destructor simply calls the destructors for all non-static data members and the destructors for all base classes.
    * It **does not** handle freeing dynamically allocated memory (like memory pointed to by a raw pointer). If your class manages resources, you must define your own destructor.

---

## 3. Copy Constructor

* **Signature:** `ClassName(const ClassName& other)`
* **When Provided:** If the class declares **no move constructor, no move assignment operator, no copy constructor, and no copy assignment operator**.
* **Purpose:** Creates a **new object** as a copy of an existing object.
    * The implicitly defined version performs a **member-wise copy** (or **shallow copy**). It copies the value of each member from the source object to the new object.

## 4. Copy Assignment Operator

* **Signature:** `ClassName& operator=(const ClassName& other)`
* **When Provided:** If the class declares **no move constructor, no move assignment operator, no copy constructor, and no copy assignment operator**.
* **Purpose:** Replaces the contents of an **existing object** with a copy of another object.
    * Like the copy constructor, the implicit version performs a **member-wise copy**.

---

## 5. Move Constructor (C++11 and later)

* **Signature:** `ClassName(ClassName&& other)`
* **When Provided:** If the class declares **no destructor, no copy constructor, no copy assignment operator, and no move assignment operator**.
* **Purpose:** Creates a new object by **transferring resources** (like memory) from a temporary (rvalue) object. This avoids expensive copying and is much faster.
    * The implicitly defined version performs a **member-wise move**.

## 6. Move Assignment Operator (C++11 and later)

* **Signature:** `ClassName& operator=(ClassName&& other)`
* **When Provided:** If the class declares **no destructor, no copy constructor, no copy assignment operator, and no move constructor**.
* **Purpose:** Replaces the contents of an existing object by **transferring resources** from a temporary (rvalue) object.
    * The implicitly defined version performs a **member-wise move**.

---

### The Rule of Three/Five/Zero

This behavior is summarized by the "Rules":

* **Rule of Three (pre-C++11):** If you define a **destructor, copy constructor, or copy assignment operator**, you probably need to define all three. (Because you are managing a resource, like raw memory).
* **Rule of Five (C++11 and later):** If you define any of the three above, you should define all **five** (adding the move constructor and move assignment operator) to correctly handle resource management and optimization.
* **Rule of Zero (Modern C++ Idiom):** Do not explicitly define any of the five/three special functions. Instead, use smart pointers (`std::unique_ptr`, `std::shared_ptr`) and other standard library resource managers to handle resource cleanup. This way, the compiler's default functions are correct and safe.