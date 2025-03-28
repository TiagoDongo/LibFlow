# Library Management  

A lightweight library management system for registering, searching, updating, and removing books/users, with JSON data persistence. Built in `C` using `cJSON` for JSON file handling.  

## Project Structure  

- **public/**: Main file (`main.c`) and system modules.  
- **src/**: Headers and definitions for structures/functions.  
- **data/**: Directory for generated JSON files.  
- **scripts/**: Python scripts for data generation and analysis.  

## ⚙ Prerequisites  

- **Windows**:  
  - Install [MinGW](https://sourceforge.net/projects/mingw/).  
  - Add `gcc` to system PATH.  
  - *Optional*: Duplicate `mingw32_make.exe` and rename to `make`.  

- **Linux**:  
  ```bash  
  sudo apt update && sudo apt install build-essential
  ```

- **Python scripts**:
  ```bash
  pip install faker 
  ```

## 🚀Installation

1. Clone the repo:
   ```bash
   git clone https://github.com/TiagoDongo/Library-Management.git
   ```

2. Navigate to the project:
    ```bash
   cd Library-Management
   ```

3. Compile:
   - Linux
    ```bash
    make
    ```

    - Windows
    ```bash
    mingw32_make
    ```

4. Run:
   - Linux
    ```bash
    make run
    ```

    - Windows
    ```bash
    mingw32_make run
    ```

5. For help:
   - Linux
    ```bash
    make help
    ```

    - Windows
    ```bash
    mingw32_make help
    ```
