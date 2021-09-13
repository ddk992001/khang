// COUNTING SUNDAYS

#include <iostream>

using namespace std;

struct Date{
	int day;
	int month;
	int year;
};

int getDay(int day, int month, int year){
	int k = day;
	int m, D, C;
	if (month == 1){
		m = 11;
		D = (year - 1) % 100;
		C = (year - 1) / 100;
	}
	else if (month == 2){
		m = 12;
		D = (year - 1) % 100;
		C = (year - 1) / 100;
	}
	else{
		m = month - 2;
		D = year % 100;
		C = year / 100;
	}
	return k + int((13*m-1)/5) + D + int(D/4) + int(C/4) - 2*C;
}

int solve(Date start, Date end){
	int count = 0;
	int day = start.day;
	int month = start.month;
	int year = start.year;
	while (day <= end.day && month <= end.month && year <= end.year){
		int F = getDay(day, month, year);
		if (F % 7 == 0)
			count++;
		month++;
		if (month > 12){
			month = 1;
			year++;
		}
	}
	return count;
}

int main() {
	Date start, end;
	start.day = 1;
	start.month = 1;
	start.year = 1901;
	end.day = 31;
	end.month = 12;
	end.year = 2000;
	cout << "Result: " << solve(start, end);
	return 0;
}