#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<iostream>
#include <openssl/sha.h>
#include <fstream>
#include<vector>
#include"generateSHA.h"
using namespace std;
#define block 524288

string generateSHAstring(string hashstring){

char *buffer=(char*)malloc(block);
 memset(buffer,'\0',block);  
buffer=(char *)hashstring.c_str();
unsigned char hash[20];
 char temp[60];
 SHA1((unsigned char *)buffer, strlen(hashstring.c_str()), hash);
    for(int i=0;i<20;i++){
      snprintf(temp+i*2,4,"%02x",hash[i]);
    }

    string st=temp;
    //free(buffer);
    return st;
}

string generateSHA(string filename){
	char *buffer=(char*)malloc(block);
  memset(buffer,0,block);
  size_t result;
  unsigned char hash[20];
  vector<string> hashfile;
  string s,hashString="";
  FILE *fptr;
  fptr=fopen(filename.c_str(),"r");
 // fstream pFile (filename);
  
 int valread;
 int count =1;
 char temp[60];
 
  while(valread=fread(buffer,sizeof(char),block,fptr)){
  
  //  s="";  
   //int n=pFile.read(buffer,block);
    SHA1((unsigned char *)buffer, sizeof(buffer), hash);
    for(int i=0;i<20;i++){
    	//printf("%02x",hash[i]);
      snprintf(temp+i*2,4,"%02x",hash[i]);
    }
    string st=temp;
    hashfile.push_back(st);
    memset(buffer,'\0',block);
}
for (int i=0;i<hashfile.size();i++)
  hashString+=hashfile[i];


free(buffer);
return hashString;
 
}