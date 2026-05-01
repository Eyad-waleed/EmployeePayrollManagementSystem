# Employee Payroll Management System

The **Employee Payroll Management System** is a lightweight, file-based C++ application that provides role-based access control for Administrators and Employees. It manages personal data, tracks working hours and monthly attendance, and automates salary calculations based on standard basic pay, overtime bonuses, and tax deductions. All data is persisted locally using text files.

---

## 🏗️ System Architecture

### Entity-Relationship Structure
* **Employee to Attendance (1:M):** One employee entity maps to multiple attendance records. They are linked via the `employeeID` attribute.
* **AdminAccount:** A standalone entity used strictly for administrative authentication and control.

### System Architecture & Control Flow
* **Persistent Storage:** The layer maintaining the `employees.txt`, `admins.txt`, and `attendance.txt` files. Data is loaded sequentially into arrays upon startup and written back upon exiting.
* **Main Controller:** Prompts the user with the Main Menu. Based on the selected choice, the controller directs the flow to either the Admin Module or the Employee Module.
* **Admin Module:** Features Read/Write state privileges interacting directly with the global arrays (Runtime Memory).
* **Employee Module:** Features Read-Only state privileges, allowing users to securely view but not mutate global arrays.

---

## 🔐 User Roles & Access

### 🛠️ Administrator Role
Administrators have full access to the system to manage personnel and payroll. The Admin menu includes the following capabilities:
* **Add/Update Employee:** Allows the admin to create a new employee profile or update an existing one.
* **Delete Employee:** Removes an employee from the system entirely.
* **Record/Update Attendance:** Logs the days present and days absent for a specific employee.
* **Delete Attendance:** Removes a logged attendance record.
* **Calculate Salary:** Triggers the system's financial calculation logic for a designated employee.
* **View All Employees Data:** Generates a comprehensive report displaying personal info, salary data, and attendance records.

### 👤 Employee Role
Employees have restricted, read-only access limited strictly to their own data. They are allowed a maximum of 3 login attempts.
* **View Personal Information:** Displays Name, ID, Age, Phone, and Role.
* **View Salary Information:** Displays the latest calculated Basic Salary, Bonus, Overtime, Tax, and Net Salary.
* **View Attendance Record:** Shows all logged attendance data.

---

## 💰 Salary Calculation Logic

The calculation handles the financial math for the payroll. The global constant `TaxRate` is set to **0.14 (14%)**.

1. **Overtime Calculation:** `Overtime = TotalHoursWorked - WorkHoursPerMonth`
2. **Bonus Calculation:** `Bonus = (Basic Salary / WorkHoursPerMonth) * Overtime`
3. **Tax Deduction:** `Tax = Basic Salary * 0.14`
4. **Net Salary:** `Net Salary = (Basic Salary + Bonus) - Tax`

---

## 🗄️ Core Data Structures & Persistence

### Data Structures
| Structure Name | Description |
|---|---|
| **Employee** | Stores all relevant personal, operational, and financial data for a single employee. |
| **Attendance** | Tracks the monthly attendance record for an employee, logging days present and absent. |
| **AdminAccount** | Stores credentials and details for administrative users. |

### Data Persistence
To ensure data is not lost when the program closes, the system utilizes text files:
* `employees.txt`: Stores all Employee structures.
* `admins.txt`: Stores AdminAccount structures.
* `attendance.txt`: Stores all attendance records.

---

## 👥 Team Information & Contributions

| Team Member | Student ID | Program | Contributions / Modules Worked On |
|---|---|---|---|
| **Eyad Waleed Ali Hassan** | 20251701506 | Cyber security | Calculated salary, updated attendance, overall project structure, data validation, and bug fixing. |
| **Mahmoud Walid Mohamed Aziz ElSayed Elgohary** | 20251701533 | Cyber security | Admin-login and handle-admin menu. |
| **Mostafa Ahmed Mostafa Mahmoud Ali Rabie** | 20251701536 | Cyber security | Add employee and update employee functions. |
| **Abdelrahman Mohamed Talaat Arafa** | 20251701721 | Software engineering | Delete employee and record attendance functions. |
| **Ahmed Ayman Fikry Abdelkhalek** | 20251701500 | Cyber security | Employee login and view personal info functions. |
| **Mostafa Mahmoud Mohamed Alhadidi** | 20251701639 | Artificial intelligence | View salary, view attendance, and delete attendance functions. |
| **Youssef Mohamed Ibrahim Arnous** | 20251701643 | Artificial intelligence | Storage handling, overall project structure, data validation, and bug fixing. |
