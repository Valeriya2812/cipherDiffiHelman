// DiffiHelman.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "DH.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	DH_EC obj;
	obj.generation_key();
	system("pause");
	return 0;
}

