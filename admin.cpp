#include "admin.h";
#include "user.h";

void admin::signIn() {
	string pass;

	cout << "If you are not an admin, enter 'Exit'" << endl;
	cout << "Enter password: " << endl;
	cin >> pass;
	if (pass == password) {
		adminMenu();
	}
	//TO LOWERRR
	else if (pass == "Exit" || pass == "exit") {
		system("cls");

		cout << "Thank you for reaching ";
		return;
	}
	else {
		cout << "Password is incorrect please try again." << endl;
		signIn();
	}

}

void admin::adminMenu() {
	char check;
	int choice;
	system("cls");
	string nid;
	int n;
	do {
		cout << "Please choose a number" << endl;
		cout << "1 for view all records" << endl;
		cout << "2 for view specific record" << endl;
		cout << "3 for delete all records" << endl;
		cout << "4 for delete specific record" << endl;
		cout << "5 for view all vaccinated records ordered by age" << endl;
		cout << "6 for view general statistics" << endl;
		cout << "7 Display Waiting list" << endl;
		cout << "8 to breakdown all users by the dose they took" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			system("cls");
			viewAllUsers();
			break;
		case 2:
			system("cls");
			cout << "Enter National ID. " << endl;
			cin >> nid;
			displayUserFound(nid);
			break;
		case 3:
			system("cls");
			deleteAll();
			break;
		case 4:
			//functions that require specific users could have two constructors,
			//one with one ID(int) & one with array of ints if wants 
			system("CLS");
			//string pass;
			cout << "Enter National ID. " << endl;
			cin >> nid;
			n = find(nid);
			while (n == -1 || n != -1) {
				if (n != -1) {
					deleteUser(nid);
				}
				else {
					cout << "record not found." << endl << endl;
					cout << "Reenter your ID:" << endl;
					cin >> nid;
					//x.find(id);
					deleteUser(nid);
				}
				break;
			}
			break;
		case 5:
			viewVaccinatedByAge();
			break;
		case 6:
			system("cls");
			viewAllStatistics();
			break;
		case 7:
			system("cls");
			DisplayWaitingList();
			break;
		case 8:
			system("cls");
			DoseBreakDown();

		default:
			break;
		}
		//system("cls");
		cout << "please enter y if you want to do another operation" << endl;
		cin >> check;
		system("cls");
	} while (check == 'y');

}

void admin::deleteAll() {
	Data.clear();
	while (!WaitingList.empty())
	{
		WaitingList.pop();
	}
}

void admin::viewAllUsers() {

	for (int i = 0; i < Data.size(); i++) {

		cout << "Name: " << Data[i].full_name << endl;
		cout << "National ID: " << Data[i].national_id << endl;
		cout << "Age: " << Data[i].age << endl;
		cout << "Gender: " << Data[i].gender << endl;
		cout << "Governorate: " << Data[i].governorate << endl;
		cout << "Vaccination Status: ";
		if (Data[i].first_dose == '1')
		{
			if (Data[i].second_dose == '1') {
				cout << "Second dose is done." << endl;
			}
			else {
				cout << "First dose is done and in the waiting list of the second dose." << endl;
			}
		}
		else {
			cout << "In the waiting list of the first dose." << endl;
		}
		cout << "-----------------------------------------------\n";
	}

}

void admin::counter_for_statictics(float& count_firstDose, float& count_vaccinated, float& countOfFemales) {
	for (int i = 0; i < Data.size(); i++) {
		if (Data.at(i).first_dose == '1')
		{
			if (Data.at(i).second_dose == '1')
			{
				count_vaccinated++;
			}
			else
				count_firstDose++;
		}
		if (Data.at(i).gender == 'f') {
			countOfFemales++;
		}
	}
}

