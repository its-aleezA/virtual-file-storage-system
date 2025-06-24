# Virtual File Storage System

An educational simulation of a file storage system, fully implemented in C++ using data structures and file handling. This project creates a virtual disk environment that models how file systems allocate blocks, store metadata, manage free space, and perform file operations, while also providing a Windows Forms GUI for user interaction.

---

## 📖 Project Overview

This project implements a simplified file system inside a single 10MB binary file (`File_system.bin`) simulating a virtual hard disk. Users can create, view, modify, delete, import, and export text files within this virtual storage system.

The system demonstrates core data structures and algorithms concepts like memory allocation, metadata management, block-level storage, and disk simulation.

---

## 🚀 Key Features

- Custom-built virtual file system with full block management
- Disk file (`File_system.bin`) divided into:
  - Metadata section (1MB)
  - Free block list (1MB)
  - Data section (8MB)
- Supports file creation, viewing, deletion, modification, import, and export
- Free block list managed using dynamic data structures
- Import/export functionality with real Windows file system
- Full graphical interface built using C++/CLI and Windows Forms (source code for interface not included in this version)

---

## 🔧 Technologies Used

- **Language:** C++
- **GUI:** Windows Forms (C++/CLI)
- **Data Structures:** Vectors, Maps, Binary File Handling, Serialization
- **Platform:** Windows

---

## 💻 System Design

The virtual disk is logically divided into:

| Section | Size | Purpose |
|---------|------|---------|
| Metadata | 1MB | Stores file entries (name, starting address, size) |
| Free Block List | 1MB | Tracks available blocks using CSV-style list |
| Data Section | 8MB | Stores actual file contents in 1KB blocks |

The system uses delimiter-based termination and direct addressing to simplify file reading and writing operations.

---

## 🖥 Graphical User Interface (GUI)

A full GUI is integrated using C++/CLI and Windows Forms, allowing users to:

- Create files
- View and modify content
- Delete files
- Import/export files to/from Windows

The GUI uses form-based controls such as buttons, text fields, native file dialogs, and menu strips to simplify interaction.

---

## 📊 Educational Value

This project provides hands-on experience in:

- Simulating real-world file systems
- Block-based memory management
- Metadata handling and serialization
- Disk block allocation and fragmentation
- Integration of data structures into full software systems

---

## 📄 Project Report

A complete report documenting the system design, implementation details, data structures, algorithms, GUI integration, and testing results is available:

👉 [Project Report (PDF)](report/project_report.pdf)

---

## 💻 Source Code

The complete source code is included in this repository:

- [`code/`](code/virtual_file_storage_system.cpp)

---

## 📸 Demonstration (Optional)

- [GUI Screenshot](images/interface.jpg)

- [System Diagram](images/system_diagram.jpg)

- [Class Diagram](images/class_diagram.jpg)
- 
---

## 👥 Contributors

- [Aleeza Rizwan](https://github.com/its-aleezA)
- [Muhammad Ibrahim Abdullah](https://github.com/Ibrahim5570)
- [Muhammad Shaheer Afzal](https://github.com/ShaheerAfzal)
  
---

## 🔖 License

This project is open-source and licensed under the MIT License.  
See the [LICENSE](LICENSE) file for full details.
