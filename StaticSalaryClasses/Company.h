#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "../rapidjson/include/rapidjson/rapidjson.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "Employee.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"


class Company {
public:
	Company();
	~Company();
	Company(const Company& object);

	Company& operator=(const Company& object);
	
	void Hire(Employee* employee);
	void Dismiss(int index);
	void ShowWorkers();
	int GetWorkerCount();
	void SimulateWork(int days);

	void SaveToJson(const std::string filename);

	static Company LoadFromJson(const std::string filename);
private:
	std::vector <Employee*> empList;
};

