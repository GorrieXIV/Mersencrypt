/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Mersencrypt - Simple Pubkey Crypto based on Mersenne Primes     *
 * Written by Robert Gorrie for CryptoWorks21 Post Quantum Crypto  *
 *                                                                 *
 * Misc functions - See README for use instructions                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "mersencrypt.h"

#include <NTL/ZZ_p.h>
#include <NTL/ZZ.h>
#include <stdio.h>
#include <time.h> 
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

/* global variables */

ZZ genNBHW(long n, long h) {
	ZZ q, p;
	long pint;
	int* table = (int*) malloc (1279 * sizeof(int));
	int x = 0;
	
	q = RandomLen_ZZ(n);	
	q = ZZ();
	while (x<17) {
		pint = rand() % 1279;
		if (table[pint] == 0) {
			table[pint] = 1;
			x++;
			p = power(conv<ZZ>(2), pint);
			q = q + p;
		} 
	}

	//cout << weight(q) << "\n";
	
	return q;
}
