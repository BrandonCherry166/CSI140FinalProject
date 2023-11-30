#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    string fileName = "adventurelog.txt";
    ifstream fin (fileName);
    ofstream fout (fileName);

    if(!fin.is_open())
    {
        cerr << fileName << " file doesn't exist";
        return -1; //End Immediately
    }

    fout << "Welcome to the Adventure! " << endl;

}
