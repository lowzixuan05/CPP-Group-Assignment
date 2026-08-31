#include <iostream>
#include <string>
using namespace std;

const int MAX_APPT = 100;  // 最多100
const int MAX_SLOTS_PER_SERVICE_PER_DAY = 16;   // 16小时营业时间 Yoga跟Personal各自最多16个位/天
const int OPEN_HOUR = 8;  // 营业开始: 08:00
const int CLOSE_HOUR = 24;  // 营业结束: 24:00 (即晚上12点)

struct Appointment {  // struct指一个appointment里面要有什么东西  （ id name date time status ）
    int id;
    string memberName;
    string service;
    string date;   // DD/MM/YYYY
    string time;   // HH:MM
    string status;  // Confirmed / Cancelled
};

Appointment appointmentList[MAX_APPT];
int apptCount = 0;     // 目前有几笔预约
int nextId = 1;         // 下一个要用的编号

bool isValidDate(string date);
bool isValidTime(string time);
bool isWithinBusinessHours(string time);  // 要在0800到2400以内
bool isSlotTaken(string date, string time, string service, int skipId);  // 避免doublebook
int countAppointmentsOnDateForService(string date, string service);   // 一天只有32个位 （personal 16 / yoga 16）
void appointmentModule();


void appointmentModule() {
    int topChoice;

    do {
        cout << "\n===== GYM APPOINTMENT MODULE =====" << endl;
        cout << "1. Member - Appointment Menu" << endl;
        cout << "2. Staff - Appointment Menu" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> topChoice;

        // member
        switch (topChoice) {
        case 1: {
            int choice;
            do {
                cout << "\n----- Member Appointment Menu -----" << endl;
                cout << "1. View appointment schedule" << endl;
                cout << "2. Search appointment schedule" << endl;
                cout << "3. Add single appointment" << endl;
                cout << "4. Add multiple appointment" << endl;
                cout << "5. Edit appointment" << endl;
                cout << "6. Cancel appointment" << endl;
                cout << "7. View appointment" << endl;
                cout << "8. Generate appointment confirmation slip" << endl;
                cout << "0. Back" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {

                    // 1. View appointment schedule
                case 1: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    for (int i = 0; i < apptCount; i++) {  // 0开始一个一个查 大于100就结束 i+1
                        // 如果i存在 显示i的相关资料
                        cout << "ID: " << appointmentList[i].id
                            << " | Member: " << appointmentList[i].memberName
                            << " | Service: " << appointmentList[i].service
                            << " | Date: " << appointmentList[i].date
                            << " | Time: " << appointmentList[i].time
                            << " | Status: " << appointmentList[i].status << endl;
                    }
                    break;
                }

                      // 2. Search appointment schedule
                case 2: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    string keyword;
                    cout << "Enter member name to search: ";
                    cin.ignore();  // 忽略之前的enter
                    getline(cin, keyword);  // keyword可以有空格

                    bool found = false;   // 默认f
                    for (int i = 0; i < apptCount; i++) { // 0开始一个一个查 大于100就结束 i+1
                        if (appointmentList[i].memberName == keyword) {  // 如果有符合的就显示
                            cout << "ID: " << appointmentList[i].id
                                << " | Service: " << appointmentList[i].service
                                << " | Date: " << appointmentList[i].date
                                << " | Time: " << appointmentList[i].time
                                << " | Status: " << appointmentList[i].status << endl;
                            found = true;  // 有符合的就t
                        }
                    }
                    if (!found) {  // 如果是f的话就..
                        cout << "No matching appointment found." << endl;
                    }
                    break;
                }

                      // 3. Add single appointment
                case 3: {
                    if (apptCount >= MAX_APPT) {  // 如果大于100就不可以
                        cout << "Appointment list is full!" << endl;
                        continue;
                    }

                    cin.ignore();
                    Appointment a;
                    a.id = nextId;  // 默认第一次为1 第二次+1 ...

                    cout << "Enter member name: ";
                    getline(cin, a.memberName);

                    cout << "Enter date (DD/MM/YYYY): ";
                    cin >> a.date;
                    if (!isValidDate(a.date)) {
                        cout << "Invalid date format! Appointment not added." << endl;
                        continue;  // 如果日期格式不符合 con就会下去看循环（do while）的 while条件 则while不等于0就重复member界面 返回上个界面
                    }

                    cout << "Booked time slots on " << a.date << ":" << endl;
                    bool anyBooked = false;  // 默认f
                    for (int i = 0; i < apptCount; i++) {  // 找一遍
                        if (appointmentList[i].date == a.date && appointmentList[i].status != "Cancelled") {  // 如果status是comfirm就t 反之
                            cout << "  - " << appointmentList[i].time << " (" << appointmentList[i].service << ")" << endl;
                            anyBooked = true;
                        }
                    }
                    if (!anyBooked) {  // 如果没有就... 
                        cout << "  (No slot booked yet)" << endl;
                    }

                    int serviceChoice;
                    cout << "Select service (1.Yoga  2.Personal)\n";
                    cout << "Enter your choice: \n";
                    cin >> serviceChoice;

                    switch (serviceChoice) {
                    case 1: a.service = "Yoga"; break;
                    case 2: a.service = "Personal"; break;
                    default:
                        cout << "Invalid service choice! Appointment not added." << endl;  // 其他的不可以
                        continue;  // 同上 跳去下面while 返回上个界面
                    }

                    if (countAppointmentsOnDateForService(a.date, a.service) >= MAX_SLOTS_PER_SERVICE_PER_DAY) {  // 当天满人就...
                        cout << "This date is fully booked for " << a.service << " (16/16 slots taken)! Please choose another date or service." << endl;
                        continue;
                    }

                    cout << "Enter time (HH:MM): ";
                    cin >> a.time;
                    if (!isValidTime(a.time)) {  // 格式
                        cout << "Invalid time format! Appointment not added." << endl;
                        continue;  // 同上
                    }

                    if (!isWithinBusinessHours(a.time)) {  // 0800到2400?
                        cout << "Invalid! Gym operating hours are 08:00 to 24:00 only." << endl;
                        continue;  // 同上
                    }

                    if (isSlotTaken(a.date, a.time, a.service, -1)) {  //三个同时重复才算doublebook （-1）指的是检查每一个
                        cout << "Invalid! " << a.service << " at " << a.time << " on " << a.date << " is already booked. Please choose another slot or another service." << endl;
                        continue;  // 同上
                    }

                    a.status = "Confirmed";  // 默认comfirm
                    appointmentList[apptCount] = a;
                    apptCount++;  // 这两个每过一次就+1
                    nextId++;

                    cout << "Appointment added! ID = " << a.id << endl;  // app id 就是a
                    break;
                }

                      // 4. Add multiple appointment
                case 4: {
                    int num;
                    cout << "How many appointments do you want to add? ";
                    cin >> num;

                    if (num <= 0) {  // 不可以小于等于0
                        cout << "Invalid number." << endl;
                        break;
                    }

                    for (int n = 0; n < num; n++) {  // 重复n次
                        if (apptCount >= MAX_APPT) {  // 不可大于等于100
                            cout << "Appointment list is full! Cannot add more." << endl;
                            break;
                        }

                        cout << "\n--- Appointment " << (n + 1) << " ---" << endl;

                        cin.ignore();
                        Appointment a;
                        a.id = nextId;

                        cout << "Enter member name: ";
                        getline(cin, a.memberName);

                        cout << "Enter date (DD/MM/YYYY): ";
                        cin >> a.date;
                        if (!isValidDate(a.date)) {
                            cout << "Invalid date format! Appointment not added." << endl;
                            continue;
                        }

                        cout << "Booked time slots on " << a.date << ":" << endl;
                        bool anyBooked = false;
                        for (int i = 0; i < apptCount; i++) {
                            if (appointmentList[i].date == a.date && appointmentList[i].status != "Cancelled") {
                                cout << "  - " << appointmentList[i].time << " (" << appointmentList[i].service << ")" << endl;
                                anyBooked = true;
                            }
                        }
                        if (!anyBooked) {
                            cout << "  (No slot booked yet)" << endl;
                        }

                        int serviceChoice;
                        cout << "Select service( 1.Yoga  2.Personal )" << endl;
                        cout << "Enter your choice: ";
                        cin >> serviceChoice;

                        switch (serviceChoice) {
                        case 1: a.service = "Yoga"; break;
                        case 2: a.service = "Personal"; break;
                        default:
                            cout << "Invalid service choice! Appointment not added." << endl;
                            continue;
                        }

                        if (countAppointmentsOnDateForService(a.date, a.service) >= MAX_SLOTS_PER_SERVICE_PER_DAY) {  // 单一service满则
                            cout << "This date is fully booked for " << a.service << " (16/16 slots taken)! Please choose another date or service." << endl;
                            continue;
                        }

                        cout << "Enter time (HH:MM): ";
                        cin >> a.time;
                        if (!isValidTime(a.time)) {
                            cout << "Invalid time format! Appointment not added." << endl;
                            continue;
                        }

                        if (!isWithinBusinessHours(a.time)) {
                            cout << "Invalid! Gym operating hours are 08:00 to 24:00 only." << endl;
                            continue;
                        }

                        if (isSlotTaken(a.date, a.time, a.service, -1)) {
                            cout << "Invalid! " << a.service << " at " << a.time << " on " << a.date << " is already booked. Please choose another slot or another service." << endl;
                            continue;
                        }

                        a.status = "Confirmed";
                        appointmentList[apptCount] = a;
                        apptCount++;
                        nextId++;

                        cout << "Appointment added! ID = " << a.id << endl;
                    }
                    break;
                }

                      // 5. Edit appointment
                case 5: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    int id;
                    cout << "Enter Appointment ID to edit: ";
                    cin >> id;

                    bool foundEdit = false;
                    for (int i = 0; i < apptCount; i++) {  // 从1找到最新的id号码
                        if (appointmentList[i].id == id) {
                            cout << "Enter new date (DD/MM/YYYY): ";
                            cin >> appointmentList[i].date;
                            cout << "Enter new time (HH:MM): ";
                            cin >> appointmentList[i].time;
                            cout << "Appointment updated!" << endl;
                            foundEdit = true;
                            break;
                        }
                    }
                    if (!foundEdit) {
                        cout << "Appointment ID not found." << endl;
                    }
                    break;
                }

                      // 6. Cancel appointment
                case 6: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    int id;
                    cout << "Enter Appointment ID to cancel: ";
                    cin >> id;

                    bool foundCancel = false;
                    for (int i = 0; i < apptCount; i++) {  // 从1找到最新的id号码
                        if (appointmentList[i].id == id) {  // 找到id 
                            appointmentList[i].status = "Cancelled";  // 放cancel
                            cout << "Appointment cancelled." << endl;
                            foundCancel = true;
                            break;
                        }
                    }
                    if (!foundCancel) {
                        cout << "Appointment ID not found." << endl;
                    }
                    break;
                }

                      // 7. View appointment (detail)
                case 7: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    int id;
                    cout << "Enter Appointment ID to view: ";
                    cin >> id;

                    bool foundView = false;
                    for (int i = 0; i < apptCount; i++) {
                        if (appointmentList[i].id == id) {
                            cout << "ID          : " << appointmentList[i].id << endl;
                            cout << "Member Name : " << appointmentList[i].memberName << endl;
                            cout << "Service     : " << appointmentList[i].service << endl;
                            cout << "Date        : " << appointmentList[i].date << endl;
                            cout << "Time        : " << appointmentList[i].time << endl;
                            cout << "Status      : " << appointmentList[i].status << endl;
                            foundView = true;
                            break;
                        }
                    }
                    if (!foundView) {
                        cout << "Appointment ID not found." << endl;
                    }
                    break;
                }

                      // 8. Generate appointment confirmation slip
                case 8: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    int id;
                    cout << "Enter Appointment ID: ";
                    cin >> id;

                    bool foundSlip = false;
                    for (int i = 0; i < apptCount; i++) {
                        if (appointmentList[i].id == id) {
                            cout << "\n===== APPOINTMENT CONFIRMATION =====" << endl;
                            cout << "Appointment ID : " << appointmentList[i].id << endl;
                            cout << "Member Name    : " << appointmentList[i].memberName << endl;
                            cout << "Service        : " << appointmentList[i].service << endl;
                            cout << "Date           : " << appointmentList[i].date << endl;
                            cout << "Time           : " << appointmentList[i].time << endl;
                            cout << "Status         : " << appointmentList[i].status << endl;
                            cout << "======================================" << endl;
                            foundSlip = true;
                            break;
                        }
                    }
                    if (!foundSlip) {
                        cout << "Appointment ID not found." << endl;
                    }
                    break;
                }

                case 0:
                    cout << "Returning..." << endl;
                    break;

                default:
                    cout << "Invalid choice." << endl;
                }

            } while (choice != 0);
            break;
        }

             
        // staff
        case 2: {
            int choice;
            do {
                cout << "\n----- Staff Appointment Menu -----" << endl;
                cout << "1. Add appointment" << endl;
                cout << "2. View appointment" << endl;
                cout << "3. Delete appointment" << endl;
                cout << "4. Edit appointment" << endl;
                cout << "5. Search appointment" << endl;
                cout << "6. Cancel appointment" << endl;
                cout << "0. Back" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {

                    // 1. Add appointment
                case 1: {
                    if (apptCount >= MAX_APPT) {
                        cout << "Appointment list is full!" << endl;
                        continue;
                    }

                    cin.ignore();
                    Appointment a;
                    a.id = nextId;

                    cout << "Enter member name: ";
                    getline(cin, a.memberName);

                    cout << "Enter date (DD/MM/YYYY): ";
                    cin >> a.date;
                    if (!isValidDate(a.date)) {
                        cout << "Invalid date format! Appointment not added." << endl;
                        continue;
                    }

                    cout << "Booked time slots on " << a.date << ":" << endl;
                    bool anyBooked = false;
                    for (int i = 0; i < apptCount; i++) {
                        if (appointmentList[i].date == a.date && appointmentList[i].status != "Cancelled") {
                            cout << "  - " << appointmentList[i].time << " (" << appointmentList[i].service << ")" << endl;
                            anyBooked = true;
                        }
                    }
                    if (!anyBooked) {
                        cout << "  (No slot booked yet)" << endl;
                    }

                    int serviceChoice;
                    cout << "Select service: 1. Yoga  2. Personal" << endl;
                    cout << "Enter your choice: ";
                    cin >> serviceChoice;

                    switch (serviceChoice) {
                    case 1: a.service = "Yoga"; break;
                    case 2: a.service = "Personal"; break;
                    default:
                        cout << "Invalid service choice! Appointment not added." << endl;
                        continue;
                    }

                    if (countAppointmentsOnDateForService(a.date, a.service) >= MAX_SLOTS_PER_SERVICE_PER_DAY) {
                        cout << "This date is fully booked for " << a.service << " (16/16 slots taken)! Please choose another date or service." << endl;
                        continue;
                    }

                    cout << "Enter time (HH:MM): ";
                    cin >> a.time;
                    if (!isValidTime(a.time)) {
                        cout << "Invalid time format! Appointment not added." << endl;
                        continue;
                    }

                    if (!isWithinBusinessHours(a.time)) {
                        cout << "Invalid! Gym operating hours are 08:00 to 24:00 only." << endl;
                        continue;
                    }

                    if (isSlotTaken(a.date, a.time, a.service, -1)) {
                        cout << "Invalid! " << a.service << " at " << a.time << " on " << a.date << " is already booked. Please choose another slot or another service." << endl;
                        continue;
                    }

                    a.status = "Confirmed";
                    appointmentList[apptCount] = a;
                    apptCount++;
                    nextId++;

                    cout << "Appointment added! ID = " << a.id << endl;
                    break;
                }

                      // 2. View appointment
                case 2: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    for (int i = 0; i < apptCount; i++) {
                        cout << "ID: " << appointmentList[i].id
                            << " | Member: " << appointmentList[i].memberName
                            << " | Service: " << appointmentList[i].service
                            << " | Date: " << appointmentList[i].date
                            << " | Time: " << appointmentList[i].time
                            << " | Status: " << appointmentList[i].status << endl;
                    }
                    break;
                }

                      // 3. Delete appointment
                case 3: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    int id;
                    cout << "Enter Appointment ID to delete: ";
                    cin >> id;

                    bool foundDel = false;
                    for (int i = 0; i < apptCount; i++) {  // 找到要删除的id（号码）
                        if (appointmentList[i].id == id) {
                            for (int j = i; j < apptCount - 1; j++) {  // （号码）是n  
                                appointmentList[j] = appointmentList[j + 1];  // 往前覆盖一格
                            }
                            apptCount--;
                            cout << "Appointment deleted." << endl;
                            foundDel = true;
                            break;
                        }
                    }
                    if (!foundDel) {
                        cout << "Appointment ID not found." << endl;
                    }
                    break;
                }

                      // 4. Edit appointment
                case 4: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    int id;
                    cout << "Enter Appointment ID to edit: ";
                    cin >> id;

                    bool foundEdit = false;
                    for (int i = 0; i < apptCount; i++) {
                        if (appointmentList[i].id == id) {
                            cout << "Enter new date (DD/MM/YYYY): ";
                            cin >> appointmentList[i].date;
                            cout << "Enter new time (HH:MM): ";
                            cin >> appointmentList[i].time;
                            cout << "Appointment updated!" << endl;
                            foundEdit = true;
                            break;
                        }
                    }
                    if (!foundEdit) {
                        cout << "Appointment ID not found." << endl;
                    }
                    break;
                }

                      // 5. Search appointment
                case 5: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    string keyword;
                    cout << "Enter member name to search: ";
                    cin.ignore();
                    getline(cin, keyword);

                    bool found = false;
                    for (int i = 0; i < apptCount; i++) {
                        if (appointmentList[i].memberName == keyword) {
                            cout << "ID: " << appointmentList[i].id
                                << " | Service: " << appointmentList[i].service
                                << " | Date: " << appointmentList[i].date
                                << " | Time: " << appointmentList[i].time
                                << " | Status: " << appointmentList[i].status << endl;
                            found = true;
                        }
                    }
                    if (!found) {
                        cout << "No matching appointment found." << endl;
                    }
                    break;
                }

                      // 6. Cancel appointment
                case 6: {
                    if (apptCount == 0) {
                        cout << "No appointment found." << endl;
                        break;
                    }
                    int id;
                    cout << "Enter Appointment ID to cancel: ";
                    cin >> id;

                    bool foundCancel = false;
                    for (int i = 0; i < apptCount; i++) {
                        if (appointmentList[i].id == id) {
                            appointmentList[i].status = "Cancelled";
                            cout << "Appointment cancelled." << endl;
                            foundCancel = true;
                            break;
                        }
                    }
                    if (!foundCancel) {
                        cout << "Appointment ID not found." << endl;
                    }
                    break;
                }

                case 0:
                    cout << "Returning..." << endl;
                    break;

                default:
                    cout << "Invalid choice." << endl;
                }

            } while (choice != 0);
            break;
        }

        case 0:
            cout << "Returning..." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

    } while (topChoice != 0);
}

