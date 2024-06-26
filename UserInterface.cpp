#include <iostream>
#include <stdexcept>
#include <limits>
#include <exception>
#include "Database.h"

// Initialize the static member with the debug logMsg file name
const string Logger::msDebugFileName = "debugLog.txt";

using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database &db);
void doFire(Database &db);
void doPromote(Database &db);
void doDemote(Database &db);
void doDelete(Database &db);
void doEdit(Database &db);
void displayManagerPanel(Database &employeeDB);
bool verifyManager();
string selectInputFileName(const string &oldName);
string selectOutputFileName(const string &oldName);

//*****************Login Information for Manager*******************
// login id --> mg1001
// password --. pw1001
//*****************Login Information for Employee*******************
// default login id for employe is staring with 'em' followed by employee number em<employeeNumber>
// default password for employee isstaring with 'pw' followeed by employee number pw<employeeNumber>
// for example, if employee number is 1000
// login id --> em1000
// password --> pw1000

int main()
{
    logMsg("started");
    Database employeeDB;
    bool done = false;
    while (!done)
    {
        bool isVerified = {false};
        cout << endl;
        cout << "Login" << endl;
        cout << "-----------------" << endl;
        cout << "1) Manager" << endl;
        cout << "2) Employee" << endl;
        cout << "0) Exit" << endl;
        cout << "\n---> ";
        int selection;
        if (cin >> selection)
        {
            ;
        }
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            selection = 500;
        }
        switch (selection)
        {
        case 0:
            logMsg("case 0");
            done = true;
            break;
        case 1:
            logMsg("case 1");
            isVerified = verifyManager();
            if (isVerified)
            {
                displayManagerPanel(employeeDB);
            }
            break;
        case 2:
            logMsg("case 2");
            employeeDB.verifyEmployee();
            break;
        default:
            logMsg("default case - unknown command");
            cerr << "Unknown command." << endl;
            break;
        }
    }

    return 0;
}

bool verifyManager()
{
    // Variables to store user input
    string loginId{};
    string password{""};

    // Prompt user for manager login credentials
    cout << endl;
    cout << "Manager" << endl;
    cout << "-----------------" << endl;
    cout << "Enter login id --> ";
    cin >> loginId;
    cout << "Enter password --> ";
    cin >> password;

    // Check if the entered login id is for the manager
    if (loginId == "mg1001")
    {
        // Check if the entered password is correct for the manager
        if (password == "pw1001")
        {
            cout << "Successfully verified!" << endl;
            return true; // Authentication successful
        }
        else
        {
            cout << "Password is incorrect!" << endl;
            return false;
        }
    }
    else
    {
        cout << "Cannot find your login id!" << endl;
        return false;
    }
}

void displayManagerPanel(Database &employeeDB)
{
    string dbFileName{""};
    bool done = false;
    while (!done)
    {
        int selection = displayMenu();
        switch (selection)
        {
        case 0:
            logMsg("case 0");
            done = true;
            break;
        case 1:
            logMsg("case 1");
            doHire(employeeDB);
            break;
        case 2:
            logMsg("case 2");
            doFire(employeeDB);
            break;
        case 3:
            logMsg("case 3");
            doPromote(employeeDB);
            break;
        case 4:
            logMsg("case 4");
            employeeDB.displayAll();
            break;
        case 5:
            logMsg("case 5");
            employeeDB.displayCurrent();
            break;
        case 6:
            logMsg("case 6");
            employeeDB.displayFormer();
            break;
        case 7:
            logMsg("case 7");
            employeeDB = generateNewDatabase();
            break;
        case 8:
            logMsg("case 8");
            dbFileName = selectOutputFileName(dbFileName);
            employeeDB.saveToFile(dbFileName);
            break;
        case 9:
            logMsg("case 9");
            dbFileName = selectInputFileName(dbFileName);
            employeeDB = loadFromFile(dbFileName);
            break;
        case 10:
            logMsg("case 10");
            doEdit(employeeDB);
            break;
        case 11:
            logMsg("case 11");
            employeeDB.searchMenu();
            break;
        case 12:
            logMsg("case 12");
            doDelete(employeeDB);
            break;
        default:
            logMsg("default case - unknown command");
            cerr << "Unknown command." << endl;
            break;
        }
    }
}

int displayMenu()
{
    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Generate New Database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database from file" << endl;
    cout << "10) Edit Employee" << endl;
    cout << "11) Search Employee" << endl;
    cout << "12) Delete Employee" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    if (cin >> selection)
    {
        return selection;
    }
    else
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 500;
    }
}

