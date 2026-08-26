#include <iostream>
using namespace std;

void memberBooking(int memberID);

int main()
{
    int memberID;

    cout << "Enter Member ID: ";
    cin >> memberID;

    memberBooking(memberID);

    return 0;
}