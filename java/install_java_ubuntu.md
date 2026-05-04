Running Java on Ubuntu is straightforward. Since you have a C++ background, you can think of the **JDK** (Java Development Kit) as your toolchain—it contains the compiler (`javac`) and the runtime (`java`), similar to how `build-essential` provides `g++`.

### 1. The Setup (Installation)

The most common way to install Java on Ubuntu is via the `apt` package manager. You have two main choices:

* **JRE (Java Runtime Environment):** Only for *running* compiled programs.
* **JDK (Java Development Kit):** For *developing* and running programs. **You want this.**

Open your terminal and run:

```bash
# Update your package list
sudo apt update

# Install the default Java Development Kit (OpenJDK)
sudo apt install default-jdk

```

To verify the installation:

```bash
java -version
javac -version

```

---

### 2. How to Run a Program (The Workflow)

In C++, you usually compile to a machine-code binary. In Java, you compile to **Bytecode** (`.class` files), which the Java Virtual Machine (JVM) then executes.

#### Step A: Create the file

Create a file named `Hello.java`. **Note:** In Java, the filename must exactly match the public class name.

```java
public class Hello {
    public static void main(String[] args) {
        System.out.println("Hello from Ubuntu!");
    }
}

```

#### Step B: Compile (Like `g++`)

Use `javac` to compile the source code into bytecode.

```bash
javac Hello.java

```

This generates a file called `Hello.class`.

#### Step C: Run (The Virtual Machine)

Use the `java` command to run the program. **Do not** include the `.class` extension.

```bash
java Hello

```

---

### 3. Setting Environment Variables (Optional but Recommended)

Many Java tools (like Maven or Gradle) look for the `JAVA_HOME` variable. To set it:

1. Find where Java is installed: `readlink -f $(which java)` (usually `/usr/lib/jvm/java-XX-openjdk-amd64/`).
2. Open your profile: `nano ~/.bashrc`.
3. Add this line at the bottom:
`export JAVA_HOME="/usr/lib/jvm/default-java"`
4. Apply changes: `source ~/.bashrc`.

---

### Summary Table for C++ Devs

| Action | C++ | Java |
| --- | --- | --- |
| **Compile** | `g++ main.cpp -o main` | `javac Main.java` |
| **Run** | `./main` | `java Main` |
| **Output File** | Binary (`main`) | Bytecode (`Main.class`) |
| **Tooling** | `make`, `cmake` | `Maven`, `Gradle` |

Would you like me to help you set up an IDE like IntelliJ IDEA or VS Code on Ubuntu to make the development process smoother?

[Running a Java program in the Linux terminal](https://www.youtube.com/watch?v=ajKhjoWQTYI)
This video provides a visual walkthrough of the compilation and execution steps mentioned above specifically for Ubuntu users.