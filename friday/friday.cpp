/*
ID: eulerphi
PROG: friday
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int START_YEAR = 1900;
// 1/13/1900 was a Saturday
// saturday == 0 ... friday == 6
int START_DAY = 0;
int NUM_DAYS = 7;
int NUM_MONTHS = 12;

int GetDaysInMonth(int month, int year) {
  // april, june, sept, nov
  if (month == 3 || month == 5 || month == 8 || month == 10) {
    return 30;
  }

  if (month == 1) {
    bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    return leap ? 29 : 28;
  }

  return 31;
}

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");

    int num_of_years;
    fin >> num_of_years;

    std::vector<int> counts(7);

    int current_day = START_DAY;

    for (int y = 0; y < num_of_years; y++) {
      for (int m = 0; m < NUM_MONTHS; m++) {
        counts[current_day]++;
        current_day = (current_day + GetDaysInMonth(m, START_YEAR + y)) % NUM_DAYS;
      }
    }

    bool first = true;
    for (int &c : counts) {
      if (!first) {
        fout << " ";
      }
      fout << c;
      first = false;
    }
    fout << endl;


    return 0;
}
