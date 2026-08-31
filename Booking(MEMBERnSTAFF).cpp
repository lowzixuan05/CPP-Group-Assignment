#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// ==============================
// DATA STRUCTURES & SAPMLE DATA
// ==============================

const int MAX_SERVICES = 100;
int serviceIDs[MAX_SERVICES]={101,102,103,104};

string serviceName[MAX_SERVICES]=
{
    "Personal Training",
    "Yoga Class",
    "Private Gym Coach",
    "Boxing Class"
};
string category[MAX_SERVICES]=
{
    "Session",
    "Class",
    "Session",
    "Class"
};
double price[MAX_SERVICES] =
{
    20.00,
    30.00,
    100.00,
    40.00
};

int serviceCount = 4;

const int MAX_BOOKINGS = 100;

int bookingIDs[MAX_BOOKINGS];
int bookingMemberIDs[MAX_BOOKINGS];
int bookingServiceIDs[MAX_BOOKINGS];
string bookingDates[MAX_BOOKINGS];
string bookingStatus[MAX_BOOKINGS];

int bookingCount = 0;

// ==============================
// STAFF: ADD SERVICE
// ==============================

void staffAddService()
{
    if (serviceCount >= MAX_SERVICES)
    {
        cout << "\nCannot add more services. System is full.\n";
        return;
    }

    int newID;
    string newName, newCategory;
    double newPrice;

    cout << "\n--- Staff: Add Service ---\n";
    cout << "Enter Service ID: ";
    cin >> newID;

    bool idExists = false;
    for (int i = 0; i < serviceCount; i++)
    {
        if (serviceIDs[i] == newID)
        {
            idExists = true;
            break;
        }
    }

    if (idExists)
    {
        cout << "Validation Error: Service ID already exists!\n";
        return;
    }

    cout << "Enter Service Name: ";
    cin.ignore();
    getline(cin, newName);

    cout << "Enter Category: ";
    getline(cin, newCategory);

    cout << "Enter Price: RM ";
    cin >> newPrice;

    if (newPrice < 0)
    {
        cout << "Validation Error: Price cannot be negative!\n";
        return;
    }

    serviceIDs[serviceCount] = newID;
    serviceName[serviceCount] = newName;
    category[serviceCount] = newCategory;
    price[serviceCount] = newPrice;

    serviceCount++;

    cout << "Service added successfully!\n";
}


// ==============================
// STAFF: DELETE SERVICE
// ==============================

