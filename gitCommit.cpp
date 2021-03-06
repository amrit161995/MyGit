#include<stdio.h>
#include<string>
#include <openssl/sha.h>
#include "tree.h"
#include "generateSHA.h"
#include "indexCreate.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<dirent.h>
#include "gitCommit.h"
#include "gitStatus.h"
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

// class Commit
// {
//     public:
//         char type[10]="commit";
//         char tree[60]= "";
//         char parent[60]="";
//         char author[200]="";
//         char committer[200]="";
//         char message[500]="";
//         char * content;

        void Commit::Print_Type()
        {
            cout<<type<<endl;
        }

        void Commit:: Print_Content()
        {
            cout<<"tree : "<<tree<<endl;
             cout<<"parent : "<<parent<<endl;
            cout<<"author : "<<author<<endl;
            cout<<"committer : "<<committer<<endl;
            cout<<endl;
            cout<<message<<endl;
        }

        void Commit:: setContent(char *con){
            content=con;
        }

        char * Commit::getContent(){
            return content;
        }

  



string Commit::createCommit(string tree,string author,string committer,string message)
{   
    string parent="";
	struct stat buf;
    if (stat(".mygit/log", &buf) != -1)
    {

    	vector <string> vecOfStrs;
        // cout<<"hello";
        std::ifstream in(".mygit/log");
        string str;
		while (std::getline(in, str))
			{
				// Line contains string of length > 0 then save it in vector
				if(str.size() > 0)
					vecOfStrs.push_back(str);
			}

			string line = vecOfStrs[vecOfStrs.size()-1]; 
		    
		    vector <string> tokens; 
		    stringstream check1(line); 
		    string intermediate; 
		     
		    while(getline(check1, intermediate, '|')) 
		    { 
		        tokens.push_back(intermediate); 
		    } 
		      
		    // cout<<tokens[1]<<endl;
		    parent = tokens[1];
		    
			in.close();
    }
    else{
    	parent="0000000000000000000000000000000000000000";
    	

    	 

    }

    strcpy(this->tree,tree.c_str());
    strcpy(this->parent,parent.c_str());
    strcpy(this->author,author.c_str());
    strcpy(this->committer,committer.c_str());
    strcpy(this->message,message.c_str());

    
   


    string temp="tree : "+tree+";"+"parent : "+parent+";"+"author : "+author+";"+"committer : "+committer+";"+"message : "+message+";";
    char* t = new char[temp.length()];
    content = t;
    // string temp=string(bytes.data(), fileSize);
     strcpy(content,temp.c_str());
    // setContent(content);
    // type="blob";
     string type1=this->type;
     
    string header=type1+" "+to_string(temp.length())+"\0";

    string store = header+ " " + temp;
    string sha1=generateSHAstring(store);

     std::time_t result = std::time(nullptr);
    	// string timetemp=(string)result;
    	string log=parent+"|" + sha1 + "|" + author + "|" + committer + "|"+to_string(result) +"|+530"+ "|commit|"+message+"\n";
    	 std::ofstream ofs;
    	 ofs.open (".mygit/log", std::ofstream::out | std::ofstream::app);
    	 ofs << log;
    	 ofs.close();


    //write master
    	 // std::ofstream ofs;
    	 ofs.open (".mygit/refs/heads/master", std::ofstream::out);
    	 ofs << sha1;
    	 ofs.close();

    return sha1;
}







void serializeCommit(string tree,string author,string committer,string message){
    //cout<<"hello";
    Commit com;
    string hash_filename=com.createCommit(tree,author,committer,message);

    string directory="";
    string commitname="";
    for(int i=0;i<2;i++)
        directory+=hash_filename[i];
    mkdir((".mygit/objects/"+directory).c_str(),0777);
     cout<<directory;

    for(int i=2;i<40;i++)
        commitname+=hash_filename[i];

     cout<<commitname<<endl;
    // cout<<hash_filename;
    FILE *File = fopen((".mygit/objects/"+directory+"/"+commitname).c_str(),"wb");
    // Test.Print_Content();
    // cout<<Test.getContent();
    fwrite((char *)&com,sizeof(com),1,File); //Treats the object as if it is a char array

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
        string writeStr=hash_filename+" commit";
        std::ofstream ofs;
        ofs.open (".mygit/info/objectsFile.txt", std::ofstream::out | std::ofstream::app);
        ofs << writeStr <<endl;
        ofs.close();
    }

    fclose(File);

    
}


