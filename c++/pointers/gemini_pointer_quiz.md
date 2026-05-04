1. What is the final value of the variable val after the execution of the following C++ code snippet?
```cpp
int x = 10;
int y = 20;
int *p = &x;
int *q = &y;
*p = *q;
p = q;
*p = 50;
int val = x;

// A.
// 10

// B.
// 20
Initially, x is 10. *p = *q; changes x to the
value of y (20). Then, p = q; makes both p and q point
to y. The final line *p = 50; changes y to 50.
However, val is assigned the value of x, which remains 20

// C.
// 50

// D.
// 20
```

2. What is the final value of the variable val after the execution of the following C++ code snippet?
```cpp
int x = 10;
int y = 20;
int *p = &x;
int *q = &y;
*p = *q;
p = q;
*p = 50;
int val = x;

// A.
// 10

// B.
// 100

// C.
// 50

// D.
// 20

Right answer
The initial dereferenced copy *p = *q sets x (via *p) to 20. However, the subsequent line p = q changes where p points, and *p = 50 changes the value of what q points to.
```

3. Given the following array and pointer setup, what is the output of the line std::cout << *ptr;?
```cpp
int arr[] = {5, 15, 25, 35};
int *ptr = arr;
ptr += 2;
std::cout << *ptr;

// A.
// 35

// B.
// 5

// C.
// 15

// D.
// 25
/*
Pointer arithmetic adds the operand multiplied
by the size of the pointed-to type. ptr += 2 moves
the pointer forward by two integer positions,
pointing to arr[2] (value 25).
*/
```
4. What is the crucial difference between the two expressions in the C++ code below, assuming p is a valid int* pointer?

    * Expression A:  `*p++`
    * Expression B:  `(*p)++`
    ```md
    A.
    Expression A increments the pointer's address and returns the value before increment; Expression B increments the value at the address and returns the value before increment.

    That's right!
    The postfix ++ operator has higher precedence than the dereference *. Thus, A is interpreted as *(p++): the pointer p is incremented, and the original value at the old address is returned. B is correctly grouped as (*p)++: the value at the address is incremented, and the original value is returned.

    B.
    Expression A increments the pointer before dereferencing; Expression B increments the value after dereferencing.

    C.
    Expression A is syntactically invalid; Expression B is the correct way to increment the value a pointer points to.

    D.
    Expression A increments the value and the pointer; Expression B only increments the value.
    ```

5. Examine the following C++ code. What is the value of final_result?
    ```cpp
    int arr[3] = {1, 2, 3};
    int *p1 = arr + 1;
    int *p2 = &arr[2];
    long final_result = (p2 - p1);

    A.
    1

    That's right!
    The subtraction of two pointers (p2 - p1) yields the number of elements between them, which is 1 element (arr[2] minus arr[1]). The result's type is a signed integer type, often ptrdiff_t or long in this context.

    B.
    -1

    C.
    Error: Cannot subtract two pointers.

    D.
    4

    ```

    ```cpp
    #include <iostream>

    int main() {
        
        int a = 5;
        int b = 3;
        int *p1 = &a;
        int *p2 = &b;
        int result = p1-p2;
        std::cout << result << std::endl; // 1?? wrong
        
        int arr[5] = {100,1,8,7,5};
        int *a1 = arr;
        int *a2 = arr+4;
        std::cout << a2-a1 << std::endl; // 4 correct (number of elements between them)

        return 0;
    }
    is only valid if p1 and p2 point into the same array (or one past the end).

    Here, a and b are two completely separate variables, not part of the same array.
    ➡️ So the subtraction p1 - p2 is undefined behavior in C++.

    Here both a1 and a2 point into the same array, so subtraction is well-defined:

    a2 - a1 = number of elements between them = 4.

    That’s why this works correctly and predictably.
    ```

6. What is the output of the following C++ program snippet?
    ```cpp
    void process(int* arr_ptr) {
    arr_ptr[1] = 99;
    }

    int main() {
    int data[3] = {10, 20, 30};
    process(data);
    std::cout << data[1];
    }

    A.
    99

    That's right!     When data is passed to
    process, it 'decays' to a pointer (int*) to its first
    element. The function then modifies the second element
    (arr_ptr[1]) of the original array, changing data[1] to 99.


    B.
    30

    C.
    10

    D.
    20
    ```

