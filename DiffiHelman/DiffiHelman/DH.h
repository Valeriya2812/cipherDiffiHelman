#pragma once

class EC_point {
public:
	long int x, y;

};
class EC {
public:
	long int p, a, b;
	EC_point G;
	EC();
	bool check_EC();
	bool check_EC_point(long  int, long  int);
	long int find_y(long int);

	EC_point add_EC_point(EC_point, EC_point);
	EC_point multiply_EC_point(EC_point, long int);
};
class BOB;



class ALICE {
	long int d_a;
public:
	EC_point Q_A;
	void Alice_generates_keys(EC);
	long int Alice_generates_common_key(EC_point, EC);
};
class BOB {
	long int d_b;
public:
	EC_point Q_B;
	void Bob_generates_keys(EC);
	long int Bob_generates_common_key(EC_point, EC);
};


class DH_EC {
	EC curve;
	ALICE A;
	BOB B;
public:
	void generation_key();
};