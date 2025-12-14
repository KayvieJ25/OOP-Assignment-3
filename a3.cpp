#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


class Transaction {
private:
    double amount;   // How much money was involved
    string type;     // Type of transaction (Deposit, Withdrawal, Fee, Interest)

public:
    // Constructor sets the amount and type
    Transaction(double amt, string kind) {
        amount = amt;
        type = kind;
    }

    // Returns a formatted string describing the transaction
    string report() const {
        ostringstream out;
        out << fixed << setprecision(2);
        out << type << " : $" << amount;
        return out.str();
    }
};


class Account {
protected:
    double balance;
    vector<Transaction> log;   // Stores all transactions

public:
    Account(double initialBalance) {
        if (initialBalance >= 0.0) {
            balance = initialBalance;
        } else {
            balance = 0.0;
            cout << "Invalid starting balance. Set to $0.00" << endl;
        }
    }

    // Adds money to the account
    virtual bool credit(double amount) {
        try {
            if (amount <= 0)
                throw invalid_argument("Deposit must be positive.");

            balance += amount;
            log.push_back(Transaction(amount, "Deposit"));
            return true;
        }
        catch (exception& e) {
            cout << "Credit Error: " << e.what() << endl;
            return false;
        }
    }

    // Removes money from the account
    virtual bool debit(double amount) {
        try {
            if (amount <= 0)
                throw invalid_argument("Withdrawal must be positive.");

            if (amount > balance)
                throw runtime_error("Not enough money in the account.");

            balance -= amount;
            log.push_back(Transaction(amount, "Withdrawal"));
            return true;
        }
        catch (exception& e) {
            cout << "Debit Error: " << e.what() << endl;
            return false;
        }
    }

    double getBalance() const {
        return balance;
    }

    // Returns a list of transaction strings
    vector<string> report() const {
        vector<string> output;
        for (const Transaction& t : log) {
            output.push_back(t.report());
        }
        return output;
    }
};


class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(double initialBalance, double rate)
        : Account(initialBalance) {
        interestRate = rate;
    }

    // Calculates and adds interest
    void addInterest() {
        double interest = balance * (interestRate / 100.0);
        balance += interest;
        log.push_back(Transaction(interest, "Interest"));
    }
};


class ChequingAccount : public Account {
private:
    double fee;

public:
    ChequingAccount(double initialBalance, double feeAmount)
        : Account(initialBalance) {
        fee = feeAmount;
    }

    // Withdraws money and charges a fee
    bool debit(double amount) override {
        bool success = Account::debit(amount);

        if (success) {
            if (fee <= balance) {
                balance -= fee;
                log.push_back(Transaction(fee, "Transaction Fee"));
            } else {
                balance = 0.0;
            }
        }
        return success;
    }
};


int main() {
    cout << fixed << setprecision(2);

    // Create accounts
    SavingsAccount savings(5000.0, 4.0);
    ChequingAccount chequing(2000.0, 50.0);

    cout << "\n--- Testing Accounts ---\n";

    // Perform transactions
    savings.addInterest();
    savings.credit(300.0);
    savings.debit(200.0);

    chequing.debit(500.0);
    chequing.debit(10000.0); // This should fail safely

    // Display transaction report
    cout << "\nSavings Account Transactions:\n";
    vector<string> report = savings.report();
    for (string line : report) {
        cout << line << endl;
    }

    // Save report to file
    try {
        ofstream file("C:\\transactions.txt");

        if (!file)
            throw runtime_error("Could not open file.");

        file << "Savings Account Transactions\n";
        for (string line : report) {
            file << line << endl;
        }

        file.close();
        cout << "\nTransactions saved to C:\\transactions.txt\n";
    }
    catch (exception& e) {
        cout << "File Error: " << e.what() << endl;
    }

    return 0;
}
