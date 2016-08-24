#include <iostream>
#include <cstdlib>

using namespace std;

extern "C" int product(int, int);
extern "C" int power(int, int);

int  main () {
  int  x, y, pro, pow;
    cout << "Please enter the first number: ";
    cin >> x;
    cout << "Please enter the second number: ";
    cin >> y;

    if (x <= 0 || y <= 0) {
        cerr << "The numbers must be positive integers.\n";
        return 1;
    }

    pro = product(x, y);
    cout << "The product of the numbers is: " << pro << endl;

    pow = power(x, y);
    cout << "The exponential of the numbers is: " << pow << endl;

    return 0;
}
