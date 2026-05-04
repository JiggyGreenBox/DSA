Yes, there are several videos on using C++ for critical safety systems and the practices employed to ensure code is made very safe. This field often relies on **coding standards** and **specific C++ features** to minimize risk.

Here are a few relevant videos:

### 1. Strategies for Developing Safety-Critical Software

* **Title:** **Safety-First: How To Develop C++ Safety-Critical Software**
    * **Channel:** CppNow
    * **Focus:** A deep dive into understanding how to develop C++ safety-critical software, which often involves adherence to standards like **MISRA C++** and avoiding problematic language features.
    * **Length:** 1 hour 32 minutes
    * **URL:** [Safety-First: How To Develop C++ Safety-Critical Software - Andreas Weis - CppNow 2023](http://www.youtube.com/watch?v=mUFRDsgjBrE)

* **Title:** **Lightning Talk: Strategies for Developing Safety-Critical Software in C++**
    * **Channel:** CppCon
    * **Focus:** A concise talk on the strategies and principles for writing reliable code in life-critical contexts.
    * **Length:** 6 minutes 47 seconds
    * **URL:** [Lightning Talk: Strategies for Developing Safety-Critical Software in C++ - Emily Durie-Johnson](http://www.youtube.com/watch?v=VJ6HrRtrbr8)

### 2. Industry Examples and Advanced Safety

* **Title:** **how NASA writes space-proof code**
    * **Channel:** Low Level
    * **Focus:** While not exclusively C++, this video discusses the rigorous coding standards and practices (like the **JPL Institutional Coding Standard for C**) used for mission-critical systems in space exploration, which heavily influence safety-critical development across all industries.
    * **Length:** 6 minutes 3 seconds
    * **URL:** [how NASA writes space-proof code](http://www.youtube.com/watch?v=GWYhtksrmhE)

* **Title:** **Safe Software for Autonomous Mobility With Modern C++**
    * **Channel:** CppCon
    * **Focus:** Discusses the application of modern C++ features for safety-critical systems in autonomous vehicles, a prime example of where code safety is paramount.
    * **Length:** 30 minutes 31 seconds
    * **URL:** [CppCon 2019: Andreas Pasternak “Safe Software for Autonomous Mobility With Modern C++”](http://www.youtube.com/watch?v=5WbdLUc9Jls)

---

## How Code is Made Very Safe

To make C++ code safe for critical systems (such as medical devices, aviation, or automotive control), developers typically follow a strict process:

1.  **Coding Standards:** Adopting and strictly enforcing industry-specific standards, most notably **MISRA C++** (Motor Industry Software Reliability Association), which prohibits error-prone C++ features (like exceptions, dynamic memory allocation, and certain forms of polymorphism).
2.  **Static Analysis:** Using tools to analyze the source code **without executing it**, to detect potential bugs, memory leaks, concurrency issues, and violations of the coding standard.
3.  **Design Patterns:** Utilizing patterns like **Resource Acquisition Is Initialization (RAII)** to manage resources automatically and prevent leaks.
4.  **Testing and Formal Methods:** Employing extensive unit testing, integration testing, and in the most critical cases, **formal methods** (mathematical techniques) to prove the correctness of algorithms.
5.  **Restricted Features:** Avoiding dynamic memory allocation (`new`/`delete`), recursion, and exceptions, as their behavior at runtime can be unpredictable or resource-intensive in a way that violates strict timing requirements.
http://googleusercontent.com/youtube_content/1