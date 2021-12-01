#pragma once
#include <conio.h>
#include "Company.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"

void PrintMenuHeader() {
	std::cout << "-------------------------------------МЕНЮ-------------------------------------" << std::endl;
}

int GetChoice() {
	char c_digit = _getch();
	int digit = (int) c_digit - (int) '0';
	return digit;
}

int BinChoice() {
	int result = GetChoice();
	switch (result) {
	case 1: return 1;
	case 2: return 2;
	default: return BinChoice();
	}
}

void ShowWorkers(Company *company) {
	system("cls");
	PrintMenuHeader();
	company->ShowWorkers();
	std::cout << std::endl;
	system("pause");
}

void Hire(Company *company) {
	Employee* employee = nullptr;
	std::string lastN, firstN, patronymic;
	Sex sex;
	unsigned normHoursPerDay;
	double moneyPerHour;
	double moneyPerExtraHour;
	double fixedSalary;
	double percentageOfSales;
	int salaryClass;


	system("cls");
	PrintMenuHeader();



	std::cout << "Выберите класс работника (1 - почасовая оплата, 2 - комиссионная)" << std::endl;
	salaryClass = BinChoice();

	std::cout << "Введите фамилию: ";
	std::getline(std::cin, lastN);

	if (lastN.empty()) {
		switch (salaryClass) {
		case 1: employee = new HourlyEmployee(); break;
		case 2: employee = new CommissionEmployee(); break;
		}
	} else {
		std::cout << "Введите имя: ";
		std::getline(std::cin, firstN);

		std::cout << "Введите отчество: ";
		std::getline(std::cin, patronymic);
		FCs fcs = { lastN, firstN, patronymic };

		std::cout << "Выберите пол работника (1 - муж, 2 - женский)" << std::endl;
		sex = (BinChoice() == 1 ? Sex::Male : Sex::Female);

		switch (salaryClass) {
		case 1: {
			std::cout << "Введите нормативное количество часов для отработки в день (целое число): ";
			std::cin >> normHoursPerDay;

			std::cout << "Введите заработную плату за час работы: ";
			std::cin >> moneyPerHour;

			std::cout << "Введите заработную плату за час работы свыше нормированного графика: ";
			std::cin >> moneyPerExtraHour;

			employee = new HourlyEmployee(fcs, sex, normHoursPerDay, moneyPerHour, moneyPerExtraHour);
		} break;
		case 2: {
			std::cout << "Введите фиксированную заработную плату за месяц: ";
			std::cin >> fixedSalary;

			std::cout << "Введите получаемый процент с продаж (0-100%): ";
			std::cin >> percentageOfSales;

			employee = new CommissionEmployee(fcs, sex, fixedSalary, percentageOfSales);
		} break;
		}
	}
	if (char(std::cin.peek()) == '\n')
		std::cin.ignore();
	company->Hire(employee);
	delete employee;
	std::cout << "Работник усепшно устроен в компанию!" << std::endl << std::endl;
	system("pause");
}

void Dismiss(Company *company) {
	system("cls");
	PrintMenuHeader();
	company->ShowWorkers();
	std::cout << "Введите номер сотрудника, которого хотите уволить (0 - отмена): " << std::endl;
	int index;
	int workerCount = company->GetWorkerCount();
	if (workerCount == 0) {
		std::cout << "В компании нет работников, некого увольнять" << std::endl;
		system("pause");
	} else {
		for (;;) {
			index = GetChoice();
			if (index == 0)
				return;
			if (index > 0 && index <= workerCount) {
				company->Dismiss(index - 1);
				std::cout << "Работник под номером " << index << " уволен" << std::endl << std::endl;
				system("pause");
				return;
			}
		}
	}
}

void SimulateWork(Company* company) {
	system("cls");
	PrintMenuHeader();
	unsigned int days;
	std::cout << "Количество дней работы: ";
	std::cin >> days;
	company->SimulateWork(days);
	std::cout << std::endl;
	system("pause");
}

void SaveInfo(Company* company) {
	system("cls");
	PrintMenuHeader();
	std::cout << "Предыдущие данные будут перезаписаны.\nВы уверены, что хотите сохранить информацию?\nЕсли да - нажмите 1, если нет - 2: ";
	int result = BinChoice();
	if (result == 2)
		return;
	company->SaveToJson("data.json");
	std::cout << std::endl << "Информация сохранена" << std::endl;
	system("pause");
}

void LoadInfo() {
	system("cls");
	PrintMenuHeader();
	std::cout << "Информация о текущей компании будет удалена.\nВы уверены, что хотите данные?\nЕсли да - нажмите 1, если нет - 2: ";
	int result = BinChoice();
	if (result == 2)
		return;
	Company company;
	try {
		company = Company::LoadFromJson("data.json");
	}
	catch (const std::invalid_argument&) {
		std::cout << "Не получилось открыть файл" << std::endl;
		system("pause");
	}
	std::cout << std::endl << "Информация загружена" << std::endl;
	throw company;
}