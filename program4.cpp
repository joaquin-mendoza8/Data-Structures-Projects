#include <iostream>
#include <string>
#include <limits>
#include "program4_db.cpp"

using namespace std;

// method for validating user input
void validate_input(int& input, const string& prompt) {
    cout << prompt;
    bool input_flag = false;
    do {
        cin >> input;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter only integers" << endl;
            cout << prompt;
        } else {
            input_flag = true;
        }
    } while(!input_flag);
    // clear remaining input from the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {

    // constant number of employees
    const int NUM_EMPLOYEES = 6;

    // array of employees
    Employee* employees[NUM_EMPLOYEES]; 

    // prompts for month's restaurant profits
    int restaurant_profit;
    validate_input(restaurant_profit, "This Month's Restaurant Profits: ");

    // prompts for number of waiters
    int num_waiters;
    validate_input(num_waiters, "Number of Waiters: ");

    // prompts for waiters' tips
    int tips[num_waiters];
    for (int i = 0; i < num_waiters; i++) {
        validate_input(tips[i], "Tips for Waiter " + to_string(i+1) + ": ");
    }

    // create employee objs using polymorphism
    Employee* O1 = new Owner("Gandalf The White", 8001, restaurant_profit);
    Employee* C1 = new Chef("Gollum The Rat", 8004, "Seafood", restaurant_profit);
    Employee* C2 = new Chef("Samwise Gamgee", 8005, "Elvish", restaurant_profit);
    Employee* W1 = new Waiter("Frodo Baggins", 8011, tips[0], 3);
    Employee* W2 = new Waiter("Boromir", 8012, tips[1], 5);
    Employee* W3 = new Waiter("Aragorn", 8014, tips[2], 7);

    // add employee objs to array
    employees[0] = O1;
    employees[1] = C1;
    employees[2] = C2;
    employees[3] = W1;
    employees[4] = W2;
    employees[5] = W3;

    // calculate salary for employee objs 
    for (int i = 0; i < NUM_EMPLOYEES; i++)
        employees[i]->calculate_salary();

    // outputs employee statistics
    cout << "====================== EMPLOYEE STATISTICS ======================\n\n";
    for (int i = 0; i < NUM_EMPLOYEES; i++)
        employees[i]->display();
    cout << "=================================================================";

    return 0;
}