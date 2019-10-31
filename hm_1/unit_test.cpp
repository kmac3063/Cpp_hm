#include <iostream>

#include "Base.h"
#include "Matrix.h"
#include "Vector.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch.hpp"

TEST_CASE("Constructor_mat"){
	mat_vec::Matrix a(4);
	REQUIRE(a.shape().first == 4);
	REQUIRE(a.shape().second == 4);

	mat_vec::Matrix b(3, 1e-9);
	REQUIRE(b.shape().first == 3);
	REQUIRE(b.shape().second == 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			REQUIRE(abs(b[i][j] - 1e-9) < EPS);

	mat_vec::Matrix c(2, 3, -10);
	REQUIRE(c.shape().first == 2);
	REQUIRE(c.shape().second == 3);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			REQUIRE(abs(c[i][j] + 10) < EPS);

	mat_vec::Matrix c_copy(c);
	REQUIRE(c.shape().first == c_copy.shape().first);
	REQUIRE(c.shape().second == c_copy.shape().second);
	REQUIRE(&c[0][0] != &c_copy[0][0]);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			REQUIRE(abs(c[i][j] - c_copy[i][j]) < EPS);
}

TEST_CASE("Constructor_vec") {
	mat_vec::Vector a(5);
	REQUIRE(a.size() == 5);

	mat_vec::Vector b(4, -100);
	REQUIRE(b.size() == 4);
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(b[i] + 100) < EPS);

	mat_vec::Vector b_copy(b);
	REQUIRE(b.size() == b_copy.size());
	REQUIRE(&b[0] != &b_copy[0]);
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(b[i] - b_copy[i]) < EPS);
}

TEST_CASE("Operator_mat") {
	mat_vec::Matrix a(10, 1), b(10, 2);
	
	mat_vec::Matrix c = a;
	REQUIRE(c.shape().first == a.shape().first);
	REQUIRE(c.shape().second == a.shape().second);
	REQUIRE(&c[0][0] != &a[0][0]);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - a[i][j]) < EPS);
	
	c = a + b;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 3) < EPS);
	c += a;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 4) < EPS);


	c = a - b;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] + 1) < EPS);
	c -= a;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] + 2) < EPS);
	

	c = a * b;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 20) < EPS);
	c *= a;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 200) < EPS);


	const double k = 2;
	c = a * k;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 2) < EPS);
	c *= k;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 4) < EPS);

	
	c = b / k;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 1) < EPS);
	c /= k;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			REQUIRE(abs(c[i][j] - 0.5) < EPS);


	mat_vec::Vector t(10, 10);
	t = c * t;
	REQUIRE(t.size() == 10);
	for (size_t i = 0; i < 10; i++)
		REQUIRE(abs(t[i] - 50) < EPS);;


	a = c;
	REQUIRE(a == c);
	a[2][2] = c[2][2] + 1;
	REQUIRE(a != c);

	a = mat_vec::Matrix(5, 10);
	c = mat_vec::Matrix(3, 10);
	REQUIRE(a != c);
}

TEST_CASE("Operator_vec") {
	mat_vec::Vector a(4, 4), b(4, 6);

	mat_vec::Vector c = a;
	REQUIRE(c.size() == a.size());
	REQUIRE(&c[0] != &a[0]);
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - a[i]) < EPS);


	c = a + b;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 10) < EPS);
	c += b;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 16) < EPS);


	c = a - b;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] + 2) < EPS);
	c -= b;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] + 8) < EPS);


	c = a ^ b;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 24) < EPS);
	c ^= b;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 144) < EPS);


	double k = a * b;
	REQUIRE(abs(k - 96) < EPS);

	k = 2;
	c = k * a;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 8) < EPS);


	c = a * k;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 8) < EPS);
	c *= k;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 16) < EPS);


	c = a / k;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 2) < EPS);
	c /= k;
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 1) < EPS);


	mat_vec::Matrix m(4, 3, 2);
	c = a * m;
	REQUIRE(c.size() == 3);
	for (size_t i = 0; i < 3; i++)
		REQUIRE(abs(c[i] - 32) < EPS);
	m = mat_vec::Matrix(3, 4, 2);
	c *= m;
	REQUIRE(c.size() == 4);
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 192) < EPS);


	b = a;
	REQUIRE(a == b);
	REQUIRE(c != a);
}

TEST_CASE("func_mat"){
	mat_vec::Matrix a = mat_vec::Matrix::eye(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			if (i == j)
				REQUIRE(abs(a[i][j] - 1) < EPS);
			else
				REQUIRE(abs(a[i][j]) < EPS);


	a = mat_vec::Matrix(4, 6, 0);
	double k = 0;
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 6; j++)
			a[i][j] = k++;
	a.reshape(24, 1);
	k = 0;
	for (size_t i = 0; i < 24; i++)
		for (size_t j = 0; j < 1; j++)
			REQUIRE(abs(a[i][j] - k++) < EPS);


	REQUIRE(a.shape().first == 24);
	REQUIRE(a.shape().second == 1);


	k = 0;
	for (size_t i = 0; i < 24; i++)
		for (size_t j = 0; j < 1; j++)
			REQUIRE(abs(a.get(i, j) - k++) < EPS);


	a.reshape(2, 12);
	a = a.transposed();
	k = 0;
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 12; j++)
			REQUIRE(abs(a[j][i] - k++) < EPS);


	a.transpose();
	k = 0;
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 12; j++)
			REQUIRE(abs(a[i][j] - k++) < EPS);


	mat_vec::Matrix c(5, 5, 0);
	k = 0;
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			c[i][j] = k++;
	c.transpose();
	k = 0;
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			REQUIRE(abs(c[j][i] - k++) < EPS);


	a = mat_vec::Matrix(5, 5, 10);
	REQUIRE(abs(a.det()) < EPS);
	for (size_t i = 0; i < 5; i++)
		a[i][i] = 1;
	REQUIRE(abs(a.det() - 269001) < EPS);

	c = mat_vec::Matrix(1, 1);
	REQUIRE(abs(c.det() - 1) < EPS);
	REQUIRE(abs(c.inv()[0][0] - 1) < EPS);

	
	REQUIRE((a.inv() * a) == mat_vec::Matrix::eye(5));
	
	a.print();
}

TEST_CASE("func_vec"){
	mat_vec::Vector a(5, 1e-7), b(4, 5);
	
	REQUIRE(a.size() == 5);

	REQUIRE(abs(b.norm() - 10) < EPS);

	mat_vec::Vector c = b.normalized();
	REQUIRE(c.size() == 4);
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(c[i] - 0.5) < EPS);

	b.normalize();
	for (size_t i = 0; i < 4; i++)
		REQUIRE(abs(b[i] - 0.5) < EPS);

	b.print();
}