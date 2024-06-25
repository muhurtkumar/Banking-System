#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

// Transaction class
class Transaction {
private:
    string type; // "Deposit" or "Withdrawal"
    double amount;
    double balanceAfter;

public:
    Transaction(string type, double amount, double balanceAfter)
        : type(type), amount(amount), balanceAfter(balanceAfter) {}

    string getType() const { return type; }
    double getAmount() const { return amount; }
    double getBalanceAfter() const { return balanceAfter; }
};

// Customer class
class Customer {
private:
    string name;
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    // Default constructor
    Customer() : name(""), accountNumber(0), balance(0.0) {}

    // Parameterized constructor
    Customer(string name, int accountNumber, double initialDeposit)
        : name(name), accountNumber(accountNumber), balance(initialDeposit) {
        transactions.push_back(Transaction("Deposit", initialDeposit, balance));
    }

    // Getters
    string getName() const { return name; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    // Deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back(Transaction("Deposit", amount, balance));
            cout << "Deposited: ₹" << amount << " into account " << accountNumber << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount, balance));
            cout << "Withdrawn: ₹" << amount << " from account " << accountNumber << endl;
        } else {
            cout << "Insufficient balance or invalid amount." << endl;
        }
    }

    // Display transaction history
    void displayTransactionHistory() const {
        cout << "Transaction history for account " << accountNumber << ":" << endl;
        for (const auto& transaction : transactions) {
            cout << transaction.getType() << ": ₹" << transaction.getAmount() 
                 << " (Balance after: ₹" << transaction.getBalanceAfter() << ")" << endl;
        }
    }
};

// Banking System class
class BankingSystem {
private:
    unordered_map<int, Customer> customers;
    int nextAccountNumber;

public:
    BankingSystem() : nextAccountNumber(1000) {}

    // Create a new account
    void createAccount(string name, double initialDeposit) {
        Customer newCustomer(name, nextAccountNumber, initialDeposit);
        customers[nextAccountNumber] = newCustomer;
        cout << "Account created successfully. Account Number: " << nextAccountNumber << endl;
        nextAccountNumber++;
    }

    // Display account information
    void displayAccountInfo(int accountNumber) {
        if (customers.find(accountNumber) != customers.end()) {
            Customer &cust = customers[accountNumber];
            cout << "Account Number: " << cust.getAccountNumber() << endl;
            cout << "Name: " << cust.getName() << endl;
            cout << "Balance: ₹" << cust.getBalance() << endl;
        } else {
            cout << "Account not found." << endl;
        }
    }

    // Display transaction history
    void displayTransactionHistory(int accountNumber) {
        if (customers.find(accountNumber) != customers.end()) {
            customers[accountNumber].displayTransactionHistory();
        } else {
            cout << "Account not found." << endl;
        }
    }

    // Deposit money into an account
    void deposit(int accountNumber, double amount) {
        if (customers.find(accountNumber) != customers.end()) {
            customers[accountNumber].deposit(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    // Withdraw money from an account
    void withdraw(int accountNumber, double amount) {
        if (customers.find(accountNumber) != customers.end()) {
            customers[accountNumber].withdraw(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }
};

// Main function
int main() {
    BankingSystem bank;

    bank.createAccount("John Doe", 500.0);
    bank.createAccount("Jane Smith", 1000.0);

    bank.displayAccountInfo(1000);
    bank.displayAccountInfo(1001);

    bank.deposit(1000, 200.0);
    bank.withdraw(1001, 150.0);

    bank.displayAccountInfo(1000);
    bank.displayAccountInfo(1001);

    bank.displayTransactionHistory(1000);
    bank.displayTransactionHistory(1001);

    return 0;
}
