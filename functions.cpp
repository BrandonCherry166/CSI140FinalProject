#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <windows.h>
#include "header.h"
#include <stdexcept>

using namespace std;

void print(string sentence)
{
    for (int k = 0; k < sentence.size();k++)
    {
        cout << sentence[k];
        Sleep(0);//210);
    }
}

int splitString(string str, string* out, char split)
{
    stringstream ss;
    short actionNum = 0;
    for (int i = 0; i < str.size();i++)
    {
        if (str[i] != split)
        {
            ss << str[i];
        }
        if (str[i] == split or i == str.size() - 1)
        {
            out[actionNum] = ss.str();
            ss.str("");
            actionNum++;
        }
        if (actionNum >= 10) //10 is the maximum size of the outside array. god this feels hacky.
        {
            invalid_argument("splitString is trying to create more than 10 values");
        }
    }
    return actionNum;
}

string actionList(string actions[], int actionLen)
{
    stringstream ss;
    for (int i = 0; i < actionLen; i++)
    {
        ss << actions[i];
        if (i < actionLen - 1) {
            ss << ", ";
        }
        if (i == actionLen - 2)
        {
            ss << "or ";
        }
    }
    return ss.str();
}
