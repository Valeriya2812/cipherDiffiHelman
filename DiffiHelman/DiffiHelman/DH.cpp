
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include "DH.h"
using namespace std;
bool check_prime_num(long int num) {
	int i;
	for (i = 2; i < num; i++)
		if (num%i == 0)
			return false;
	return true;
}
EC::EC() {
	srand(time(NULL));
	p = 67;
	do {
		a = (rand() % 10 + 1);
		b = (rand() % 10 + 1);
	} while (!check_EC());

	G.x = (rand() % 20 + 2) % p;
	G.y = find_y(G.x);
	cout << "p = " << p << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "G.x = " << G.x << endl;
	cout << "G.y = " << G.y << endl;
}
long int EC::find_y(long int x) {
	long int y;
	y = (sqrt(pow(x, 3) + a*x + b));
	y = y% p;
	return y;
}

bool EC::check_EC_point(long int x, long int y)
{
	if (pow(y, 2) == pow(x, 3) + a*x + b)
		return true;
	else return false;

}
bool EC::check_EC() {
	if (4 * pow(a, 3) + 27 * pow(b, 2) == 0)
		return false;
	else return true;
}
EC_point EC::add_EC_point(EC_point P, EC_point Q) {
	EC_point R;
	long int s, s1;
	if ((P.x == Q.x) && (P.y != Q.y))
		return P;
	if (((P.x == Q.x) && (P.y == Q.y)) || ((P.x == Q.x) && (P.y == -Q.y)))
	{
		s = (3 * pow(P.x, 2) + a);
		s = (s / (2 * P.y)) % p;

	}
	else
	{

		s = (P.y - Q.y + p) % p;
		s1 = (P.x - Q.x + p) % p;
		s = s / s1;
	}
	R.x = pow(s, 2) + p + p - P.x - Q.x;
	R.x = R.x%p;
	R.y = (s*(P.x + p - R.x) - P.y + p) % p;
	return R;
}

EC_point EC::multiply_EC_point(EC_point P, long int num) {
	EC_point R;

	R.x = P.x;
	R.y = P.y;
	for (int i = 1; i < num; i++)
		R = add_EC_point(P, R);
	return R;
}



void  ALICE::Alice_generates_keys(EC curve) {

	d_a = 8;
	Q_A = curve.multiply_EC_point(curve.G, d_a);
	cout << "Alice open key:  (" << Q_A.x << ", " << Q_A.y << ")" << endl;

}
void BOB::Bob_generates_keys(EC curve) {

	d_b = 12;
	Q_B = curve.multiply_EC_point(curve.G, d_b);
	cout << "Bob open key: (" << Q_B.x << ", " << Q_B.y << ")" << endl;
}
long int ALICE::Alice_generates_common_key(EC_point Q_B, EC curve) {
	unsigned long int key;
	EC_point K;
	K = curve.multiply_EC_point(Q_B, d_a);
	key = K.x;
	cout << "Alice common key: " << key << endl;
	return key;

}
long int BOB::Bob_generates_common_key(EC_point Q_A, EC curve) {
	unsigned long int key;
	EC_point K;
	K = curve.multiply_EC_point(Q_A, d_b);
	key = K.x;
	cout << "Bob common key: " << key << endl;
	return key;
}

void DH_EC::generation_key() {

	A.Alice_generates_keys(curve);
	B.Bob_generates_keys(curve);
	A.Alice_generates_common_key(B.Q_B, curve);
	B.Bob_generates_common_key(A.Q_A, curve);

}#include "DH.h"


DH::DH()
{
}


DH::~DH()
{
}
