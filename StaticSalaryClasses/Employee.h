#pragma once
#include <iostream>
#include <stdexcept>
#include <time.h>
#include "../rapidjson/include/rapidjson/document.h"
#include "ConstantValues.h"
#include "Sex.h"
#include "FCs.h"

class Employee {
public:	
	Employee();
	Employee(FCs fcs, Sex sex);
	virtual Employee* MyClone() = 0;
	std::string GetFirstName();
	std::string GetLastName();
	std::string GetPatronymic();
	virtual rapidjson::Document toJSON() = 0;
	virtual void SimulateWork(unsigned days) = 0;
	virtual void CalculateSalary() = 0;
	void PaySalary();
	Sex GetSex();

protected:
	FCs fcs;
	Sex sex;
	double salary;
	double bankAccount;
	unsigned daysAfterSalary;
};

