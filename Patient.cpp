#include<string>
#include"Patient.h"
using namespace std;

Patient & Patient::setID(const char * id)
{
	strcpy_s(ID, id);
	return(*this);
}

Patient & Patient::setFirstName(const char * fname)
{
	strcpy_s(firstName, fname);
	return(*this);
}

Patient & Patient::setLastName(const char * lname)
{
	strcpy_s(lastName, lname);
	return (*this);
}

Patient & Patient::setBirthDate(Date birthday)
{
	birthdate = birthday;
	return(*this);
}

Patient & Patient::setPrimaryDoctorID(int PdID)
{
	primaryDoctorID = PdID;
	return(*this);
}

const char * Patient::getID()
{
	return ID;
}

const char * Patient::getFirstName()
{
	return firstName;
}

const char * Patient::getLastName()
{
	return lastName;
}

Date Patient::getBirthDate()
{
	return birthdate;
}

int Patient::getPrimaryDoctorID()
{
	return primaryDoctorID;
}

bool Patient::enterProcedure(Date procedureDate, int procID, int provID)
{
	record[currentCountOfProcedures].dateOfProcedure = procedureDate;
	record[currentCountOfProcedures].procedureID = procID;
	record[currentCountOfProcedures].procedureProviderID = provID;
	currentCountOfProcedures++;
	return true;
}

void Patient::printAllProcedures()
{
	for (int i = 0; i < currentCountOfProcedures; i++)
	{
		cout << "Procedure Date: " << record[i].dateOfProcedure << endl;
		cout << "Procedure ID: " << record[i].procedureID << endl;
		cout << "Procedure Provider ID: " << record[i].procedureProviderID << endl << endl;
	}
}

void Patient::printGeneral()
{
	cout << "PatientID: " << ID << endl;
	cout << "Name: " << firstName << " " << lastName << endl;
	cout << "Primary Doctor ID: " << primaryDoctorID << endl << endl;
}

bool Patient::operator<(const Patient & right) const
{
	return (strcmp(ID, right.ID) < 0);
}

bool Patient::operator>(const Patient & right) const
{
	return (strcmp(ID, right.ID) > 0);
}

bool Patient::operator==(const Patient & right) const
{
	return (strcmp(ID, right.ID) == 0);
}

ostream & operator<<(ostream & out, Patient somebody)
{
	out << "Name: " << somebody.getFirstName() << " " << somebody.getLastName() << endl;
	out << "PatientID: " << somebody.getID() << endl;
	out << "Primary Doctor ID: " << somebody.getPrimaryDoctorID() << endl;
	return out;
}