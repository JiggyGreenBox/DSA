# Polymorphism
* Mutate behaviour according to code context
* means multiple forms
* it is either:
  - compile time (static)
  - run time (dynamic aka virtual functions)

## Preprocessing
```cpp
# define ADD(x, y) x + y
// ADD(3, 4) or ADD(3.0, 4.0)
```

## Function/Operator overloading
```cpp
void f(int);
void f(double);
```

## Templates
```cpp
template<typename T>
void f(T); // f(3) or f(3.0)
```

## Virtual functions
```cpp
struct A {
    void f() { cout << "A"; }
}

struct B : A {
    void f() { cout << "B"; }
}

void g(A& a) {a.f();} // accepts both A and B

// void h(B& b) {b.f();} // accepts only B

A a; B b;
g(a); // prints "A"
g(b); // prints "A" it did not print "B"!

```