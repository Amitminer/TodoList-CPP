---

# Todo-List

This project is my learning exercise in developing a ToDo List cli application.

## Installation

### Linux

1. **Install Python and Conan**:
   ```bash
   # Install Python (if not already installed)
   sudo apt-get update
   sudo apt-get install python3

   # Install Conan using pip
   python3 -m pip install --upgrade pip
   pip install conan
   conan profile detect
   ```

2. **Make build.sh executable**:
   ```bash
   chmod +x build.sh
   ```

### Windows

1. **Install Python and Conan**:
   - Install Python from [python.org](https://www.python.org/downloads/)
   - Open Command Prompt or PowerShell and install Conan:
     ```bash
     python -m pip install --upgrade pip
     pip install conan
     conan profile detect
     ```

2. **Run build.bat**:
   - Open Command Prompt or PowerShell and run:
     ```bash
     cd path\to\project
     build.bat
     ```

## Usage

### Linux

- After building with `build.sh`, run the executable:
  ```bash
  ./todolist
  ```

### Windows

- After running `build.bat`, execute the built executable:
  ```bash
  todolist.exe
  ```

---
