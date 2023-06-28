#pragma once
#include <iostream>
#define MAX_SIZE 8
using namespace std;

void input(char&, char&);
void printArray(char[], int);
void output(char a, char b);

void convertToBinary(int, char[]);
char convertToDecimal(char[], int);
void calculate2complement(char[]);
void resetArray(char[]);
void copyArray(char[], char[], int);
void fillArray(char[], char, int);
void shiftRight(char[], int);
void shiftLeft(char[], int);

void add(char[], char[], char[]);
void subtract(char[], char[], char[]);
void multiply(char[], char arrB[], char[]);
void divide(char[], char[], char[], char[]);

void input(char& a, char& b)
{
	float x, y;
	cout << "Nhap 2 so nguyen co dau 8-bit A va B (-128 <= A,B <= 127): ";
	cin >> x >> y;
	
	while ((x - (int)x != 0) || (x < -128) || (x > 127) || (y - (int)y != 0) || (y < -128) || (y > 127))
	{
		cout << "Ban da nhap sai. Vui long nhap lai: ";
		cin >> x >> y;
	}
	a = (char)x;
	b = (char)y;
}
void printArray(char a[], int n = MAX_SIZE)
{
	for (int i = 0; i < n; ++i)
		cout << (int)a[i] << ' ';
	cout << endl;
}

void convertToBinary(int a, char arr[])
{
	char temp = a, k = 0;
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		k = temp >> i;
		k = k & 1;
		arr[MAX_SIZE - i - 1] = k;
	}
}
char convertToDecimal(char arr[], int n = MAX_SIZE)
{
	char result = 0;
	for (int i = 0; i < n; ++i)
	{
		result = (result << 1) | arr[i];
	}
	return result;
}
void calculate2complement(char arr[])
{
	char one[MAX_SIZE] = { 0 };
	one[MAX_SIZE - 1] = 1;
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		if (arr[i] == 0) arr[i] = 1;
		else if (arr[i] == 1) arr[i] = 0;
	}

	int i = MAX_SIZE - 1, temp = 0, k = 0;
	while (i >= 0)
	{
		k = arr[i] + one[i] + temp;
		switch (k)
		{
		case 0:
			arr[i] = 0;
			temp = 0;
			break;
		case 1:
			arr[i] = 1;
			temp = 0;
			break;
		case 2:
			arr[i] = 0;
			temp = 1;
			break;
		case 3:
			arr[i] = 1;
			temp = 1;
			break;
		default:
			break;
		}
		i--;
	}
	return ;
}
void resetArray(char arr[])
{
	for (int i = 0; i < MAX_SIZE; ++i)
		arr[i] = 0;
}
void copyArray(char src[], char dest[], int n = MAX_SIZE)
{
	for (int i = 0; i < 8; ++i)
		dest[i] = src[i];
}
void fillArray(char arr[], char data, int n = MAX_SIZE)
{
	for (int i = 0; i < n; ++i)
		arr[i] = data;
}
void shiftRight(char arr[], int n = MAX_SIZE)
{
	for (int i = n - 1; i > 0; --i)
		arr[i] = arr[i - 1];
}
void shiftLeft(char arr[], int n = MAX_SIZE)
{
	for (int i = 0; i < MAX_SIZE - 1 ; ++i)
		arr[i] = arr[i + 1];
	arr[MAX_SIZE - 1] = 0;
}

