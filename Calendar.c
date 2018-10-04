#include <stdlib.h>

const int gCommonMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const int gLeapMonth[13]   = {0,31,29,31,30,31,30,31,31,30,31,30,31};

int GetMonthDays(int year, int month){
	if(year < 0 || month < 1 || month > 12){
		return -1;
	}
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
		return gLeapMonth[month];
	}
	else{
		return gCommonMonth[month];	
	}
}

int IsLeapYear(int year){
	 if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
		return 1;
	 }
	 else{
		return 0;	
	 }
}

//輸入西元年月日yyyymmdd以及deltaDays，輸出yyyymmdd
int AddDays(int tDate, int deltaDays){
	int mRemain;
	int year, month, day;
	//int* MonthArr;
	year  = tDate / 10000;
	month = (tDate / 100) % 100;
	day   = tDate % 100;

	//測試年份月份是否合法
	if(tDate < 0 || month > 12 || month < 1){
		return -1;
	}

	//決定是否閏年測試天是否合法
	if(day < 1 || day > GetMonthDays(year, month)){
		return -1;
	}

	//若deltaDays是正的，則...
	while(deltaDays > 0){
		mRemain = GetMonthDays(year, month) - day;
		if(mRemain >= deltaDays){
			day += deltaDays;
			deltaDays = 0;
		}else{
			day = 0;
			deltaDays -= mRemain;
			month++;
			if(month == 13){
				month = 1;
				year++;
			}
		}
	}

	//若deltaDays是負的，則...
	while(deltaDays < 0){
		mRemain = day - 1;
		if(mRemain + deltaDays >= 0){
			day += deltaDays;
			deltaDays = 0;
		}else{
			month--;
			deltaDays += mRemain;
			if(month == 0){
				month = 12;
				year--;
				if(year < 0){
					return -1;
				}
			}
			day = GetMonthDays(year, month) + 1;
		}
	}

	return year * 10000 + month * 100 + day;
}
