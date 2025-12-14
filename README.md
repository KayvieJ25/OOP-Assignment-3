# OOP-Assignment-3
Assignment 3 – Bank Accounts with Transaction Logging

This repository contains our solution for Assignment 3 in our Introduction to Object-Oriented Programming course.

In this assignment, we extended the bank system from Assignment 2 by adding the ability to record and report all transactions made on an account. We introduced a new Transaction class to store information about each transaction, including the transaction amount and type (such as deposits, withdrawals, interest, and fees).

The Account class was modified to include a transaction log using a vector of Transaction objects. Each time a deposit, withdrawal, interest calculation, or fee occurs, a corresponding transaction is added to the log. A report() function was also added to the Account class to format and display all recorded transactions to the user.

In the main class, we test this new functionality by performing several transactions on both a savings account and a chequing account, displaying the transaction history, and saving the transaction report to a text file (transactions.txt).We used  try/catch statements to safely handle invalid transactions and file-handling errors.

Group Members

Kayvian Johnson – ID: 2401010516

Tashecca Mullings – ID: 2401010139

Kyle Whitbly – ID: 2401010579

Files in this Project

Assignment3.cpp
This is the main C++ source file containing all class definitions and the main() test program.

transactions.txt
This file is automatically created by the program and contains the saved transaction report.

Classes Used in This Project
Account

This is the main (base) class.
It stores the account balance and a transaction log, and provides the common functions credit, debit, getBalance, and report to manage and display transactions.

Transaction

This class represents a single transaction made on an account.
It stores the transaction amount and type and includes a report() function that formats the transaction information as a readable string.

SavingsAccount

This class inherits from Account.
It adds an interestRate and a function to calculate and apply interest to the account balance, while also logging the interest as a transaction.

ChequingAccount

This class also inherits from Account.
It adds a transactionFee and overrides the debit() function so that a fee is charged only when a withdrawal is successful, with the fee also being logged as a transaction.
