#include "std_lib_facilities.h"

int main()
{
    cout << "in numbers(= & -): ";
    int lval = 0;
    int rval = 0;
    int res;
    char op;

    cin>>lval>>op>>rval;

    if(op=='+')
        res = lval+rval;
    else if (op=='-')
        res = lval-rval;

    cout << "resul: " << res <<'\n';
    return 0;
}