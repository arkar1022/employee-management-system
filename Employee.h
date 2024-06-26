#pragma once

#include <string>
#include "my_debugger.h"

namespace Records
{
	const int kDefaultStartingSalary = 30000;

	class Employee
	{
	public:
		static const size_t INDEX_EMPLOYEE_NUMBER{0};
		static const size_t INDEX_FIRST_NAME{1};
		static const size_t INDEX_MIDDLE_NAME{2};
		static const size_t INDEX_LAST_NAME{3};
		static const size_t INDEX_ADDRESS{4};
		static const size_t INDEX_SALARY{5};
		static const size_t INDEX_ISHIRED{6};
		static const size_t INDEX_LOGINID{7};
		static const size_t INDEX_PASSWORD{8};

		Employee() = default;
		// Employee(const std::string &firstName, const std::string &lastName);
		Employee(const std::string &firstName, const std::string &middleName, const std::string &lastName, const std::string &address);

		void promote(int raiseAmount = 1000);
		void demote(int demeritAmount = 1000);
		void hire();		  // Hires or rehires the employee
		void fire();		  // Dismisses the employee
		void display() const; // Outputs employee info to console

		// Getters and setters
		void setFirstName(const std::string &firstName);
		const std::string &getFirstName() const;

		void setMiddleName(const std::string &middleName);
		const std::string &getMiddleName() const;

		void setLastName(const std::string &lastName);
		const std::string &getLastName() const;

		void setEmployeeNumber(int employeeNumber);
		int getEmployeeNumber() const;

		void setSalary(int newSalary);
		int getSalary() const;

		void setAddress(const std::string &address);
		const std::string &getAddress() const;

		void setHired(const bool &hire);
		bool isHired() const;

		void setLoginId(const std::string &loginId);
		const std::string &getLoginId() const;

		void setPassword(const std::string &password);
		const std::string &getPassword() const;

	private:
		std::string mFirstName;
		std::string mMiddleName;
		std::string mLastName;
		std::string mAddress;
		std::string mloginId;
		std::string mPassword;
		int mEmployeeNumber = -1;
		int mSalary = kDefaultStartingSalary;
		bool mHired = false;
	};

};
