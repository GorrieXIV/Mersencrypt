/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Mersencrypt - Simple Pubkey Crypto based on Mersenne Primes     *
 * Written by Robert Gorrie for CryptoWorks21 Post Quantum Crypto  *
 *                                                                 *
 * Key Generation file - See README for use instructions           *
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

using namespace std;
using namespace NTL;

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
	F = genNBHW(n, h); //generate n-bit number with hamming weight h
	ZZ G;
	G = genNBHW(n, h); //generate n-bit number with hamming weight h

	ZZ_p::init(p);
	ZZ_p H = (conv<ZZ_p>(F))/(conv<ZZ_p>(G));
	
	streambuf *coutbuf = cout.rdbuf();
	
	//write H to pk.key
	ofstream outpk("pk.key");
	cout.rdbuf(outpk.rdbuf());
	cout << H;

	printf("Public key H stored in pk.key\n");

	cout.rdbuf(coutbuf);

	//write G to sk.key
	ofstream outsk("sk.key");
	cout.rdbuf(outsk.rdbuf());
	cout << G;

	printf("Secret key G stored in sk.key\n");

	cout.rdbuf(coutbuf);

	return 0;
}


