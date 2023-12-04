#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;
int main(){
    string fileName = "adventurelog.txt";
    ifstream fin (fileName);
    ofstream fout ("out"+fileName);

    if(!fin.is_open())
    {
        cerr << fileName << " file doesn't exist";
        return -1; //End Immediately
    }

    print(fileName);

    fout << "Welcome to the Adventure! " << endl;

}
