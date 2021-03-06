#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include"gitCommit.h"
#include"diff.h"
#include "tree.h"
#include "generateSHA.h"
#include "indexCreate.h"
#include "gitAdd.h"
#include "gitStatus.h"
#include "gitRevert.h"
// #include"tree.cpp"

using namespace std;

#define debug(x) cout<<"Checkpoint "<<x<<endl

// class TestA
// {
//     public:
//         char type[10];
//         char header[50];
//         char content[100000];
//         int length;
// };


void retCommitObjectTree(string hash,string &treeObj,string &parent){
    if(hash!="0000000000000000000000000000000000000000") {
        Commit com;
        FILE *File;
        // string treeObj="";

        string directory="";
        string commitname="";

        for(int i=0;i<2;i++)
           directory+=hash[i];

        for(int i=2;i<40;i++)
            commitname+=hash[i];

        string path=".mygit/objects/"+directory+"/"+commitname;
        File = fopen(path.c_str(),"rb");
        fread((char *)&com,sizeof(com),1,File); //Treats the object as if it is a char array
        treeObj = com.tree;
        parent = com.parent;
        fclose(File);
    }
}

void deserialize1(string file,string name){
    TestA Test2;

    string directory="";
    string blobname="";

    for(int i=0;i<2;i++)
        directory+=file[i];

    for(int i=2;i<40;i++)
        blobname+=file[i];

    string path=".mygit/objects/"+directory+"/"+blobname;
    // ifstream ifs (path.c_str(),ios::in);
    // ifs.read((char *)&Test2,sizeof(Test2));
    // ifs.close();

    string te;
    std::ifstream binFile(path.c_str(), std::ios::in | std::ios::binary);
   if(binFile.is_open())
   {
      size_t len = 0;
      binFile.read((char*)&len, sizeof(len));
      te.resize(len);
      binFile.read((char*)&te[0], len);
   }

    ofstream ofs(".mygit/diff/"+name);
    // string con(Test2.content);  
    ofs << te;
    ofs.close();
}

void revert(string hash,string tre,map<string,int> &lis){
    if(hash!="") {
        Tree tr;
        FILE *File;
        // string treeObj="";

        string directory="";
        string commitname="";

        for(int i=0;i<2;i++)
           directory+=hash[i];

        for(int i=2;i<40;i++)
            commitname+=hash[i];

        string path=".mygit/objects/"+directory+"/"+commitname;
        File = fopen(path.c_str(),"rb");
        fread((char *)&tr,sizeof(tr),1,File); //Treats the object as if it is a char array
        // cout<<tr.treeContent<<endl;
        string content(tr.treeContent);
        vector<string> files = splitStrings(content,'\n');
        for(int i=0;i<files.size();i++) {
            vector<string> p = splitStrings(files[i],' ');
            if(p[1]=="blob") {
                vector<string> na = splitStrings(p[3],'/');
                string name = tre;
                for(int i=0;i<na.size();i++) name = name + ":" + na[i];
                string f = name.substr(0,strlen(name.c_str())-1);
                deserialize1(p[2],f);
                lis[f]=0;
            }
            else if(p[1]=="tree") {
                revert(p[2],tre,lis);
            }
        }
        fclose(File);
    }
}

vector<string> fileToVector(string name) {
    vector<string> v;
    string str;
    ifstream ifs(name.c_str());  
    while (getline(ifs, str)) v.push_back(str);
    ifs.close();
    return v;
}

// void addEnter(string name) {
//     vector<string> v;
//     string str;
//     ifstream ifs(name.c_str());  
//     while (getline(ifs, str)) v.push_back(str);
//     ifs.close();
//     for(int i=1;i<v.size();i++) {
//         string st = v[i-1];
//         if(v[i].length()==0 and st[st.lenght()-1]!="\n") st[st.length()-1]="\n";
//     }    

//     ofstream ofs(name.c_str());
//     for(unsigned int i=0; i<v.size(); i++)
//         ofs << v[i] << endl;
//     ofs.close();
// }

void calculateDiff(map<string,int> &newFiles,map<string,int> &oldFiles,map<string,int> &diffFiles) {    
    map<string,int>::iterator it1;
    map<string,int>::iterator it2;
    for(it1=newFiles.begin();it1!=newFiles.end();it1++) {
        for(it2=oldFiles.begin();it2!=oldFiles.end();it2++) {
            string f = it1->first.substr(4,strlen(it1->first.c_str()));
            string s = it2->first.substr(4,strlen(it2->first.c_str()));
            if(f==s) {
                it1->second = 1;
                it2->second = 1;    
                // addEnter(it1->first);
                // addEnter(it2->first);                
                diff(it1->first,it2->first,f);
                diffFiles[f] = 1;
            }
        }
    }
    for(it1=newFiles.begin();it1!=newFiles.end();it1++) {
        if(it1->second==0) {
            it1->second=1;
            string f = it1->first.substr(4,strlen(it1->first.c_str()));
            string command = "cp .mygit/diff/"+it1->first+" .mygit/diff_files/"+f;
            system(command.c_str());
            diffFiles[f] = 2;
        }
    }
    for(it1=oldFiles.begin();it1!=oldFiles.end();it1++) {
        if(it1->second==0) {
            it1->second=1;
            string f = it1->first.substr(4,strlen(it1->first.c_str()));
            string command = "cp .mygit/diff/"+it1->first+" .mygit/diff_files/"+f;
            system(command.c_str());
            diffFiles[f] = 3;
        }
    }
}

