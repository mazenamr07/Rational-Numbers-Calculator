#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

double fract_dec(const string & fract ){
    stringstream ss(fract);
    double nume , denm ;
    char slsh;
    ss >> nume >> slsh >> denm;

    return static_cast <double>(nume) / slsh;

// Function to erase spaces from a string
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

void menu() {
    cout << "**Welcome to Rational Number Calculator**" << endl;
    while (true) {
        string choice;
        cout << "Firstly, choose your way of entering numbers (type 0 to exit)\n"
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

        if (choice == "0") {
            cout << "Bye bye!";
            break;
        }

        string number_1, number_2, operation;
        cout << "Please enter two numbers and an operation:\n"
                "(e.g. 1/2 + 1/4, 5/3 - 3/5)\n"
                "1st Number >>";

        if (choice == "1") {
            getline(cin, number_1, ' ');
            getline(cin, operation, ' ');
            getline(cin, number_2);

            while (!number_check(number_1) or !number_check(number_2)) {
                cout << "Operation is invalid, enter again:";
                getline(cin, number_1, ' ');
                getline(cin, operation, ' ');
                getline(cin, number_2);
            }
        }
        else if (choice == "2") {
            getline(cin, number_1);

            while (!number_check(number_1)) {
                cout << "Number is invalid, enter again:\n"
                        ">>";
                getline(cin, number_1);
            }
            cout << "Operation >>";
            getline(cin, operation);

            string operations = "+-*/%";
            while (operations.find(operation) == string::npos or operation.empty()) {
                cout << "Operation is invalid, enter again:\n"
                        ">>";
                getline(cin, operation);
            }
            cout << "2nd Number >>";
            getline(cin, number_2);

            while (!number_check(number_2)) {
                cout << "Number is invalid, enter again:\n"
                        ">>";
                getline(cin, number_2);
            }
        }

        cout << number_1 << endl << operation << endl << number_2;

        break;
    }
}

int main() {

}
