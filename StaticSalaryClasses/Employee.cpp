#include "Employee.h"


Employee::Employee() {
	fcs.firstName = "noname";
	fcs.lastName = "noname";
	fcs.patronymic = "noname";
	sex = Sex::Male;
	salary = 0;
	bankAccount = 0;
	daysAfterSalary = 0;
}

Employee::Employee(FCs _fcs, Sex _sex) {
	fcs = _fcs;
	sex = _sex;
	salary = 0;
	bankAccount = 0;
	daysAfterSalary = 0;
}

std::string Employee::GetFirstName() {
	return fcs.firstName;
}
std::string Employee::GetLastName() {
	return fcs.lastName;
}
std::string Employee::GetPatronymic() {
	return fcs.patronymic;
}

void Employee::PaySalary() {
	if (salary != 0) {
		bankAccount += salary;
		std::cout << "Выплата " << salary << " работнику:" << this->fcs.lastName << " " << this->fcs.firstName << " " << this->fcs.patronymic << std::endl;
		salary = 0;
	}
	
}

Sex Employee::GetSex() {
	return sex;
}
