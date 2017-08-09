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
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <unordered_map>

//#define n 1279
//#define h 17

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
	SetSeed(seed, 4); //hash address of var to seed randomness
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
	ZZ q, p;
	int pint;
	int table[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int x = 0;
	while (hamCheck == 1) {
		q = RandomLen_ZZ(n);	
		q = ZZ();
		while (x<17) {
			//p = RandomBnd(conv<ZZ>(n));
			pint = rand() % 17;
			if (table[pint] == 0) { //can't use a ZZ as an index, generate an int then convert to ZZ
				table[pint] = 1;
				x++;
				p = power(conv<ZZ>(2), p);
				q = q + p;
				cout << p << "\n";
				cout << q << "\n";
				cout << weight(q) << "\n";
			} 
		}
		
		cout << h << "\n";
		//if (weight(q) == h) {
		hamCheck = 0;
		//}
	}
	
	return q;
}


