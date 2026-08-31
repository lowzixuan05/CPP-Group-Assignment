#include <iostream>
using namespace std;

//Login
void staffLogin();
void memberLogin();

//Main Menu
void staffMainMenu();
void memberMainMenu();

//Staff Modules
void staffMemberManagementMenu();
void staffBookingMenu();
void staffFeedbackMenu();


//Member Modules
void memberMemberManagementMenu();
void memberBookingMenu();
void memberFeedbackMenu();




int main()
{
    int memberID;
    int choice;

    do {
        cout << "\n=========================================\n";
        cout << "       GYM MANAGEMENT SYSTEM MAIN MENU    \n";
        cout << "=========================================\n";
        cout << "1. Customer / Member Management\n";
        cout << "2. Staff / Admin Management\n";
        cout << "3. Exit System\n";
        cout << "-----------------------------------------\n";
        cout << "Choose who is logging in (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:memberLogin();break;
        case 2:staffLogin();break;
        case 3:break;
        default:cout << "Invalid Selection";
        }
    } while (choice != 3);

    cout << "Exiting..." << endl;
}

void staffLogin()
    {
        cout << "\nEnter Your Staff ID : ";
        cout << "\nEnter Your Password : ";
        staffMainMenu();
    }

void memberLogin() {
    memberMainMenu();
}

void staffMainMenu() { cout << "\nWelcome to Staff Menu\n"; }
void memberMainMenu() { cout << "\nWelcome to Member Menu\n"; }
