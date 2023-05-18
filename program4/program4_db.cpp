#include <iostream>
#include <string>

using namespace std;

// Employee abstract class
class Employee {
    protected:
        string name;
        int id;
        char employee_class;
        double base_salary;
        double profit_share;
        double salary;
    public:

        // pure virtual method for calculating salary
        virtual void calculate_salary() = 0;

        // shows analysis of all employees' individual data
        virtual void display() {
            cout << "Name: " << name << "\nID: " << id << "\nClass: " \
                 << employee_class << "\nSalary: " << salary << endl;
        }
};

// Owner class
class Owner : public Employee {
    protected:
        int profits;

    public:
        Owner(string n, int i, int p) {
            name = n;
            id = i;
            employee_class = 'O';
            base_salary = 15000;
            profit_share = 0.6 * p;
            salary = 0;
        }

        void calculate_salary() override {
            salary = base_salary + profit_share;
        }

        // add spacing
        void display() override {
            Employee::display();
            cout << endl;
        }        
};

// Chef class
class Chef : public Employee {
    protected:
        int profits;
        string specialty;
    
    public:
        Chef(string n, int i, string s, int p) {
            name = n;
            id = i;
            employee_class = 'C';
            base_salary = 10000;
            profit_share = 0.2 * p;
            specialty = s;
            salary = 0;
        }

        void calculate_salary() override {
            salary = base_salary + profit_share;
        }

        // include additional chef field in display
        void display() override {
            Employee::display();
            cout << "Specialty: " << specialty << "\n\n";
        }
};

// Waiter class
class Waiter : public Employee {
    protected:
        int years; // employee's years of service 
        int tips;
    
    public:
        Waiter(string n, int i, int t, int y) {
            name = n;
            id = i;
            employee_class = 'W';
            base_salary = 3000;
            profit_share = 0;
            tips = t;
            years = y;
            salary = 0;
        }

        void calculate_salary() override {
            salary = base_salary + tips;
        }

        // include additional waiter field in display
        void display() override {
            Employee::display();
            cout << "Years of Service: " << years << "\n\n";
        }
};