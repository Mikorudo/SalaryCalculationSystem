#include "CommissionEmployee.h"


CommissionEmployee::CommissionEmployee() : Employee(), sales(0), fixedSalary(commonFixedSalary), percentageOfSales(commonPercentageOfSales) {
}

CommissionEmployee::CommissionEmployee(FCs _fcs, Sex _sex, double _fixedSalary, double _percentageOfSales) : Employee(_fcs, _sex), sales(0), fixedSalary(_fixedSalary), percentageOfSales(_percentageOfSales) {
	if (fixedSalary < 0)
		throw std::invalid_argument("Negative amount (fixed salary)");
	if (_percentageOfSales < 0)
		throw std::invalid_argument("Negative amount (percentage of sales)");
	if (_percentageOfSales > 100)
		throw std::invalid_argument("Percentage greater than 100");
}

CommissionEmployee::CommissionEmployee(FCs _fcs, Sex _sex, double _sales, double _fixedSalary, double _percentageOfSales) : Employee(_fcs, _sex), sales(_sales), fixedSalary(_fixedSalary), percentageOfSales(_percentageOfSales) {}

rapidjson::Document CommissionEmployee::toJSON() {
	rapidjson::Value json_val;
	rapidjson::Document doc;
	auto& allocator = doc.GetAllocator();

	doc.SetObject();

	std::string employeeClass = "CommissionEmployee";
	json_val.SetString(employeeClass.c_str(), allocator);
	doc.AddMember("employeeClass", json_val, allocator);

	json_val.SetString(fcs.lastName.c_str(), allocator);
	doc.AddMember("lastName", json_val, allocator);

	json_val.SetString(fcs.firstName.c_str(), allocator);
	doc.AddMember("firstName", json_val, allocator);

	json_val.SetString(fcs.patronymic.c_str(), allocator);
	doc.AddMember("patronymic", json_val, allocator);

	json_val.SetInt(sex);
	doc.AddMember("sex", json_val, allocator);

	json_val.SetDouble(sales);
	doc.AddMember("sales", json_val, allocator);

	json_val.SetDouble(fixedSalary);
	doc.AddMember("fixedSalary", json_val, allocator);

	json_val.SetDouble(percentageOfSales);
	doc.AddMember("percentageOfSales", json_val, allocator);

	return doc;
}

CommissionEmployee CommissionEmployee::fromJSON(const rapidjson::Value& doc) {

	std::string _lastName = doc["lastName"].GetString();
	std::string _firstName = doc["firstName"].GetString();
	std::string _patronymic = doc["patronymic"].GetString();
	Sex _sex = (Sex)doc["sex"].GetInt();
	double _sales = doc["sales"].GetDouble();
	double _fixedSalary = doc["fixedSalary"].GetDouble();
	double _percentageOfSales = doc["percentageOfSales"].GetDouble();

	FCs fcs = { _lastName, _firstName, _patronymic };
	CommissionEmployee result(fcs, _sex, _sales, _fixedSalary, _percentageOfSales);
	return result;
}


Employee* CommissionEmployee::MyClone() {
	return new CommissionEmployee(*this);
}

void CommissionEmployee::Sell(double money) {
	if (money < 0)
		throw std::invalid_argument("Negative amount");
	sales += money;
}

void CommissionEmployee::SimulateWork(unsigned days) {
	for (size_t i = 0; i < days; i++) {
		Sell(rand()%(maxSales - minSales) + minSales);
		daysAfterSalary++;
		CalculateSalary();
		PaySalary();
	}
}

void CommissionEmployee::CalculateSalary() {
	if (daysAfterSalary >= daysBetweenSalary) {
		salary += fixedSalary / 30 * daysAfterSalary;
		salary += sales * percentageOfSales/100;
		daysAfterSalary = 0;
		sales = 0;
	}
}