void doHire(Database &db)
{
    logMsg("started");
    string firstName;
    string middleName;
    string lastName;
    string address;

    cout << "First name? ";
    cin >> firstName;
    cout << "Middle name? ";
    cin >> middleName;
    cout << "Last name? ";
    cin >> lastName;
    cout << "Address? ";
    cin.ignore();          // Ignore any previous newline character in the buffer
    getline(cin, address); // Use getline to read the entire line, including spaces, for the address

    // db.addEmployee(firstName, lastName);
    db.addEmployee(firstName, middleName, lastName, address);
    logMsg("ended");
}

void doFire(Database &db)
{
    logMsg("started");
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try
    {
        Employee &emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    }
    catch (const std::logic_error &exception)
    {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
    logMsg("ended");
}

void doPromote(Database &db)
{
    logMsg("started");
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try
    {

        Employee &emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    }
    catch (const std::logic_error &exception)
    {
        cout << "Unable to promote employee: " << exception.what() << endl;
    }
    logMsg("ended");
}

void doDelete(Database &db)
{
    logMsg("started");
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;

    db.deleteEmployee(employeeNumber);
    logMsg("ended");
}

void doEdit(Database &db)
{
    int employeeNumber{};
    cout << "Employee Number? ";
    cin >> employeeNumber;
    try
    {
        Employee &emp = db.getEmployee(employeeNumber);
        bool done{false};
        while (!done)
        {
            cout << endl;
            emp.display();
            int option;
            string userInput;
            cout << "1) Edit first name\n";
            cout << "2) Edit middle name\n";
            cout << "3) Edit last name\n";
            cout << "4) Edit address\n";
            cout << "5) Edit salary\n";
            cout << "6) Edit hired\n";
            cout << "7) Edit login id\n";
            cout << "8) Edit password\n";
            cout << "0) Exit\n";
            cout << "\n--->  ";
            if (cin >> option)
            {
                ;
            }
            else
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                option = 500;
            }
            switch (option)
            {
            case 0:
                cout << "Finished Editing!" << endl;
                done = true;
                break;
            case 1:
                cout << "Enter new first name --> ";
                cin >> userInput;
                emp.setFirstName(userInput);
                break;
            case 2:
                cout << "Enter new middle name --> ";
                cin >> userInput;
                emp.setMiddleName(userInput);
                break;
            case 3:
                cout << "Enter new last name --> ";
                cin >> userInput;
                emp.setLastName(userInput);
                break;
            case 4:
                cout << "Enter new address --> ";
                cin.ignore();
                getline(cin, userInput);
                emp.setAddress(userInput);
                break;
            case 5:
                cout << "Enter new salary --> ";
                cin >> userInput;
                emp.setSalary(stoi(userInput));
                break;
            case 6:
                cout << "Hired? (y/n) -->  ";
                cin >> userInput;
                if (userInput == "y")
                {
                    emp.setHired(true);
                }
                else if (userInput == "n")
                {
                    emp.setHired(false);
                }
                else
                {
                    cout << "comamnd not found!" << endl;
                }
                break;
            case 7:
                cout << "Enter new login id --> ";
                cin >> userInput;
                emp.setLoginId(userInput);
                break;
            case 8:
                cout << "Enter new password --> ";
                cin >> userInput;
                emp.setPassword(userInput);
                break;
            default:
                cout << "Unknown command!" << endl;
                break;
            }
        }
    }
    catch (const std::logic_error &exception)
    {
        cerr << "Unable to edit employee: " << exception.what() << endl;
    }
}

string selectInputFileName(const string &oldName)
{
    string result{""};
    bool done{false};
    while (!done)
    {
        if (oldName.size() > 0)
        {
            cout << "Old file name: " << oldName << endl;
        }
        cout << "Enter file name or 0 to exit: ";
        cin >> result;
        if (result == "0")
        {
            cout << "Exiting..." << endl;
            return "";
        };
        cout << "Entered file name: " << result << endl;
        ifstream inFile;
        inFile.open(result);
        if (inFile)
        {
            cout << "File exists" << endl;
            return result;
        }
        else
        {
            cout << "File doesn't exist. Try again" << endl;
        }
    }
    return "";
}

string selectOutputFileName(const string &oldName)
{
    string result{""};
    string confirm{""};
    bool done{false};
    while (!done)
    {
        if (oldName.size() > 0)
        {
            cout << "Old file name: " << oldName << endl;
        }
        cout << "Enter file name or 0 to exit: ";
        cin >> result;
        if (result == "0")
        {
            cout << "Exiting..." << endl;
            return "";
        };
        cout << "Entered file name: " << result << endl;
        ifstream inFile;
        inFile.open(result);
        if (inFile)
        {
            cout << "File already exist.\nConfirm to overwrite (y/n): ";
            cin >> confirm;
            if (confirm == "y")
            {
                return result;
            }
            else
            {
                cout << "Please provide new file name!" << endl;
            }
        }
        else
        {
            return result;
        }
    }
    return "";
}
