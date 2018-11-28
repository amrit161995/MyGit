#include<stdio.h>
#include<iostream>
#include <sstream>
#include <vector>
#include "gitInit.h"
#include "gitAdd.h"
#include "gitCommit.h"
#include "gitLog.h"
#include "gitStatus.h"

using namespace std;

int main(int argc,char* argv[]){
    if(strcmp(argv[0],"init")){
        gitInit();
    }

    else if(strcmp(argv[0],"add")){
        serialize();  
    }

    else if(strcmp(argv[0],"commit") ){
        if(strcmp(argv[1],"-m") != 0){
            cout<<"Did you mean -m ?"<<endl;
            return -1;
        }
        string m=argv[2];
        commitMain(m);
    }


    // else if(strcmp(argv[0],"catfile")){
    //     catfile(argv[1]);
    // }

    else if(strcmp(argv[0],"status")){
        status();
    }
    else if(strcmp(argv[0],"log")){
        gitlog();
    }

    else{
        cout<<"No such command !"<<endl;
        return -1;
    }

    return 0;
}