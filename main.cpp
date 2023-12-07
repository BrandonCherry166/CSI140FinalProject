#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;

const string EVENTS[] = {"Bear!","Calming down","AAAH","AAAAAAH"}; //This stores the titles of the various events
const string PROMPTS[] = {"Your troop is approached by a bear.","","",""}; //This stores the main description the user is shown
const string ACTIONS[] = {"stay calm/get loud/scatter","","",""}; //This stores the list of actions available for them to take. The sublist is stored as a slash-seperated string
const string NEXT_EVENTS[] = {"1/2/3","","",""}; //Choosing an action will move the user to another event. This stores the list of next events, also using a slash-seperated string. Each one results from the action in the same position - so if the action choices were run/hide, and the user types 'hide', the second slash-seperated number would be the event to go to.

const short MAX_ACTIONS = 10; //Maximum number of actions for one event. Should be as small as possible to save memory.
const string FILENAME = "outadventurelog.txt"; //Target for writing down the logs
const string INPUTNAME = "inadventurelog.txt"; //Target for reading from the log


int main(){
    int decisionCount = 0;
    short currentEvent = 0; //Keeps track of the current event the user is on
    ifstream fin(INPUTNAME);
    ofstream fout (FILENAME);
    string name;
    int troopNumber;
    string rank;

    fin >> name >> troopNumber >> rank;
    string intro = "Welcome, " + name + ", of Troop ";
    string intro2 = ". You are a " + rank + " scout and the SPL of your troop!";

    print (intro);
    print (to_string(troopNumber));
    print (intro2);
    fout << "Welcome to the Adventure Log. This will log all of your decisions!" << endl;

    while (currentEvent != -1) //Mainloop
    {
        print(EVENTS[currentEvent] + "\n"); //Print the name and description of the event
        print(PROMPTS[currentEvent] + "\n");

        string actions[MAX_ACTIONS]; //Find the list of valid actions the user can take
        int actionLen = splitString(ACTIONS[currentEvent],actions,'/', MAX_ACTIONS);

        short choiceNum = -1;
        while (choiceNum == -1) //Wait for the user to input a valid action
        {
            print("You can order the troop to " + actionList(actions,actionLen) + ".\n");
            cout << "\n";
            print("You order them to ...");
            string chosenAction;


            getline(cin, chosenAction);
            decisionCount++;
            fout << "Decision #" << decisionCount <<": " << chosenAction << endl;
            cout << "\n";
            for (int i = 0; i < actionLen; i++) //Check if the user input matches anything in the list of valid actions
            {
                if (chosenAction == actions[i])
                {
                    choiceNum = i;
                    break;
                }
            }
            if (choiceNum == -1) //If the user didn't choose a valid action, let them know
            {
                print("You give the order, but the troop doesn't seem to understand. Maybe try something else?\n");
            }
        }

        string nextEvents[MAX_ACTIONS]; //Get the list of next events to go to
        splitString(NEXT_EVENTS[currentEvent],nextEvents,'/',MAX_ACTIONS);

        currentEvent = stoi(nextEvents[choiceNum]); //Set the current event to the event we're going to
    }

    //Wrap up
    fout.close();
    return 0;
}
