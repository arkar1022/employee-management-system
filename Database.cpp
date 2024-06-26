#include <iostream>
#include <stdexcept>
#include <limits>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Database.h"

using namespace std;

namespace Records
{

	// Employee& Database::addEmployee(const string& firstName,
	// 	const string& lastName)
	// {
	// 	logMsg("started");
	// 	Employee theEmployee(firstName, lastName);
	// 	theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
	// 	theEmployee.hire();
	// 	mEmployees.push_back(theEmployee);
	// 	logMsg("ended");
	// 	return mEmployees[mEmployees.size() - 1];

	// }

	Employee &Database::addEmployee(const string &firstName,
									const string &middleName,
									const string &lastName,
									const string &address)
	{
		logMsg("started");
		Employee theEmployee(firstName, middleName, lastName, address);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.setLoginId("em" + to_string(theEmployee.getEmployeeNumber()));
		theEmployee.setPassword("pw" + to_string(theEmployee.getEmployeeNumber()));
		theEmployee.hire();
		mEmployees.push_back(theEmployee);
		logMsg("ended");
		return mEmployees[mEmployees.size() - 1];
	}

	Employee &Database::addEmployee(const Employee &empl)
	{
		logMsg("started");
		mEmployees.push_back(empl);
		logMsg("ended");
		return mEmployees[mEmployees.size() - 1];
	}

