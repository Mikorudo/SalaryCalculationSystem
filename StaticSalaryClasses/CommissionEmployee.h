#pragma once
#include "Employee.h"

class CommissionEmployee : public Employee {
public:
	CommissionEmployee();
	CommissionEmployee(FCs _fcs, Sex _sex, double _fixedSalary, double _percentageOfSales);
	Employee* MyClone();
	void Sell(double money);
	void SimulateWork(unsigned days);
	void CalculateSalary();

	rapidjson::Document toJSON();
	static CommissionEmployee fromJSON(const rapidjson::Value& doc);
private:
	double sales;
	double fixedSalary;
	double percentageOfSales;
	CommissionEmployee(FCs _fcs, Sex _sex, double _sales, double _fixedSalary, double _percentageOfSales);
};

