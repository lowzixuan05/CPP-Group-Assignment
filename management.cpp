#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

const int MAX_MEMBERS = 100;

int memberIDs[MAX_MEMBERS];
string memberNames[MAX_MEMBERS];
string memberPasswords[MAX_MEMBERS];
char memberGenders[MAX_MEMBERS];
int memberAges[MAX_MEMBERS];
bool isMemberActive[MAX_MEMBERS] = { false };

int currentMemberCount = 0;
string staffUsername = "admin";
string staffpassword = "02zuikeai";

int loggedInMemberIndex = -1;
bool isStaffLoggedIn = false;


void memberMemberManagementMenu() {
	int memberMenuChoice = 0;

	do {
		cout << "\n-----------------------------------------\n";
		cout << "     CUSTOMER / MEMBER MENU\n";
		cout << "-----------------------------------------\n";
		cout << "1. Register\n";
		cout << "2. Login\n";
		cout << "3. Logout\n";
		cout << "4. View Profile\n";
		cout << "5. Edit Profile\n";
		cout << "6. Change Password\n";
		cout << "7. Return to Main Menu\n";
		cout << "Choice (1-7): ";
		cin >> memberMenuChoice;

		switch (memberMenuChoice) {

		case 1: {

			cout << "\n--- Member Registration ---\n";
			if (currentMemberCount >= MAX_MEMBERS) {
				cout << "Validation Error: System reached maximum member capacity!\n";
			}
			else {
				int newID;

				string newName, newPass;
				char newGender;
				int newAge;

				cout << "Enter Member ID (Numbers only): ";
				cin >> newID;

				bool idExist = false;
				for (int i = 0;i < MAX_MEMBERS;i++) {
					if (isMemberActive[i] && memberIDs[i] == newID) {

						idExist = true;
						break;
					}


				}
				if (idExist) {
					cout << "Validation Error: Member ID already exists!\n";

				}
				else {
					cout << "Enter Password: ";
					cin >> newPass;

					cout << "Enter Name: ";
					cin.ignore();
					getline(cin, newName);

					cout << "Enter Gender (M/F): ";
					cin >> newGender;

					cout << "Enter Age: ";
					cin >> newAge;

					if (newAge <= 0 || newAge >= 100) {
						cout << "Validation Error: Invalid age entered!\n";
					}
					else {
						for (int i = 0;i < MAX_MEMBERS;i++) {
							if (!isMemberActive[i]) {
								memberIDs[i] = newID;
								memberPasswords[i] = newPass;
								memberNames[i] = newName;
								memberGenders[i] = newGender;
								memberAges[i] = newAge;
								isMemberActive[i] = true;
								currentMemberCount++;
								cout << "Registration successful! You can now login.\n";
								break;
							}
						}
					}
				}
			}
			break;
		}
		case 2: {
			cout << "\n--- Member Login ---\n";
			if (loggedInMemberIndex != -1) {
				cout << "Validation Error: Already logged in as " << memberNames[loggedInMemberIndex] << "!\n";
			}
			else {
				int inputID;
				string inputPass;

				cout << "Enter Member ID: ";
				cin >> inputID;
				cout << "Enter Password: ";
				cin >> inputPass;

				bool found = false;

				for (int i = 0;i < MAX_MEMBERS;i++) {
					if (isMemberActive[i] && memberIDs[i] == inputID && memberPasswords[i] == inputPass) {
						loggedInMemberIndex = i;
						found = true;
						cout << "Login successful! Welcome, " << memberNames[i] << ".\n";
						break;
					}
				}

				if (!found) {
					cout << "Validation Error: Invalid Member ID or Password!\n";
				}
			}
			break;

		}
		case 3: {
			cout << "\n--- Member Logout ---\n";
			if (loggedInMemberIndex == -1) {
				cout << "Validation Error: No member is currently logged in!\n";
			}
			else {
				cout << "Logged out successfully from " << memberNames[loggedInMemberIndex] << ".\n";
				loggedInMemberIndex = -1;
			}
			break;
		}
		case 4: {
			cout << "\n--- Member Profile ---\n";
			if (loggedInMemberIndex == -1) {
				cout << "Validation Error: Please login first to view your profile!\n";
			}
			else {
				cout << "ID       : " << memberIDs[loggedInMemberIndex] << endl;
				cout << "Name     : " << memberNames[loggedInMemberIndex] << endl;
				cout << "Gender   : " << memberGenders[loggedInMemberIndex] << endl;
				cout << "Age      : " << memberAges[loggedInMemberIndex] << endl;
			}
			break;
		}
		case 5: {

			cout << "\n--- Edit Profile ---\n";
			if (loggedInMemberIndex == -1) {
				cout << "Validation Error: Please login first to edit your profile!\n";
			}
			else {
				cout << "Enter New Name: ";
				cin.ignore();
				getline(cin, memberNames[loggedInMemberIndex]);

				cout << "Enter New Gender (M/F): ";
				cin >> memberGenders[loggedInMemberIndex];

				cout << "Enter New Age: ";
				cin >> memberAges[loggedInMemberIndex];

				cout << "Profile updated successfully!\n";
			}
			break;
		}
		case 6: {
			cout << "\n--- Change Password ---\n";
			if (loggedInMemberIndex == -1) {
				cout << "Validation Error: Please login first to change password!\n";
			}
			else {
				string oldPass, newPass;
				cout << "Enter Current Password: ";
				cin >> oldPass;

				if (oldPass == memberPasswords[loggedInMemberIndex])
				{
					cout << "Enter New Password: ";
					cin >> newPass;
					memberPasswords[loggedInMemberIndex] = newPass;
					cout << "Password changed successfully!\n";
				}
				else {

					cout << "Validation Error: Incorrect current password!\n";
				}
			}
			break;
		}
		case 7:
			cout << "Returning to Main Menu...\n";
			break;

		default:
			cout << "Validation Error: Invalid choice! Try again.\n";
		}
	} while (memberMenuChoice != 7);
}



