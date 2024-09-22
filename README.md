# Banking System Simulation

This project simulates a simple banking system using object-oriented programming (OOP) principles in C++. The system allows users to open a bank account, deposit and withdraw money, check their balance, and close their accounts. The account data is persisted to a file, enabling data retrieval and updates across multiple runs of the program.

## Features

### 1. Open an Account
   - Create a new bank account by providing the first name, last name, and an initial deposit.
   - Each account is assigned a unique account number.
   - Account details are stored persistently in a file (`Bank.data`).
 ![CODE](https://github.com/user-attachments/assets/c3623dcf-e65a-420f-91f3-4185adb99cd3)


### 2. Balance Enquiry
   - Check the balance of an account by providing the account number.
   - Displays the account details and current balance.
![CODE2](https://github.com/user-attachments/assets/028448d7-fe31-457f-82a2-a60f1fb125d1)
### 3. Deposit Money
   - Deposit money into an account by providing the account number and deposit amount.
   - Updates the balance and displays the new balance.

### 4. Withdraw Money
   - Withdraw money from an account by providing the account number and withdrawal amount.
   - Enforces a minimum balance of 500, throwing an `InsufficientFunds` exception if the balance goes below the limit.

### 5. Close an Account
   - Close an account by providing the account number.
   - Deletes the account and removes it from the persistent storage.

### 6. Show All Accounts
   - Displays all active accounts with details including account number, first name, last name, and balance.

### 7. Persistent Storage
   - The system stores account details in a file (`Bank.data`), ensuring that account information is retained between program runs.

## System Requirements

- **Compiler**: Any C++ compiler (such as g++, clang++)
- **C++ Standard**: The code is compatible with C++11 and newer standards.
