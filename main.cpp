#include <iostream>
using namespace std;

//Main Menu
void staffMainMenu();
void memberMainMenu();

//Staff Modules
extern void staffMemberManagementMenu();
extern void staffBookingMenu();
extern void staffFeedbackMenu();
extern void advertisementModule();
extern void reporting();
void staffPortal();

//Member Modules
extern void memberMemberManagementMenu();
extern void memberBookingMenu(int memberID);
extern void appointmentModule();
extern void memberFeedbackMenu(int memberID);
extern void billingStart();
void memberPortal();


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
 \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\  \  \  \__\  \__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \              \  \__\__\  \__\  \__\  \  \
 \__\  \__\  \__\  \___         Welcome       \  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \___                 \__\__\  \__\  \__\  \__\ 
\  \__\  \__\  \__\  \__\  \__            \  \  \  \__\  \  \  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__    __\  \__\  \__\  \__\  \__\  \__
__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  
\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \
 \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__\  \__
            )";
        cout << "\nWelcome to Staff Menu\n";
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
        case 1:staffMemberManagementMenu();
            break;
        case 2:staffBookingMenu();
            break;
        case 3:appointmentModule();
            break;
        case 4:advertisementModule();
            break;
        case 5:staffPortal();
            break;
        case 6:reporting();
            break;
        case 7:staffFeedbackMenu();
            break;
        case 8:break;
        default:cout << "Invalid Choice! Try Again!";
        }

    } while (menuChoice != 8);

    cout << " Back to previous menu...";
    return;
}

//Member Main Menu
void memberMainMenu() 
{
    int memberID = 0;
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
        cout << "4. Billing and Payment Processing\n";
        cout << "5. Feedback\n";
        cout << "6. Back\n";
        cout << "Enter your Choice (1-7): ";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:memberMemberManagementMenu();
            break;
        case 2:memberBookingMenu(memberID);
            break;
        case 3:appointmentModule();
            break;
        case 4:memberPortal();
            break;
        case 5: memberFeedbackMenu(memberID);
            break;
        case 6:break;
        default:cout << "Invalid Choice! Try Again!";
        }

    } while (menuChoice != 6);
    
    cout << " Back to previous menu...";
    return;
}