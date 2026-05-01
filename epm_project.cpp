#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>
using namespace std;

struct Employee {
    long long employeeID = 0;
    string name;
    string username;
    int age = 0;
    long long phone = 0;
    string role;
    double basicSalary = 0;
    double bonus = 0;
    double overtime = 0;
    double tax = 0;
    double netSalary = 0;
    string password;
    double TotalHoursWorked = 0;
    double WorkHoursPerMonth = 0;
};

struct Attendance {
    long long employeeID = 0;
    int month = 0;
    int daysPresent = 0;
    int daysAbsent = 0;
};

struct AdminAccount {
    long long adminID = 0;
    string name;
    string username;
    string password;
};


// Constants
const int MAX_EMPLOYEES = 100;
const int MAX_ATTENDANCE = 200;
const int MAX_ADMINS = 2;
const double TaxRate = 0.14;


// Function Declarations
void showMainMenu();
void handleAdmin();
void handleEmployee();
int getValidInt();
long long getValidId();

// Employee Functions Declarations
bool employeeLogin();
void viewPersonalInfo();
void viewSalary(long long empId);
void viewAttendance();

// Admin Functions Declarations
bool adminLogin();
void addEmployee();
void updateEmployee(long long empId);
void deleteEmployee();
void recordAttendance();
void deleteAttendance();
void updateAttendance(long long empId);
void calculateSalary(long long empId);
void viewAllEmployeesData();


// Storage
void loadEmployees();
void saveEmployees();
void loadAdmins();
void saveAdmins();
void loadAttendance();
void saveAttendance();


// Global Variables Definitions
Employee employees[MAX_EMPLOYEES];
Attendance attendanceRecords[MAX_ATTENDANCE];
AdminAccount admins[MAX_ADMINS];

int employeeCount = 0;
int attendanceCount = 0;
int adminCount = 0;
int currentEmployeeIndex = -1;
int currentAdminIndex = -1;