void staffDeleteService()
{
    int targetID;

    cout << "\n--- Staff: Delete Service ---\n";
    cout << "Enter Service ID to delete: ";
    cin >> targetID;

    int targetIndex = -1;

    for (int i = 0; i < serviceCount; i++)
    {
        if (serviceIDs[i] == targetID)
        {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1)
    {
        cout << "Validation Error: Service ID not found!\n";
        return;
    }

    // Shift all later elements one position left to fill the gap
    for (int i = targetIndex; i < serviceCount - 1; i++)
    {
        serviceIDs[i] = serviceIDs[i + 1];
        serviceName[i] = serviceName[i + 1];
        category[i] = category[i + 1];
        price[i] = price[i + 1];
    }

    serviceCount--;

    cout << "Service deleted successfully!\n";
}


// ==============================
// STAFF: EDIT SERVICE
// ==============================

void staffEditService()
{
    int targetID;

    cout << "\n--- Staff: Edit Service ---\n";
    cout << "Enter Service ID to edit: ";
    cin >> targetID;

    for (int i = 0; i < serviceCount; i++)
    {
        if (serviceIDs[i] == targetID)
        {
            cout << "Enter New Service Name: ";
            cin.ignore();
            getline(cin, serviceName[i]);

            cout << "Enter New Category: ";
            getline(cin, category[i]);

            cout << "Enter New Price: RM ";
            cin >> price[i];

            cout << "Service updated successfully!\n";
            return;
        }
    }

    cout << "Validation Error: Service ID not found!\n";
}


// ==============================
// VIEW SERVICES
// ==============================

void viewServices()
{
    cout << "\n===== AVAILABLE SERVICES =====\n";

    for (int i = 0; i < serviceCount; i++)
    {
        cout << "Service ID: " << serviceIDs[i] << endl;
        cout << "Service: " << serviceName[i] << endl;
        cout << "Category: " << category[i] << endl;
        cout << "Price: RM " << price[i] << endl;
        cout << "-----------------------------\n";
    }
}


// ==============================
// SEARCH SERVICES
// ==============================

void searchServices()
{
    int searchID;
    int i;

    cout << "\nEnter Service ID to search: ";
    cin >> searchID;

    bool found = false;

    for (i = 0; i < serviceCount; i++)
    {
        if (serviceIDs[i] == searchID)
        {
            cout << "\nService Found!\n";
            cout << "Service ID: " << serviceIDs[i] << endl;
            cout << "Name: " << serviceName[i] << endl;
            cout << "Category: " << category[i] << endl;
            cout << "Price: RM " << price[i] << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Service not found.\n";
    }
}

// ==============================
// VALIDATE DATE FORMAT
// ==============================

bool validateDate(string date)
{
    // Check length: DD/MM/YYYY = 10 characters
    if (date.length() != 10)
    {
        cout << "Invalid date format. Use DD/MM/YYYY.\n";
        return false;
    }

    // Check slashes are in the right positions
    if (date[2] != '/' || date[5] != '/')
    {
        cout << "Invalid date format. Use DD/MM/YYYY.\n";
        return false;
    }

    // Check all other characters are digits
    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
        {
            continue;
        }
        if (date[i] < '0' || date[i] > '9')
        {
            cout << "Invalid date format. Use DD/MM/YYYY.\n";
            return false;
        }
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // Check month range
    if (month < 1 || month > 12)
    {
        cout << "Invalid month.\n";
        return false;
    }

    // Days in each month (index 0 unused)
    int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Leap year check for February
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeapYear)
    {
        daysInMonth[2] = 29;
    }

    // Check day range
    if (day < 1 || day > daysInMonth[month])
    {
        cout << "Invalid day for the given month.\n";
        return false;
    }

    // Reasonable year range
    if (year < 2024 || year > 2100)
    {
        cout << "Invalid year.\n";
        return false;
    }

    // ----- Reject past dates -----
    //time_t now = time(0);
    //tm localTime;
    //localtime_s(&localTime, &now);   // MSVC: (tm*, time_t*) — note the reversed arg order vs localtime()
    //int todayYear = localTime.tm_year + 1900;
    //int todayMonth = localTime.tm_mon + 1;
    //int todayDay = localTime.tm_mday;
    //int enteredDateValue = year * 10000 + month * 100 + day;
    //int todayDateValue = todayYear * 10000 + todayMonth * 100 + todayDay;
    //if (enteredDateValue < todayDateValue)
    //{
    //    cout << "Booking date cannot be in the past.\n";
    //    return false;
    //}

    return true;
}


// ==============================
// VALIDATE BOOKING
// ==============================

bool validateBooking(int memberID, int serviceID, string date)
{
    // Check whether service exists
    bool serviceExists = false;

    for (int i = 0; i < serviceCount; i++)
    {
        if (serviceIDs[i] == serviceID)
        {
            serviceExists = true;
            break;
        }
    }

    if (!serviceExists)
    {
        cout << "Invalid Service ID.\n";
        return false;
    }

    // Check whether member already booked this service
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingServiceIDs[i] == serviceID &&
            bookingDates[i] == date &&
            bookingStatus[i] == "Active")
        {
            cout << "You already have an active booking for this service.\n";
            return false;
        }
    }

    return true;
}


// ==============================
// ADD SINGLE BOOKING
// ==============================

void addSingleBooking(int memberID)
{
    if (bookingCount >= MAX_BOOKINGS)
    {
        cout << "\nBooking system is full. Cannot add more bookings.\n";
        return;
    }

    int serviceID;
    string date;

    viewServices();

    cout << "\nEnter Service ID: ";
    cin >> serviceID;

    cout << "Enter Booking Date (DD/MM/YYYY): ";
    cin >> date;
    
    if (!validateDate(date))
    {
        return;
    }

    if (!validateBooking(memberID, serviceID, date))
    {
        return;
    }

    bookingIDs[bookingCount] = 1001 + bookingCount;
    bookingServiceIDs[bookingCount] = serviceID;
    bookingDates[bookingCount] = date;
    bookingStatus[bookingCount] = "Active";

    cout << "\nBooking successful!\n";
    cout << "Booking ID: "
        << bookingIDs[bookingCount] << endl;

    bookingCount++;
}

