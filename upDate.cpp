// Name: Aveline Villaganas
// Class (CECS 282-04)
// Project Name (Program 4 - Overloading Operators)
// Due Date (4/12/2022)
//
// I certify that this program is my own original work. I did not copy any part of this program from any other source. 
// I further certify that I typed each and every line of code in this program.
#include "upDate.h"
#include <iostream>
#include <string>
using namespace std; 
int upDate::dateCount = 0;

// Calendar Conversions ======================

/* Converts date from Gregorian to Julian Calendar 
 * IN: int month, int day, int year
 * OUT: int julian date 
 */
int Greg2Julian(int month, int day, int year){
  double signChunk = 100*year + month - 190002.5;
  int sign = 1; 
  if(signChunk < 0){
    sign = -1;
  }
  int i = year;
  int j = month; 
  int k = day; 
  double JD2 = k-32075+1461*(i+4800+(j-14)/12)/4+367*(j-2-(j-14)/12*12) / 12-3*((i+4900+(j-14)/12)/100)/4; 

  return JD2;
}


/* Converts date from Julian to Gregorian Calendar using pass by reference 
 * IN: int Julian Date, int& month, int& day, int& year
 * OUT: NONE
 */
void Julian2Greg(int JD, int& month, int& day, int& year){
  int i, j, k;
  int l = JD + 68569;
  int n = 4*l/146097;

  l=l-(146097*n+3) / 4;
  i = 4000 * (l+1) / 1461001; 
  l = l-1461*i/4+31;
  j = 80*l/2447;
  k = l-2447*j/80; 
  l=j/11;
  j=j+2-12*l;
  i=100*(n-49)+i+l;

  year = i;
  month = j;
  day = k;

  return; 
}

// upDate ====================================

/* Default Constructor 
 * Set the date to May 11, 1959
 */
upDate::upDate(){
  dptr = new int[3];
  //cout << "yo" << endl; 
  dptr[0] = 5;
  dptr[1] = 11;
  dptr[2] = 1959;
  //cout << "HI";
  dateCount++;
}


/* Overloaded Constructor 
 * Set the date to values passed through parameter list
 * If out of range, set to default date 
 */
upDate::upDate(int M, int D, int Y){
  dptr = new int[3]; 
  //cout << " check 1" << endl;
  // Check for invalid: 
  int monthStore = 0;
  int dayStore = 0; 
  int yearStore = 0; 
  
  int JDtest = Greg2Julian(M, D, Y); 
  Julian2Greg(JDtest, monthStore, dayStore, yearStore);

  //cout << "check 2" << endl; 
  // Not equal to original input -> invalid date  
  if(monthStore != M || dayStore != D || yearStore != Y){
    // Set to default date
    dptr[0] = 5;
    dptr[1] = 11;
    dptr[2] = 1959;
  }else{
    //cout << " check 3" << endl;
    dptr[0] = M;
    dptr[1] = D;
    dptr[2] = Y;
    //cout << "check 4" << endl;
  }
  dateCount++;
  //cout << "check 5" << endl;
}

/* Overloaded Constructor 
 * Create date using Julian date
 */
upDate::upDate(int J){
  dptr = new int[3];
  int monthStore = 0;
  int dayStore = 0;
  int yearStore = 0;
  Julian2Greg(J, monthStore, dayStore, yearStore);
  //cout << monthStore << " " << dayStore << " " << yearStore << endl; 
  dptr[0] = monthStore;
  dptr[1] = dayStore;
  dptr[2] = yearStore;
  dateCount++;
  //cout << "counted" << endl;
}

/* Copy Constructor 
 * Create date using another date 
 */
upDate::upDate(const upDate &date){
  dptr = new int[3];
  dptr[0] = date.dptr[0];
  dptr[1] = date.dptr[1];
  dptr[2] = date.dptr[2];
  dateCount++;
  //cout << dptr[0] << " " << dptr[1] << " " << dptr[2] << endl; 
  //cout << "counted" << endl;
}

