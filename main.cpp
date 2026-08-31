#include <iostream>
using namespace std;

//Main Menu
void staffMainMenu();
void memberMainMenu();

//Staff Modules
void staffMemberManagementMenu();
void staffBookingMenu();
void staffFeedbackMenu();


//Member Modules
extern void memberMemberManagementMenu();
extern void memberBookingMenu(int memberID);
extern void memberFeedbackMenu(int memberID);




int main()
{
    int choice;

    do {
       
        cout << "\n=========================================\n";
        cout << "       GYM MANAGEMENT SYSTEM MAIN MENU    \n";
        cout << "=========================================\n";
        cout << "1. Member\n";
        cout << "2. Staff\n";
        cout << "3. Exit System\n";
        cout << "-----------------------------------------\n";
        cout << "Choose who is logging in (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:memberMainMenu();break;
        case 2:staffMainMenu();break;
        case 3:break;
        default:cout << "Invalid Selection";
        }
    } while (choice != 3);

    cout << "Exiting..." << endl;
}



void staffMainMenu() {
    int menuChoice;
    do {
        cout << R"(
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__\__\__\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\     \__\__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \              \__\  \__\  \__\  \__\  \  \
 \__\  \__\  \__\  \___         Welcome       \  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \___                 \  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__          _____\  \__\  \__\  \__\  \  \
 \__\  \__\  \__\  \__\  \__\  \__    __\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__
            )";
        cout << "\nWelcome to Member Menu\n";
        cout << "1. Member Management\n";
        cout << "2. Booking\n";
        cout << "3. Appointment\n";
        cout << "4. Advertisement\n";
        cout << "5. Billing and Payment Processing\n";
        cout << "6. Reporting and Statistic\n";
        cout << "7. Feedback\n";
        cout << "8. Back\n";
        cout << "Enter your Choice (1-8): ";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:memberMemberManagementMenu();
            break;
        case 2:
            int memberID;
            cout << "Member ID: ";
            cin >> memberID;
            memberBookingMenu(memberID);
            break;
        case 3:
        case 8:break;
        default:cout << "Invalid Choice! Try Again!";
        }

    } while (menuChoice != 8);

    cout << " Back to previous menu...";
    return;
}
void memberMainMenu() 
{
    int menuChoice;
    do {
        cout << R"(
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\        \__\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\              \__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\                    \__\  \  \__\  \__\  \
 \__\  \__\  \__\  \__\         Welcome          \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__                     \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__               \__\  \__\  \__\  \__\
 \__\  \__\  \__\  \__\  \__\  \__         \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\
            )";
        cout << "\nWelcome to Member Menu\n";
        cout << "1. Member Management\n";
        cout << "2. Booking\n";
        cout << "3. Appointment\n";
        cout << "4. Advertisement\n";
        cout << "5. Billing and Payment Processing\n";
        cout << "6. Reporting and Statistic\n";
        cout << "7. Feedback\n";
        cout << "8. Back\n";
        cout << "Enter your Choice (1-8): ";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:memberMemberManagementMenu();
            break;
        case 2:
            int memberID;
            cout << "Member ID: ";
            cin >> memberID;
            memberBookingMenu(memberID);
            break;
        case 3:
        case 8:break;
        default:cout << "Invalid Choice! Try Again!";
        }

    } while (menuChoice != 8);
    
    cout << " Back to previous menu...";
    return;
}