#include "std_lib_facilities.h"

class Token
{
    public:
        char kind;
        double value;

        Token(char ch)
            :kind(ch),value(0)
            {

            }
        Token(char ch,double val)
            :kind(ch),value(val)
            {

            }          
};

Token get_token(){
    return Token(8);
}

double expression()
{
    double left = term();
    Token t = get_token();

    while(true)
    {
        switch(t.kind)
        {
            case '+':
                left += term();
                t = get_token();
                break;
            case '-':
                left -= term();
                t = get_token();
                break;
            default:
                return left;    
        }

    }
    
}

double term()
{
    double left = primary();
    Token t = get_token();

    while(true)
    {
        switch(t.kind)
        {
            case '*':
                left *= primary();
                break;
            case '/':
            {
                double d = primary();
                if(d == 0) error("divinit 0");
                left /= primary();
                break;
            }
            default:
                return left;
        }
    }
}

int main()
{

}