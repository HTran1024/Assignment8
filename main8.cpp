#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "Patient.h"
#include "Tree.h"

using namespace std;

void printMenu()
{
	cout << "-----------------PATIENT RECORDS MENU----------------- \n"
			"N - Enter and check in a new patient. \n"
			"R - Check in a returning patient. \n"
			"O - Input procedure information for checked in patients then check that patient out. \n"
			"I - Print all information about a particular patient. \n"
			"P - Print general info of all checked in patients. \n"
			"Q - Quit this sesion. \n"
			"------------------------------------------------------ \n"
			"> ";
}

int main()
{
	Patient patient;
	Patient foundPatient;
	Patient patientInfo[20];
	Tree <Patient> patientRecord;
	Tree <Patient> currentPatientRecord;

	int totalCount = 0;	// Tracks the amount of patients int he patientRecord object.
	int curCount = 0;	// Tracks the amount of patients in the currentPatientRecord object.
	Date today;
	int tMonth;
	int tDay;
	int tYear;
	char tempID[33];
	char tempFirstName[20];
	char tempLastName[20];
	char tempfName[20];
	char templName[20];
	int cLength;
	int birthMonth;
	int birthDay;
	int birthYear;
	char birthyear[5];
	int tempPrimaryDoctorID;
	Date tempDate;
	Date tempBirthDate;
	char IDsearch[33];
	char input;
	int currentMonth;
	int currentDay;
	int currentYear;
	Date tempCurrentDate;
	int procedureID;
	int providerID;

	ifstream inFile;
	inFile.open("CurrentPatients.dat", ios::binary);
	if (inFile.is_open())
	{
		while (inFile.read(reinterpret_cast<char*>(&patientRecord), sizeof(Patient)))
		{
			totalCount++;
		}
	}
	inFile.close();

	cout << "Enter in today's date (MM DD YYYY): ";
	cin >> tMonth;
	cin >> tDay;
	cin >> tYear;
	today.setDate(tMonth, tDay, tYear);

	cout << "Hello! Todays date is: " << today << " \n"
		"What would you like to do to this session? \n"
		"Input one of the options below: \n";
	char menuChoice;
	bool quit = false;

	do 
	{
		printMenu();
		cin >> menuChoice;
		menuChoice = toupper(menuChoice);
		switch (menuChoice)
		{
		case 'N':
			{
				cout << "Type in the patient's first name: ";
				cin >> tempfName;
				cLength = strlen(tempfName);
				if (cLength >= 15)	// If the first name is longer than 15 characters, shorten it to 14 characters.
				{
					for (int i = 0; i < 14; i++)
					{
						tempFirstName[i] = tempfName[i];
					}
					tempFirstName[14] = '\0';
				}
				else
				{
					for (int i = 0; i < cLength; i++)
					{
						tempFirstName[i] = tempfName[i];
					}
					tempFirstName[cLength] = '\0';
				}

				cout << "Type in the patient's last name: ";
				cin >> templName;
				cLength = strlen(templName);
				if (cLength >= 15)	// If the last name is longer than 15 characters, shorten it to 14 characters.
				{
					for (int i = 0; i < cLength; i++)
					{
						tempLastName[i] = templName[i];
					}
					tempLastName[14] = '\0';
				}
				else
				{
					for (int i = 0; i < cLength; i++)
					{
						tempLastName[i] = templName[i];
					}
					tempLastName[cLength] = '\0';
				}

				cout << "Type in the patient's date of birth (Use format mm dd yyyy): " << endl;
				cin >> birthMonth;
				cin >> birthDay;
				cin >> birthyear;

				birthYear = stoi(birthyear);	// get birthyear(int) by using stoi which converts birthYear(char) into an int.
				tempDate.setDate(birthMonth, birthDay, birthYear);
				tempBirthDate = tempDate;

				strcpy_s(tempID, tempLastName);
				strcat_s(tempID, tempFirstName);
				strcat_s(tempID, birthyear);

				cout << "Type in the primary doctor's ID: " << endl;
				cin >> tempPrimaryDoctorID;
				
				patient.setFirstName(tempFirstName).setLastName(tempLastName).setID(tempID).setBirthDate(tempBirthDate).setPrimaryDoctorID(tempPrimaryDoctorID);
				if (currentPatientRecord.insert(patient))
				{
					cout << "Patient information sucessfully stored for current session." << endl;
					cout << "Patient ID is: " << tempID << endl;
					//curCount++;
					if (patientRecord.insert(patient))
					{
						cout << "Patient information successfully strored in the patient record as well." << endl;
						totalCount++;
					}
					else
					{
						cout << "Patient information could not be stored in the patient record." << endl;
					}
				}
				else
				{
					cout << "Patient information could not be stored for current session." << endl;
				}
				break;
			}
		case 'R':
			{
				if (patientRecord.isEmpty() == true)	// If the program has just started meaning no patient information is in the patientRecord object.
				{
					cout << "The Patient Record is empty" << endl;
				}
				else
				{
					bool found = false;		// Used for retrying purposes later on.
					do
					{
						cout << "Please enter the ID of the patient that is checking in: " << endl;
						cin >> IDsearch;
						patient.setID(IDsearch);

						if (patientRecord.retrieve(patient, foundPatient))
						{
							currentPatientRecord.insert(foundPatient);
							cout << "Patient checked in for current session." << endl;
							curCount++;
							found = true;
						}
						else
						{
							found = false;
						}

						if (found != true)
						{
							cout << "Your inputted ID is not found. Would you like to input again? (y/n): ";
							cin >> input;
							input = tolower(input);
							if (input == 'n')
							{
								found = true;
							}
						}
					} while (found != true);
				}
				break;
			}
		case 'O':
			{
				if (currentPatientRecord.isEmpty() == true)
				{
					cout << "No patients are checked in." << endl;
				}
				else
				{
					bool exit = false;
					do
					{
						cout << "Enter in the patient's ID (Note: Make sure the patient is checked in): " << endl;
						cin >> IDsearch;
						patient.setID(IDsearch);
						if (currentPatientRecord.retrieve(patient, foundPatient))
						{
							cout << "Enter the procedure date (Use format mm dd yyyy): ";
							cin >> currentMonth;
							cin >> currentDay;
							cin >> currentYear;
							tempDate.setDate(currentMonth, currentDay, currentYear);
							tempCurrentDate = tempDate;

							cout << "Enter Procedure ID: ";
							cin >> procedureID;

							cout << "Enter Provider ID: ";
							cin >> providerID;

							foundPatient.enterProcedure(tempCurrentDate, procedureID, providerID);
							patientRecord.deleteInfo(patient);
							currentPatientRecord.deleteInfo(patient);

							if (patientRecord.insert(foundPatient))
							{
								patientInfo[totalCount] = foundPatient;
								totalCount++;
								cout << "Procedure information successfully strored in the patient record." << endl;
							}
							else
							{
								cout << "Procedure information could not be stored in the patient record." << endl;
							}
							
							exit = true;
						}
						else
						{
							exit = false;
						}

						if (exit != true)
						{
							cout << "Your inputted ID is not found. Would you like to input again? (y/n): ";
							cin >> input;
							input = tolower(input);
							if (input == 'n')
							{
								exit = true;
							}
						}
					} while (exit != true);
				}
				break;
			}
		case 'I':
			{
				if (patientRecord.isEmpty() == true)
				{
					cout << "Patient Record is empty." << endl;
				}
				else
				{
					cout << "Type in the Patient's ID: ";
					cin >> IDsearch;
					patient.setID(IDsearch);
					if (patientRecord.retrieve(patient, foundPatient))
					{
						cout << "Patient found!" << endl;
						cout << "Name: " << foundPatient.getFirstName() << " " << foundPatient.getLastName() << endl;
						cout << "Patient ID: " << foundPatient.getID() << endl;
						cout << "Primary Doctor ID: " << foundPatient.getPrimaryDoctorID() << endl;
						foundPatient.printAllProcedures();
					}
				}
				break;
			}
		case 'P':
			{
				cout << "General info of all currently checked in patients:" << endl << endl;
				currentPatientRecord.print(cout, preorder);
				break;
			}
		case 'Q':
			{
				if (currentPatientRecord.isEmpty() != true)
				{
					cout << "You still have patients checked in. \n"
						"The patients that are still checked in are: \n";
					patientRecord.print(cout, preorder);
					cout << endl << "Please check them out before exitting this program." << endl << endl;
				}
				else
				{
					cout << "Good Bye!" << endl;
					quit = true;
				}
				break;
			}
		default:
			{
				cout << "This input is invalid. Enter one of the choices seen in the menu." << endl;
				break;
			}
		}
	}while (quit != true);

	ofstream outFile;
	outFile.open("CurrentPatients.dat", ios::binary);
	for (int i = 0; i < totalCount; i++)
	{
		outFile.write(reinterpret_cast<char*>(&patientRecord), sizeof(Patient));
	}

	return 0;
}
