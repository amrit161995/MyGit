#include<stdio.h>
#include<iostream>
// #include <sstream>
#include<string.h>
#include<stdlib.h>
#include <vector>
#include "gitInit.h"
#include "gitAdd.h"
#include "gitCommit.h"
#include "cat-file.h"
#include "gitLog.h"
#include "gitStatus.h"
#include "gitCheckout.h"
#include "gitRevert.h"
#include "diff.h"
// #include "gitLog.h"
// #include "gitStatus.h"

using namespace std;

int main(int argc,char* argv[]){
    if(strcmp(argv[1],"init")==0){
    	if(argc == 2)
        	gitInit();
        else
        	cout<<"Invalid Syntax"<<endl;
    }

    else if(strcmp(argv[1],"add")==0){
    	// cout<<argv[2];
    	if(argc == 3){
    	if( argv[2]!=".")
        	serialize(argv[2]); 

        // string hash;
        // cin>>hash;
        // cout<<deserialize(hash); 
        // else{
        // 	addAll();
        // }
    	}
    	else{
    		cout<<"Invalid Syntax"<<endl;
    	}

    }

    else if(strcmp(argv[1],"commit")==0){
    	if(argc == 4){
	        if(strcmp(argv[2],"-m") != 0){
	            cout<<"Did you mean -m ?"<<endl;
	            
	        }
	        else{
		        string m=argv[3];
		        string author = "xyz";
		        string commiter= "abc";
		        commitMain(author,commiter,m);
	   		 }
   		}
   		else
   			cout<<"Invalid Syntax"<<endl;
        // string hash;
        // cin>>hash;
        // deserializeCommit(hash);
    }


    else if(strcmp(argv[1],"catfile")==0){
    	// cout<<"j";
    	if(argc == 3)
        	catfile(argv[2]);
        else
        	cout<<"Invalid Syntax"<<endl;
    }

    else if(strcmp(argv[1],"status") == 0){
    	if(argc == 2)
        	status();
        else
        	cout<<"Invalid Syntax"<<endl;
    }

    else if(strcmp(argv[1],"checkout")==0){
    	if(argc==3){
	        if( argv[2]!=".")
	        	checkoutMain();
	        else
	        	checkout(argv[2]);
    	}

    	else
        	cout<<"Invalid Syntax"<<endl;
    }

    else if(strcmp(argv[1],"revert")==0){
    	if(argc==3)
        	revertMain(argv[2]);
        else
        	cout<<"Invalid Syntax"<<endl;
    }

    else if(strcmp(argv[1],"log")==0){
    	if(argc==2)
        	gitlog();
        else
        	cout<<"Invalid Syntax"<<endl;
    }

    else{
        cout<<"No such command !"<<endl;
        // return -1;
    }

    return 0;
}