void admin::viewAllStatistics()
{
	//float firstDose, seconddose, not_vaccinated                                                        
	//firstDose = float(s.counter());
	/*cout << endl<<count_firstDose << endl;*/
	system("cls");
	float count_firstDose = 0;
	float count_vaccinated = 0;
	float count_not_vaccinated = 0;
	float countOfFemales = 0;
	float countOfMales = 0;
	counter_for_statictics(count_firstDose, count_vaccinated, countOfFemales);
	count_not_vaccinated = (float(Data.size() - count_vaccinated - count_firstDose)) / Data.size() * 100;
	count_firstDose = (float(count_firstDose) / Data.size()) * 100;
	count_vaccinated = (float(count_vaccinated) / Data.size()) * 100;
	countOfMales = (float(Data.size() - countOfFemales)) / Data.size() * 100;
	countOfFemales = (float(countOfFemales) / Data.size()) * 100;

	cout << "perecentage of people who take first dose is: " << count_firstDose << endl;
	cout << "perecentage of people who take two doses is: " << count_vaccinated << endl;
	cout << "perecentage of people who not vaccinated is: " << count_not_vaccinated << endl;
	cout << "perecentage of females is: " << countOfFemales << endl;
	cout << "perecentage of males is: " << countOfMales << endl;
}

void admin::viewVaccinatedByAge()
{
	system("cls");
	sort(Data.begin(), Data.end(), [](const citizen & c1, const citizen & c2) {
		return (c1.age < c2.age);
		});
	for (int i = 0; i < Data.size(); i++) {
		if (Data.at(i).first_dose == '1' && Data.at(i).second_dose == '1') {
			cout << "Name: " << Data[i].full_name << endl;
			cout << "National ID: " << Data[i].national_id << endl;
			cout << "Age: " << Data[i].age << endl;
			cout << "Gender: " << Data[i].gender << endl;
			cout << "Governorate: " << Data[i].governorate << endl;
			cout << "Vaccination Status: ";
			cout << "Second dose is done." << endl;

			cout << "-----------------------------------------------\n";
		}
	}
}

void admin::DisplayWaitingList()
{
	queue<pair<string, string>>temp;
	temp = WaitingList;
	cout << "The size of temp queue is: ";
	cout << temp.size() << endl;
	int i = 1;
	while (!temp.empty())
	{
		cout << i << "-" << temp.front().first << "      " << temp.front().second << endl;
		i++;
		temp.pop();
	}

}

void admin::DoseBreakDown() {
	vector<citizen> ZeroDose, FirstDose, BothDoses;
	for (int i = 0; i < Data.size(); i++) {
		if (Data[i].first_dose == '0' && Data[i].second_dose == '0') {
			ZeroDose.push_back(Data[i]);
		}
		else if (Data[i].first_dose == '1' && Data[i].second_dose == '0') {
			FirstDose.push_back(Data[i]);
		}
		else if (Data[i].first_dose == '1' && Data[i].second_dose == '1') {
			BothDoses.push_back(Data[i]);
		}
	}
	cout << endl <<endl << "The people who got no vaccines: " << endl<<endl;
	for (int i = 0; i < ZeroDose.size(); i++) {
		cout << "Name: " << ZeroDose[i].full_name << endl;
		cout << "National ID: " << ZeroDose[i].national_id << endl;
		cout << "Age: " << ZeroDose[i].age << endl;
		cout << "Gender: " << ZeroDose[i].gender << endl;
		cout << "Governorate: " << ZeroDose[i].governorate << endl;
		cout << "Vaccination Status: ";
		cout << "In the waiting list of the first dose." << endl;
		cout << "-----------------------------------------------\n";
	}

	cout << endl << endl << "The people who got the first dose only: " << endl <<endl;
	for (int i = 0; i < FirstDose.size(); i++) {
		cout << "Name: " << FirstDose[i].full_name << endl;
		cout << "National ID: " << FirstDose[i].national_id << endl;
		cout << "Age: " << FirstDose[i].age << endl;
		cout << "Gender: " << FirstDose[i].gender << endl;
		cout << "Governorate: " << FirstDose[i].governorate << endl;
		cout << "Vaccination Status: ";
		cout << "First dose is done and in the waiting list of the second dose." << endl;
		cout << "-----------------------------------------------\n";
	}

	cout << endl <<endl << "The people who got both doses: " << endl << endl;
	for (int i = 0; i < BothDoses.size(); i++) {
		cout << "Name: " << BothDoses[i].full_name << endl;
		cout << "National ID: " << BothDoses[i].national_id << endl;
		cout << "Age: " << BothDoses[i].age << endl;
		cout << "Gender: " << BothDoses[i].gender << endl;
		cout << "Governorate: " << BothDoses[i].governorate << endl;
		cout << "Vaccination Status: ";
		cout << "Second dose is done." << endl;
		cout << "-----------------------------------------------\n";
	}
}