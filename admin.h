#pragma once
#include "System.h";

class admin : System
{
private:
	const string password = "admin@123";
public:
	void signIn();
	void adminMenu();
	void viewAllUsers();
	void deleteAll();
	void counter_for_statictics(float& count_firstDose, float& count_vaccinated, float& countOfFemales);
	void viewAllStatistics();
	void viewVaccinatedByAge();
	void DisplayWaitingList();
	void DoseBreakDown();
};