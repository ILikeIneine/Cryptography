#pragma once
#include <string>
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

int cmp(string num1, string num2);

string int_add(string, string);						// BIG_INT add
string mod_add(string, string, string);				 				

string int_subs(string, string);					// BIG_INT minus
string mod_subs(string, string, string);		

string int_mult(string, string);					// BIG_INT multiply
string mod_mult(string, string, string);

string int_divi(string, string, int);				// BIG_INT divide
string gcd(string, string);
string exgcd(string, string, string&, string&);
string inv(string, string);								// INVERSE 

string _mod(string, string);							// ADVANCE
string power_mod(string, string, string);				// ADVANCE

bool Miller_Rabin_test(string);

//long long mod_divi(string, string, long long);		// (a/b) % mod

//long long _mod(string, long long);					// divide % mod (no limit)

//long long power_mod(int, int, long long);				// (a ^b ) % mod

