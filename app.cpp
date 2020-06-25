#include "std_lib_facilities.h"

int main()
{
    cout << "(=,-,*,/)\n >> ";
    int lval = 0;
    int rval;
    char op;
    cin >> lval;

    if (!cin)
        error("Нет первого операнда ");

    while (cin >> op)
    {
        cin >> rval;
        if (!cin)error("Нет второго оперранда");

        switch (op)
        {
            case '+':
                lval += rval;
                cout << "!\n";
                break;
            case '-':
                lval -= rval;
                break;
            case '*':
                lval *= rval;
                break;
            case '/':
                lval /= rval;
                break;
            default:
                cout << "result: " << lval << '\n';
                return 0;
        }
    }

    error("no operations!");
}