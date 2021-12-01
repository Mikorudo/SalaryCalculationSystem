#include "HourlyEmployee.h"

HourlyEmployee::HourlyEmployee() : Employee(), hours(0), normHoursPerDay(commonNormHoursHerDay) , moneyPerHour(commonMoneyPerHour), moneyPerExtraHour(commonMoneyPerExtraHour) {
}

HourlyEmployee::HourlyEmployee(FCs _fcs, Sex _sex, unsigned _normHoursPerDay, double _moneyPerHour, double _moneyPerExtraHour) : Employee(_fcs, _sex), hours(0), normHoursPerDay(_normHoursPerDay), moneyPerHour(_moneyPerHour), moneyPerExtraHour(_moneyPerExtraHour) {
	if (_normHoursPerDay == 0)
		throw std::invalid_argument("The daily work norm is 0 hours");
	if (_moneyPerHour < 0)
		throw std::invalid_argument("Negative amount (money per hour)");
	if (_moneyPerExtraHour < 0)
		throw std::invalid_argument("Negative amount (money per extra hour)");
}

HourlyEmployee::HourlyEmployee(FCs _fcs, Sex _sex, double _hours, unsigned _normHoursPerDay, double _moneyPerHour, double _moneyPerExtraHour) : Employee(_fcs, _sex), hours(_hours), normHoursPerDay(_normHoursPerDay), moneyPerHour(_moneyPerHour), moneyPerExtraHour(_moneyPerExtraHour) {
}

rapidjson::Document HourlyEmployee::toJSON() {
	rapidjson::Value json_val;
	rapidjson::Document doc;
	auto& allocator = doc.GetAllocator();

	doc.SetObject();

	std::string employeeClass = "HourlyEmployee";
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

	json_val.SetDouble(hours);
	doc.AddMember("hours", json_val, allocator);

	json_val.SetUint(normHoursPerDay);
	doc.AddMember("normHoursPerDay", json_val, allocator);

	json_val.SetDouble(moneyPerHour);
	doc.AddMember("moneyPerHour", json_val, allocator);

	json_val.SetDouble(moneyPerExtraHour);
	doc.AddMember("moneyPerExtraHour", json_val, allocator);

	return doc;
}

HourlyEmployee HourlyEmployee::fromJSON(const rapidjson::Value& doc) {

	std::string _lastName = doc["lastName"].GetString();
	std::string _firstName = doc["firstName"].GetString();
	std::string _patronymic = doc["patronymic"].GetString();
	Sex _sex = (Sex)doc["sex"].GetInt();
	double _hours = doc["hours"].GetDouble();
	unsigned _normHoursPerDay = doc["normHoursPerDay"].GetUint();
	double _moneyPerHour = doc["moneyPerHour"].GetDouble();
	double _moneyPerExtraHour = doc["moneyPerExtraHour"].GetDouble();

	FCs fcs = { _lastName, _firstName, _patronymic };
	HourlyEmployee result(fcs, _sex, _hours, _normHoursPerDay, _moneyPerHour, _moneyPerExtraHour);
	return result;
}

Employee* HourlyEmployee::MyClone() {
	return new HourlyEmployee(*this);
}

void HourlyEmployee::Work(double _hours) {
	if (_hours < 0)
		throw std::invalid_argument("Negative time");
	hours += _hours;
}

void HourlyEmployee::SimulateWork(unsigned days) {
	for (size_t i = 0; i < days; i++) {
		Work(rand() % 6 + 4);
		daysAfterSalary++;
		CalculateSalary();
		PaySalary();
	}
}

void HourlyEmployee::CalculateSalary() {
	if (daysAfterSalary >= daysBetweenSalary) {
		if (hours >= normHoursPerDay * daysAfterSalary) {
			salary += normHoursPerDay * daysAfterSalary * moneyPerHour;
			hours -= normHoursPerDay * daysAfterSalary;
			salary += hours * moneyPerExtraHour;
		} else
			salary += hours * moneyPerHour;

		hours = 0;
		daysAfterSalary = 0;
	}
}