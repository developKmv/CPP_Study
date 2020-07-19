#include<iostream>

int main()
{
    int i =5;
    int& r =i;
    r = 6;
    std::cout << "i = " << i << '\n';
}