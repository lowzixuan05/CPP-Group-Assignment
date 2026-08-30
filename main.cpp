#include <iostream>
using namespace std;

//Login
void staffLogin();
void memberLogin();

//Main Menu
void staffMainMenu();
void memberMainMenu();

//Staff Modules
void staffMemberManagement();
void staff();
void staff();
void staff();
void staff();
void staff();
void staff();

//Member Modules
void member();
void member();
void member();
void member();
void member();
void memberBooking(int memberID);
void memberFeedbackMenu(int memberID);



int main()
{
    int memberID;
    int choice;

    cout << "Enter Member ID: ";
    cin >> memberID;
    
    do{
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
        case 1:memberBooking(memberID);break;
        case 2:memberFeedbackMenu(memberID);break;
        case 3:break;
        default:cout << "invalid";
        }
    } while (choice != 9);

    return 0;
}