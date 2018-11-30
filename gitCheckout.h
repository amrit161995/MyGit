#ifndef GIT_CHECKOUT
#define GIT_CHECKOUT
#include <string>
#include<iostream>

using namespace std;

string deserial(string hash);
void read();
void checkout(string filename);
void getRootPath();
void checkoutAll(const char* pathname);
void checkoutMain();

#endif
