#include<stdio.h>
#include<string>
#include<ctime>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;

void gitlog(){
	struct stat buf;
    if (stat("log", &buf) != -1)
    {
    	vector <string> vecOfStrs;
        // cout<<"hello";
        std::ifstream in("log");
        string str;
		while (std::getline(in, str))
			{
				// Line contains string of length > 0 then save it in vector
				if(str.size() > 0)
					vecOfStrs.push_back(str);
			}


			for(int i=0;i<vecOfStrs.size();i++){
				string line = vecOfStrs[i]; 
			    
			    vector <string> tokens; 
			    stringstream check1(line); 
			    string intermediate; 
			     
			    while(getline(check1, intermediate, '|')) 
			    { 
			        tokens.push_back(intermediate); 
			    } 
			      
			    // cout<<tokens[1]<<endl;

			    time_t t=(time_t)stoi(tokens[4]);
			    std::tm* now = std::localtime(&t);
			     // std::cout << (now->tm_year + 1900) << '-'          << (now->tm_mon + 1) << '-'         <<  now->tm_mday  << "\n";
			     // cout<<asctime(now);
			    cout<<tokens[6]<<" : "<<" "<<tokens[1]<<endl;
			    cout<<"Author : "<<" "<<tokens[2]<<endl;
			    cout<<"Date :   "<<" "<<asctime(now)<<endl;
			    cout<<endl;
			    cout<<"	"<<tokens[7]<<endl;
			    cout<<endl;
		    }

			in.close();
    }	
}

// int main(){
// 	gitlog();
// 	return 0;
// }