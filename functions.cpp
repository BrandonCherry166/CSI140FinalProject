#include <iostream>
#include <string>
#include <fstream>
#include<windows.h>
#include "header.h"
using namespace std;

void print(string sentence)
{
    for (int k = 0; k < sentence.size();k++)
    {
        cout << sentence[k];
        Sleep(210);
    }
}