int main() {
    //Load Data
    loadEmployees();
    loadAdmins();
    loadAttendance();
    int choice;

    while (true) {
        showMainMenu();
        choice = getValidInt();

        switch (choice) {
        case 1:
            handleAdmin();
            break;

        case 2:
            handleEmployee();
            break;

        case 3:
            cout << "Exiting system...\n";

            //Save Data Before Exiting
            saveEmployees();
            saveAdmins();
            saveAttendance();

            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

void showMainMenu() {
    cout << "\n===== Employee Payroll Management System =====\n";
    cout << "1. Admin Login\n";
    cout << "2. Employee Login\n";
    cout << "3. Exit\n";
    cout << "Choose: ";
}  // youssef 


void handleAdmin() {
    if (adminLogin()) {
        cout << "\n========================================\n";
        cout << "           Login Successful\n";
        cout << "           Welcome, " << admins[currentAdminIndex].name << "!\n";
        cout << "========================================\n";
        int choice_admin;
        long long  empId;
        while (true) {
            cout << "\n===== Admin Menu =====\n";
            cout << "1. Add/Update Employee\n";
            cout << "2. Delete Employee\n";
            cout << "3. Record/Update Attendance\n";
            cout << "4. Delete Attendance\n";
            cout << "5. Calculate Salary\n";
            cout << "6. View All Employees Data\n";
            cout << "7. Logout\n";
            cout << "Choose: ";
            choice_admin = getValidInt();
            switch (choice_admin) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                recordAttendance();
                break;
            case 4:
                deleteAttendance();
                break;
            case 5: {
                cout << "\n========================================\n";
                cout << "           Calculate Salary            \n";
                cout << "========================================\n";
                cout << "Note: Salary will be calculated based on the current attendance and hours data for the employee.\n";
                cout << "Formula is (Basic Salary + Bonus) - Tax\n";
                cout << "Enter Employee ID to calculate salary: ";
                empId = getValidId();
                calculateSalary(empId);
                viewSalary(empId);
                break;
            }
            case 6:
                viewAllEmployeesData();
                break;
            case 7:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }


    }
    else {
        cout << "\nError: Invalid username or password\n";
    }
}


void handleEmployee() {

    int chance = 3;
    bool loggedIn = false;

    while (chance > 0) {
        if (employeeLogin()) {
            loggedIn = true;
            cout << "\n========================================\n";
            cout << "           Login Successful\n";
            cout << "           Welcome, " << employees[currentEmployeeIndex].name << "!\n";
            cout << "========================================\n";
            break;
        }

        chance--;
        cout << "Invalid credentials (" << chance << " attempts left)\n";
    }

    if (!loggedIn) {
        cout << "Access denied!\n";
        return;
    }

    int choice;

    while (true) {
        cout << "\n===== Employee Menu =====\n";
        cout << "1. View Personal Information\n";
        cout << "2. View Salary Information\n";
        cout << "3. View Attendance Record\n";
        cout << "4. Logout\n";
        cout << "Choose: ";
        choice = getValidInt();

        switch (choice) {
        case 1:
            viewPersonalInfo();
            break;

        case 2:
            calculateSalary(employees[currentEmployeeIndex].employeeID);
            viewSalary(employees[currentEmployeeIndex].employeeID);
            break;

        case 3:
            viewAttendance();
            break;

        case 4:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

bool adminLogin() {
    cout << "\n==================================\n";
    cout << "           Admin Login\n";
    cout << "==================================\n";
    string adminname;
    string adminpass;
    cout << "Enter Username: ";
    getline(cin >> ws, adminname);
    cout << "Enter Password: ";
    getline(cin, adminpass);

    for (int i = 0; i < adminCount; i++) {
        if (admins[i].username == adminname && admins[i].password == adminpass) {
            currentAdminIndex = i;
            return true;
        }
    }
    return false;
} // mahmoud

bool employeeLogin()
{
    cout << "\n==================================\n";
    cout << "          Employee Login\n";
    cout << "==================================\n";
    string Username;
    string Password;

    cout << "Enter your username: ";
    getline(cin >> ws, Username);
    cout << "Enter your password: ";
    getline(cin, Password);

    for (int i = 0; i < employeeCount; i++)
    {
        if (employees[i].username == Username && employees[i].password == Password)
        {
            currentEmployeeIndex = i;
            return true;

        }


    }
    return false;
} // ahmed 

//Storage functions
void loadEmployees() {
    ifstream in("employees.txt");

    if (!in) {
        cout << "ERROR: employees.txt not found in execution folder\n";
        return;
    }

    employeeCount = 0;

    while (employeeCount < MAX_EMPLOYEES) {
        Employee& e = employees[employeeCount];

        // 1. Read ID
        if (!(in >> e.employeeID)) break;
        in.ignore();

        // 2 & 3. Read Name and Username
        getline(in, e.name, '|');
        getline(in, e.username, '|');

        // 4. Read Age
        in >> e.age;
        in.ignore();

        // 5 & 6. Read Phone and Role
        in >> e.phone;
        in.ignore();
        getline(in, e.role, '|');

        // 7 to 11. Read Salary & Financials
        in >> e.basicSalary;
        in.ignore();

        in >> e.bonus;
        in.ignore();

        in >> e.overtime;
        in.ignore();

        in >> e.tax;
        in.ignore();

        in >> e.netSalary;
        in.ignore();

        // 12. Read Password
        getline(in, e.password, '|');

        // 13 & 14. Read Hours
        in >> e.TotalHoursWorked;
        in.ignore();

        in >> e.WorkHoursPerMonth;

        // Clear the leftover newline character before the next loop
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        employeeCount++;
    }

    in.close();
    cout << "Loaded " << employeeCount << " employees successfully.\n";
}//yossef

void saveEmployees() {
    ofstream out("employees.txt");

    if (!out.is_open()) {
        cout << "Error: Could not open employees.txt for writing!" << endl;
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        out << employees[i].employeeID << "|"
            << employees[i].name << "|"
            << employees[i].username << "|"
            << employees[i].age << "|"
            << "0" << employees[i].phone << "|"
            << employees[i].role << "|"
            << employees[i].basicSalary << "|"
            << employees[i].bonus << "|"
            << employees[i].overtime << "|"
            << employees[i].tax << "|"
            << employees[i].netSalary << "|"
            << employees[i].password << "|"
            << employees[i].TotalHoursWorked << "|"
            << employees[i].WorkHoursPerMonth << endl;
    }
    out.close();
    cout << "Successfully saved " << employeeCount << " employees to file." << endl;
}

void loadAdmins() {
    ifstream in("admins.txt");
    if (!in) {
        cout << "no file found\n";
        return;
    }
    adminCount = 0;

    while (adminCount < MAX_ADMINS) {

        AdminAccount& a = admins[adminCount];
        if (!(in >> a.adminID)) break;
        in.ignore();
        getline(in, a.name, '|');
        getline(in, a.username, '|');
        getline(in, a.password);
        adminCount++;
    }
    in.close();
}

void saveAdmins() {
    ofstream out("admins.txt");
    for (int i = 0; i < adminCount; i++) {
        out << admins[i].adminID << "|" << admins[i].name << "|" << admins[i].username << "|" << admins[i].password << endl;
    }
    out.close();
}

void loadAttendance() {
    ifstream in("attendance.txt");
    if (!in) {
        cout << "no file found" << endl;
        return;
    }
    attendanceCount = 0;
    while (attendanceCount < MAX_ATTENDANCE) {
        Attendance& a = attendanceRecords[attendanceCount];
        if (!(in >> a.employeeID)) break;
        in.ignore();
        in >> a.month;
        in.ignore();
        in >> a.daysPresent;
        in.ignore();
        in >> a.daysAbsent;
        in.ignore();
        attendanceCount++;
    }
    in.close();
}

void saveAttendance() {
    ofstream out("attendance.txt");
    for (int i = 0; i < attendanceCount; i++) {
        out << attendanceRecords[i].employeeID << "|" << attendanceRecords[i].month << "|"
            << attendanceRecords[i].daysPresent << "|" << attendanceRecords[i].daysAbsent << endl;
    }
    out.close();
}

void viewPersonalInfo()
{

    cout << "\n========================================\n";
    cout << "          Personal Information            \n";
    cout << "========================================\n";
    cout << "Name:     " << employees[currentEmployeeIndex].name << endl;
    cout << "ID:       " << employees[currentEmployeeIndex].employeeID << endl;
    cout << "Age:      " << employees[currentEmployeeIndex].age << endl;
    cout << "Phone:    0" << employees[currentEmployeeIndex].phone << endl;
    cout << "Role:     " << employees[currentEmployeeIndex].role << endl;
    cout << "========================================\n";
} //ahmed

void viewSalary(long long empId) {

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == empId) {

            cout << "\n========================================\n";
            cout << "           Salary Information\n";
            cout << "========================================\n";
            cout << "Employee ID: " << employees[i].employeeID << "\n";
            cout << "Name: " << employees[i].name << "\n";
            //Fixed and setprecision to show 2 decimal places for all financial values
            cout << "Basic Salary: " << fixed << setprecision(2) << employees[i].basicSalary << "\n";
            cout << "Overtime Hours: " << fixed << setprecision(2) << employees[i].overtime << "\n";
            cout << "Bonus: " << fixed << setprecision(2) << employees[i].bonus << "\n";
            cout << "Tax 14% of Basic Salary : " << fixed << setprecision(2) << employees[i].tax << "\n";
            cout << "Net Salary: " << fixed << setprecision(2) << employees[i].netSalary << "\n";
            cout << "========================================\n";
            break;
        }
    }

} // mostafa elhadidy

void viewAttendance() {
    cout << "\n========================================\n";
    cout << "           Attendance Records\n";
    cout << "========================================\n";

    cout << "\n========================================\n";
    cout << "Employee ID: " << employees[currentEmployeeIndex].employeeID << "\n";
    cout << "Name: " << employees[currentEmployeeIndex].name << "\n\n";

    bool found = false;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == employees[currentEmployeeIndex].employeeID) {
            cout << "Month: " << attendanceRecords[i].month << "\n";
            cout << "Days Present: " << attendanceRecords[i].daysPresent << "\n";
            cout << "Days Absent: " << attendanceRecords[i].daysAbsent << "\n";
            cout << "========================================\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No attendance records found for this employee\n";
        cout << "========================================\n";
    }
}// mostafa elhadidy



void addEmployee() {
    cout << "\n========================================\n";
    cout << "          Adding Employee            \n";
    cout << "========================================\n";
    // Check if employee list is full
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee list is full!\n";
        return;
    }

    Employee e;
    cout << "Enter the following details:\n";

    cout << "ID: ";
    e.employeeID = getValidId();

    // Check duplicate ID
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == e.employeeID) {
            char choice;
            cout << "\nExisting Employee found with this ID. Update record? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                cout << "Redirecting to update...\n";
                updateEmployee(e.employeeID);
            }
            else {
                cout << "Operation cancelled. Returning to main menu...\n";
            }
            return;
        }
    }

    //Taking details from user
    cout << "Username: ";
    getline(cin >> ws, e.username);

    cout << "Password: ";
    getline(cin, e.password);

    cout << "Name: ";
    getline(cin, e.name);

    cout << "Phone: ";
    e.phone = getValidId();

    cout << "Role: ";
    getline(cin, e.role);

    cout << "Age: ";
    e.age = getValidInt();

    cout << "Salary: ";
    e.basicSalary = getValidInt();

    employees[employeeCount] = e;
    employeeCount++;

    cout << "\nEmployee added successfully!\n";
    cout << "========================================\n";
    saveEmployees();
}// mostafa2

