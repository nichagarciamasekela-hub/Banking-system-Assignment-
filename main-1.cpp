#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Number of registered bank users
const int SIZE = 3;

// Function declarations
int readInteger(string message);
double readPositiveAmount();

int findUser(const int accountNumbers[], int size, int accountNumber);

bool loginUser(const int accountNumbers[],
               const int pins[],
               int size,
               int &loggedInIndex);

int displayMenu();

void deposit(double balances[], int userIndex);

void withdraw(double balances[], int userIndex);

void sendCash(const int accountNumbers[],
              double balances[],
              int size,
              int senderIndex);

void checkBalance(const double balances[], int userIndex);


// MAIN PROGRAM
int main()
{
    // User details stored in parallel arrays
    string names[SIZE] = {"Sarah", "John", "Michael"};

    int accountNumbers[SIZE] = {1001, 1002, 1003};

    int pins[SIZE] = {1234, 5678, 4321};

    double balances[SIZE] = {2000.00, 1500.00, 3000.00};

    int loggedInIndex = -1;
    int choice;

    cout << "=================================\n";
    cout << "          WELCOME TO GCC BANK\n";
    cout << "=================================\n";

    // Login verification
    if (!loginUser(accountNumbers, pins, SIZE, loggedInIndex))
    {
        cout << "\nToo many failed attempts.\n";
        cout << "Access denied. Goodbye!\n";

        return 0;
    }

    cout << "\nWelcome, " << names[loggedInIndex] << "!\n";

    // Banking menu loop
    do
    {
        choice = displayMenu();

        switch (choice)
        {
            case 1:
                deposit(balances, loggedInIndex);
                break;

            case 2:
                withdraw(balances, loggedInIndex);
                break;

            case 3:
                sendCash(accountNumbers, balances,
                         SIZE, loggedInIndex);
                break;

            case 4:
                checkBalance(balances, loggedInIndex);
                break;

            case 5:
                cout << "\nThank you for banking with GCC BANK.\n";
                cout << "Goodbye, " << names[loggedInIndex] << "!\n";
                break;

            default:
                cout << "\nInvalid menu choice!\n";
                cout << "Please select a number between 1 and 5.\n";
        }

    } while (choice != 5);

    return 0;
}


// FUNCTION 1: Read and validate integer input
int readInteger(string message)
{
    int number;

    while (true)
    {
        cout << message;
        cin >> number;

        if (cin.fail())
        {
            cout << "Invalid input! Please enter a number.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
    }
}


// FUNCTION 2: Read and validate deposit/withdrawal amount
double readPositiveAmount()
{
    double amount;

    while (true)
    {
        cout << "Enter amount (R): ";
        cin >> amount;

        if (cin.fail())
        {
            cout << "Invalid input! Please enter a valid amount.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (amount <= 0)
            {
                cout << "Amount must be greater than R0.\n";
            }
            else
            {
                return amount;
            }
        }
    }
}


// FUNCTION 3: Find a user's account
int findUser(const int accountNumbers[], int size,
             int accountNumber)
{
    for (int i = 0; i < size; i++)
    {
        if (accountNumbers[i] == accountNumber)
        {
            return i;
        }
    }

    return -1;
}


// FUNCTION 4: Login and PIN verification
bool loginUser(const int accountNumbers[],
               const int pins[],
               int size,
               int &loggedInIndex)
{
    int accountNumber;
    int enteredPin;

    for (int attempt = 1; attempt <= 3; attempt++)
    {
        cout << "\n========== CUSTOMER LOGIN ==========\n";

        accountNumber = readInteger("Enter account number: ");

        loggedInIndex = findUser(accountNumbers, size,
                                 accountNumber);

        if (loggedInIndex == -1)
        {
            cout << "Account not found!\n";
        }
        else
        {
            enteredPin = readInteger("Enter your PIN: ");

            if (enteredPin == pins[loggedInIndex])
            {
                cout << "\nLogin successful!\n";
                return true;
            }
            else
            {
                cout << "Incorrect PIN!\n";
            }
        }

        cout << "Attempts remaining: " << 3 - attempt << "\n";
    }

    return false;
}


// FUNCTION 5: Display banking menu
int displayMenu()
{
    cout << "\n=================================\n";
    cout << "            GCC BANK\n";
    cout << "=================================\n";

    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";

    cout << "=================================\n";

    return readInteger("Enter your choice: ");
}


// FUNCTION 6: Deposit money
void deposit(double balances[], int userIndex)
{
    double amount;

    cout << "\n========== DEPOSIT ==========\n";

    amount = readPositiveAmount();

    balances[userIndex] += amount;

    cout << fixed << setprecision(2);

    cout << "\nDeposit successful!\n";
    cout << "Amount deposited: R" << amount << "\n";
    cout << "New balance: R" << balances[userIndex] << "\n";
}


// FUNCTION 7: Withdraw money
void withdraw(double balances[], int userIndex)
{
    double amount;

    cout << "\n========== WITHDRAW ==========\n";

    amount = readPositiveAmount();

    if (amount > balances[userIndex])
    {
        cout << "\nInsufficient balance!\n";
        cout << "Your available balance is R"
             << fixed << setprecision(2)
             << balances[userIndex] << "\n";
    }
    else
    {
        balances[userIndex] -= amount;

        cout << "\nWithdrawal successful!\n";
        cout << "Amount withdrawn: R"
             << fixed << setprecision(2) << amount << "\n";

        cout << "Remaining balance: R"
             << balances[userIndex] << "\n";
    }
}


// FUNCTION 8: Send cash to another account
void sendCash(const int accountNumbers[],
              double balances[],
              int size,
              int senderIndex)
{
    int recipientAccount;
    int recipientIndex;
    double amount;

    cout << "\n========== SEND CASH ==========\n";

    recipientAccount = readInteger(
        "Enter recipient account number: ");

    // Check whether recipient account exists
    recipientIndex = findUser(accountNumbers, size,
                              recipientAccount);

    if (recipientIndex == -1)
    {
        cout << "\nError: Recipient account does not exist!\n";
        return;
    }

    // Prevent sending money to the same account
    if (recipientIndex == senderIndex)
    {
        cout << "\nError: You cannot send cash to yourself!\n";
        return;
    }

    amount = readPositiveAmount();

    // Check available balance
    if (amount > balances[senderIndex])
    {
        cout << "\nTransaction failed!\n";
        cout << "Insufficient balance.\n";
        return;
    }

    // Update both account balances
    balances[senderIndex] -= amount;
    balances[recipientIndex] += amount;

    cout << fixed << setprecision(2);

    cout << "\nCash sent successfully!\n";
    cout << "Amount sent: R" << amount << "\n";

    cout << "Your new balance: R"
         << balances[senderIndex] << "\n";

    cout << "Recipient new balance: R"
         << balances[recipientIndex] << "\n";
}


// FUNCTION 9: Check account balance
void checkBalance(const double balances[], int userIndex)
{
    cout << "\n========== CHECK BALANCE ==========\n";

    cout << fixed << setprecision(2);

    cout << "Your current account balance is: R"
         << balances[userIndex] << "\n";
}
