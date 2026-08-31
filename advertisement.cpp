#include <iostream>
#include <string>
using namespace std;

const int MAX_ADS = 50;   // 广告数组的最大容量

struct Advertisement {
    int id;
    string title;
    string description;
    string startDate;   // DD/MM/YYYY
    string endDate;      // DD/MM/YYYY
    string status;       // Active / Expired
};

// ---------- Global Variables ----------
Advertisement adList[MAX_ADS];
int adCount = 0;      // 目前有几笔广告
int nextAdId = 1;      // 下一个要用的编号

// ---------- Function Prototypes ----------
bool isValidAdDate(string date);
bool isValidTitle(string title);
void advertisementModule();

// ============================================================
// Advertisement 模块入口，组员的总 main() 呼叫这个 function 就能进来
// ============================================================
void advertisementModule() {
    int choice;

    do {
        cout << "\n----- Advertisement Menu -----" << endl;
        cout << "1. Add Advertisement" << endl;
        cout << "2. View All Advertisements" << endl;
        cout << "3. Edit Advertisement" << endl;
        cout << "4. Delete Advertisement" << endl;
        cout << "5. Search Advertisement" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        // 1. Add Advertisement
        case 1: {
            if (adCount >= MAX_ADS) {
                cout << "Advertisement list is full!" << endl;
                continue;
            }

            Advertisement ad;
            ad.id = nextAdId;

            cin.ignore();
            cout << "Enter advertisement title: ";
            getline(cin, ad.title);
            if (!isValidTitle(ad.title)) {
                cout << "Title cannot be empty! Advertisement not added." << endl;
                continue;
            }

            cout << "Enter description: ";
            getline(cin, ad.description);

            cout << "Enter start date (DD/MM/YYYY): ";
            cin >> ad.startDate;
            if (!isValidAdDate(ad.startDate)) {
                cout << "Invalid date format! Advertisement not added." << endl;
                continue;
            }

            cout << "Enter end date (DD/MM/YYYY): ";
            cin >> ad.endDate;
            if (!isValidAdDate(ad.endDate)) {
                cout << "Invalid date format! Advertisement not added." << endl;
                continue;
            }

            ad.status = "Active";

            adList[adCount] = ad;
            adCount++;
            nextAdId++;

            cout << "Advertisement added! ID = " << ad.id << endl;
            break;
        }

        // 2. View All Advertisements
        case 2: {
            if (adCount == 0) {
                cout << "No advertisement found." << endl;
                break;
            }

            for (int i = 0; i < adCount; i++) {
                cout << "ID: " << adList[i].id
                     << " | Title: " << adList[i].title
                     << " | Start: " << adList[i].startDate
                     << " | End: " << adList[i].endDate
                     << " | Status: " << adList[i].status << endl;
            }
            break;
        }

        // 3. Edit Advertisement
        case 3: {
            if (adCount == 0) {
                cout << "No advertisement found." << endl;
                break;
            }

            int id;
            cout << "Enter Advertisement ID to edit: ";
            cin >> id;

            bool foundEdit = false;
            for (int i = 0; i < adCount; i++) {
                if (adList[i].id == id) {
                    cin.ignore();
                    cout << "Enter new title (current: " << adList[i].title << "): ";
                    getline(cin, adList[i].title);

                    cout << "Enter new description (current: " << adList[i].description << "): ";
                    getline(cin, adList[i].description);

                    cout << "Enter new end date DD/MM/YYYY (current: " << adList[i].endDate << "): ";
                    cin >> adList[i].endDate;

                    cout << "Advertisement updated!" << endl;
                    foundEdit = true;
                    break;
                }
            }
            if (!foundEdit) {
                cout << "Advertisement ID not found." << endl;
            }
            break;
        }

        // 4. Delete Advertisement
        case 4: {
            if (adCount == 0) {
                cout << "No advertisement found." << endl;
                break;
            }

            int id;
            cout << "Enter Advertisement ID to delete: ";
            cin >> id;

            bool foundDel = false;
            for (int i = 0; i < adCount; i++) {
                if (adList[i].id == id) {
                    for (int j = i; j < adCount - 1; j++) {
                        adList[j] = adList[j + 1];
                    }
                    adCount--;
                    cout << "Advertisement deleted." << endl;
                    foundDel = true;
                    break;
                }
            }
            if (!foundDel) {
                cout << "Advertisement ID not found." << endl;
            }
            break;
        }

        // 5. Search Advertisement
        case 5: {
            if (adCount == 0) {
                cout << "No advertisement found." << endl;
                break;
            }

            string keyword;
            cout << "Enter title keyword to search: ";
            cin.ignore();
            getline(cin, keyword);

            bool found = false;
            for (int i = 0; i < adCount; i++) {
                if (adList[i].title == keyword) {
                    cout << "ID: " << adList[i].id
                         << " | Description: " << adList[i].description
                         << " | Start: " << adList[i].startDate
                         << " | End: " << adList[i].endDate
                         << " | Status: " << adList[i].status << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No matching advertisement found." << endl;
            }
            break;
        }

        case 0:
            cout << "Returning..." << endl;
            break;

        default:
            cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 0);
}

// ============================================================
// -------------------- Helper Functions (有回传值，不是 void) --------------------
// ============================================================

// 只做基本格式检查：长度对不对、分隔符位置对不对
bool isValidAdDate(string date) {
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    return true;
}

// 标题不能是空的
bool isValidTitle(string title) {
    if (title.length() == 0) return false;
    return true;
}