void staffMemberManagementMenu() {
	int staffMenuChoice = 0;
	do {
		cout << "\n-----------------------------------------\n";
		cout << "     STAFF / ADMIN MANAGEMENT MENU\n";
		cout << "-----------------------------------------\n";
		cout << "1. Login\n";
		cout << "2. Logout\n";
		cout << "3. Add New Member\n";
		cout << "4. View Member Profile (Single)\n";
		cout << "5. View All Members\n";
		cout << "6. Edit Member Profile\n";
		cout << "7. Delete Member Profile\n";
		cout << "8. Search Member Profile\n";
		cout << "9. Return to Main Menu\n";
		cout << "Choice (1-9): ";
		cin >> staffMenuChoice;

		switch (staffMenuChoice) {

		case 1: {
			cout << "\n--- Staff Login ---\n";
			if (isStaffLoggedIn) {
				cout << "Validation Error: Staff is already logged in!\n";
			}
			else {
				string user, pass;
				cout << "Enter Staff Username: ";
				cin >> user;
				cout << "Enter Staff Password: ";
				cin >> pass;

				if (user == staffUsername && pass == staffpassword)
				{
					isStaffLoggedIn = true;
					cout << "Staff Login Successful!\n";
				}
				else {
					cout << "Validation Error: Invalid Staff Username or Password!\n";
				}
			}
			break;
		}

		case 2: {
			cout << "\n--- Staff Logout ---\n";
			if (!isStaffLoggedIn) {
				cout << "Validation Error: Staff is not logged in!\n";
			}
			else {
				isStaffLoggedIn = false;
				cout << "Staff Logged Out successful! \n";

			}
			break;
		}

		case 3: {
			cout << "\n--- Staff: Add New Member ---\n";

			if (!isStaffLoggedIn) {
				cout << "Validation Access Error: Please login as Staff first!\n";
			}
			else if (currentMemberCount > MAX_MEMBERS) {
				cout << "Validation Error: System capacity full!\n";
			}
			else {
				int newID;
				string newName, newPass;
				char newGender;
				int newAge;

				cout << "Enter Member ID: ";
				cin >> newID;

				bool idExists = false;
				for (int i = 0; i < MAX_MEMBERS; i++) {
					if (isMemberActive[i] && memberIDs[i] == newID) {
						idExists = true;
						break;
					}
				}

				if (idExists) {
					cout << "Validation Error: Member ID already exists!\n";
				}
				else {
					cout << "Enter Password: ";
					cin >> newPass;

					cout << "Enter Name: ";
					cin.ignore();
					getline(cin, newName);

					cout << "Enter Gender (M/F): ";
					cin >> newGender;

					cout << "Enter Age: ";
					cin >> newAge;


					for (int i = 0;i < MAX_MEMBERS;i++) {
						if (!isMemberActive[i]) {
							memberIDs[i] = newID;
							memberPasswords[i] = newPass;
							memberNames[i] = newName;
							memberGenders[i] = newGender;
							memberAges[i] = newAge;
							isMemberActive[i] = true;
							currentMemberCount++;
							cout << "Registration successful! You can now login.\n";
							break;
						}
					}
				}
			}

			break;
		}
		case 4: {
			cout << "\n--- Staff: View Single Member Profile ---\n";
			if (!isStaffLoggedIn) {
				cout << "Validation Access Error: Please login as Staff first!\n";
			}
			else {
				int targetID;
				cout << "Enter Member ID to View: ";
				cin >> targetID;

				bool found = false;

				for (int i = 0; i < MAX_MEMBERS; i++) {
					if (isMemberActive[i] && memberIDs[i] == targetID) {
						cout << "-----------------------------------------\n";
						cout << "ID       : " << memberIDs[i] << endl;
						cout << "Name     : " << memberNames[i] << endl;
						cout << "Gender   : " << memberGenders[i] << endl;
						cout << "Age      : " << memberAges[i] << endl;
						cout << "-----------------------------------------\n";
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Validation Error: Member ID not found!\n";
				}
			}
			break;
		}
		case 5: {
			cout << "\n--- Staff: View All Members ---\n";
			if (!isStaffLoggedIn) {
				cout << "Validation Access Error: Please login as Staff first!\n";
			}
			else if (currentMemberCount == 0) {
				cout << "No members registered in the system.\n";
			}
			else {
				cout << left << setw(10) << "ID"
					<< setw(20) << "Name"
					<< setw(10) << "Gender"
					<< setw(8) << "Age" << endl;
				cout << "--------------------------------------------------\n";
				for (int i = 0; i < MAX_MEMBERS; i++) {
					if (isMemberActive[i]) {
						cout << left << setw(10) << memberIDs[i]
							<< setw(20) << memberNames[i]
							<< setw(10) << memberGenders[i]
							<< setw(8) << memberAges[i] << endl;
					}
				}
			}
			break;
		}

		case 6: {

			cout << "\n--- Staff: Edit Member Profile ---\n";
			if (!isStaffLoggedIn) {
				cout << "Validation Access Error: Please login as Staff first!\n";
			}
			else {
				int targetID;
				cout << "Enter Member ID to Edit: ";
				cin >> targetID;

				bool found = false;
				for (int i = 0; i < MAX_MEMBERS; i++) {
					if (isMemberActive[i] && memberIDs[i] == targetID) {
						cout << "Editing profile for " << memberNames[i] << endl;

						cout << "Enter New Name: ";
						cin.ignore();
						getline(cin, memberNames[i]);

						cout << "Enter New Gender (M/F): ";
						cin >> memberGenders[i];

						cout << "Enter New Age: ";
						cin >> memberAges[i];

						cout << "Member profile updated successfully!\n";
						found = true;
						break;

					}
				}
				if (!found) {
					cout << "Validation Error: Member ID not found!\n";
				}
			}
			break;
		}
		case 7:
		{
			cout << "\n--- Staff: Delete Member Profile ---\n";
			if (!isStaffLoggedIn)
			{
				cout << "Validation Access Error: Please login as Staff first!\n";
			}

			else
			{
				int targetID;
				cout << "Enter Member ID to Delete: ";
				cin >> targetID;

				bool found = false;
				for (int i = 0; i < MAX_MEMBERS; i++) {
					if (isMemberActive[i] && memberIDs[i] == targetID) {
						isMemberActive[i] = false;
						currentMemberCount--;

						if (loggedInMemberIndex == i)
						{
							loggedInMemberIndex = -1;
						}
						cout << "Member deleted successfully!\n";
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Validation Error: Member ID not found!\n";
				}
			}
			break;
		}
		case 8: {
			cout << "\n--- Staff: Search Member Profile ---\n";
			if (!isStaffLoggedIn) {
				cout << "Validation Access Error: Please login as Staff first!\n";
			}
			else {
				int targetID;
				cout << "Enter Member ID to Search: ";
				cin >> targetID;

				bool found = false;
				for (int i = 0; i < MAX_MEMBERS; i++) {
					if (isMemberActive[i] && memberIDs[i] == targetID) {
						cout << "\n[ Search Result Found ]\n";
						cout << "ID       : " << memberIDs[i] << endl;
						cout << "Name     : " << memberNames[i] << endl;
						cout << "Gender   : " << memberGenders[i] << endl;
						cout << "Age      : " << memberAges[i] << endl;
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Search Result: No member found with ID " << targetID << endl;
				}
			}
			break;
		}
		case 9: {
			cout << "Returning to Main Menu...\n";
			break;
		}

		default: {
			cout << "Validation Error: Invalid choice! Try again.\n";
			break;
		}

		}

	} while (staffMenuChoice != 9);
}