	Employee &Database::getEmployee(int employeeNumber)
	{
		for (auto &employee : mEmployees)
		{
			if (employee.getEmployeeNumber() == employeeNumber)
			{
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee &Database::getEmployee(const string &firstName, const string &lastName)
	{
		for (auto &employee : mEmployees)
		{
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName)
			{
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto &employee : mEmployees)
		{
			employee.display();
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto &employee : mEmployees)
		{
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto &employee : mEmployees)
		{
			if (!employee.isHired())
				employee.display();
		}
	}

	void Database::deleteEmployee(int &emplNum)
	{
		// Find the employee using std::remove_if and a lambda function
		auto employeeIterator = std::remove_if(mEmployees.begin(), mEmployees.end(), [emplNum](const Employee &emp)
											   { return emp.getEmployeeNumber() == emplNum; });

		// Check if an employee with the specified employee number was found
		if (employeeIterator != mEmployees.end())
		{
			// Erase the elements from the iterator position to the end of the vector
			mEmployees.erase(employeeIterator, mEmployees.end());
			cout << "Successfully deleted!" << endl;
		}
		else
		{
			// Print a message if no employee with the specified number was found
			cout << "Employee Number not found!" << endl;
		}
	}

	int Database::displaySearchMenu() const
	{
		int selection;

		cout << endl;
		cout << "Search Employee Database" << endl;
		cout << "-----------------" << endl;
		cout << "1) Search by first name" << endl;
		cout << "2) Search by middle namee" << endl;
		cout << "3) Search by last name" << endl;
		cout << "4) Search by address" << endl;
		cout << "0) Quit" << endl;
		cout << endl;
		cout << "--->";
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

	void Database::searchMenu() const
	{
		bool done{false};
		while (!done)
		{
			int selection = displaySearchMenu();
			switch (selection)
			{
			case 0:
				cout << "Exiting..." << endl;
				done = true;
				break;
			case 1:
				searchBy(SearchOption::BY_FIRST);
				break;
			case 2:
				searchBy(SearchOption::BY_MIDDLE);
				break;
			case 3:
				searchBy(SearchOption::BY_LAST);
				break;
			case 4:
				searchBy(SearchOption::BY_ADDRESS);
				break;
			default:
				cout << "Unknown command!" << endl;
				break;
			}
		}
	}

	void Database::searchBy(SearchOption option) const
	{
		// Initialize variables
		string searchTag;
		Database result;

		// Prompt user for the search string
		cout << "Enter search string here --> ";

		// Ignore any characters in the input buffer before reading the search string
		cin.ignore();

		// Read the entire line, including spaces
		getline(cin, searchTag);

		// Convert the search string to lowercase for case-insensitive comparison
		searchTag = stringToLower(searchTag);

		// Loop through each employee in the database
		for (const auto &e : mEmployees)
		{
			string targetString{""};
			switch (option)
			{
			case SearchOption::BY_FIRST:
				targetString = stringToLower(e.getFirstName());
				break;
			case SearchOption::BY_MIDDLE:
				targetString = stringToLower(e.getMiddleName());
				break;
			case SearchOption::BY_LAST:
				targetString = stringToLower(e.getLastName());
				break;
			case SearchOption::BY_ADDRESS:
				targetString = stringToLower(e.getAddress());
				break;
			default:
				cout << "Invalid option" << endl;
				break;
			}

			// Find the position of the search string within the target string
			size_t pos = targetString.find(searchTag, 0);

			// If the search string is not found in the target string, continue to the next employee
			if (pos == string::npos)
			{
				continue;
			}

			e.display();

			result.addEmployee(e);
		}

		// If no matches were found, print a message
		if (result.size() == 0)
		{
			cout << "Nothing matches!" << endl;
		}
	}

	void Database::verifyEmployee() const
	{
		// Variables to store user input
		string loginId{};
		string password{""};

		bool isFound(false);

		// Prompt user for login credentials
		cout << endl;
		cout << "Employee" << endl;
		cout << "-----------------" << endl;
		cout << "Enter login id --> ";
		cin >> loginId;
		cout << "Enter password --> ";
		cin >> password;

		// Iterate through each employee in the database
		for (auto &employee : mEmployees)
		{
			// Check if the login id matches
			if (employee.getLoginId() == loginId)
			{
				isFound = true;

				// If login id matches, check if the password is correct
				if (employee.getPassword() == password)
				{
					// Display employee information upon successful verification
					string exit;
					cout << "Successfully verified!" << endl;
					employee.display();
					cout << "\nEnter 0 to exit --> ";
					cin >> exit;
				}
				else
				{
					// Print a message if the password is incorrect
					cout << "Password is incorrect!" << endl;
				}
			}
		}

		// Print a message if the login id is not found
		if (!isFound)
		{
			cout << "Cannot find your login id" << endl;
		}
	}

	void Database::saveToFile(const string &fileName) const
	{
		// Check if the provided file name is empty
		if (fileName.empty())
		{
			return; // Do nothing if the file name is empty
		}

		// Open the file for writing
		ofstream dbFile(fileName, ios_base::trunc);

		// Check if the file opening fails
		if (dbFile.fail())
		{
			cerr << "Unable to open " << fileName << " !" << endl;
			return;
		}

		cout << "Saving to " << fileName << "..." << endl;

		// Write header line to the file
		dbFile << "EmployeeNumber;";
		dbFile << "FirstName;";
		dbFile << "MiddleName;";
		dbFile << "LastName;";
		dbFile << "Address;";
		dbFile << "Salary;";
		dbFile << "isHired;";
		dbFile << "LoginId;";
		dbFile << "Password" << endl;

		// Iterate through each employee and write their information to the file
		for (const auto &employee : mEmployees)
		{
			// Convert various employee attributes to strings
			string emplNum{to_string(employee.getEmployeeNumber())};
			string fName{employee.getFirstName()};
			string mName{employee.getMiddleName()};
			string lName{employee.getLastName()};
			string address{employee.getAddress()};
			string salary{to_string(employee.getSalary())};
			string isHired{to_string(employee.isHired())};
			string loginId{employee.getLoginId()};
			string password{employee.getPassword()};

			// Write employee information to the file
			dbFile << emplNum << ";";
			dbFile << fName << ";";
			dbFile << mName << ";";
			dbFile << lName << ";";
			dbFile << address << ";";
			dbFile << salary << ";";
			dbFile << isHired << ";";
			dbFile << loginId << ";";
			dbFile << password << endl;
		}

		// Print a message indicating that the saving process was successful
		cout << "Successfully Saved!" << endl;
	}

	Database loadFromFile(const string &fileName)
	{
		Database db;

		// Check if the provided file name is empty
		if (fileName.empty())
		{
			return db; // Return an empty database if the file name is empty
		}

		// Open the file for reading
		ifstream dbFile(fileName, ios_base::in);

		// Check if the file opening fails
		if (dbFile.fail())
		{
			cerr << "Unable to open " << fileName << " !" << endl;
			return db; // Return an empty database if the file opening fails
		}

		cout << "Loading database from " << fileName << "..." << endl;

		// Read the header line from the file (not used in this implementation)
		string header;
		getline(dbFile, header);

		// Read each line from the file and populate the database
		string line;
		while (getline(dbFile, line))
		{
			// Tokenize the line using ';' as a delimiter
			vector<string> tokens;
			stringstream streamFromLine(line);
			string token;
			while (getline(streamFromLine, token, ';'))
			{
				tokens.push_back(token);
			}

			// Extract information from tokens and create an Employee object
			int emplNum{stoi(tokens[Employee::INDEX_EMPLOYEE_NUMBER])};
			string fName{tokens[Employee::INDEX_FIRST_NAME]};
			string mName{tokens[Employee::INDEX_MIDDLE_NAME]};
			string lName{tokens[Employee::INDEX_LAST_NAME]};
			string address{tokens[Employee::INDEX_ADDRESS]};
			int salary{stoi(tokens[Employee::INDEX_SALARY])};
			bool isHired{static_cast<bool>(stoi(tokens[Employee::INDEX_ISHIRED]))};
			string loginId{tokens[Employee::INDEX_LOGINID]};
			string password{tokens[Employee::INDEX_PASSWORD]};

			// Create an Employee object and set its attributes
			Employee empl(fName, mName, lName, address);
			empl.setEmployeeNumber(emplNum);
			empl.setSalary(salary);
			empl.setHired(isHired);
			empl.setLoginId(loginId);
			empl.setPassword(password);

			// Add the Employee to the Database
			db.addEmployee(empl);
		}
		cout << "Successfully Loaded!" << endl;

		// Return the populated Database
		return db;
	}

	Database generateNewDatabase()
	{
		logMsg("started");
		// 20 First Names
		std::vector<std::string> arrFirstName{
			"John", "Michael", "William", "David", "Richard",
			"Joseph", "Thomas", "Charles", "Robert", "James",
			"Daniel", "Matthew", "Brian", "Christopher", "Andrew",
			"Edward", "George", "Donald", "Paul", "Mark"};

		// 20 Middle Names
		std::vector<std::string> arrMiddleName{
			"Alexander", "Benjamin", "Carter", "Daniel", "Elijah",
			"Finn", "Gabriel", "Harrison", "Isaac", "Jacob",
			"Kai", "Liam", "Mason", "Nathan", "Oliver",
			"Parker", "Quincy", "Ryan", "Samuel", "Tyler"};

		// 20 Last Names
		std::vector<std::string> arrLastName{
			"Anderson", "Baker", "Carter", "Davis", "Evans",
			"Fisher", "Garcia", "Harrison", "Irwin", "Johnson",
			"Keller", "Lopez", "Martinez", "Nelson", "Owens",
			"Perez", "Quinn", "Rodriguez", "Smith", "Taylor"};

		Database db;
		int uniqueNumber{1};
		for (const string &firstName : arrFirstName)
		{
			for (const string &middleName : arrMiddleName)
			{
				for (const string &lastName : arrLastName)
				{
					string address = generateRandomAddress(uniqueNumber);
					db.addEmployee(firstName, middleName, lastName, address);
					uniqueNumber++;
				}
			}
		}
		cout << "New Database Has Been Generated\n";
		logMsg("ended");
		return db;
	}

	string generateRandomAddress(int &uniqueNumber)
	{
		logMsg("started");
		vector<string> streetNames = {"Maple", "Oak", "Cedar", "Pine", "Elm", "Main", "Broad", "High"};
		vector<string> cities = {"Springfield", "Rivertown", "Lakeview", "Hillside", "Meadowville"};
		vector<string> states = {"CA", "NY", "TX", "FL", "IL"};

		string address =
			"No." +
			to_string(100 + uniqueNumber % 900) + ", " +					  // House number
			streetNames[(uniqueNumber / 10) % streetNames.size()] + "_St, " + // Street name
			cities[(uniqueNumber / 100) % cities.size()] + ", " +			  // City
			states[(uniqueNumber / 1000) % states.size()];					  // State
		logMsg("ended");
		return address;
	}
	string stringToLower(string str)
	{
		for (char &c : str)
		{
			c = std::tolower(c);
		};
		return str;
	}

}