/* Destructor
 * De-allocate any memory that was allocated in constructor 
 */
upDate::~upDate(){
  delete []dptr;
  dateCount--;
}

/* Sets the date with inputs parameters like constructor
 * IN: int M (month), int D (day), int Y (year)
 * OUT: None
 */
void upDate::setDate(int M, int D, int Y){
  dptr[0] = M;
  dptr[1] = D;
  dptr[2] = Y;
}

/* Returns the month in integer form   
 * IN: None
 * OUT: Integer 
 */
int upDate::getMonth(){
  return dptr[0];
}

/* Returns the day of the month in integer form   
 * IN: None
 * OUT: Integer 
 */
int upDate::getDay(){
  return dptr[1];
}

/* Returns the year in integer form   
 * IN: None
 * OUT: Integer 
 */
int upDate::getYear(){
  return dptr[2];
}

/* Returns the name of the month 
 * IN: None 
 * OUT: String 
 */
string upDate::getMonthName(){
  string monthNames[12] = {"January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  int monthNum = dptr[0];
  return monthNames[monthNum - 1];  
}

/* Returns the number of upDate objects that currently exist
 * IN: None
 * OUT: Integer
 */
int upDate::GetDateCount(){
  return upDate::dateCount; 
}

/* Returns the julian date of the upDate object
 * IN: None
 * OUT: Integer 
 */
int upDate::julian(){
  int date = Greg2Julian((*this).getMonth(),(*this).getDay(),(*this).getYear());
  return date;
}

/* Displays the date is Month/Day/Year
 * IN: None
 * OUT: None
 */
void upDate::display(){
  cout << (*this).getMonth() << "/" << (*this).getDay() << "/" << (*this).getYear() << endl; 
}

// Operator Overloading ========================

/* Assignment Operator = 
 * upDate = upDate 
 * IN: upDate
 * OUT: None 
 */
void upDate::operator=(upDate d1){
  dptr[0] = d1.getMonth();
  dptr[1] = d1.getDay();
  dptr[2] = d1.getYear();
}

/* upDate += int
 * IN: int days 
 * OUT: None 
 */
void upDate::operator+=(int days){
  int julDate = (*this).julian();
  julDate += days; 
  // Julian2Greg(int JD, int& month, int& day, int& year) 
  Julian2Greg(julDate, dptr[0], dptr[1], dptr[2]);
}

/* upDate -= int 
 * IN: int days
 * OUT: None 
 */
void upDate::operator-=(int days){
  int julDate = (*this).julian();
  julDate -= days; 
  Julian2Greg(julDate, dptr[0], dptr[1], dptr[2]);
}

/* upDate + int 
 * IN: upDate, int days 
 * OUT: upDate 
 */
upDate operator+(upDate d1, int days){
  //cout << "Duck go quack" << endl; 
  upDate d;
  int julDate = d1.julian();
  julDate += days; 
  int monthStore = 0;
  int dayStore = 0;
  int yearStore = 0; 
  Julian2Greg(julDate, monthStore, dayStore, yearStore);
  //d1.setDate(monthStore, dayStore, yearStore); 
  d.setDate(monthStore, dayStore, yearStore);
  //d.display();
  return d;
}

/* int + upDate 
 * IN: int days, upDate
 * OUT: upDate 
 */
upDate operator+(int days, upDate d1){
  //cout << "Yoshi goes nom" << endl;
  upDate d;
  int julDate = d1.julian();
  julDate += days; 
  int monthStore = 0;
  int dayStore = 0;
  int yearStore = 0; 
  Julian2Greg(julDate, monthStore, dayStore, yearStore);
  //d1.setDate(monthStore, dayStore, yearStore); 
  d.setDate(monthStore, dayStore, yearStore);
  return d;
}

/* upDate - int 
 * IN: upDate, int days 
 * OUT: upDate 
 */
upDate operator-(upDate d1, int days){
  //cout << "And I'm singingggg" << endl; 
  upDate d;
  int julDate = d1.julian();
  //cout << "And now to the weather :  :  : " << d1 << endl; 
  julDate -= days; 
  int monthStore = 0;
  int dayStore = 0;
  int yearStore = 0; 
  Julian2Greg(julDate, monthStore, dayStore, yearStore);
  d.setDate(monthStore, dayStore, yearStore);
  //cout << "Here. .. . ";
  //d.display();
  //cout << endl; 
  return d;
}

/* upDate - upDate 
 * *Days between upDate objs, can be negative or positive
 * IN: 2 upDate objects 
 * OUT: Integer
}*/
int operator-(upDate d1, upDate d2){
  //cout << "Golden cats" << endl;
  //upDate d;
  int julDate1 = d1.julian();
  int julDate2 = d2.julian();
  int julDate = julDate1 - julDate2;
  //int monthStore = 0;
  //int dayStore = 0;
  //int yearStore = 0; 
  
  //Julian2Greg(julDate, monthStore, dayStore, yearStore);
  //d.setDate(monthStore, dayStore, yearStore);
  //return d; 
  return julDate; 
}

/* cout << upDate obj 
 * IN: upDate
 * OUT: output format 
 */
ostream &operator<<(ostream &out, upDate d1){
  out << d1.getMonth() << "/" << d1.getDay() << "/" << d1.getYear();
  return out; 
}


/* Postfix style 
 * upDate++ 
 * IN: placeholder to distinguish post and pre 
 * OUT: upDate
}*/
upDate upDate::operator++(int nothing){
  upDate d; 
  //cout << "Post ++" << endl; 
  int julDate = (*this).julian();
  julDate++;
  Julian2Greg(julDate, dptr[0], dptr[1], dptr[2]);
  d.setDate(dptr[0], dptr[1], dptr[2]);
  return d;
}

/* Prefix style
 * ++upDate
 * IN: None
 * OUT: upDate
}*/
upDate upDate::operator++(){
  upDate d; 
  int julDate = (*this).julian();
  ++julDate;
  Julian2Greg(julDate, dptr[0], dptr[1], dptr[2]);
  d.setDate(dptr[0], dptr[1], dptr[2]);
  return d;
}

/* Postfix style 
 * upDate--
 * IN: placeholder to distinguish post and pre 
 * OUT: upDate
}*/
upDate upDate::operator--(int nothing){
  upDate d; 
  //cout << "Post -- 2" << endl;
  int julDate = (*this).julian();
  julDate--; 
  Julian2Greg(julDate, dptr[0], dptr[1], dptr[2]);
  d.setDate(dptr[0], dptr[1], dptr[2]);
  return d;
}

/* Prefix style
 * --upDate
 * IN: None
 * OUT: upDate
}*/
upDate upDate::operator--(){
  upDate d; 
  //cout << "Pre -- 2" << endl;
  int julDate = (*this).julian();
  --julDate; 
  Julian2Greg(julDate, dptr[0], dptr[1], dptr[2]);
  d.setDate(dptr[0], dptr[1], dptr[2]);
  return d;
}


/* Comparison
 * upDate == upDate 
 * IN: upDate
 * OUT: Bool 
 */
bool upDate::operator==(upDate d1){
  if((*this).julian() == d1.julian()){
    return true;
  }
  return false; 
}

/* Comparison
 * upDate < upDate 
 * IN: upDate
 * OUT: Bool 
 */
bool upDate::operator<(upDate d1){
  if((*this).julian() < d1.julian()){
    return true;
  }
  return false; 
}

/* Comparison
 * upDate > upDate 
 * IN: upDate
 * OUT: Bool 
 */
bool upDate::operator>(upDate d1){
  if((*this).julian() > d1.julian()){
    return true;
  }
  return false; 
}