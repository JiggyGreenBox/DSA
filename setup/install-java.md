# Install Java on Ubuntu
## 1. Install Java Development Kit (JDK)
```sh
sudo apt update
sudo apt install openjdk-21-jdk

java -version
javac -version
```

## 2. Install VS Code and the Java Extension Pack
 - download: **Extension Pack for Java by Microsoft**
```sh
# Download the .deb package for Ubuntu/Debian.
sudo dpkg -i <path-to-downloaded-file>.deb
```

## 3. Make a test project
```sh
touch TestSetup.java
```
```java
public class TestSetup {
    public static void main(String[] args) {
        String version = System.getProperty("java.version");
        System.out.println("Java Setup is working!");
        System.out.println("Running on JDK version: " + version);

        // Quick logic test
        int a = 10;
        int b = 20;
        System.out.println("Sum test: " + (a + b));
    }
}
```

Run the script from vscode *(play icon)*.

```sh
# cleanup
rm TestSetup.java
```