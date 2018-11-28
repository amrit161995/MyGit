#include<stdio.h>
#include<string>
#include<cstring>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<bits/stdc++.h>
// #include "generateSHA.cpp"
using namespace std;

#include "gitAdd.cpp"


class Tree
{
        public:
        char treeContent[100000];

        void Print_Content1()
        {
            // int len = sizeof(content)/sizeof(char);
            // cout<<"len: "<<len<<endl;
            cout<<treeContent;
        }

        
        
};

typedef struct treeObj{
    // char type[10];
    // char hash[40];
    string type;
    string hash;
}treeObj;

string createTreeObject(char *path1,vector<Index> list){
    string content ="";
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path1)))
        return content;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (entry->d_name[0]=='.')
                continue;
            snprintf(path, sizeof(path), "%s/%s", path1, entry->d_name);
            string hash_temp=createTreeObject(path,list);
            // cout<<endl;
            // cout<<hash_temp<<endl;            
            string temp1=entry->d_name;
            cout<<temp1<<endl;
            string temp="040000 tree " + hash_temp +" "+ temp1+";\n";
            content=content+temp;

        } 

        else {
            string hash_temp="";
            char cwd[1024];
            getcwd(cwd,sizeof(cwd));
            string pa(cwd);
            string temp1=pa+"/"+entry->d_name;
            for(int i=0;i<list.size();i++){
                
                string tempath=realpath(path1,NULL);
                string tempath1=tempath + "/" + entry->d_name;
                // cout<<i<<" "<<tempath1<<endl;
                if(list[i].path==tempath1){

                    hash_temp=list[i].hash;
                    string temp="100644 blob "+ hash_temp +" "+ temp1 +";\n" ;
                    content=content+temp;
                }

            }

            
            }
        }
    


    // chdir("..");
    closedir(dir);

    string header = "tree " + to_string(content.length()) + "\0";
    string store = header + content;

    string sha= generateSHAstring(store);
    // cout<<path1<<endl;
    // cout<<content<<endl;
    
    string hash_filename = sha;
    treeObj tr;

    tr.hash=sha;
    tr.type="tree";
    
    string writeStr=tr.hash+" "+tr.type;
    // cout<<"object "<<writeStr<<endl;

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
                  
                if(hash_filename == tokens[0])
                    flag++;
                // parent = tokens[1];
            }
            in.close();
    }

    if(flag==0){
        std::ofstream ofs;
        ofs.open (".mygit/info/objectsFile.txt", std::ofstream::out | std::ofstream::app);
        ofs << writeStr <<endl;
        ofs.close();
       }
    string directory="";
    string treename="";
    for(int i=0;i<2;i++)
        directory+=hash_filename[i];

     string pathwd=getenv("PWD");
    mkdir((pathwd+"/.mygit/objects/"+directory).c_str(),0777);
     // cout<<directory<<endl;

    for(int i=2;i<40;i++)
        treename+=hash_filename[i];

    // cout<<treename<<endl;

    Tree t;
    // t.treeContent = new char[content.length()+1];
    strcpy(t.treeContent,content.c_str());
    // cout<<t.treeContent;
    FILE *File = fopen((pathwd+"/.mygit/objects/"+directory+"/"+treename).c_str(),"wb");
    

   
    fwrite((char *)&t,sizeof(t),1,File);
     
    return sha;
}


void deserializeTree(string file){
     Tree t;
     FILE *File;

     string directory="";
     string treename="";

     for(int i=0;i<2;i++)
        directory+=file[i];
     for(int i=2;i<40;i++)
        treename+=file[i];

    string pathwd=getenv("PWD");
     string path=pathwd+"/.mygit/objects/"+directory+"/"+treename;
     // cout<<path;
    File = fopen(path.c_str(),"rb");

    // ifstream ifs(path.c_str(), ios::binary);
    // ifs.seekg(0, std::ios::end);
    // int fileSize = ifs.tellg();
    // ifs.seekg(0, std::ios::beg);

    fread((char *)&t,sizeof(t),1,File); //Treats the object as if it is a char array
    t.Print_Content1();
    fclose(File);

 }




// int main(){
//     string hash;
//     Index i;
    
//     vector<Index> v;
//     v=indexRead();

    
//     cout<<createTreeObject(".",v)<<endl;
//     cout<<"enter hash :"<<endl;
//     cin>>hash;

//     deserializeTree(hash);
//     return 0;
// }