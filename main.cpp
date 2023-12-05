#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;

const string EVENTS[] = {"Bear!","Calming down","AAAH","AAAAAAH"};
const string PROMPTS[] = {"Your troop is approached by a bear.","","",""};
const string ACTIONS[] = {"stay calm/get loud/scatter","","",""};
const string NEXT_EVENTS[] = {"1/2/3","","",""};

const short MAX_ACTIONS = 10;
const string FILENAME = "adventurelog.txt";

int main(){
    short currentEvent = 0;
    ofstream fout (FILENAME);

    while (currentEvent != -1)
    {
        print(EVENTS[currentEvent] + "\n");
        print(PROMPTS[currentEvent] + "\n");

        string actions[MAX_ACTIONS];
        int actionLen = splitString(ACTIONS[currentEvent],actions,'/');

        short choiceNum = -1;
        while (choiceNum == -1)
        {
            print("You can order the troop to " + actionList(actions,actionLen) + ".\n");
            cout << "\n";
            print("You order them to ...");
            string chosenAction;
            getline(cin, chosenAction);
            cout << "\n";
            for (int i = 0; i < actionLen; i++)
            {
                if (chosenAction == actions[i])
                {
                    choiceNum = i;
                    break;
                }
            }
            if (choiceNum == -1)
            {
                print("You give the order, but the troop doesn't seem to understand. Maybe try something else?\n");
            }
        }

        string nextEvents[MAX_ACTIONS];
        int nextLen = splitString(NEXT_EVENTS[currentEvent],nextEvents,'/');
        currentEvent = stoi(nextEvents[choiceNum]);
    }
    fout << "Welcome to the Adventure! " << endl;

    fout.close();
    return 0;
}