// ==============================
// ADD MULTIPLE BOOKINGS
// ==============================

void addMultipleBookings(int memberID)
{
    int numBookings;

    cout << "\nHow many bookings would you like to make? ";
    cin >> numBookings;

    if (numBookings <= 0)
    {
        cout << "Invalid number of bookings.\n";
        return;
    }

    for (int n = 1; n <= numBookings; n++)
    {
        cout << "\n--- Booking " << n << " of " << numBookings << " ---\n";

        if (bookingCount >= MAX_BOOKINGS)
        {
            cout << "Booking system is full. Cannot add more bookings.\n";
            cout << "Stopped after " << (n - 1) << " successful booking(s).\n";
            return;
        }

        int serviceID;
        string date;

        viewServices();

        cout << "\nEnter Service ID: ";
        cin >> serviceID;

        cout << "Enter Booking Date (DD/MM/YYYY): ";
        cin >> date;

        if (!validateDate(date))
        {
            return;
        }

        if (!validateBooking(memberID, serviceID, date))
        {
            cout << "Skipping this booking.\n";
            continue;
        }

        bookingIDs[bookingCount] = 1001 + bookingCount;
        bookingMemberIDs[bookingCount] = memberID;
        bookingServiceIDs[bookingCount] = serviceID;
        bookingDates[bookingCount] = date;
        bookingStatus[bookingCount] = "Active";

        cout << "Booking successful! Booking ID: "
            << bookingIDs[bookingCount] << endl;

        bookingCount++;
    }

    cout << "\nFinished adding bookings.\n";
}

// ==============================
// VIEW BOOKING
// ==============================

void viewBooking(int memberID)
{
    bool found = false;

    cout << "\n===== MY BOOKINGS =====\n";

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingMemberIDs[i] == memberID)
        {
            cout << "Booking ID: "
                << bookingIDs[i] << endl;

            cout << "Service ID: "
                << bookingServiceIDs[i] << endl;

            cout << "Date: "
                << bookingDates[i] << endl;

            cout << "Status: "
                << bookingStatus[i] << endl;

            cout << "-----------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "You do not have any bookings.\n";
    }
}


// ==============================
// CANCEL BOOKING
// ==============================

void cancelBooking(int memberID)
{
    int bookingID;

    viewBooking(memberID);

    cout << "\nEnter Booking ID to cancel: ";
    cin >> bookingID;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingIDs[i] == bookingID &&
            bookingMemberIDs[i] == memberID)
        {
            if (bookingStatus[i] == "Cancelled")
            {
                cout << "Booking is already cancelled.\n";
                return;
            }

            bookingStatus[i] = "Cancelled";

            cout << "Booking cancelled successfully.\n";
            return;
        }
    }

    cout << "Booking not found.\n";
}


// ==============================
// EDIT BOOKING
// ==============================

void editBooking(int memberID)
{
    int bookingID;
    string newDate;

    viewBooking(memberID);

    cout << "\nEnter Booking ID to edit: ";
    cin >> bookingID;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingIDs[i] == bookingID &&
            bookingMemberIDs[i] == memberID)
        {
            if (bookingStatus[i] == "Cancelled")
            {
                cout << "Cannot edit a cancelled booking.\n";
                return;
            }

            cout << "Enter new booking date(DD/MM/YYYY): ";
            cin >> newDate;

            bookingDates[i] = newDate;

            cout << "Booking updated successfully.\n";
            return;
        }
    }

    cout << "Booking not found.\n";
}


// ==============================
// GENERATE CONFIRMATION SLIP
// ==============================

