#pragma once
#include "Employee.h"

class HourlyEmployee : public Employee {
public:
	HourlyEmployee();
	HourlyEmployee(FCs _fcs, Sex _sex, unsigned _normHoursPerDay, double _moneyPerHour, double _moneyPerExtraHour);
	Employee* MyClone();
	void Work(double hours);
	void SimulateWork(unsigned days);
	void CalculateSalary();

    rapidjson::Document toJSON();
	static HourlyEmployee fromJSON(const rapidjson::Value& doc);
private:
	double hours;
	unsigned normHoursPerDay;
	double moneyPerHour;
	double moneyPerExtraHour;
    HourlyEmployee(FCs _fcs, Sex _sex, double _hours, unsigned _normHoursPerDay, double _moneyPerHour, double _moneyPerExtraHour);
};

