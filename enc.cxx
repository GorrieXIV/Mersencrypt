/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Mersencrypt - Simple Pubkey Crypto based on Mersenne Primes     *
 * Written by Robert Gorrie for CryptoWorks21 Post Quantum Crypto  *
 *                                                                 *
 * Encryption file - See README for use instructions               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "mersencrypt.h"

#include <NTL/ZZ_p.h>
#include <NTL/ZZ.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace NTL;

/* global variables */
long n = 1279;
long h = 17;
char* m;
int l;

/* main */
int main (int argc, char** argv) {
	streambuf *cinbuf = cin.rdbuf();
	streambuf *coutbuf = cout.rdbuf();
	
	ifstream key(argv[1]);
	cin.rdbuf(key.rdbuf());

	ZZ p;
	p = power(conv<ZZ>(2), n);
	p = p - conv<ZZ>(1);
	ZZ_p::init(p);

	ZZ_p H;
	cin >> H;

	readMessage(argv[2]);

	ofstream ctxt("ciphertxt");
	cout.rdbuf(ctxt.rdbuf());

	ZZ_p C;
	ZZ A, B;
	A = genNBHW(n, h);
	B = genNBHW(n, h);
	cout << m;

	int i, d;
	int sign;
	for(d = 0; d < l; d++) {
		for(i = 7; 0 <= i; i --) {
			sign = -1 ^ (((*m+d) >> i) & 0x01);
			C = conv<ZZ_p>(A) * H;
			C = C + conv<ZZ_p>(B);
			C = C * conv<ZZ_p>(sign);
			cout << C << "\n";
		} 
	}

	printf("Encryption of input file stored in ciphertxt\n");

	cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf);

	return 0;
}

void readMessage(char* message) {
	FILE *f = fopen(message, "rb");
	fseek(f, 0, SEEK_END);
	l = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	m = (char*) malloc ((l + 1) * sizeof(char));
	fread(m, l, 1, f);

	fclose(f);

	m[l] = 0;
}
