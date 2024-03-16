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

}
int result(){
    string num;
    double sum = '0.0';
    cout << "enter what u want: ";
    while (getline(cin,num,'+')){
        sum += fract_dec(num);
        cout << sum << endl;
    }
     return 0;
}
