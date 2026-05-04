# Install Rust on Ubuntu
## 1. Install curl (if you don't have it)
```sh
sudo apt update
sudo apt install curl -y

curl --version
```

## 2. Run the rustup installer
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

## 3. Configure your shell
```sh
source "$HOME/.cargo/env"
```

## 4. Verify the installation
```sh
rustc --version
cargo --version
```

## 5. Make a test project
```sh
cargo new hello-world

cd hello-world

cargo run
# Hello, world!

cd .. && rm -rf ./hello-world
```