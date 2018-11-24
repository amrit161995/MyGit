#include<stdio.h>
#include<iostream>
#include <sstream>
#include <vector>
#include "gitInit.h"
#include "gitAdd.h"

using namespace std;

int main(int argc,char* argv[]){
    if(strcmp(argv[0],"init")){
        gitInit();
    }

    else if(strcmp(argv[0],"add")){
        serialize();  
    }
    return 0;
}