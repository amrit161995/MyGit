#include<vector>
#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
#include<errno.h>

using namespace std;
int main() 
{ 
    int check; 
   string dirname = "geeskforgeeks"; 
    // clrscr(); 
  
    check = mkdir(dirname.c_str(),0755); 
  
    // check if directory is created or not 
    if (!check) 
        printf("Directory created\n"); 
    else { 
        printf("Unable to create directory\n"); 
        exit(1); 
    } 
  
   
return 0;
} 