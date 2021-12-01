#include "pch.h"
#include "CppUnitTest.h"
#include "Company.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Employee* testEmp = new CommissionEmployee();

			Assert::AreEqual(testEmp->GetFirstName(), (std::string)"noname");
			Assert::AreEqual(testEmp->GetLastName(), (std::string)"noname");
			Assert::AreEqual(testEmp->GetPatronymic(), (std::string)"noname");
			Assert::AreEqual((int)testEmp->GetSex(), (int)Sex::Male);
			delete testEmp;
		}

		TEST_METHOD(TestMethod2) {
			Employee* testEmp = new HourlyEmployee();

			Assert::AreEqual(testEmp->GetFirstName(), (std::string)"noname");
			Assert::AreEqual(testEmp->GetLastName(), (std::string)"noname");
			Assert::AreEqual(testEmp->GetPatronymic(), (std::string)"noname");
			Assert::AreEqual((int)testEmp->GetSex(), (int)Sex::Male);
			delete testEmp;
		}

		TEST_METHOD(TestMethod3) {
			FCs fcs = { "TestLN", "TestFN", "TestP" };
			Sex sex = Sex::Female;
			Employee* testEmp = new HourlyEmployee(fcs, sex, commonNormHoursHerDay, commonMoneyPerHour, commonMoneyPerExtraHour);

			Assert::AreEqual(testEmp->GetLastName(), (std::string)"TestLN");
			Assert::AreEqual(testEmp->GetFirstName(), (std::string)"TestFN");
			Assert::AreEqual(testEmp->GetPatronymic(), (std::string)"TestP");
			Assert::AreEqual((int)testEmp->GetSex(), (int)Sex::Female);
			delete testEmp;
		}

		TEST_METHOD(TestMethod4) {
			FCs fcs = { "TestLN", "TestFN", "TestP" };
			Sex sex = Sex::Male;
			Employee* testEmp = new CommissionEmployee(fcs, sex, commonFixedSalary, commonPercentageOfSales);

			Assert::AreEqual(testEmp->GetLastName(), (std::string)"TestLN");
			Assert::AreEqual(testEmp->GetFirstName(), (std::string)"TestFN");
			Assert::AreEqual(testEmp->GetPatronymic(), (std::string)"TestP");
			Assert::AreEqual((int)testEmp->GetSex(), (int)Sex::Male);
			delete testEmp;
		}

		TEST_METHOD(TestMethod5) {
			FCs fcs = { "TestLN", "TestFN", "TestP" };
			Sex sex = Sex::Male;
			CommissionEmployee testEmp(fcs, sex, commonFixedSalary, commonPercentageOfSales);
			rapidjson::Document doc = testEmp.toJSON();
			CommissionEmployee newTestEmp = CommissionEmployee::fromJSON(doc);

			Assert::AreEqual(newTestEmp.GetLastName(), (std::string)"TestLN");
			Assert::AreEqual(newTestEmp.GetFirstName(), (std::string)"TestFN");
			Assert::AreEqual(newTestEmp.GetPatronymic(), (std::string)"TestP");
			Assert::AreEqual((int)newTestEmp.GetSex(), (int)Sex::Male);
		}

		TEST_METHOD(TestMethod6) {
			FCs fcs = { "TestLN", "TestFN", "TestP" };
			Sex sex = Sex::Male;
			HourlyEmployee testEmp(fcs, sex, commonNormHoursHerDay, commonMoneyPerHour, commonMoneyPerExtraHour);
			rapidjson::Document doc = testEmp.toJSON();
			HourlyEmployee newTestEmp = HourlyEmployee::fromJSON(doc);

			Assert::AreEqual(newTestEmp.GetLastName(), (std::string)"TestLN");
			Assert::AreEqual(newTestEmp.GetFirstName(), (std::string)"TestFN");
			Assert::AreEqual(newTestEmp.GetPatronymic(), (std::string)"TestP");
			Assert::AreEqual((int)newTestEmp.GetSex(), (int)Sex::Male);
		}
	};
}
