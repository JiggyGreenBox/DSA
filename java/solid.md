The **SOLID** principles are five design guidelines that help developers create software that is easy to maintain, scale, and understand. While the logic is the same in both C++ and Java, the implementation differs slightly due to memory management and language syntax.

---

## 1. Single Responsibility Principle (SRP)

**A class should have only one reason to change.**

* **Java:** Uses standard classes and private fields.
* **C++:** Often separates declaration (`.h`) and implementation (`.cpp`), but follows the same logic.

| Language | Code Snippet |
| --- | --- |
| **Java** | `class Invoice { void calculateTotal() { /*...*/ } }` <br>

<br> `class InvoicePrinter { void print(Invoice i) { /*...*/ } }` |
| **C++** | `class Invoice { public: void calculateTotal(); };` <br>

<br> `class InvoicePrinter { public: void print(const Invoice& i); };` |

---

## 2. Open/Closed Principle (OCP)

**Software entities should be open for extension, but closed for modification.**

We use **Interfaces** (Java) or **Abstract Base Classes** (C++).

### Java snippet:

```java
interface Shape { double area(); }

class Circle implements Shape {
    public double radius;
    public double area() { return Math.PI * radius * radius; }
}

```

### C++ snippet:

```cpp
class Shape {
public:
    virtual double area() const = 0; // Pure virtual function
};

class Circle : public Shape {
    double radius;
public:
    double area() const override { return 3.14 * radius * radius; }
};

```

---

## 3. Liskov Substitution Principle (LSP)

**Objects of a superclass should be replaceable with objects of its subclasses without breaking the application.**

A classic example is the "Square-Rectangle" problem. A Square should not inherit from Rectangle if it violates the behavior of the width/height setters.

---

## 4. Interface Segregation Principle (ISP)

**Clients should not be forced to depend on methods they do not use.**

Rather than one large "Worker" interface, create smaller, specific ones.

### Java snippet:

```java
interface Printer { void print(); }
interface Scanner { void scan(); }

class MultiFunctionMachine implements Printer, Scanner {
    public void print() { /*...*/ }
    public void scan() { /*...*/ }
}

```

### C++ snippet:

```cpp
class IPrinter { public: virtual void print() = 0; };
class IScanner { public: virtual void scan() = 0; };

class MultiFunctionMachine : public IPrinter, public IScanner {
public:
    void print() override { /*...*/ }
    void scan() override { /*...*/ }
};

```

---

## 5. Dependency Inversion Principle (DIP)

**High-level modules should not depend on low-level modules. Both should depend on abstractions.**

### Java (Using Dependency Injection):

```java
class Switch {
    private Device device; // Depends on Interface, not concrete class
    Switch(Device d) { this.device = d; }
}

```

### C++ (Using Smart Pointers):

```cpp
class Switch {
    std::unique_ptr<Device> device; 
public:
    Switch(std::unique_ptr<Device> d) : device(std::move(d)) {}
};

```

---

### Key Differences to Note:

* **Interfaces:** Java has a dedicated `interface` keyword. C++ achieves this using classes with **pure virtual functions** (e.g., `virtual void func() = 0;`).
* **Memory:** In C++, you must be careful with object ownership (using `std::unique_ptr` or `std::shared_ptr`) when applying DIP or OCP. Java handles this via the Garbage Collector.

Would you like me to expand on any specific principle with a full, compilable code example?