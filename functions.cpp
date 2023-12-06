#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <windows.h>
#include "header.h"
#include <stdexcept>

using namespace std;

void print(string sentence) //Takes in a string and prints it out letter by letter. For effect.
{
    for (int k = 0; k < sentence.size();k++)
    {
        cout << sentence[k];
        Sleep(210);
    }
}

int splitString(string str, string* out, char split, short maxValues) //Splits a string into chunks seperated by some character 'split'
{
    stringstream ss; //Stream for storing each chunk as we build it
    short chunkNum = 0;
    for (int i = 0; i < str.size();i++) //Go through the string one character at a time
    {
        if (str[i] != split) //If it's not the split character, add it to the current chunk
        {
            ss << str[i];
        }
        if (str[i] == split or i == str.size() - 1) //If it is the split character, or this is the last character, save the current chunk
        {
            out[chunkNum] = ss.str();
            ss.str("");
            chunkNum++;
        }
        //We need to both add the last character of the string (which shouldn't be a split character) and then save the last chunk.
        //That's why we have the extra bit about the last character only in the saving block

        //Error checking; make sure we're not overflowing the outside array.
        if (chunkNum >= maxValues)
        {
            throw invalid_argument("splitString is trying to create more values than the passed array has space for");
        }
    }
    return chunkNum; //return the number of chunks found
}

string actionList(string actions[], int actionLen) //Prettys up a list of actions for display
{
    stringstream ss; //Buffer to hold the output
    for (int i = 0; i < actionLen; i++) //For each action
    {
        ss << actions[i]; //Add it to the output
        if (i < actionLen - 1) { //Seperated by a comma if it's not the last element
            ss << ", ";
        }
        if (i == actionLen - 2) //Add an "or" to the split only if it's the second to last element
        {
            ss << "or ";
        }
    }
    return ss.str();
}
