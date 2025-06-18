# Bank Management System

## Description
This C++ project implements a console-based Bank Management System. It allows for managing bank clients and users, performing financial transactions such as deposits and withdrawals, and maintaining user-level access control.

## Features
- **Client Management:** Add, view, update, delete, and find bank clients.
- **User Management:** Add, view, update, delete, and find system users with different access levels.
- **Transactions:** Perform deposit and withdrawal operations, and view total balances.
- **Access Control:** Role-based access control for users, allowing different permissions for various functionalities.
- **Data Persistence:** Client and user data are stored in text files (`clients.txt` and `users.txt`).
- **Interactive Console Interface:** User-friendly menus for navigation and operations.

## Getting Started

### Prerequisites
- C++ Compiler (e.g., g++)
- A text editor or IDE (e.g., VS Code, Code::Blocks)

### Installation
1. Clone the repository or download the `BankSystem.cpp` file.
2. Compile the `BankSystem.cpp` file using a C++ compiler:
   ```bash
   g++ BankSystem.cpp -o BankSystem
   ```

### Usage
1. Run the compiled executable:
   ```bash
   ./BankSystem
   ```
2. The system will prompt for a username and password. Default admin user is 'Admin' with password 'Admin'.
3. Follow the on-screen menu to navigate through the system functionalities.

## File Structure
- `BankSystem.cpp`: The main source code file containing all the logic for the bank management system.
- `clients.txt` (created automatically): Stores client data (account number, PIN, name, phone, balance).
- `users.txt` (created automatically): Stores user data (username, password, access permissions).