bool isValidDate(string date) {  // 日期格式要是10个字 从0开始算第2 5格要是/
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    return true;
}

bool isValidTime(string time) {  // 时间格式要是5个字 从0开始算第2格要是：
    if (time.length() != 5) return false;
    if (time[2] != ':') return false;
    return true;
}

bool isWithinBusinessHours(string time) {  // 检查时间是不是 (08:00 - 24:00)
    int hour = stoi(time.substr(0, 2));  //从第0的位获取2个字  比如24：00  获取第1个字：2第二个字：4  即24 （stoi指string to int整数）
    if (hour < OPEN_HOUR || hour >= CLOSE_HOUR) return false;
    return true;
}

// 检查同一个日期+时间是不是已经有人预约了 (防止 double booking)
// 检查同一个日期+时间+服务项目是不是已经有人预约了 (防止 double booking)
// 同一时间 Yoga 和 Personal 可以并存，但同一时间同一个 service 不能重复
bool isSlotTaken(string date, string time, string service, int skipId) {
    for (int i = 0; i < apptCount; i++) {
        if (appointmentList[i].id == skipId) continue;
        if (appointmentList[i].status == "Cancelled") continue;
        if (appointmentList[i].date == date && appointmentList[i].time == time
            && appointmentList[i].service == service) {
            return true;
        }
    }
    return false;
}

// 数一数某个日期、某个service已经有几笔预约了 (用来检查16个位满了没)
// 数一数某个日期、某个service已经有几笔预约了 (Yoga跟Personal分开算，各自最多16个位)
int countAppointmentsOnDateForService(string date, string service) {
    int total = 0;
    for (int i = 0; i < apptCount; i++) {
        if (appointmentList[i].date == date && appointmentList[i].service == service
            && appointmentList[i].status != "Cancelled") {
            total++;
        }
    }
    return total;
}
