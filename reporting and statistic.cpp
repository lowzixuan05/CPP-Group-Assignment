#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// =====================================================
// MEMBER DATA
// =====================================================

struct Member
{
    string memberID;
    string memberName;
    int age;
    string gender;
    string membershipType;
    string membershipStatus;
};

Member members[3] =
{
    {"M001", "John", 25, "Male", "Monthly", "Active"},
    {"M002", "Mary", 30, "Female", "Yearly", "Active"},
    {"M003", "Ali", 40, "Male", "Monthly", "Expired"}
};

int memberCount = 3;


// =====================================================
// 1. SEARCH MEMBER REPORT
// =====================================================

void searchReport()
{
    int choice;
    string keyword;
    bool found = false;

    cout << "\n==============================================\n";
    cout << "             SEARCH MEMBER REPORT\n";
    cout << "==============================================\n";

    cout << "1. Search by Member ID\n";
    cout << "2. Search by Member Name\n";
    cout << "3. Search by Membership Type\n";
    cout << "4. Return to Main Menu\n";

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 4)
        return;

    if (choice < 1 || choice > 3)
    {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Enter search value: ";
    cin >> keyword;

    for (int i = 0; i < memberCount; i++)
    {
        if ((choice == 1 && members[i].memberID == keyword) ||
            (choice == 2 && members[i].memberName == keyword) ||
            (choice == 3 && members[i].membershipType == keyword))
        {
            cout << "\n==============================================\n";
            cout << "           MEMBER REPORT FOUND\n";
            cout << "==============================================\n";

            cout << "Member ID       : " << members[i].memberID << endl;
            cout << "Name            : " << members[i].memberName << endl;
            cout << "Age             : " << members[i].age << endl;
            cout << "Gender          : " << members[i].gender << endl;
            cout << "Membership Type : " << members[i].membershipType << endl;
            cout << "Status          : " << members[i].membershipStatus << endl;

            cout << "==============================================\n";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nNo member report found.\n";
    }
}


// =====================================================
// 2. WEEKLY REPORT
// =====================================================

void weeklyReport()
{
    string day[7] =
    {
        "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday", "Sunday"
    };

    int attendance[7] =
    {
        25, 30, 28, 35, 40, 50, 32
    };

    int newMembers[7] =
    {
        2, 3, 1, 4, 5, 6, 3
    };

    double revenue[7] =
    {
        100, 150, 80, 200, 250, 300, 150
    };

    int totalAttendance = 0;
    int totalNewMembers = 0;
    double totalRevenue = 0;

    int highest = attendance[0];
    int lowest = attendance[0];

    string busiestDay = day[0];
    string quietestDay = day[0];

    cout << "\n====================================================\n";
    cout << "                 WEEKLY GYM REPORT\n";
    cout << "====================================================\n";

    cout << left
         << setw(12) << "Day"
         << setw(15) << "Attendance"
         << setw(15) << "New Members"
         << "Revenue" << endl;

    cout << "----------------------------------------------------\n";

    for (int i = 0; i < 7; i++)
    {
        cout << left
             << setw(12) << day[i]
             << setw(15) << attendance[i]
             << setw(15) << newMembers[i]
             << "RM " << fixed << setprecision(2)
             << revenue[i] << endl;

        totalAttendance += attendance[i];
        totalNewMembers += newMembers[i];
        totalRevenue += revenue[i];

        if (attendance[i] > highest)
        {
            highest = attendance[i];
            busiestDay = day[i];
        }

        if (attendance[i] < lowest)
        {
            lowest = attendance[i];
            quietestDay = day[i];
        }
    }

    double averageAttendance = totalAttendance / 7.0;

    cout << "\n====================================================\n";
    cout << "                    STATISTICS\n";
    cout << "====================================================\n";

    cout << "Total Attendance    : "
         << totalAttendance << " visits" << endl;

    cout << "Average Attendance  : "
         << fixed << setprecision(2)
         << averageAttendance << " visits/day" << endl;

    cout << "New Members         : "
         << totalNewMembers << endl;

    cout << "Total Revenue       : RM "
         << fixed << setprecision(2)
         << totalRevenue << endl;

    cout << "Busiest Day         : "
         << busiestDay << " (" << highest << " visits)" << endl;

    cout << "Quietest Day        : "
         << quietestDay << " (" << lowest << " visits)" << endl;

    cout << "\n====================================================\n";
    cout << "                 ATTENDANCE BAR CHART\n";
    cout << "====================================================\n";

    for (int i = 0; i < 7; i++)
    {
        cout << left << setw(12) << day[i] << " | ";

        // One * represents 2 visits
        for (int j = 0; j < attendance[i] / 2; j++)
        {
            cout << "*";
        }

        cout << " " << attendance[i] << endl;
    }

    cout << "====================================================\n";
}


// =====================================================
// 3. MONTHLY REPORT
// =====================================================

void monthlyReport()
{
    string month[12] =
    {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    int attendance[12] =
    {
        120, 150, 135, 180,
        200, 175, 220, 240,
        190, 210, 230, 250
    };

    int newMembers[12] =
    {
        10, 12, 8, 15,
        18, 14, 20, 22,
        16, 19, 21, 25
    };

    double revenue[12] =
    {
        1200, 1500, 1350, 1800,
        2000, 1750, 2200, 2400,
        1900, 2100, 2300, 2500
    };

    int totalAttendance = 0;
    int totalNewMembers = 0;
    double totalRevenue = 0;

    int highest = attendance[0];
    int lowest = attendance[0];

    string busiestMonth = month[0];
    string quietestMonth = month[0];

    cout << "\n==============================================\n";
    cout << "             MONTHLY GYM REPORT\n";
    cout << "==============================================\n";

    cout << left
         << setw(13) << "Month"
         << setw(15) << "Attendance"
         << setw(15) << "New Members"
         << "Revenue" << endl;

    cout << "----------------------------------------------\n";

    for (int i = 0; i < 12; i++)
    {
        cout << left
             << setw(13) << month[i]
             << setw(15) << attendance[i]
             << setw(15) << newMembers[i]
             << "RM " << fixed << setprecision(2)
             << revenue[i] << endl;

        totalAttendance += attendance[i];
        totalNewMembers += newMembers[i];
        totalRevenue += revenue[i];

        if (attendance[i] > highest)
        {
            highest = attendance[i];
            busiestMonth = month[i];
        }

        if (attendance[i] < lowest)
        {
            lowest = attendance[i];
            quietestMonth = month[i];
        }
    }

    double average = totalAttendance / 12.0;

    cout << "\n==============================================\n";
    cout << "                 STATISTICS\n";
    cout << "==============================================\n";

    cout << "Total Attendance   : "
         << totalAttendance << endl;

    cout << "Average Attendance : "
         << fixed << setprecision(2)
         << average << endl;

    cout << "Total New Members  : "
         << totalNewMembers << endl;

    cout << "Total Revenue      : RM "
         << fixed << setprecision(2)
         << totalRevenue << endl;

    cout << "Busiest Month      : "
         << busiestMonth << " (" << highest << ")" << endl;

    cout << "Quietest Month     : "
         << quietestMonth << " (" << lowest << ")" << endl;

    cout << "\n==============================================\n";
    cout << "              ATTENDANCE BAR CHART\n";
    cout << "==============================================\n";

    for (int i = 0; i < 12; i++)
    {
        cout << left << setw(13) << month[i] << " | ";

        // One * represents 10 visits
        for (int j = 0; j < attendance[i] / 10; j++)
        {
            cout << "*";
        }

        cout << " " << attendance[i] << endl;
    }

    cout << "==============================================\n";
}


// =====================================================
// 4. MEMBERSHIP REPORT
// =====================================================

void membershipReport()
{
    string membershipType[4] =
    {
        "Student",
        "Regular",
        "Premium",
        "Senior"
    };

    int members[4] =
    {
        40,
        30,
        20,
        10
    };

    int totalMembers = 0;
    int highest = members[0];
    string mostPopular = membershipType[0];

    for (int i = 0; i < 4; i++)
    {
        totalMembers += members[i];

        if (members[i] > highest)
        {
            highest = members[i];
            mostPopular = membershipType[i];
        }
    }

    cout << "\n==============================================\n";
    cout << "             MEMBERSHIP REPORT\n";
    cout << "==============================================\n";

    cout << left
         << setw(15) << "Type"
         << setw(15) << "Members"
         << "Percentage" << endl;

    cout << "----------------------------------------------\n";

    for (int i = 0; i < 4; i++)
    {
        double percentage =
            (members[i] * 100.0) / totalMembers;

        cout << left
             << setw(15) << membershipType[i]
             << setw(15) << members[i]
             << fixed << setprecision(1)
             << percentage << "%" << endl;
    }

    cout << "\n==============================================\n";
    cout << "                  STATISTICS\n";
    cout << "==============================================\n";

    cout << "Total Members     : "
         << totalMembers << endl;

    cout << "Most Popular      : "
         << mostPopular << endl;

    cout << "Number of Members : "
         << highest << endl;

    cout << "\n==============================================\n";
    cout << "            MEMBERSHIP BAR CHART\n";
    cout << "==============================================\n";

    for (int i = 0; i < 4; i++)
    {
        cout << left
             << setw(15) << membershipType[i]
             << " | ";

        // One * represents 2 members
        for (int j = 0; j < members[i] / 2; j++)
        {
            cout << "*";
        }

        cout << " " << members[i] << endl;
    }

    cout << "==============================================\n";
}


// =====================================================
// MAIN REPORT MENU
// =====================================================

int main()
{
    int choice;

    do
    {
        cout << "\n\n";
        cout << "====================================================\n";
        cout << "              GYM MANAGEMENT SYSTEM\n";
        cout << "                  REPORTING MENU\n";
        cout << "====================================================\n";

        cout << "1. Search Member Report\n";
        cout << "2. Generate Weekly Report\n";
        cout << "3. Generate Monthly Report\n";
        cout << "4. Generate Membership Report\n";
        cout << "5. Exit\n";

        cout << "====================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                searchReport();
                break;

            case 2:
                weeklyReport();
                break;

            case 3:
                monthlyReport();
                break;

            case 4:
                membershipReport();
                break;

            case 5:
                cout << "\nThank you for using the Gym Management System.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
