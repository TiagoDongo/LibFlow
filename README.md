# LibFlow

![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
[![cJSON](https://img.shields.io/badge/Library-cJSON-green?style=for-the-badge)](https://github.com/DaveGamble/cJSON)

A lightweight library management system for registering, searching, updating, and removing books, with JSON data persistence. Built in `C` using `cJSON` for JSON file handling.

---

> [!NOTE]
> **Test Environment**
> - Windows 10
> - cJSON library included in the project

---

## Project Structure

- **src/**: Main file (`main.c`) and system modules
- **libs/**: Headers and definitions for structures/functions
- **data/**: Directory for generated JSON files
- **scripts//**: Python scripts for data generation

## ⚙ Prerequisites

- **Windows**:  
  - Install [MinGW](https://sourceforge.net/projects/mingw/).  
  - Add `gcc` to system PATH.  
  - *Optional*: Duplicate `mingw32-make.exe` and rename to `make`.  

- **Linux**:  
  ```bash  
  sudo apt update && sudo apt install build-essential
  ```
- **Python scripts**:
  - Install python 
  ```bash
  pip install faker 
  ```
## 🚀Installation & Usage

1. Clone the repo:
   ```bash
   git clone https://github.com/TiagoDongo/LibFlow.git
   ```

2. Navigate to the project:
    ```bash
   cd LibFlow 
   ```

3. Compile:
    ```bash
    # linux:
        make

    # windows:
        mingw32-make        
    ```

4. Run:
    ```bash
    # linux:
        make run

    # windows:
        mingw32-make run        
    ```

5. For help:
    ```bash
    # linux:
        make help

    # windows:
        mingw32-make help        
    ```

## 🤝 Contributing
- 🐛 Report bugs via `Issues`
- 📚 Contribution guidelines [`CONTRIBUTING.md`](CONTRIBUTING.md)


feat: implement complete book management and JSON persistence

- Adds functions to add, edit, remove, and list books
- Implements book search by ID
- Adds data persistence in JSON files using cJSON
- Allows saving, loading, and deleting book lists in JSON format
- Improves error messages and user feedback
- Refactors project structure to support multiple book list files