void add(char arrA[], char arrB[], char arrRes[])
{
	int i = MAX_SIZE - 1 , temp = 0, k = 0;
	while (i >= 0)
	{
		k = arrA[i] + arrB[i] + temp;
		switch (k)
		{
		case 0:
			arrRes[i] = 0;
			temp = 0;
			break;
		case 1:
			arrRes[i] = 1;
			temp = 0;
			break;
		case 2:
			arrRes[i] = 0;
			temp = 1;
			break;
		case 3:
			arrRes[i] = 1;
			temp = 1;
			break;
		default:
			break;
		}
		i--;
	}
}
void subtract(char arrA[], char arrB[], char arrRes[])
{
	char tempB[MAX_SIZE] = { 0 };
	for (int i = 0; i < 8; ++i)
		tempB[i] = arrB[i];
	calculate2complement(tempB);
	add(arrA, tempB, arrRes);
}
void multiply(char arrA[], char arrB[], char result[])
{
	char tempA[MAX_SIZE], tempB[MAX_SIZE + 1];
	char tempRes[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; ++i)
		tempA[i] = arrA[i];
	for (int i = 0; i < MAX_SIZE; ++i)
		tempB[i] = arrB[i];
	tempB[MAX_SIZE] = 0;

	int k = MAX_SIZE;
	while (k > 0)
	{
		copyArray(result, tempRes);
		if (tempB[MAX_SIZE - 1] == 1 && tempB[MAX_SIZE] == 0)
		{
			subtract(tempRes, arrA, result);
		}
		else if (tempB[MAX_SIZE - 1] == 0 && tempB[MAX_SIZE] == 1)
		{
			add(tempRes, tempA, result);
		}
		else if (tempB[MAX_SIZE - 1] == tempB[MAX_SIZE])
		{
			// do nothing
		}

		shiftRight(tempB, MAX_SIZE + 1);
		tempB[0] = result[MAX_SIZE - 1];
		shiftRight(result);

		k--;
	}
	for (int i = 0; i < MAX_SIZE; ++i)
		result[i] = tempB[i];
}
void divide(char arrA[], char arrB[], char result[], char modulo[])
{
	// Q (thuong): arrA, M: arrB, A (so du): result & tempRes
	char tempA[MAX_SIZE];
	copyArray(arrA, tempA);
	char tempRes[MAX_SIZE] = { 0 };
	if (arrA[0] == 0) fillArray(result, 0);
	if (arrA[0] == 1) fillArray(result, 1);

	int k = MAX_SIZE;
	while (k > 0)
	{
		shiftLeft(result);
		result[MAX_SIZE - 1] = arrA[0];
		shiftLeft(arrA);

		copyArray(result, tempRes);
		subtract(tempRes, arrB, result);

		if (result[0] == 1)
		{
			copyArray(result, tempRes);
			add(tempRes, arrB, result);
		}
		else if (result[0] == 0)
		{
			arrA[MAX_SIZE - 1] = 1;
		}
		k--;
	}

	copyArray(result, modulo);
	copyArray(arrA, result);
	copyArray(tempA, arrA);
}

void output(char a, char b)
{
	char arrA[MAX_SIZE], arrB[MAX_SIZE];
	char result[MAX_SIZE] = { 0 }, modulo[MAX_SIZE] = { 0 };
	convertToBinary(a, arrA);
	convertToBinary(b, arrB);

	cout << "Input A (decimal): " << (int)a << endl;
	cout << "Input B (decimal): " << (int)b << endl;
	cout << "A (binary): ";
	printArray(arrA);
	cout << "B (binary): ";
	printArray(arrB);
	cout << endl;

	add(arrA, arrB, result);
	cout << "A + B (binary) : ";
	printArray(result);
	cout << "A + B (decimal): " << (int)convertToDecimal(result) << endl << endl;

	cout << "A - B (binary) : ";
	subtract(arrA, arrB, result);
	printArray(result);
	cout << "A - B (decimal): " << (int)convertToDecimal(result) << endl << endl;

	resetArray(result);
	multiply(arrA, arrB, result);
	cout << "A * B (binary) : ";
	printArray(result);
	cout << "A * B (decimal): " << (int)convertToDecimal(result) << endl << endl;

	if (b == 0)
	{
		cout << "KHONG THE CHIA CHO 0!!!" << endl;
		return;
	}

	resetArray(result);
	divide(arrA, arrB, result, modulo);
	cout << "A / B (binary) : ";
	printArray(result);
	cout << "A / B (decimal): " << (int)convertToDecimal(result) << endl << endl;

	cout << "A % B (binary) : ";
	printArray(modulo);
	cout << "A % B (decimal): " << (int)convertToDecimal(modulo) << endl << endl;
}


int main()
{
	char a, b;
	input(a, b);
	output(a, b);
	return 0;
}



















