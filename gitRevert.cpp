#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include"gitCommit.cpp"
#include"diff.cpp"
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

// vector<string> splitStrings(string str, char dl)
// {
//     string word = "";
//     str = str + dl;
//     int l = str.size();
//     vector<string> substr_list;
//     for (int i = 0; i < l; i++) {
//         if (str[i] != dl) {
//             if(str[i]=='\\') {
//                 i++;
//             }
//             word = word + str[i];
//         }
//         else {
//             if ((int)word.size() != 0)
//                 substr_list.push_back(word);
//             word = "";
//         }
//     }
//     return substr_list;
// }

void deserialize(string file,string name){
    TestA Test2;
    // FILE *File;

    string directory="";
    string blobname="";

    for(int i=0;i<2;i++)
        directory+=file[i];

    for(int i=2;i<40;i++)
        blobname+=file[i];

    string path=".mygit/objects/"+directory+"/"+blobname;
    ifstream ifs (path.c_str(),ios::in);
    ifs.read((char *)&Test2,sizeof(Test2));
    ifs.close();
    // debug(path);
    // File = fopen(path.c_str(),"rb");
    // debug(sizeof(Test2));
    // fread((char *)&Test2,sizeof(Test2),1,File); //Treats the object as if it is a char array
    // debug(Test2.content);
    // fclose(File);
    // mkdir(".mygit/diff",0777);
    // debug(2);    
    ofstream ofs(".mygit/diff/"+name+".txt");
    // debug(2);
    // debug(Test2.content);
    string con(Test2.content);
    // debug(con);
    // ofs.write((char*)&con,sizeof(con));     
    ofs << con;
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
                for(int i=0;i<na.size();i++) name = name + "_" + na[i];
                string f = name.substr(0,strlen(name.c_str())-1);
                deserialize(p[2],f);
                lis[f+".txt"]=0;
            }
            else if(p[1]=="tree") {
                revert(p[2],tre,lis);
            }
        }
        fclose(File);
    }
}

void calculateDiff(map<string,int> &newFiles,map<string,int> &oldFiles) {
    // if(newFiles.size()<oldFiles.size()) {
        map<string,int>::iterator it1;
        map<string,int>::iterator it2;
        for(it1=newFiles.begin();it1!=newFiles.end();it1++) {
            for(it2=oldFiles.begin();it2!=oldFiles.end();it2++) {
                string f = it1->first.substr(4,strlen(it1->first.c_str()));
                string s = it2->first.substr(4,strlen(it2->first.c_str()));
                if(f==s) {
                    it1->second = 1;
                    it2->second = 1;                    
                    diff(it1->first,it2->first,f);
                }
            }
        }
        for(it1=newFiles.begin();it1!=newFiles.end();it1++) {
            if(it1->second==0) {
                it1->second=1;
                string f = it1->first.substr(4,strlen(it1->first.c_str()));
                string command = "cp .mygit/diff/"+it1->first+" .mygit/diff_files/"+f;
                system(command.c_str());
            }
        }
    // }
    // else {


    // }
}


int main(){
    string oldTreeObj,newTreeObj,parent;
    retCommitObjectTree("f11c8e3ddd9a7862f75865509a4fb4064f818101",newTreeObj,parent);
    cout<<newTreeObj<<endl;
    retCommitObjectTree(parent,oldTreeObj,parent);
    cout<<oldTreeObj<<endl;
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
    calculateDiff(newFiles,oldFiles);
    return 0;
}