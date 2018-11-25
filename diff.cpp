#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <vector>
#include<fstream>
using namespace std;

void diff(string f1, string f2){

    string command("diff -u " +f1+" "+f2);

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

int main(){


    diff("abc" , "def");

    return 0;
}
