// Name: Aveline Villaganas
// Class (CECS 282-04)
// Project Name (Program 4 - Overloading Operators)
// Due Date (4/12/2022)
//
// I certify that this program is my own original work. I did not copy any part of this program from any other source. 
// I further certify that I typed each and every line of code in this program. 
#ifndef upDate_hpp
#define upDate_hpp
#include <string>
#include <iostream>
using namespace std;

class upDate{
  private:
    int *dptr;
    static int dateCount;
  public:
    upDate();
    upDate(int M, int D, int Y);
    upDate(int J);
    upDate(const upDate &date); 
    ~upDate();
    void setDate(int M, int D, int Y);
    int getMonth();
    int getDay();
    int getYear();
    string getMonthName();
    int julian();
    static int GetDateCount();
    void display();

    void operator=(upDate d1); 
    void operator+=(int days);
    void operator-=(int days);
    friend upDate operator+(upDate d1, int days);
    friend upDate operator+(int days, upDate d1);
    friend upDate operator-(upDate d1, int days);
    //friend upDate operator-(int days, upDate d1);
    //friend upDate operator-(upDate d1, upDate d2); 
    friend int operator-(upDate d1, upDate d2); 
    //friend int operator+(upDate d1, upDate d2); 
    friend ostream &operator<<(ostream &out, upDate d1);
    //void operator++(int nothing);
    upDate operator++(int nothing);
    //void operator++(); 
    upDate operator++();
    //void operator--(int nothing);
    upDate operator--(int nothing);
    //void operator--(); 
    upDate operator--(); 
    bool operator==(upDate d1); 
    bool operator<(upDate d1);
    bool operator>(upDate d1);
};


#endif