7. Consider the declaration const int *ptr;. Which of the following statements is TRUE about this pointer?
    ```md
    A.
    The value that ptr points to can be modified, but the pointer itself cannot be reassigned.

    B.
    The pointer ptr cannot be changed to point to a different memory location.

    C.
    Both the pointer and the value it points to are constant and cannot be changed.

    D.
    The pointer ptr can be changed to point to a different memory location, but the value it points to cannot be modified through ptr.

    That's right!
    This is a 'pointer to a constant integer'. The const applies to the data type (int), so the data is constant, but the pointer variable is not constant.

    # STUDY THIS CAREFULLY
    # SPIRAL RULE FOR POINTERS
    https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const
    ```

8. What is the value of **pp after the execution of the following code snippet?
    ```cpp
    int a = 7;
    int *p = &a;
    int **pp = &p;
    *p = 14;

    A.
    The memory address of a.

    B.
    14

    That's right!     The double pointer pp points
    to p, which points to a. **pp is equivalent to *p,
    which is equivalent to a. Since *p = 14 modifies a,
    **pp will also evaluate to 14.


    C.
    The memory address of p.

    D.
    7
    ```

9. Which of the following declarations correctly declares an array of 5 pointers to a constant integer?
    ```cpp
    A.
    int const *arr[5];

    Right answer
    This is a correct declaration. It is an array of 5 elements (arr[5]), where each element is a pointer (*) to a constant integer (int const).

    B.
    const int arr*[5];

    Not quite
    This is syntactically invalid. The asterisk should be placed next to the variable name (arr).

    C.
    int *arr[5] const;

    D.
    int *const arr[5];
    ```

10. Consider the following code snippet. What is the value of y after execution?
    ```cpp
    int x = 100;
    int &r = x;
    int *p = &r;
    int y = ++(*p);
    ```
    ```
    A.
    A random or garbage value, as &r is not a valid operation.

    B.
    102

    C.
    101

    That's right! The reference r is an alias for x.
    The pointer p points to x. *p is x. The prefix
    increment ++(*p) changes x to 101, and the result of the
    prefix increment expression (101) is assigned to y. 

    D.
    100
    ```

11. The following code contains a common and dangerous programming practice. What is the final output to the console?

    ```cpp
    int *dang_ptr = new int(1);
    int **p_to_ptr = &dang_ptr;

    delete dang_ptr;

    // Line of Confusion
    *p_to_ptr = new int(25);

    std::cout << *dang_ptr;
    ```
    ```
    A.
    25

    Right answer     
    The delete dang_ptr call
    deallocates the memory first pointed to by dang_ptr. The
    line *p_to_ptr = new int(25) then assigns the address
    of a new block of memory holding 25 to dang_ptr
    (since *p_to_ptr is an alias for dang_ptr). The final
    dereference *dang_ptr outputs the value 25 from the newly
    allocated memory.


    B.
    The memory address of the integer with value 25.

    C.
    A runtime error or undefined behavior.

    Not quite    
    While the code is dangerous (the
    initial memory is deleted, creating a dangling pointer
    until the reassignment), the subsequent line *p_to_ptr
    = new int(25); reassigns the dang_ptr variable to
    point to valid memory, preventing the immediate
    undefined behavior. The code executes and prints the new
    value.


    D.
    1
    ```

12. What is the final value of the variable sum after this code executes? Pay close attention to the post-decrement operator.
    ```cpp
    int arr[] = {10, 20, 30};
    int *p = arr + 2;
    int sum = 0;
    sum = *p-- + *p;
    ```
    ```
    A.
    60

    B.
    50

    That's right!
    The first term *p-- evaluates to 30 (the value
    at arr[2]) and then decrements p to point to
    arr[1]. The second term *p then evaluates to 20. Thus,
    30+20=50. 


    C.
    30

    D.
    40
    ```