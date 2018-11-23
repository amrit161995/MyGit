#ifndef GENERATESHA_H_  
#define GENERATESHA_H_ 
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<iostream>
#include <openssl/sha.h>
#include <fstream>
#include<vector>
using namespace std;
string generateSHAstring(string hashstring);	
string generateSHA(string filename);

#endif // GENERATESHA_H_ 
