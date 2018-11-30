#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sstream>
#include <fstream>
// #include "gitAdd.cpp"
// #include "tree.cpp"
#include "gitCommit.cpp"

using namespace std;

vector<Index> readV;

// void read(){
//     readV=indexRead();
// }

vector<string> splitString(string s,char delim){
    vector<string> v;
    istringstream ss(s);
    string token;
    while(getline(ss, token, delim)) {
        v.push_back(token);
    }
    return v;
}


void reset(string hash){
    if(hash!="") {
        Tree tr;
        FILE *File;
    
        string directory="";
        string objectname="";

        for(int i=0;i<2;i++)
           directory+=hash[i];

        for(int i=2;i<40;i++)
            objectname+=hash[i];

        string path=".mygit/objects/"+directory+"/"+objectname;
        File = fopen(path.c_str(),"rb");
        fread((char *)&tr,sizeof(tr),1,File); //Treats the object as if it is a char array
        
        string content(tr.treeContent);
        vector<string> files = splitString(content,'\n');

        for(int i=0;i<files.size();i++) {
            vector<string> p = splitString(files[i],' ');

            if(p[1]=="blob") {
                string fPath=p[3];
                string fContent=deserialize(p[2]);
                string con(fContent);
                std::ofstream ofs;
                ofs.open (fPath, std::ofstream::out);
                ofs << fContent;
                ofs.close();
            }

            else if(p[1]=="tree") {
                string dir=p[3];
                dir.pop_back();
                mkdir(dir.c_str(),0755);
                
                chdir(dir.c_str());
                reset(p[2]);
            }
        }
        fclose(File);
    }
}

string retCommitObjectTree(string hash){
    if(hash!="0000000000000000000000000000000000000000") {
        Commit com;
        FILE *File;
        string treeObj="";
        string directory="";
        string commitname="";

        for(int i=0;i<2;i++)
        directory+=hash[i];

        for(int i=2;i<40;i++)
            commitname+=hash[i];

        string path=".mygit/objects/"+directory+"/"+commitname;
        File = fopen(path.c_str(),"rb");
        fread((char *)&com,sizeof(com),1,File); //Treats the object as if it is a char array
        treeObj=com.tree;
        // cout<<treeObj<<endl;
        fclose(File);
        return treeObj;
    }
}

int main(){
    string hash=retCommitObjectTree("3e8c51e70f0d45bbc906bfad503238067fed25cf");
    cout<<hash;
    reset(hash);
    return 0;
}