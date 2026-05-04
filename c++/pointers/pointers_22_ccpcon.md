# raw pointers in c++ are dangerous
* they can be null or not
* they can point to a single object or an array of objects
* so ++p and --p and p[n] are not needed on single objects
* but these are valid on an array of objects
* allocate with new and delete
* allocate with new[] and delete[]
* owner vs non-owning
    * owner must free the memory
    * non owner must never free
---

# smart vs raw pointer
* automatic release of resources is the most common
* restrictions - no nullptr
* extra safety checks
---
# where to use raw pointers
* non-owning single object - use raw poiter
* owning pointers use smart pointer
* span type to pointers to arrays ????????

# unique_ptr
* assumes only owner
* automatic destroy memory
* move-only

# unique pointer gotchas
*  be careful with the raw pointers returned by `release()`. be carefull with raw pointer for `reset()`
    ```cpp
    auto a = std::make_unique<T>();
    // ...
    std::unique_ptr<T> b{a.release()};  // very bad code
    // ...
    a.reset(b.release());               // very bad code

    // should be
    auto a = std::make_unique<T>();
    // ...
    std::unique_ptr<T> b{std::move(a)};
    // ...
    a = std::move(b);
    ```

* use `std::move()`
    ```cpp
    T* p = new T();
    std::unique_ptr<T> a{p};
    std::unique_ptr<T> b{p};
    // crash double free

    auto c = std::make_unique<T>();
    std::unique_ptr<T> d{c.get()};
    // crash double free

    // get() function can be dangerous
    ```
* dangling pointers are still possible
    ```cpp
    int* get_raw_pointer() {
        auto c = std::make_unique<int>(); // Memory is allocated. 'c' owns it.
        return c.get();                   // Raw pointer returned.
    } // <--- 'c' goes out of scope here. The unique_ptr deletes the memory it owns.

    auto bad = get_raw_pointer(); // 'bad' now points to deallocated memory.
    ```

gemini
i need to study for a quiz which will involve pointers. the quiz will be intentionally designed to be confusing. can u create some questions with code examples with increasing difficulty to test my pointer knowledge in c++
