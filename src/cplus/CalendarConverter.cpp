#include <iostream>
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <errno.h>        /* errno */

using namespace std;

struct EthiopianDate {
    int year;
    int month;
    int day;
};

struct GregorianDate {
    int year;
    int month;
    int day;
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}



int startDayOfEthiopian(int year) {
  int newYearDay = floor(year / 100) - floor(year / 400) - 4;
  // if the prev ethiopian year is a leap year, new-year occrus on 12th
  if ((year - 1) % 4 == 3){
    return newYearDay + 1;
  } else {
    return newYearDay;
  }
};

GregorianDate toGregorian(EthiopianDate ethDate) {
  // Allow argument to be array year, month, day, or 3 separate params
    int year, month, day, gregorianYear, newYearDay, nextYear, until, m, gregorianDate;

    year = ethDate.year;
    month = ethDate.month;
    day = ethDate.day;
  // Ethiopian new year in Gregorian calendar
  newYearDay = startDayOfEthiopian(year);

  // September (Ethiopian) sees 7y difference
  gregorianYear = year + 7;

  // Number of days in gregorian months
  // starting with September (index 1)
  // Index 0 is reserved for leap years switches.
  // Index 4 is December, the final month of the year.
  int gregorianMonths[14] = {0, 30, 31, 30, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30};

  // if next gregorian year is leap year, February has 29 days.
  nextYear = gregorianYear + 1;
  if ((nextYear % 4 == 0 && nextYear % 100 != 0) || nextYear % 400 == 0) {
    gregorianMonths[6] = 29;
  }

  // calculate number of days up to that date
  until = ((month - 1) * 30.0) + day;
  if (until <= 37 && year <= 1575) { // mysterious rule
    until += 28;
    gregorianMonths[0] = 31;
  } else {
    until += newYearDay - 1;
  }

  // if ethiopian year is leap year, paguemain has six days
  if (year - 1 % 4 == 3) {
    until += 1;
  }

  // calculate month and date incremently
  m = 0;
  gregorianDate;
  for (int i = 0; i < sizeof(gregorianMonths); i++) {
    if (until <= gregorianMonths[i]) {
      m = i;
      gregorianDate = until;
      break;
    } else {
      m = i;
      until -= gregorianMonths[i];
    }
  }

  // if m > 4, we're already on next Gregorian year
  if (m > 4) {
    gregorianYear += 1;
  }

  // Gregorian months ordered according to Ethiopian
  int order[14] = {8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int gregorianMonth = order[m];
    GregorianDate * gregDate = new GregorianDate();
    gregDate->year = gregorianYear;
    gregDate->month = gregorianMonth;
    gregDate->day = gregorianDate;
    return *gregDate;
};

EthiopianDate toEthiopian(GregorianDate gregDate) {

  int year, month, day, ethiopiamYear, newYearDay, until, tahissas, m, ethiopianDay;

    year = gregDate.year;
    month = gregDate.month;
    day = gregDate.day;

  // date between 5 and 14 of May 1582 are invalid
  if (month == 10 && day >= 5 && day <= 14 && year == 1582) {
     perror("Invalid Date between 5-14 May 1582.");
  }

  // Number of days in gregorian months
  // starting with January (index 1)
  // Index 0 is reserved for leap years switches.
  int gregorianMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Number of days in ethiopian months
  // starting with January (index 1)
  // Index 0 is reserved for leap years switches.
  // Index 10 is month 13, the final month of the year
  int ethiopianMonths[15] = {0, 30, 30, 30, 30, 30, 30, 30, 30, 30, 5, 30, 30, 30, 30};

  // if gregorian leap year, February has 29 days.
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
    gregorianMonths[2] = 29;
  }

  // September sees 8y difference
  int ethiopianYear = year - 8;

  // if ethiopian leap year pagumain has 6 days
  if (ethiopianYear % 4 == 3) {
    ethiopianMonths[10] = 6;
  }

  // Ethiopian new year in Gregorian calendar
  newYearDay = startDayOfEthiopian(year - 8);

  // calculate number of days up to that date
  until = 0;
  for (int i = 1; i < month; i++) {
    until += gregorianMonths[i];
  }
  until += day;

  // update tahissas (december) to match january 1st
  if ((ethiopianYear % 4) == 0){
    tahissas =  26;
  } else {
    tahissas =  25;
  }

  // take into account the 1582 change
  if (year < 1582) {
    ethiopianMonths[1] = 0;
    ethiopianMonths[2] = tahissas;
  } else if (until <= 277 && year == 1582) {
    ethiopianMonths[1] = 0;
    ethiopianMonths[2] = tahissas;
  } else {
    tahissas = newYearDay - 3;
    ethiopianMonths[1] = tahissas;
  }

  // calculate month and date incremently
  for (m = 1; m < sizeof(ethiopianMonths); m++) {
    if (until <= ethiopianMonths[m]) {
        if ((m == 1 || ethiopianMonths[m] == 0)){
            ethiopianDay = until + (30 - tahissas);
        } else {
            ethiopianDay = until;
        }
      break;
    } else {
      until -= ethiopianMonths[m];
    }
  }

  // if m > 10, we're already on next Ethiopian year
  if (m > 10) {
    ethiopianYear += 1;
  }

  // Ethiopian months ordered according to Gregorian
  int order[15] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 2, 3, 4};
  int ethiopianMonth = order[m];
    EthiopianDate * ethDate = new EthiopianDate();
    ethDate->year = ethiopianYear;
    ethDate->month = ethiopianMonth;
    ethDate->day = ethiopianDay;
    return *ethDate;
}