void generateBookingConfirmationSlip(int memberID)
{
    int bookingID;

    cout << "\nEnter Booking ID: ";
    cin >> bookingID;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingIDs[i] == bookingID &&
            bookingMemberIDs[i] == memberID)
        {
            cout << "\n================================\n";
            cout << "      BOOKING CONFIRMATION\n";
            cout << "================================\n";
            cout << "Booking ID : " << bookingIDs[i] << endl;
            cout << "Member ID  : " << bookingMemberIDs[i] << endl;
            cout << "Service ID : " << bookingServiceIDs[i] << endl;
            cout << "Date       : " << bookingDates[i] << endl;
            cout << "Status     : " << bookingStatus[i] << endl;
            cout << "================================\n";

            return;
        }
    }

    cout << "Booking not found.\n";
}

// ==============================
// STAFF: ADD BOOKING (ON BEHALF OF MEMBER)
// ==============================

void staffAddBooking()
{
    if (bookingCount >= MAX_BOOKINGS)
    {
        cout << "\nBooking system is full. Cannot add more bookings.\n";
        return;
    }

    int memberID;
    int serviceID;
    string date;

    cout << "\n--- Staff: Add Booking ---\n";
    cout << "Enter Member ID: ";
    cin >> memberID;

    viewServices();

    cout << "\nEnter Service ID: ";
    cin >> serviceID;

    cout << "Enter Booking Date (DD/MM/YYYY): ";
    cin >> date;

    if (!validateDate(date))
    {
        return;
    }

    if (!validateBooking(memberID, serviceID, date))
    {
        return;
    }

    bookingIDs[bookingCount] = 1001 + bookingCount;
    bookingMemberIDs[bookingCount] = memberID;
    bookingServiceIDs[bookingCount] = serviceID;
    bookingDates[bookingCount] = date;
    bookingStatus[bookingCount] = "Active";

    cout << "\nBooking successful!\n";
    cout << "Booking ID: " << bookingIDs[bookingCount] << endl;

    bookingCount++;
}


// ==============================
// STAFF: VIEW ALL BOOKINGS
// ==============================

void staffViewAllBookings()
{
    if (bookingCount == 0)
    {
        cout << "\nNo bookings have been made yet.\n";
        return;
    }

    cout << "\n===== ALL BOOKINGS =====\n";

    for (int i = 0; i < bookingCount; i++)
    {
        cout << "Booking ID : " << bookingIDs[i] << endl;
        cout << "Member ID  : " << bookingMemberIDs[i] << endl;
        cout << "Service ID : " << bookingServiceIDs[i] << endl;
        cout << "Date       : " << bookingDates[i] << endl;
        cout << "Status     : " << bookingStatus[i] << endl;
        cout << "-----------------------------\n";
    }
}


// ==============================
// STAFF: SEARCH BOOKING (BY BOOKING ID OR MEMBER ID)
// ==============================

void staffSearchBooking()
{
    cout << "\nSearch by:\n";
    cout << "1. Booking ID\n";
    cout << "2. Member ID\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    bool found = false;

    if (choice == 1)
    {
        int bookingID;
        cout << "Enter Booking ID: ";
        cin >> bookingID;

        for (int i = 0; i < bookingCount; i++)
        {
            if (bookingIDs[i] == bookingID)
            {
                cout << "\nBooking ID : " << bookingIDs[i] << endl;
                cout << "Member ID  : " << bookingMemberIDs[i] << endl;
                cout << "Service ID : " << bookingServiceIDs[i] << endl;
                cout << "Date       : " << bookingDates[i] << endl;
                cout << "Status     : " << bookingStatus[i] << endl;
                found = true;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        int memberID;
        cout << "Enter Member ID: ";
        cin >> memberID;

        for (int i = 0; i < bookingCount; i++)
        {
            if (bookingMemberIDs[i] == memberID)
            {
                cout << "\nBooking ID : " << bookingIDs[i] << endl;
                cout << "Member ID  : " << bookingMemberIDs[i] << endl;
                cout << "Service ID : " << bookingServiceIDs[i] << endl;
                cout << "Date       : " << bookingDates[i] << endl;
                cout << "Status     : " << bookingStatus[i] << endl;
                cout << "-----------------------------\n";
                found = true;
            }
        }
    }
    else
    {
        cout << "Invalid choice.\n";
        return;
    }

    if (!found)
    {
        cout << "No matching booking found.\n";
    }
}


// ==============================
// STAFF: EDIT BOOKING (ANY MEMBER'S)
// ==============================

void staffEditBooking()
{
    int bookingID;

    cout << "\n--- Staff: Edit Booking ---\n";
    cout << "Enter Booking ID to edit: ";
    cin >> bookingID;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingIDs[i] == bookingID)
        {
            if (bookingStatus[i] == "Cancelled")
            {
                cout << "Cannot edit a cancelled booking.\n";
                return;
            }

            string newDate;
            cout << "Enter new booking date (DD/MM/YYYY): ";
            cin >> newDate;

            if (!validateDate(newDate))
            {
                return;
            }

            bookingDates[i] = newDate;
            cout << "Booking updated successfully.\n";
            return;
        }
    }

    cout << "Booking not found.\n";
}


