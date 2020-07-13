#include "std_lib_facilities.h"
//#include "calculator00.cpp"

const char number = 8;
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";


class Variable
{
    public:
        string name;
        double value;
        Variable(string n,double v):name(n),value(v)
        {

        }
};
vector<Variable> var_table;

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

class Token_stream
{
    public:
        Token_stream();
        Token get();
        void putback(Token t);
        void ignore(char c);
    private:
        bool full;
        Token buffer;
};
Token_stream ts;

void Token_stream::ignore(char c)
{
    if(full && c==buffer.kind)
    {
        full=false;
        return;
    }
    full=false;
    char ch =0;
    while(cin>>ch)
    {
        if(ch==c)return;
    }
}

Token_stream::Token_stream()
    :full(false),buffer(0)
    {

    }

void Token_stream::putback(Token t)
{   
    if(full)error("buffer is full");

    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if(full)
    {
        full=false;
        return buffer;
    }
    char ch;
    cin >> ch;

    switch(ch)
    {
        case print:
        case quit: 
        case '(': 
        case ')': 
        case '+': 
        case '-': 
        case '*': 
        case '/':
        case '%':
            return Token(ch);
        
        case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8':
        case '9': case '.':
            {
              cin.putback(ch);
              double val;
              cin >> val;
              return Token(number,val); 
            }
        default:
            error("unxepcted leksem");
    }
}

double primary();
double term();

double expression()
{
    double left = term();
    Token t = ts.get();

    while(true)
    {
        switch(t.kind)
        {
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;    
        }

    }
    
}

double term()
{
    double left = primary();
    Token t = ts.get();

    while(true)
    {
        switch(t.kind)
        {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if(d == 0) error("divinit 0");
                left /= d;
                t = ts.get();
                break;
            }
            case '%':
                {
                    double d = primary();
                    int i1 = int(left);
                    if(i1 !=left)
                        error("left operator not int");
                    int i2 = int(d);
                    if(i2 !=d) error("right operator not int");
                    if(i2 ==0) error("divinit 0");

                    left = i1%i2;
                    t=ts.get();
                    break;
                }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double primary()
{
    Token t = ts.get();

    switch(t.kind)
    {
        case '(':
        {
            double d = expression();
            t = t = ts.get();
            if (t.kind != ')') error("epected )");
            return d;
        }
        case number:
            return t.value;
        case '-':
            return t.value;
        case '+':
            return t.value;        
        default:
            error("expected expected primary");
    }
}
void clean_up_mess()
{
   ts.ignore(print);
}
void calculate()
{ 
    while (cin)
        {
            try
            {   
                cout << prompt;
                Token t = ts.get();
                while(t.kind ==print) t=ts.get();

                if (t.kind == quit) return;
                
                ts.putback(t);
                cout << result << expression() << endl;
            }
            catch(exception& e){
                cerr<< e.what() << endl;
                clean_up_mess();
            }    
        }
}

double get_value(string s)
{
    for(int i=0;i<var_table.size(); ++i)
    {
        if(var_table[i].name==s)return var_table[i].value;
        error("get: неопределенная переменая", s);
    }
}

void set_value(string s,double d)
{
    for(int i=0;i<var_table.size(); ++i)
    {
        if(var_table[i].name==s){
            var_table[i].value=d;
            return;
        }
        error("set: неопределенная переменая", s);
    }
}

int main()
{
    try
    {
        // double val = 0;
        // cout << "> ";
        calculate();
        keep_window_open();
        return 0;
    }
    catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
        keep_window_open("~~");
        return 1;    
    }
    catch (...) {  
        cerr << "Oops: unknown exception!\n";
         keep_window_open("~~");
    return 2;
    }
}