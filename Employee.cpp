#include <iostream>
#include "Employee.h"

using namespace std;

namespace Records
{

	// Employee::Employee(const std::string &firstName, const std::string &lastName)
	// 	: mFirstName(firstName), mLastName(lastName)
	// {
	// }

	Employee::Employee(const std::string &firstName, const std::string &middleName, const std::string &lastName, const std::string &address)
		: mFirstName(firstName), mMiddleName(middleName), mLastName(lastName), mAddress(address)
	{
	}

	void Employee::promote(int raiseAmount)
	{
		setSalary(getSalary() + raiseAmount);
	}

	void Employee::demote(int demeritAmount)
	{
		setSalary(getSalary() - demeritAmount);
	}

	void Employee::hire()
	{
		mHired = true;
	}

	void Employee::fire()
	{
		mHired = false;
	}

	void Employee::display() const
	{
		cout << "\nEmployee: " << getLastName() << ", " << getFirstName() << " " << getMiddleName() << endl;
		cout << "-------------------------" << endl;
		cout << (isHired() ? "Current Employee" : "Former Employee") << endl;
		cout << "Employee Number: " << getEmployeeNumber() << endl;
		cout << "Salary: $" << getSalary() << endl;
		cout << "Address: " << getAddress() << endl;
		cout << "Login id: " << getLoginId() << endl;
		cout << "Password: " << getPassword() << endl;
		cout << endl;
	}

	// Getters and setters
	void Employee::setFirstName(const string &firstName)
	{
		mFirstName = firstName;
	}

	const string &Employee::getFirstName() const
	{
		return mFirstName;
	}

	void Employee::setMiddleName(const string &middleName)
	{
		mMiddleName = middleName;
	}

	const string &Employee::getMiddleName() const
	{
		return mMiddleName;
	}

	void Employee::setLastName(const string &lastName)
	{
		mLastName = lastName;
	}

	const string &Employee::getLastName() const
	{
		return mLastName;
	}

	void Employee::setEmployeeNumber(int employeeNumber)
	{
		mEmployeeNumber = employeeNumber;
	}

	int Employee::getEmployeeNumber() const
	{
		return mEmployeeNumber;
	}

	void Employee::setSalary(int salary)
	{
		mSalary = salary;
	}

	int Employee::getSalary() const
	{
		return mSalary;
	}

	void Employee::setAddress(const string &address)
	{
		mAddress = address;
	}

	const string &Employee::getAddress() const
	{
		return mAddress;
	}

	void Employee::setHired(const bool &hire)
	{
		mHired = hire;
	}

	bool Employee::isHired() const
	{
		return mHired;
	}

	void Employee::setLoginId(const string &loginId)
	{
		mloginId = loginId;
	}

	const string &Employee::getLoginId() const
	{
		return mloginId;
	}

	void Employee::setPassword(const string &password)
	{
		mPassword = password;
	}

	const string &Employee::getPassword() const
	{
		return mPassword;
	}

}
