# havoc.sh 🐚

A simple Unix-like shell written in C.  
Built for learning, hacking, and extending — `havoc.sh` supports built-in commands, external programs, and a custom prompt.

## ✨ Features

- 🖥️ Custom shell prompt: `havoc.sh>`
- 🧠 Built-in commands:
  - `cd` – change directory
  - `pwd` – print current working directory
  - `exit` – exit the shell
  - `clear` – clear the terminal screen
- ⚙️ External command execution (via `fork()` + `execvp()`)
- 🔄 REPL loop (read-eval-print-loop)
- 🧹 Memory-safe input parsing with `fgets()` and `strtok()`
- 🔒 Basic error handling and feedback

---

## 🚀 Getting Started

### 📦 Prerequisites

- GCC or any C compiler
- Unix-like system (Linux, macOS, WSL, etc.)

### 🔧 Build & Run

```bash
gcc -o havoc havoc.c
./havoc
