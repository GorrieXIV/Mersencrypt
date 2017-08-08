/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Mersencrypt - Simple Pubkey Crypto based on Mersenne Primes     *
 * Written by Robert Gorrie for CryptoWorks21 Post Quantum Crypto  *
 *                                                                 *
 * Key Generation file - See README for use instructions           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <NTL/ZZ_p.h>
#include <NTL/ZZ.h>
#include <stdio.h>
#include <time.h> 
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;
using namespace NTL;

/* function contracts */
ZZ genNBHW(long n, long h);

/* global variables */
long n = 1279;
long h = 17;
char* pfile = "pk.key";
char* sfile = "sk.key";
const unsigned char* seed;

/* main */
int main (int argc, char** argv) {
	ZZ p;
	p = power(conv<ZZ>(2), n);
	p = p - conv<ZZ>(1);

	int var = 14; //garbage var to introduce randomness (using vars address)
	seed = (const unsigned char*) malloc (4 * sizeof(char));
	seed = (const unsigned char*) &var;
	SetSeed(seed, 4);
	ZZ F;
	cout << "suh\n";
	F = genNBHW(n, h); //generate n-bit number with hamming weight h
	ZZ G;
	cout << "suh2\n";
	G = genNBHW(n, h); //generate n-bit number with hamming weight h

	ZZ_p::init(p);
	ZZ_p H = (conv<ZZ_p>(F))/(conv<ZZ_p>(G));
	
	//if (argc == 2) {
		//freopen(argv[0],"w",stdout);
		//cout << H;
		//freopen(argv[1],"w",stdout);
		//cout << G;
	//} else {
		//freopen(pfile,"w",stdout);
		cout << H;
		//freopen(sfile,"w",stdout);
		cout << G;
	//}

	return 0;
}

ZZ genNBHW(long n, long h) {
	int hamCheck = 1;
	ZZ q;
	while (hamCheck == 1) {
		q = RandomLen_ZZ(n);	
	
		cout << weight(q) << "\n";
		cout << h << "\n";
		if (weight(q) == h) {
			hamCheck = 0;
		}
	}
	
	return q;
}
