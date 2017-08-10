/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Mersencrypt - Simple Pubkey Crypto based on Mersenne Primes     *
 * Written by Robert Gorrie for CryptoWorks21 Post Quantum Crypto  *
 *                                                                 *
 * Decryption file - See README for use instructions               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "mersencrypt.h"

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <stdio.h>
#include <time.h> 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace NTL;

/* function contracts */
ZZ stringtoZZ (string s);

/* global variables */
long n = 1279;
long h = 17;
char* m;

int main (int argc, char** argv) {
	streambuf *cinbuf = cin.rdbuf();
	streambuf *coutbuf = cout.rdbuf();

	ifstream key(argv[1]);
	cin.rdbuf(key.rdbuf());

	ofstream pt("plaintxt");
	cout.rdbuf(pt.rdbuf());

	ZZ p;
	p = power(conv<ZZ>(2), n);
	p = p - conv<ZZ>(1);
	ZZ_p::init(p);

	ZZ_p G;
	cin >> G;

	ifstream ct(argv[2]);
	cin.rdbuf(ct.rdbuf());

	ZZ C;
	long w;
	char c = 0x00;
	string line;
	int i = 0;
	while(getline(cin, line)) {
		C = stringtoZZ (line);
		G = conv<ZZ_p>(C) * G;
		w = weight(C);

		if (w <= 2 * (h^2)) {
			//do nothing
		} else if (w >= n - (2 * (h^2))) {
			c = c + 0x01;
		} else {
			printf ("\n NOTE: ERROR IN DECRYPTION \n\n");
			//return 1;
		}
		
		c = c << 1;
		i++;
		if (i == 7) {
			//after 8 bits post a char
			cout << c;
			printf("%c\n", c);
			c = 0x00;
			i = 0;
		}
	}

	printf("Decryption of input file stored in plaintxt\n");
	
	return 0;
}

ZZ stringtoZZ (string s) {
	ZZ n = conv<ZZ>(s[0]);
	long l = s.length();
	for(long i = 1; i < l; i++) {
		n *= 128;
		n += conv<ZZ>(s[i]);
	}
	return n;
}
