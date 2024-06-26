#pragma once

#include <iostream>
#include <vector>

#include "Employee.h"

namespace Records
{
	const int kFirstEmployeeNumber = 1000;

	class Database
	{
	public:
		// Employee &addEmployee(const std::string &firstName,
		// 					  const std::string &lastName);
		Employee &addEmployee(const std::string &firstName,
							  const std::string &middleName,
							  const std::string &lastName,
							  const std::string &address);
		Employee &addEmployee(const Employee &empl);
		Employee &getEmployee(int employeeNumber);
		Employee &getEmployee(const std::string &firstName,
							  const std::string &lastName);

		void displayAll() const;
		void displayCurrent() const;
		void displayFormer() const;
		void saveToFile(const string &filename) const;
		void searchMenu() const;
		int displaySearchMenu() const;
		std::size_t size() const { return mEmployees.size(); };
		void verifyEmployee() const;
		void deleteEmployee(int &emplNum);

	private:
		std::vector<Employee> mEmployees;
		int mNextEmployeeNumber = kFirstEmployeeNumber;
		enum class SearchOption
		{
			BY_FIRST = 1,
			BY_MIDDLE,
			BY_LAST,
			BY_ADDRESS
		};
		void searchBy(SearchOption option) const;
	};
	Database loadFromFile(const string &fileName);
	Database generateNewDatabase();
	string generateRandomAddress(int &uniqueNumber);
	string stringToLower(string str);
}
