#include<stdio.h>
#include<string>
#include <openssl/sha.h>
#include "gitCommit.cpp"
// #include "gitAdd.cpp"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;


void catfile(string hash){
    string type="";
    // cout<<"ad";
    struct stat buf;
        int flag=0;
        if (stat(".mygit/info/objectsFile.txt", &buf) != -1)
        {
            vector <string> objectsvec;
            // cout<<"hello";
            std::ifstream in(".mygit/info/objectsFile.txt");

            string str;
            
            while (std::getline(in, str))
                {
                    // Line contains string of length > 0 then save it in vector
                    if(str.size() > 0)
                        objectsvec.push_back(str);
                }

                for(int i=0;i<objectsvec.size();i++){
                    string line = objectsvec[i]; 
                    
                    vector <string> tokens; 
                    stringstream check1(line); 
                    string intermediate; 
                     
                    while(getline(check1, intermediate, ' ')) 
                    { 
                        tokens.push_back(intermediate); 
                    } 
                      
                    if(hash == tokens[0])
                        type=tokens[1];
                    // parent = tokens[1];
                }
                in.close();

                // cout<<type;
                if(type == "blob"){   
                    // serialize("7");                 
                    cout<<deserialize(hash);
                }
                if(type == "tree")
                    deserializeTree(hash);
                if(type == "commit")
                    deserializeCommit(hash);

        }

        else{
            cout<<"Does not exist"<<endl;
        }
}

int main(){
    string hash;
    cout<<"enter hash"<<endl;
    cin>>hash;
    catfile(hash);

    return 0;
}