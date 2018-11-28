#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <array>
#include<unistd.h>
#include <vector>
#include<fstream>
using namespace std;

void diff(string f1, string f2,string name){

    cout<<endl;
    cout<<f1<<endl;
    cout<<f2<<endl;
    cout<<name<<endl;    

    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    string pa(cwd);

    string path_f1 = pa + "/.mygit/diff/" + f1;
    string path_f2 = pa + "/.mygit/diff/" + f2;

    cout<<path_f1<<endl;
    cout<<path_f2<<endl;

    string command = "diff -u " +path_f1+" "+path_f2;

    array<char, 128> buffer;
    string result;
    vector<string> s;

    //cout << "Opening reading pipe" << endl;
    FILE* pipe = popen(command.c_str(), "r");
    // if (!pipe)
    // {
    //     cerr << "Couldn't start command." << endl;
    //     return 0;
    // }
    while (fgets(buffer.data(), 128, pipe) != NULL) {

        s.push_back(buffer.data());

    }

    cout<<s.size()<<endl;

    int in = 0;
    int del = 0;
    auto returnCode = pclose(pipe);

    //cout << s[2];

     std::ofstream ofs;
         ofs.open ((".mygit/diff_files/"+name).c_str(), std::ofstream::out );
         

    for(int i = 3; i < s.size(); i++){
        // if(s[i][0]=='+')
        //     in++;
        // else if(s[i][0]=='-'){
        //     del++;
        // }
        cout<<s[i]<<endl;
        ofs << s[i];

        //cout << s[i][0]<< endl;
    }

    // cout << "1 file changed, " << in << " insertions(+), "<< del << " deletions(-)" << endl;


}

void diff2(string f1, string f2){


    string command = "diff -u " +f1+" "+f2;

    array<char, 128> buffer;
    string result;
    vector<string> s;

    //cout << "Opening reading pipe" << endl;
    FILE* pipe = popen(command.c_str(), "r");
    // if (!pipe)
    // {
    //     cerr << "Couldn't start command." << endl;
    //     return 0;
    // }
    while (fgets(buffer.data(), 128, pipe) != NULL) {

        s.push_back(buffer.data());

    }

    int in = 0;
    int del = 0;
    auto returnCode = pclose(pipe);

    //cout << s[2];

     std::ofstream ofs;
         ofs.open ("temp_diff", std::ofstream::out );
         

    for(int i = 3; i < s.size(); i++){
        // if(s[i][0]=='+')
        //     in++;
        // else if(s[i][0]=='-'){
        //     del++;
        // }

        ofs << s[i];

        //cout << s[i][0]<< endl;
    }

    // cout << "1 file changed, " << in << " insertions(+), "<< del << " deletions(-)" << endl;


}

// int main(){


//     diff2("abc" , "def");

//     return 0;
// }
