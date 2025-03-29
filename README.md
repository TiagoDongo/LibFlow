# LibFlow 

[![License](https://img.shields.io/github/license/TiagoDongo/LibFlow?style=for-the-badge&color=green)](https://github.com/TiagoDongo/LibFlow/blob/main/LICENSE)
[![Alpha](https://img.shields.io/badge/Status-alpha-orange?style=for-the-badge)](https://github.com/TiagoDongo/LibFlow/releases)
![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
[![cJSON](https://img.shields.io/badge/Library-cJSON-green?style=for-the-badge)](https://github.com/DaveGamble/cJSON)

A lightweight library management system for registering, searching, updating, and removing books/users, with JSON data persistence. Built in `C` using `cJSON` for JSON file handling.  

---

> [!NOTE]
> **Test Environment**  
> - Windows 10  
> - cJSON library included in the project

---

## Project Structure  

- **public/**: Main file (`main.c`) and system modules.  
- **src/**: Headers and definitions for structures/functions.  
- **data/**: Directory for generated JSON files.  
- **scripts/**: Python scripts for data generation and analysis.  

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
   - Linux
    ```bash
    make
    ```

    - Windows
    ```bash
    mingw32-make
    ```

4. Run:
   - Linux
    ```bash
    make run
    ```

    - Windows
    ```bash
    mingw32-make run
    ```

5. For help:
   - Linux
    ```bash
    make help
    ```

    - Windows
    ```bash
    mingw32-make help
    ```

## 🤝 Contributing
- 🐛 Report bugs via `Issues`
- 📚 Contribution guidelines [`CONTRIBUTING.md`](CONTRIBUTING.md)