void updateEmployee(long long empId)
{
    int index = -1;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == empId) {
            index = i;
            break;
        }
    }

    //Warning because there's no input validation for index but we don't need it because we already validate the ID in the calling function (addEmployee)
    cout << "Current Name: " << employees[index].name << endl;
    cout << "Enter New Name: ";
    getline(cin >> ws, employees[index].name);

    cout << "Current Salary: " << employees[index].basicSalary << endl;
    cout << "Enter New Salary: ";
    employees[index].basicSalary = getValidInt();

    cout << "Enter New Password: " << endl;
    getline(cin, employees[index].password);

    cout << "Current Phone: 0" << employees[index].phone << endl;
    cout << "Enter New Phone: ";
    employees[index].phone = getValidId();

    cout << "Current Role: " << employees[index].role << endl;
    cout << "Enter New Role: ";
    getline(cin, employees[index].role);

    cout << "Current Age: " << employees[index].age << endl;
    cout << "Enter New Age: ";
    employees[index].age = getValidInt();


    cout << "Current overtime: " << employees[index].overtime << endl;
    cout << "Enter New overtime: ";
    employees[index].overtime = getValidInt();


    cout << "Current Total Hours Worked: " << employees[index].TotalHoursWorked << endl;
    cout << "Enter New Total Hours Worked: ";
    employees[index].TotalHoursWorked = getValidInt();

    cout << "Current Work Hours Per Month: " << employees[index].WorkHoursPerMonth << endl;
    cout << "Enter New Work Hours Per Month: ";
    employees[index].WorkHoursPerMonth = getValidInt();

    cout << "\nEmployee updated successfully!\n";
    cout << "========================================\n";
    saveEmployees();
} // mostafa2

