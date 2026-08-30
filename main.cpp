#include <iostream>
using namespace std;

void memberBooking(int memberID);
void memberFeedbackMenu(int memberID);

int main()
{
    int memberID;
    int choice;

    cout << "Enter Member ID: ";
    cin >> memberID;
    
    do{
        cout << "menu test\n1. booking\n2. feedback\n3. exit program\nchoice: ";
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