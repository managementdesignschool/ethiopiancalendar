package com.tjgwebservices.app;



class EthiopianDate {
  int day;
  int month;
  int year;
    public EthiopianDate(){}
    
    public EthiopianDate(int day, int month, int year){
        this.day =day;
        this.month = month;
        this.year = year;
    }
}


class GregorianDate {
  int day;
  int month;
  int year;
  
  public GregorianDate(){}

  public GregorianDate(int day, int month, int year){
      this.day = day;
      this.month = month;
      this.year = year;
  }
}

public class CalendarConverter {
    double epoch = 1721425.5;
    int[] GregorianDaysPerMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


private EthiopianDate AbsoluteToEthiopic (int absolute) {
EthiopianDate ethdate = new EthiopianDate();

ethdate.year = (int) ((4* (absolute - this.epoch)) + 1463)/1461;
EthiopianDate absdate = new EthiopianDate(1,1,ethdate.year);
ethdate.month = 1 + (absolute - this.EthiopicToAbsolute(absdate))/30;
absdate = new EthiopianDate(1, ethdate.month, ethdate.year);
ethdate.day = (absolute - this.EthiopicToAbsolute(absdate)) + 1;
return ethdate;
}

public boolean isBogusEthiopicDate (EthiopianDate ethdate) {
	if ( !(ethdate.day >=1 && ethdate.day <= 30 ) ||
	!(ethdate.month >= 1 && ethdate.month <= 13 ) ||
        (ethdate.month == 13 && ethdate.day > 6) ||
	(ethdate.month == 13 && ethdate.day == 6 && this.isLeapYear(ethdate.year) )  ){
		return true;
	} else {
		return false;
	}
} 

public boolean isBogusGregorianDate (GregorianDate gredate) {
	if ( !(gredate.month >= 1 && gredate.day <= 12) ||
		!(gredate.day >=1 && gredate.day <= GregorianDaysPerMonth[gredate.month -1]) ||
		(gredate.day == 29 && gredate.month == 2 && !this.isGregorianLeapYear(gredate.year)) ) {
		return true;
	} else {
		return false;
	}
}
 
private int EthiopicToAbsolute(EthiopianDate ethdate){
	return (int) ( this.epoch - 1 + 365 * (ethdate.year - 1) + (ethdate.year/4) + 30 * (ethdate.month - 1) + ethdate.day );
} 
 
private int GregorianYear(int a) {
	int b = a -1;
	int c = b / 146097;
	int d = b % 146097;
	int e = d / 36524;
	int f = d % 36524;
	int g = f / 1461;
	int h = f % 1461;
	int i = h / 365;
	int j = (400 * c) + (100 * e) + (4 * g) + i;

	if ((e == 4) || (i == 4)) {
		return j;
	} else {
		return j + 1;
	}
}

private GregorianDate abSoluteToGregorian (int absolute){
	GregorianDate gredate = new GregorianDate();
	gredate.year = GregorianYear(absolute);
        GregorianDate absdate = new GregorianDate(1,1, gredate.year);
	int priorDays = (absolute - gregorianToAbsolute(absdate));
	int correction;
        absdate = new GregorianDate(1,3, gredate.year);
	if (absolute < this.gregorianToAbsolute(absdate) ) {
		correction = 0;
	} else {
		if (isGregorianLeapYear(gredate.year)) {
			correction = 1;
		} else {
			correction = 2;
		}
	}

	gredate.month = (( 12 * (priorDays + correction) + 373)/367) / 1;
        absdate = new GregorianDate(1, gredate.month, gredate.year);
        
	gredate.day = absolute - gregorianToAbsolute(absdate) + 1;

	return gredate;
}	
	

 
 private int gregorianToAbsolute(GregorianDate gredate) {
	float absolute;
	int correction;
	if (gredate.month <= 2){
		correction = 2;
	} else {
		if (isGregorianLeapYear(gredate.day)) {
			correction = -1;
		} else {
			correction = -2;
		}

	}

	absolute = (365 *
		((gredate.year - 1)/4) +
		((gredate.year - 1)/100) -
		((gredate.year - 1)/400) +
		((367 * gredate.month - 362) /12) +
		correction + gredate.day);
        int abso = (int) Math.floor(absolute);
	return abso;
 
}

private boolean isGregorianLeapYear(int year) {
	if (
		((year % 4) != 0) || ((year % 400) == 100) || ((year % 400) == 200) || ((year % 400) == 300)
	) {
		return false;
	} else {
		return true;
	}
}


private boolean isLeapYear(int year){
	if ( ( (year + 1) % 4) == 0) {
		return false;
	} else {
		return true;
	}
} 
 
}