void calculateSalary(long long empId)
{
    int index = -1;

    //Finding index
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == empId) {
            index = i;
            break;
        }
    }

    //If index is -1 the ID doesn't exist
    if (index == -1) {
        cout << "Error: Employee with ID " << empId << " not found.\n";
        return;
    }

    //Validation if 0 or negative to prevent division by zero and incorrect calculations
    if (employees[index].WorkHoursPerMonth <= 0) {
        cout << "Error: Work Hours Per Month must be greater than 0 to calculate salary.\n";
        return;
    }

    //Calculating overtime
    employees[index].overtime = employees[index].TotalHoursWorked - employees[index].WorkHoursPerMonth;

    //Prevent negative overtime if they worked less than the required hours
    if (employees[index].overtime < 0) {
        employees[index].overtime = 0;
    }

    //Calculating bonus based on overtime
    employees[index].bonus = (employees[index].basicSalary / employees[index].WorkHoursPerMonth) * employees[index].overtime;

    //Calculating tax
    employees[index].tax = (employees[index].basicSalary * TaxRate);

    //Calculating net salary according to the formula: (Basic Salary + Bonus) - Tax
    employees[index].netSalary = (employees[index].basicSalary + employees[index].bonus) - employees[index].tax;

    cout << "\nSalary calculated successfully for Employee ID " << empId << ".\n";
    cout << "========================================\n";
}
// eyad 