void deserializeCommit(string file){
     Commit com;
     FILE *File;

     string directory="";
     string commitname="";

     for(int i=0;i<2;i++)
        directory+=file[i];
    // mkdir(".git/objects/"+directory);
    // cout<<directory<<endl;

    for(int i=2;i<40;i++)
        commitname+=file[i];
     string path=".mygit/objects/"+directory+"/"+commitname;
    File = fopen(path.c_str(),"rb");
    fread((char *)&com,sizeof(com),1,File); //Treats the object as if it is a char array
    com.Print_Content();
    fclose(File);

 }

//  vector<string> splitStrings(string str, char dl)
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



// void listdir(const char *name, int indent, vector<string> &lis)
// {
//     DIR *dir;
//     struct dirent *entry;

//     if (!(dir = opendir(name)))        
//         return;

//     while ((entry = readdir(dir)) != NULL) {
//         if (entry->d_type == DT_DIR and entry->d_name[0]!='.') {
//             char path[1024];
//             if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
//                 continue;
//             snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
//             // printf("%*s[%s]\n", indent, "", entry->d_name);
//             listdir(path, indent + 2,lis);
//         } 
//         else if(entry->d_name[0]!='.'){
//             char cwd[1024];
//             getcwd(cwd,sizeof(cwd));
//             string pa(cwd);
//             vector<string> na = splitStrings(name,'/');
//             string path;
//             if(na.size()>1) path = pa + "/" + na[na.size()-1] + "/" + entry->d_name;
//             else path = pa + "/" + entry->d_name;
//             lis.push_back(path);
//             // printf("%*s- %s\n", indent, "", entry->d_name);
//         }
//     }
//     closedir(dir);
// }

void commitMain(string author,string committer,string message){
	vector<Index> v;
    v=indexRead();

    int flag=0;
    for(int i=0;i<v.size();i++){
    	// cout<<v[i].commit<<endl;
    	if(v[i].commit == 0){

    		flag++;
    	}
    }

    // cout<<flag<<endl;
    vector<string> lis;
    listdir(".", 0,lis);
    map< string,vector<string> > m = getFiles(lis);

   if(flag>0){
   if(m["tracked"].size()!=0) {
        string treehash=createTreeObject(".",v);
	    serializeCommit(treehash,author,committer,message);
	    commitAll();
    }
    else{


    	if(m["untracked"].size()!=0){
    		cout<<"Untracked files:"<<endl;
	        cout<<"  (use \"mygit add <file>...\" to include in what will be committed)"<<endl<<endl;
	        for(int j=0;j<m["untracked"].size();j++) cout<<"\t"<<m["untracked"][j]<<endl;
	        cout<<endl;
    	}

    	if(m["modified"].size()!=0 or m["deleted"].size()!=0){
    		cout<<"Changes not staged for commit:"<<endl;
	        cout<<"  (use \"mygit add <file>...\" to update what will be committed)"<<endl;
	        cout<<"  (use \"mygit checkout -- <file>...\" to discard changes in working directory)"<<endl<<endl;
	        for(int j=0;j<m["modified"].size();j++) cout<<"\tmodified:   "<<m["modified"][j]<<endl;
	        for(int j=0;j<m["deleted"].size();j++) cout<<"\tdeleted:   "<<m["deleted"][j]<<endl;
	        cout<<endl;


    	}

    	
    		if(m["tracked"].size()==0){
		        if(m["untracked"].size()!=0)
		            cout<<"nothing added to commit but untracked files present (use \"mygit add\" to track)"<<endl;
		        else
		            cout<<"nothing to commit, working directory clean"<<endl;
		    

    	}
	}
}

else{
	cout<<"nothing to commit, working directory clean"<<endl;
}
}


//  int main(){
//     // string fileName="abc.txt";
    
//  	commitMain("abc","xyz","ad");
//     string hash;
//     cout<<"enter hash: ";
//     cin>>hash;
//     deserializeCommit(hash);
//     cout<<"enter tree hash: ";
//     cin>>hash;
//     deserializeTree(hash);
//     return 0;
// }
