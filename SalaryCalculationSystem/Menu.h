#pragma once
#include "MenuActions.h"

void PrintMenuSelection() {
	std::cout << "1. �������� ������ �����������" << std::endl;
	std::cout << "2. ������� �� ������" << std::endl;
	std::cout << "3. ������� ���������" << std::endl;
	std::cout << "4. ������������ ������" << std::endl;
	std::cout << "5. ��������� ���������� � ��������" << std::endl;
	std::cout << "6. ��������� ���������� � ��������" << std::endl;
	std::cout << "7. ����� �� ���������" << std::endl;
}

void SelectAction(Company *company) {
	for (;;) {
		switch (GetChoice()) {
		case 1: ShowWorkers(company); return;
		case 2: Hire(company); return;
		case 3: Dismiss(company); return;
		case 4: SimulateWork(company); return;
		case 5: SaveInfo(company); return;
		case 6: LoadInfo(); return;
		case 7: exit(0);
		}
	}
}

void Menu() {
	Company company;
	for (;;) {
		try {
			for (;;) {
				system("cls");
				PrintMenuHeader();
				PrintMenuSelection();
				SelectAction(&company);
			}
		}
		catch (Company newCompany) {
			company = newCompany;
			system("pause");
		}
	}
	
	
}