void recordAttendance() {
    long long id;
    bool employeeExists = false;
    int month = 0;

    cout << "\n========================================\n";
    cout << "           Record Attendance\n";
    cout << "========================================\n";

    //Get and Validate Employee ID
    while (true) {
        cout << "Enter Employee ID: ";
        id = getValidId();

        employeeExists = false;
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].employeeID == id) {
                employeeExists = true;
                break;
            }
        }

        if (employeeExists) {
            break;
        }
        else {
            cout << "ID not found! Please enter again.\n\n";
        }
    }

    //Validation on month
    while (true) {
        cout << "Enter Month (1-12): ";
        month = getValidInt();

        if (month >= 1 && month <= 12) {
            break;
        }
        else {
            cout << "Error: Month must be between 1 and 12. Try again: ";
        }
    }

    //Check for an existing record
    int recordIndex = -1;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == id && attendanceRecords[i].month == month) {
            recordIndex = i;
            break;
        }
    }

    if (recordIndex != -1) {

        //Giving user the choice to update or cancel
        char choice;
        cout << "\nExisting attendance record found for this ID.";
        cout << "\nWould you like to update it? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "Redirecting to update...\n";
            updateAttendance(id);
        }
        else {
            cout << "Update cancelled. Returning to menu.\n";
        }
        return;
    }

    else {
        //Creating a new record if it doesn't exist
        if (attendanceCount >= MAX_ATTENDANCE) {
            cout << "Error: Attendance records are full.\n";
            cout << "========================================\n";
            return;
        }

        cout << "\nNo existing record found for this ID. Creating a new one.\n";

        //Initializing the new record with ID and Month
        attendanceRecords[attendanceCount].employeeID = id;
        attendanceRecords[attendanceCount].month = month;

        //Validation for Days Present and Absent
        while (true) {
            cout << "Enter Days Present: ";
            while (true) {
                attendanceRecords[attendanceCount].daysPresent = getValidInt();
                if (attendanceRecords[attendanceCount].daysPresent >= 0 && attendanceRecords[attendanceCount].daysPresent <= 31) {
                    break;
                }
                else {
                    cout << "Error: Days Present must be between 0 and 31. Try again: ";
                }
            }

            cout << "Enter New Days Absent: ";
            while (true) {
                attendanceRecords[attendanceCount].daysAbsent = getValidInt();
                if (attendanceRecords[attendanceCount].daysAbsent >= 0 && attendanceRecords[attendanceCount].daysAbsent <= 31) {
                    break;
                }
                else {
                    cout << "Error: Days Absent must be between 0 and 31. Try again: ";
                }
            }
            if (attendanceRecords[attendanceCount].daysPresent + attendanceRecords[attendanceCount].daysAbsent > 31) {
                cout << "Error: Total days cannot exceed 31. Please re-enter the values.\n";
            }
            else {
                break;
            }
        }

        attendanceCount++;

        cout << "\nAttendance recorded successfully.\n";
        cout << "========================================\n";
        saveAttendance();
    }
}//abdelrahman

void updateAttendance(long long empId) {

    cout << "\n========================================\n";
    cout << "           Update Attendance\n";
    cout << "========================================\n";

    //Updating process
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == empId) {

            cout << "Current Days Present: " << attendanceRecords[i].daysPresent << "\n";
            cout << "Current Days Absent: " << attendanceRecords[i].daysAbsent << "\n";


            //Validation for Days Present and Absent
            while (true) {

                cout << "Enter New Days Present: ";
                while (true) {
                    attendanceRecords[i].daysPresent = getValidInt();
                    if (attendanceRecords[i].daysPresent >= 0 && attendanceRecords[i].daysPresent <= 31) {
                        break;
                    }
                    else {
                        cout << "Error: Days Present must be between 0 and 31. Try again: ";
                    }
                }

                cout << "Enter New Days Absent: ";
                while (true) {
                    attendanceRecords[i].daysAbsent = getValidInt();
                    if (attendanceRecords[i].daysAbsent >= 0 && attendanceRecords[i].daysAbsent <= 31) {
                        break;
                    }
                    else {
                        cout << "Error: Days Absent must be between 0 and 31. Try again: ";
                    }
                }
                if (attendanceRecords[i].daysPresent + attendanceRecords[i].daysAbsent > 31) {
                    cout << "Error: Total days cannot exceed 31. Please re-enter the values.\n";
                }
                else {
                    break;
                }
            }


            cout << "\nAttendance updated successfully!\n";
            cout << "========================================\n";

            saveAttendance();
            break;
        }
    }

}//eyad

