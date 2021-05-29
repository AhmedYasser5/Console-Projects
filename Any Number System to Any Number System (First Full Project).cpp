#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
using namespace std;
//	Adding two numbers (x & y) in a certain base (base)
string add(string x, const string &y, const long long base = 10) {
	unsigned int size = y.size(), carry = 0;
	for (unsigned int i = 0; i < size; i++) {
		while (x.size() <= i)
			x += char(0);
		x[i] += carry + y[i];
		carry = x[i] / base;
		x[i] %= base;
	}
	while (carry) {
		while (size >= x.size())
			x += char(0);
		x[size] += carry;
		carry = x[size] / base;
		x[size++] %= base;
	}
	return x;
}
//	Multiplies a string (x) by a number (y) in base 10
string mul(const string &x, long long y) {
	unsigned int size = x.size(), carry = 0, shift = 0;
	long long tmp;
	string ret;
	while (y) {
		unsigned int i, z = y % 10;
		for (i = 0; i < size; i++) {
			while (ret.size() <= i + shift)
				ret += char(0);
			tmp = ret[i + shift] + x[i] * z + carry;
			carry = tmp / 10;
			ret[i + shift] = tmp % 10;
		}
		while (carry) {
			while (i + shift >= ret.size())
				ret += char(0);
			tmp = ret[i + shift] + carry;
			carry = tmp / 10;
			ret[i++ + shift] = tmp % 10;
		}
		y /= 10;
		shift++;
	}
	return ret;
}
//	Multiplies two strings (x & y) in base 10
string mul_string(const string &x, const string &y) {
	unsigned int size = x.size(), carry = 0, shift = 0, m = y.size();
	long long tmp;
	string ret;
	while (shift < m) {
		unsigned int i, z = y[shift];
		for (i = 0; i < size; i++) {
			while (ret.size() <= i + shift)
				ret += char(0);
			tmp = ret[i + shift] + x[i] * z + carry;
			carry = tmp / 10;
			ret[i + shift] = tmp % 10;
		}
		while (carry) {
			while (i + shift >= ret.size())
				ret += char(0);
			tmp = ret[i + shift] + carry;
			carry = tmp / 10;
			ret[i++ + shift] = tmp % 10;
		}
		shift++;
	}
	return ret;
}
//	Converts the integer part of a decimal string (x) to a string in base (to)
string dvd_rem(string x, const long long &to) {
	unsigned int size;
	long long tmp;
	string ret;
	while (!x.empty()) {
		size = x.size();
		tmp = 0;
		for (int i = size - 1; i >= 0; i--) {
			tmp = tmp * 10 + x[i];
			x[i] = tmp / to;
			tmp %= to;
		}
		ret += char(tmp);
		while (!x.empty() && !x.back())
			x.pop_back();
	}
	while (!ret.empty() && !ret.back())
		ret.pop_back();
	if (ret.empty())
		ret += char(0);
	return ret;
}
//	Converts the fractional part of a decimal (x) to a string in base (to)
//	with at most a specific number of base places (fraction_printing) using rounding to
//	(fraction_printing) base places
//	Rounding may also be caused by the long double type itself
//	If the rounding is to cause an increase in the integer part of the number, the variable
//	(integer_round) counts it
string mul_rem(long double x, const long long &to, const int &fraction_printing,
		int &integer_round) {
	int tmp;
	string ret;
	if (x >= 1) {
		integer_round++;
		x--;
	}
	while ((int) ret.size() < fraction_printing) {
		x *= to;
		tmp = floor(x);
		ret += char(tmp);
		x -= tmp;
	}
	if (floor(x * to) > to / 2) {
		reverse(ret.begin(), ret.end());
		tmp = ret.size();
		ret = add(ret, string(1, 1), to);
		if ((int) ret.size() > tmp) {
			integer_round++;
			ret.pop_back();
		}
		reverse(ret.begin(), ret.end());
	}
	while (!ret.empty() && !ret.back())
		ret.pop_back();
	return ret;
}
//	Prints a number after reversing it if needed
void print(string x, bool r = 0) {
	if (r)
		reverse(x.begin(), x.end());
	for (char &c : x)
		if (c < 10)
			c += '0';
		else
			c += 'A' - 10;
	cout << x;
}
//	Ask the user if he wants to end the program after the current conversion
char anotherIteration() {
	char again;
	cout << "\n\nDo you want another conversion? (y/n): " << flush;
	cin >> again;
	return again;
}
int main() {
	cout << "*****Start of Program*****\n" << endl;
	char again;
	do {
		cout << "Enter the number you want to convert:\n\t" << flush;
		string num;
		cin >> num;
		int size = num.size();
		int base_point = size;
		//	Determining the location of the base point and preparing the string number
		for (int i = 0; i < size; i++)
			if (num[i] != '.') {
				if (num[i] <= '9')
					num[i] -= '0';
				else
					num[i] -= 'A' - 10;
			} else
				base_point = i;
		cout << "Enter the base of the number: " << flush;
		int from;
		cin >> from;
		cout << "Enter the target base: " << flush;
		int to;
		cin >> to;
		//	Checking for the validity of the input
		if (from > 36 || to > 36) {
			cout << "This program is limited to base conversions of at most 36"
					<< endl;
			again = anotherIteration();
			continue;
		}
		bool ok = 1;
		for (const char &c : num)
			if (c != '.' && (c >= from || c < 0)) {
				cout << "Not a valid number" << endl;
				ok = 0;
				break;
			}
		if (!ok) {
			again = anotherIteration();
			continue;
		}
		string integer, tmp(1, 1), fraction_string;
		//	Converting the integer part
		for (int i = base_point - 1; i >= 0; i--, tmp = mul(tmp, from))
			integer = add(integer, mul_string(string(1, num[i]), tmp));
		integer = dvd_rem(integer, to);
		if (base_point < size) {
			cout << "Enter the number of base places needed: " << flush;
			int fraction_printing;
			cin >> fraction_printing;
			//	Checking the validity for the number of base places
			if (fraction_printing < 0) {
				cout << "Number of base places should be non-negative" << endl;
				again = anotherIteration();
				continue;
			}
			long double tmp = 1.0 / from, fraction = 0;
			//	Converting the fractional part
			for (int i = base_point + 1; i < size; i++, tmp /= from)
				fraction += num[i] * tmp;
			int integer_round = 0;
			fraction_string = mul_rem(fraction, to, fraction_printing,
					integer_round);
			while (integer_round--)
				integer = add(integer, string(1, 1), to);
			if (fraction_printing)
				fraction_string += string(
						fraction_printing - fraction_string.size(), 0);
		}
		cout << "The converted number is: " << endl;
		print(integer, 1);
		if (!fraction_string.empty()) {
			cout << '.';
			print(fraction_string);
		}
		cout << endl;
		again = anotherIteration();
	} while (again == 'y');
	cout << "\n*****End of program*****" << endl;
	return 0;
}
