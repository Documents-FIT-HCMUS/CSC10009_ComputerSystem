#include <iostream>
#include <limits.h>
using namespace std;

class CBinary
{
private:
	short int n;
	short int minus_n = 0;
	char arr[16] = { 0 };
	char one[16] = { 0 };
	char opposite[16] = { 0 };
	float dummy;
public:
	void input();
	void output();

	void process();
	void convertToBin();
	void printBinary();

	void addOne();
	void invertBinary();
	void calculateOppositeNum();
	void calculate2complement();

	short int getNumber();
	short int getOppositeNumber();
};

void CBinary::input()
{
	cout << "Nhap so nguyen n (co dau hoac khong dau) nam trong doan [-32768, 32767]: ";
	cin >> dummy;
	while ((dummy - (int)dummy != 0) || (dummy < SHRT_MIN) || (dummy > SHRT_MAX))
	{
		cout << "Ban da nhap sai. Vui long nhap lai: ";
		cin >> dummy;
	}
	n = (short int)dummy;
	one[15] = 1;
}
void CBinary::convertToBin()
{
	short int temp;
	char k;
	temp = n;
	for (int i = 0; i < 16; ++i)
	{
		k = temp >> i;
		k = k & 1;
		arr[16 - i - 1] = k;
	}
}
void CBinary::printBinary()
{
	cout << "N Binary:\t";
	for (int i = 0; i < 16; ++i)
		cout << (int)arr[i] << " ";
	cout << endl;

	cout << "-N Binary:\t";
	for (int i = 0; i < 16; ++i)
		cout << (int)opposite[i] << " ";
	cout << endl;
}

void CBinary::addOne()
{
	int i = 15, temp = 0, k = 0;
	while (i >= 0)
	{
		k = opposite[i] + one[i] + temp;
		switch (k)
		{
		case 0:
			opposite[i] = 0;
			temp = 0;
			break;
		case 1:
			opposite[i] = 1;
			temp = 0;
			break;
		case 2:
			opposite[i] = 0;
			temp = 1;
			break;
		case 3:
			opposite[i] = 1;
			temp = 1;
			break;
		default:
			break;
		}
		i--;
	}
}
void CBinary::invertBinary()
{
	for (int i = 0; i < 16; ++i)
	{
		if (arr[i] == 0) opposite[i] = 1;
		if (arr[i] == 1) opposite[i] = 0;
	}
}
void CBinary::calculate2complement()
{
	invertBinary();
	addOne();
}
void CBinary::calculateOppositeNum()
{
	short int temp = 0;

	for (int i = 0; i < 16; ++i)
	{
		temp = (temp << 1) | opposite[i];
	}
	minus_n = temp;
}

void CBinary::process()
{
	convertToBin();
	calculate2complement();
	calculateOppositeNum();
}

short int CBinary::getNumber()
{
	return n;
}
short int CBinary::getOppositeNumber()
{
	return minus_n;
}

void CBinary::output()
{
	cout << endl << "So N da nhap:\t" << n << endl;
	process();
	printBinary();
	cout << "So doi cua N:\t" << minus_n << endl;
}

int main()
{
	CBinary number; 
	number.input();
	number.output();
	return 0;
}