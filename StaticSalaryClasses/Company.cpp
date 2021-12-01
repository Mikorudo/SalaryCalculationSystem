#include "Company.h"

Company::Company() {};

Company::~Company() {
	for (auto& x: empList)
		delete x;
	empList.clear();
}

Company::Company(const Company& object) {
	for (size_t i = 0; i < object.empList.size(); i++) {
		Employee* temp = object.empList[i]->MyClone();
		this->empList.push_back(temp);
	}
}

Company& Company::operator=(const Company& object) {
	if (&object == this)
		return *this;

	for (auto& x : this->empList)
		delete x;
	this->empList.clear();

	for (size_t i = 0; i < object.empList.size(); i++) {
		Employee* temp = object.empList[i]->MyClone();
		this->empList.push_back(temp);
	}

	return *this;
}

void Company::Hire(Employee* emp) {
	Employee* temp = emp->MyClone();
	empList.push_back(temp);
}

void Company::Dismiss(int index) {
	Employee* temp = empList[index];
	empList.erase(empList.begin() + index);
	delete temp;
}

void Company::ShowWorkers() {
	size_t size = empList.size();
	std::cout << "Список сотрудников :" << std::endl;
	
	for (size_t i = 0; i < size; i++) {
		Employee* temp = empList[i];
		std::cout << i + 1 << ". " << temp->GetLastName() << " " << temp->GetFirstName() << " " << temp->GetPatronymic();
		std::cout << ".     Пол: " << (temp->GetSex() == Sex::Male ? "мужской" : "женский") << std::endl;
		temp = nullptr;
	}
}

int Company::GetWorkerCount() {
	return empList.size();
}

void Company::SimulateWork(int days) {
	for (size_t i = 0; i < GetWorkerCount(); i++) {
		empList[i]->SimulateWork(days);
	}
}

void Company::SaveToJson(const std::string filename) {
	size_t size = empList.size();
	std::ofstream fout;
	fout.open(filename);
	for (size_t i = 0; i < size; i++) {
		Employee* temp = empList[i];
		rapidjson::Document doc = temp->toJSON();
		temp = nullptr;
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		const std::string& str = buffer.GetString();
		fout << str;
		if (i != size - 1)
			fout << std::endl;
	}
	fout.close();
}

Company Company::LoadFromJson(const std::string filename) {
	Company company;
	std::ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
		throw std::invalid_argument("There is no access to the file");
	std::string str;
	while (!fin.eof()) {
		str = "";
		std::getline(fin, str);
		if (str == "")
			break;
		rapidjson::Document doc;
		doc.Parse(str.c_str());
		if (doc["employeeClass"] == "HourlyEmployee") {
			HourlyEmployee temp = HourlyEmployee::fromJSON(doc);
			company.Hire(&temp);
		}
		if (doc["employeeClass"] == "CommissionEmployee") {
			CommissionEmployee temp = CommissionEmployee::fromJSON(doc);
			company.Hire(&temp);
		}
	}
	fin.close();
	return company;
}