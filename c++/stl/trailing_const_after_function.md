## C++ Class Methods and the `this` Pointer

C++ class methods have an **implicit `this` parameter** that is conceptually passed before all the explicit parameters.

Consider a class method declared like this:

```cpp
class C {
  void f(int x);
};
```

You can imagine the underlying function signature essentially looks like this:

```cpp
  void f(C* this, int x);
```

The `this` pointer is a pointer to the object on which the method was invoked.

-----

## The Effect of the Trailing `const`

If you declare the method with a **trailing `const`** keyword:

```cpp
  void f(int x) const;
```

It is as if the `this` parameter were declared as a pointer to a constant object:

```cpp
  void f(const C* this, int x);
```

### Implications of `const`

  * **Invoking on `const` Objects**: The trailing `const` allows you to invoke the method on **`const` objects** of the class type. This is because a non-`const` method would require a `C* this` (a non-`const` pointer to a non-`const` object), which cannot be implicitly converted from a `const C*` (a non-`const` pointer to a `const` object).
  * **Preventing Modification**: The method **cannot modify the object** on which it was invoked (at least, not via the normal members) because the `this` pointer points to a constant object (`const C*`). This enforces **const correctness**, ensuring the method's call doesn't change the object's observable state.

```cpp
struct X
{
    void foo() const // <== The implicit "this" pointer is const-qualified!
    {
        _x = 42; // ERROR! The "this" pointer is implicitly const
        _y = 42; // OK (_y is mutable)
    }

    void bar(X& obj) const // <== The implicit "this" pointer is const-qualified!
    {
        obj._x = 42; // OK! obj is a reference to non-const
        _x = 42; // ERROR! The "this" pointer is implicitly const
    }

    void bar(X const& obj) // <== The implicit "this" pointer is NOT const-qualified!
    {
        obj._x = 42; // ERROR! obj is a reference to const
        obj._y = 42; // OK! obj is a reference to const, but _y is mutable
        _x = 42; // OK! The "this" pointer is implicitly non-const
    }

    int _x;
    mutable int _y;
};
```