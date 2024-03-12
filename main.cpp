#include <iostream>

using namespace std;

// Function to check if input is a valid number
bool number_check(const string& number) {
    int mini_check = 0;
//    bool digit_count = false;

    if (number[0] == '.' or number[0] == '/') {
        return false;
    }
    if (number[number.size() - 1] == '.' or number[number.size() - 1] == '/') {
        return false;
    }

    for (char digit : number) {
//        if ((digit == '.' or digit == '/') and !digit_count) {
//            return false;
//        }
        if (!isdigit(digit)) {
            if (digit == '.' or digit == '/') {
                mini_check += 1;
            }
            else {
                return false;
            }
        }
//        digit_count = true;
    }
    if (mini_check > 1) {
        return false;
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
            cout << "Please select a valid option" << endl << ">>";
            getline(cin, choice);
        }

        if (choice == "0") {
            cout << "Bye bye!";
            break;
        }

        string number_1, number_2, operation;
        cout << "Please enter two numbers and an operation:\n"
                "(e.g. 1/2 + 1/4, 5/3 - 3/5)" << endl << ">>";

        if (choice == "1") {
            getline(cin, number_1, ' ');
            getline(cin, operation, ' ');
            getline(cin, number_2);

            while (!number_check(number_1) or !number_check(number_2)) {
                cout << "Operation isn't valid, enter again:";
                getline(cin, number_1, ' ');
                getline(cin, operation, ' ');
                getline(cin, number_2);
            }
        }
        else if (choice == "2") {
            getline(cin, number_1);
            cout << ">>";
            getline(cin, operation);
            cout << ">>";
            getline(cin, number_2);
        }

        cout << number_1 << endl << operation << endl << number_2;

        break;
    }
}

int main() {
    menu();
}
