#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// ==============================
// DATA STRUCTURES
// ==============================

const int MAX_FEEDBACK = 100;

int feedbackIDs[MAX_FEEDBACK];
int feedbackMemberIDs[MAX_FEEDBACK];
string feedbackTopic[MAX_FEEDBACK];      // free-text topic written by the member
int feedbackRating[MAX_FEEDBACK];        // 1 to 5
string feedbackComment[MAX_FEEDBACK];
string feedbackDate[MAX_FEEDBACK];

int feedbackCount = 0;


// ==============================
// GET CURRENT DATE (DD/MM/YYYY)
// ==============================

string getCurrentDate()
{
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);   // MSVC: (tm*, time_t*) — reversed arg order vs localtime()

    int day = localTime.tm_mday;
    int month = localTime.tm_mon + 1;
    int year = localTime.tm_year + 1900;

    string dayStr = (day < 10 ? "0" : "") + to_string(day);
    string monthStr = (month < 10 ? "0" : "") + to_string(month);

    return dayStr + "/" + monthStr + "/" + to_string(year);
}


// ==============================
// SUBMIT FEEDBACK
// ==============================

void submitFeedback(int memberID)
{
    if (feedbackCount >= MAX_FEEDBACK)
    {
        cout << "\nFeedback system is full. Cannot accept more feedback.\n";
        return;
    }

    cout << "\n===== SUBMIT FEEDBACK =====\n";

    string topic;
    cout << "Enter a topic for your feedback (e.g. Booking, Locker Room, Trainer): ";
    cin.ignore();
    getline(cin, topic);

    if (topic.length() == 0)
    {
        cout << "Topic cannot be empty.\n";
        return;
    }

    int rating;
    cout << "Enter rating (1 = Very Poor, 5 = Excellent): ";
    cin >> rating;

    if (rating < 1 || rating > 5)
    {
        cout << "Invalid rating. Must be between 1 and 5.\n";
        return;
    }

    string comment;
    cout << "Enter your comments (or type NONE to skip): ";
    cin.ignore();
    getline(cin, comment);

    feedbackIDs[feedbackCount] = 5001 + feedbackCount;
    feedbackMemberIDs[feedbackCount] = memberID;
    feedbackTopic[feedbackCount] = topic;
    feedbackRating[feedbackCount] = rating;
    feedbackComment[feedbackCount] = comment;
    feedbackDate[feedbackCount] = getCurrentDate();

    cout << "\nThank you! Your feedback has been submitted.\n";
    cout << "Feedback ID: " << feedbackIDs[feedbackCount] << endl;

    feedbackCount++;
}


// ==============================
// VIEW MY FEEDBACK (MEMBER)
// ==============================

void viewMyFeedback(int memberID)
{
    bool found = false;

    cout << "\n===== MY FEEDBACK HISTORY =====\n";

    for (int i = 0; i < feedbackCount; i++)
    {
        if (feedbackMemberIDs[i] == memberID)
        {
            cout << "Feedback ID: " << feedbackIDs[i] << endl;
            cout << "Topic      : " << feedbackTopic[i] << endl;
            cout << "Rating     : " << feedbackRating[i] << "/5" << endl;
            cout << "Comment    : " << feedbackComment[i] << endl;
            cout << "Date       : " << feedbackDate[i] << endl;
            cout << "-----------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "You have not submitted any feedback yet.\n";
    }
}


// ==============================
// STAFF: VIEW ALL FEEDBACK
// ==============================

void viewAllFeedback()
{
    if (feedbackCount == 0)
    {
        cout << "\nNo feedback has been submitted yet.\n";
        return;
    }

    cout << "\n===== ALL MEMBER FEEDBACK =====\n";

    for (int i = 0; i < feedbackCount; i++)
    {
        cout << "Feedback ID: " << feedbackIDs[i] << endl;
        cout << "Member ID  : " << feedbackMemberIDs[i] << endl;
        cout << "Topic      : " << feedbackTopic[i] << endl;
        cout << "Rating     : " << feedbackRating[i] << "/5" << endl;
        cout << "Comment    : " << feedbackComment[i] << endl;
        cout << "Date       : " << feedbackDate[i] << endl;
        cout << "-----------------------------\n";
    }
}


// ==============================
// STAFF: SEARCH FEEDBACK BY TOPIC KEYWORD
// ==============================

void searchFeedbackByTopic()
{
    string keyword;

    cout << "\nEnter a keyword to search in feedback topics: ";
    cin.ignore();
    getline(cin, keyword);

    bool found = false;

    cout << "\n===== SEARCH RESULTS: \"" << keyword << "\" =====\n";

    for (int i = 0; i < feedbackCount; i++)
    {
        // npos means "not found"; anything else means the keyword exists somewhere in the topic
        if (feedbackTopic[i].find(keyword) != string::npos)
        {
            cout << "Feedback ID: " << feedbackIDs[i] << endl;
            cout << "Member ID  : " << feedbackMemberIDs[i] << endl;
            cout << "Topic      : " << feedbackTopic[i] << endl;
            cout << "Rating     : " << feedbackRating[i] << "/5" << endl;
            cout << "Comment    : " << feedbackComment[i] << endl;
            cout << "Date       : " << feedbackDate[i] << endl;
            cout << "-----------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "No feedback found matching that keyword.\n";
    }
}


// ==============================
// STAFF: OVERALL AVERAGE RATING
// ==============================

void averageRatingReport()
{
    if (feedbackCount == 0)
    {
        cout << "\nNo feedback has been submitted yet.\n";
        return;
    }

    int total = 0;

    for (int i = 0; i < feedbackCount; i++)
    {
        total += feedbackRating[i];
    }

    double average = (double)total / feedbackCount;

    cout << "\n===== OVERALL FEEDBACK RATING =====\n";
    cout << "Total Feedback Submitted: " << feedbackCount << endl;
    cout << "Average Rating: " << average << " / 5\n";
}


// ==============================
// MEMBER FEEDBACK MENU
// ==============================

void memberFeedbackMenu(int memberID)
{
    int choice;

    do
    {
        cout << "\n===== MEMBER FEEDBACK =====\n";
        cout << "1. Submit Feedback\n";
        cout << "2. View My Feedback\n";
        cout << "3. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            submitFeedback(memberID);
            break;

        case 2:
            viewMyFeedback(memberID);
            break;

        case 3:
            cout << "Returning to previous menu...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);
}


// ==============================
// STAFF FEEDBACK MENU
// ==============================

void staffFeedbackMenu()
{
    int choice;

    do
    {
        cout << "\n===== STAFF: FEEDBACK MANAGEMENT =====\n";
        cout << "1. View All Feedback\n";
        cout << "2. Search Feedback by Topic Keyword\n";
        cout << "3. Overall Average Rating\n";
        cout << "4. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAllFeedback();
            break;

        case 2:
            searchFeedbackByTopic();
            break;

        case 3:
            averageRatingReport();
            break;

        case 4:
            cout << "Returning to previous menu...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}