// ==============================
// STAFF: RESCHEDULE / CANCEL BOOKING (ANY MEMBER'S)
// ==============================

void staffRescheduleOrCancelBooking()
{
    int bookingID;

    cout << "\n--- Staff: Reschedule / Cancel Booking ---\n";
    cout << "Enter Booking ID: ";
    cin >> bookingID;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingIDs[i] == bookingID)
        {
            if (bookingStatus[i] == "Cancelled")
            {
                cout << "Booking is already cancelled.\n";
                return;
            }

            cout << "1. Reschedule\n";
            cout << "2. Cancel\n";
            cout << "Enter choice: ";

            int choice;
            cin >> choice;

            if (choice == 1)
            {
                string newDate;
                cout << "Enter new booking date (DD/MM/YYYY): ";
                cin >> newDate;

                if (!validateDate(newDate))
                {
                    return;
                }

                bookingDates[i] = newDate;
                cout << "Booking rescheduled successfully.\n";
            }
            else if (choice == 2)
            {
                bookingStatus[i] = "Cancelled";
                cout << "Booking cancelled successfully.\n";
            }
            else
            {
                cout << "Invalid choice.\n";
            }

            return;
        }
    }

    cout << "Booking not found.\n";
}


// ==============================
// MEMBER BOOKING MENU
// ==============================

void memberBookingMenu(int memberID)
{
    int choice;

    do
    {
        cout << "\n===== MEMBER BOOKING =====\n";
        cout << "1. View Services\n";
        cout << "2. Search Services\n";
        cout << "3. Add Single Booking\n";
        cout << "4. Add Multiple Booking\n";
        cout << "5. View Booking\n";
        cout << "6. Edit Booking\n";
        cout << "7. Cancel Booking\n";
        cout << "8. Generate Confirmation Slip\n";
        cout << "9. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewServices();
            break;

        case 2:
            searchServices();
            break;

        case 3:
            addSingleBooking(memberID);
            break;

        case 4:
            addMultipleBookings(memberID);
            break;

        case 5:
            viewBooking(memberID);
            break;

        case 6:
            editBooking(memberID);
            break;

        case 7:
            cancelBooking(memberID);
            break;

        case 8:
            generateBookingConfirmationSlip(memberID);
            break;

        case 9:
            cout << "Returning to previous menu...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 9);
}
// ==============================
// STAFF MENU (SERVICES + BOOKINGS)
// ==============================

void staffBookingMenu()
{
    int choice;

    do
    {
        cout << "\n===== STAFF MENU =====\n";
        cout << "1. Add Service\n";
        cout << "2. View Services\n";
        cout << "3. Delete Service\n";
        cout << "4. Edit Service\n";
        cout << "5. Search Service\n";
        cout << "6. Add Booking (for a member)\n";
        cout << "7. View All Bookings\n";
        cout << "8. Reschedule / Cancel Booking\n";
        cout << "9. Edit Booking\n";
        cout << "10. Search Booking\n";
        cout << "11. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            staffAddService();
            break;

        case 2:
            viewServices();
            break;

        case 3:
            staffDeleteService();
            break;

        case 4:
            staffEditService();
            break;

        case 5:
            searchServices();
            break;

        case 6:
            staffAddBooking();
            break;

        case 7:
            staffViewAllBookings();
            break;

        case 8:
            staffRescheduleOrCancelBooking();
            break;

        case 9:
            staffEditBooking();
            break;

        case 10:
            staffSearchBooking();
            break;

        case 11:
            cout << "Returning to previous menu...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 11);
}