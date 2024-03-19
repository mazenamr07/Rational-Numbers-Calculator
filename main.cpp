#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

// Function to remove spaces from a string
string removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

// Function to check if input is a valid number
bool number_check(string number) {
    int decimal_check = 0;
    int sign_check = 0;
    number = removeSpaces(number);

    if (number.empty()) {
        return false;
    }
    if (!isdigit(number[number.size() - 1])) {
        return false;
    }
    if (!isdigit(number[0])) {
        if (number[0] != '+' and number[0] != '-') {
            return false;
        }
    }
    int check = -2;
    for (int i = 0; i < number.size(); i++) {
        if (decimal_check > 1 or sign_check > 2) {
            return false;
        }
        if (!isdigit(number[i])) {
            if (number[i] == '/' or number[i] == '.') {
                decimal_check += 1;
                check = i;
            } else if ((number[i] == '+' or number[i] == '-') and number[check] != '.'
            and (i == 0 or i == check + 1)) {
                sign_check += 1;
            } else {
                return false;
            }
        }
    }
    return true;
}

// Function to check if input is a valid operation
bool operationCheck(char operation) {
    char validOperations[4] = {'+', '-', '*', '/'};

    if (operation == ' ') {
        return false;
    }
    bool check = any_of(begin(validOperations), end(validOperations),
                        [operation](char i) {return operation == i;});
    if (!check) {
        return false;
    }
    return true;
}

// Function to convert rational number string to double
double fractionDec(string fraction ) {
    if (fraction.find('/') == string::npos) {
        fraction = fraction + "/1";
    }

    stringstream ss(fraction);
    double numerator, denominator;
    char slash;
    ss >> numerator >> slash >> denominator;

    return static_cast <double>(numerator) / denominator;
}

void menu() {
    cout << "**Welcome to Rational Number Calculator**" << endl;
    while (true) {
        string choice;
        cout << "Choose your way of entering numbers (type 0 to exit)\n"
                "1- 1/2 + 1/4\n"
                "2- 1/2 (enter)\n"
                "   +   (enter)\n"
                "   1/4 (enter)" << endl << ">>";
        getline(cin, choice);

        // Checking if input is valid
        while (choice != "0" and choice != "1" and choice != "2") {
            cout << "Please select a valid option\n"
                    ">>";
            getline(cin, choice);
        }
        if (choice == "0") { // Exiting the program
            cout << "Bye bye!";
            break;
        }

        // Taking in numbers and operation
        string number_1, number_2, operationX;
        if (choice == "1") {
            cout << "Please enter two numbers and an operation:\n"
                    "(e.g. 1/2 + 1/4, 5/3 - 3/5)\n"
                    ">>";

            string expression;
            char operation = 0;
            getline(cin, expression);

            stringstream ss(expression);
            ss >> number_1 >> operation >> number_2;

            // Checking if both numbers and operation are valid
            while (!number_check(number_1) or !number_check(number_2)
            or !operationCheck(operation) or fractionDec(number_1) == numeric_limits<double>::infinity()
            or fractionDec(number_2) == numeric_limits<double>::infinity()
            or (operation == '/' and fractionDec(number_2) == 0)) {

                if (!number_check(number_1)
                or fractionDec(number_1) == numeric_limits<double>::infinity()) {
                    cout << "Number 1 is invalid, enter expression again:\n"
                            ">>";

                    getline(cin, expression);
                    ss.str(""); // Clearing content
                    ss.clear(); // Clearing any error flags
                    ss << expression;
                    ss >> number_1 >> operation >> number_2;
                }
                else if (!number_check(number_2)
                or fractionDec(number_2) == numeric_limits<double>::infinity()) {
                    cout << "Number 2 is invalid, enter expression again:\n"
                            ">>";

                    getline(cin, expression);
                    ss.str(""); // Clearing content
                    ss.clear(); // Clearing any error flags
                    ss << expression;
                    ss >> number_1 >> operation >> number_2;
                }
                else {
                    cout << "Operation is invalid, enter expression again:\n"
                            ">>";

                    getline(cin, expression);
                    ss.str(""); // Clearing content
                    ss.clear(); // Clearing any error flags
                    ss << expression;
                    ss >> number_1 >> operation >> number_2;
                }
            }
            operationX += operation;
        }
        else if (choice == "2") {
            cout << "Please enter two numbers and an operation:\n"
                    "(e.g. 1/2 + 1/4, 5/3 - 3/5)\n"
                    "1st Number >>";
            getline(cin, number_1);

            string operation;
            // checking if 1st number is valid
            while (!number_check(number_1)
                   or fractionDec(number_1) == numeric_limits<double>::infinity()) {
                cout << "Number is invalid, enter again:\n"
                        ">>";
                getline(cin, number_1);
            }
            cout << "Operation >>";
            getline(cin, operation);
            char op = operation[0];

            // checking if operation is valid
            while (!operationCheck(op) or operation.size() > 1) {
                cout << "Operation is invalid, enter again:\n"
                        ">>";
                getline(cin, operation);
                op = operation[0];
            }
            cout << "2nd Number >>";
            getline(cin, number_2);

            // checking if 2nd number is valid
            while (!number_check(number_2)
                   or fractionDec(number_2) == numeric_limits<double>::infinity()
                   or (operation == "/" and fractionDec(number_2) == 0)) {

                if (operation == "/" and fractionDec(number_2) == 0) {
                    cout << "(Operation chosen '/')Unable to divide by zero, enter again:\n"
                            ">>";
                    getline(cin, number_2);
                    continue;
                }
                cout << "Number is invalid, enter again:\n"
                        ">>";
                getline(cin, number_2);
            }
            operationX += operation;
        }

        // Adjusting numbers with signs
        string numberX_1, numberX_2;
        int minusSign = 0;
        bool negative_1 = false;

        for (char digit : number_1) { // Checking if 1st number is negative
            if (digit == '+') {
                continue;
            } else if (digit == '-') {
                minusSign += 1;
                continue;
            }
            numberX_1 += digit;
        }
        if (minusSign == 1) {
            negative_1 = true;
        }

        minusSign = 0;
        bool negative_2 = false;

        for (char digit : number_2) { // Checking if 2nd number is negative
            if (digit == '+') {
                continue;
            } else if (digit == '-') {
                minusSign += 1;
                continue;
            }
            numberX_2 += digit;
        }
        if (minusSign == 1) {
            negative_2 = true;
        }

        // Performing actual calculations
        double double_1, double_2, result = 0;

        // Converting numbers to double
        if (numberX_1.find('/') != string::npos) {
            double_1 = fractionDec(numberX_1);
        }
        else {
            double_1 = stod(numberX_1);
        }
        if (numberX_2.find('/') != string::npos) {
            double_2 = fractionDec(numberX_2);
        }
        else {
            double_2 = stod(numberX_2);
        }

        // Assigning signs to each number
        if (negative_1) {
            double_1 = 0 - double_1;
        }
        if (negative_2) {
            double_2 = 0 - double_2;
        }

        // Calculating final result
        if (operationX == "+") {
            result = double_1 + double_2;
        } else if (operationX == "-") {
            result = double_1 - double_2;
        } else if (operationX == "*") {
            result = double_1 * double_2;
        } else if (operationX == "/") {
            result = double_1 / double_2;
        }

        // Displaying result and looping to reuse the program
        cout << "That would be:" << ' ' << result << endl << endl;
    }
}

int main() {
    menu();
}