void deleteAttendance() {
    long long id;
    int month;
    bool found = false;

    cout << "\n========================================\n";
    cout << "            Delete Attendance\n";
    cout << "========================================\n";

    //Searching for employee
    while (true) {
        cout << "Enter Employee ID: ";
        id = getValidId();
        found = false; //Reset found flag for ID search

        for (int i = 0; i < attendanceCount; i++) {
            if (attendanceRecords[i].employeeID == id) {
                found = true;
                break;
            }
        }

        if (found) {
            break;
        }
        else {
            cout << "ID not found! Please enter again.\n\n";
        }
    }

    //Validation on month
    while (true) {
        cout << "Enter Month (1-12) to delete: ";
        month = getValidInt();

        if (month >= 1 && month <= 12) {
            found = false;
            for (int i = 0; i < attendanceCount; i++) {
                if (attendanceRecords[i].employeeID == id && attendanceRecords[i].month == month) {
                    found = true;
                    break;
                }
            }

            if (found) {
                break;
            }
            else {
                cout << "Error: Month not found for this employee. Please try again.\n\n";
            }
        }
        else {
            cout << "Error: Month must be between 1 and 12. Try again.\n\n";
        }
    }

    //Delete the record
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == id && attendanceRecords[i].month == month) {

            //Shift elements to the left to delete
            for (int j = i; j < attendanceCount - 1; j++) {
                attendanceRecords[j] = attendanceRecords[j + 1];
            }

            attendanceCount--;

            cout << "\nAttendance record deleted successfully.\n";
            cout << "========================================\n";

            saveAttendance();
            break;
        }
    }
}//mostafa hadidi

void deleteEmployee() {
    long long id;
    bool found = false;
    cout << "\n========================================\n";
    cout << "           Delete Employee\n";
    cout << "========================================\n";

    //Searching for employee
    while (true) {
        cout << "Enter Employee ID: ";
        id = getValidId();

        found = false;
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].employeeID == id) {
                found = true;
                break;
            }
        }

        if (found) {
            break;
        }
        else {
            cout << "ID not found! Please enter again.\n\n";
        }
    }

    for (int j = 0; j < employeeCount; j++) {
        if (employees[j].employeeID == id) {
            found = true;

            //Shift elements to the left to delete
            for (int k = j; k < employeeCount - 1; k++) {
                employees[k] = employees[k + 1];
            }

            cout << "\nEmployee with ID " << id << " deleted successfully.\n";
            cout << "========================================\n";

            employeeCount--;
            //To delete attendance records too
            for (int a = attendanceCount - 1; a >= 0; a--) {
                if (attendanceRecords[a].employeeID == id) {
                    //Shift elements to the left to delete
                    for (int m = a; m < attendanceCount - 1; m++) {
                        attendanceRecords[m] = attendanceRecords[m + 1];
                    }
                    attendanceCount--;
                }
            }
            saveEmployees();
            saveAttendance();
            break;
        }
    }

}//abdelrahman

int getValidInt() {
    int value;

    while (true) {
        cin >> value;

        //Check if the input was successful (!cin.fail()) AND meets your criteria (> 0)
        if (!cin.fail() && value >= 0) {

            //Clear the rest of the input buffer to prevent leftover characters from interfering with future inputs
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }


        //Reset the error flags on cin so it can be used again
        cin.clear();

        //Throws away the bad input so the loop can start again
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input! Please enter a number: ";
    }
}

//Same logic as getValidInt but for long long type to handle larger numbers like IDs and phone numbers
long long  getValidId() {
    long long id;
    while (true) {
        cin >> id;

        if (!cin.fail() && id >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return id;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }
}

void viewAllEmployeesData() {
    cout << "\n========================================\n";
    cout << "          All Employees Report          \n";
    cout << "========================================\n";

    if (employeeCount == 0) {
        cout << "\nNo employees found in the system.\n";
        cout << "========================================\n";
        return;
    }

    //Save the original index
    int originalIndex = currentEmployeeIndex;

    //Loop through all employees
    for (int i = 0; i < employeeCount; i++) {
        cout << "\n\n>>>>>>>>>> EMPLOYEE #" << (i + 1) << " <<<<<<<<<<";

        // Temporarily trick the program into thinking 'i' is the logged-in employee
        currentEmployeeIndex = i;

        //View data
        viewPersonalInfo();
        viewSalary(employees[currentEmployeeIndex].employeeID);
        viewAttendance();
    }

    //Restore original index
    currentEmployeeIndex = originalIndex;

}//mahmoud 