void applyDiff(map<string,int> diffFiles) {
    map<string,int>::iterator it;    
    for(it=diffFiles.begin();it!=diffFiles.end();it++) {
        vector<string> na = splitStrings(it->first,':');
        string name = "",temp = "",relPath = "";
        for(int i=0;i<na.size();i++) name = name + "/" + na[i];
        char cwd[1024];
        getcwd(cwd,sizeof(cwd));
        string pa(cwd);
        vector<string> nam = splitStrings(pa,'/');
        for(int i=0;i<na.size();i++) {
            if(na[i]!=nam[nam.size()-1]) relPath = relPath + "/" + na[i];
            else {
                relPath = relPath + "/" + na[i] + "/";
                break;
            }
        }
        // cout<<relPath<<endl;
        temp = name;
        temp.erase(0,relPath.length());
        relPath = temp;
        // cout<<"after"<<endl;
        // cout<<relPath<<endl;
        if(it->second==1) {
            vector<string> curFile,diffFile,outFile;
            // na = splitStrings(it->first,':');
            // string name = "";
            // for(int i=0;i<na.size();i++) name = name + "/" + na[i];
            curFile = fileToVector(name);        

            string pathDiff = ".mygit/diff_files/" + it->first;
            diffFile = fileToVector(pathDiff);
            // for(int i=0;i<diffFile.size();i++) cout<<diffFile[i]<<endl;  
            // diffFile.erase(diffFile.begin());
            // diffFile.erase(diffFile.begin());

            for(int i=0;i<curFile.size();i++) cout<<curFile[i]<<endl;
            for(int i=0;i<diffFile.size();i++) cout<<diffFile[i]<<endl;
            // string st = diffFile[diffFile.size()-1];
            // if(diffFile[diffFile.size()-1]=="")            
            int i=0,j=0;
            bool flag = false; 
            while(i<curFile.size() and j<diffFile.size()) {
                // if(diffFile[j]=="\\ No newline at end of file") {
                //     j++;
                //     continue;
                // }
                string sign = diffFile[j].substr(0,1);
                string line = diffFile[j].substr(1,strlen(diffFile[j].c_str()));
                if(sign=="+") {
                    outFile.push_back(line);
                    j++;
                }
                else if(curFile[i]==line) {
                    if(sign=="-") {
                        i++;
                        j++;
                    }
                    else {
                        outFile.push_back(line);
                        i++;
                        j++;
                    }
                }
                else {
                    flag = true;
                    break;
                }
            }
            while(i<curFile.size()) {
                outFile.push_back(curFile[i]);
                i++;
            }
            while(j<diffFile.size()) {
                string sign = diffFile[j].substr(0,1);
                string line = diffFile[j].substr(1,strlen(diffFile[j].c_str()));
                if(sign=="+") {
                    outFile.push_back(line);
                    j++;
                }
                else {
                    flag=true;
                    break;
                }
            }
            if(!flag) {
                // for(int i=0;i<outFile.size();i++) cout<<outFile[i]<<endl;
                ofstream ofs(name.c_str());
                for(unsigned int i=0; i<outFile.size(); i++)
                    ofs << outFile[i] << endl;
                ofs.close();
                serialize(relPath);
            }
            else {
                cout<<"Merge Conflicts"<<endl;
            }
        }
        else if(it->second==2) {
            ifstream ifs(name.c_str());
            if(ifs) {
                ifs.close();
                remove(name.c_str());
            }
        }
        else {
            string command = "cp .mygit/diffFiles/"+it->first+" "+name;
            system(command.c_str());
            serialize(relPath);
        }
    }
    commitMain("xyz","abc","Revert commit");
    debug("after commitmain");
}

void revertMain(string hash){
	string oldTreeObj,newTreeObj,parent;
    retCommitObjectTree(hash,newTreeObj,parent);
    // cout<<newTreeObj<<endl;
    retCommitObjectTree(parent,oldTreeObj,parent);
    // cout<<oldTreeObj<<endl;
    mkdir(".mygit/diff",0777);
    mkdir(".mygit/diff_files",0777);
    map<string,int> newFiles;
    map<string,int> oldFiles;
    revert(newTreeObj,"new",newFiles);
    revert(oldTreeObj,"old",oldFiles);
    // map<string,int>::iterator it;
    // for(it=newFiles.begin();it!=newFiles.end();it++) {
    //     cout<<it->first<<" "<<it->second<<endl;
    // }
    // for(it=oldFiles.begin();it!=oldFiles.end();it++) {
    //     cout<<it->first<<" "<<it->second<<endl;
    // }
    map<string,int> diffFiles;
    calculateDiff(newFiles,oldFiles,diffFiles);
    string command = "rm -rf .mygit/diff";
    system(command.c_str());
    applyDiff(diffFiles);
    command = "rm -rf .mygit/diff_files";
    system(command.c_str());
}

// int main(){
    
//     return 0;
// }