#include <iostream>
#include <Windows.h>
#include <stdexcept>


using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNumber, double initialBalance) : accountNumber(accNumber), balance(initialBalance), interestRate(0.0) {}

    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма депозита должна быть положительной.");
        }
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма для вывода должна быть положительной.");
        }
        if (amount > balance) {
            throw invalid_argument("Недостаточно средств.");
        }
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }

    double getInterest() const {
        return balance * interestRate * (1.0 / 12);
    }

    void setInterestRate(double rate) {
        if (rate < 0) {
            throw invalid_argument("Процентная ставка должна быть неотрицательной.");
        }
        interestRate = rate;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount) {
        try {
            from.withdraw(amount);
            to.deposit(amount);
            return true;
        }
        catch (const std::invalid_argument& e) {
            cerr << "Не удалось выполнить передачу: " << e.what() << endl;
            return false;
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    setlocale(0, "Russian");
    BankAccount acc1(12345, 1000.0);
    BankAccount acc2(67890, 500.0);

    cout << "Первоначальные остатки:" << endl;
    cout << "Счет " << acc1.getAccountNumber() << ": " << acc1.getBalance() << endl;
    cout << "Счёт " << acc2.getAccountNumber() << ": " << acc2.getBalance() << endl;

    double transferAmount = 300.0;
    if (transfer(acc1, acc2, transferAmount)) {
        cout << "Передача прошла успешно!" << endl;
    }

    cout << "Окончательный баланс:" << endl;
    cout << "Счет " << acc1.getAccountNumber() << ": " << acc1.getBalance() << endl;
    cout << "Счёт " << acc2.getAccountNumber() << ": " << acc2.getBalance() << endl;

    return 0;
}
