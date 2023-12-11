#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "header.h"

using namespace std;

const short MAX_ACTIONS = 10; //Maximum number of actions for one event. Should be as small as possible to save memory.
const string LOGNAME = "adventurelog.txt"; //Target for writing down the logs
const string STORYNAME = "story.twee"; //File containing the story details

int main(){
    //Initialization
    int decisionCount = 0; //Keeps track of how many decisions the user has made
    short currentEvent = 0; //Keeps track of the current event the user is on
    ofstream fout (LOGNAME);

    fout << "Welcome to the Adventure Log. This will log all of your decisions!" << endl;

    //Reading in the story
    ifstream fin(STORYNAME);
    if (!fin.is_open()) {
        throw runtime_error("Cannot find " + STORYNAME);
    }
    string line;
    string firstEvent;
    int eventNum = -2; //Find the total number of events in the file so we know how big the arrays need to be. Starts at -2 because two file headers use the same notation, even though they're not events. There should always be two of them, though
    while (getline(fin, line))
    {
        if (line[0] == ':')
        {
            eventNum++;
        }
        //While we're at it, find whatever the name of the first event is
        if (line.substr(0,9) == "  \"start\"")
        {
            firstEvent = line.substr(12,line.length()-14);
        }
    }

    //Initialize arrays
    string *events = new string[eventNum + 1];//This stores the titles of the various events
    string *prompts = new string[eventNum + 1]; //This stores the main description the user is shown
    string *actions = new string[eventNum + 1]; //This stores the list of actions available for them to take. The sublist is stored as a slash-seperated string
    string *nextEvents = new string[eventNum + 1]; //Choosing an action will move the user to another event. This stores the list of next events, also using a slash-seperated string. Each one results from the action in the same position - so if the action choices were run/hide, and the user types 'hide', the second slash-seperated number would be the event to go to.

    //Start from the beginning for the real read
    fin.clear();
    fin.seekg(0);
    eventNum = -2;

    bool inDesc = false;
    while (getline(fin, line))
    {
        if (line[0] == ':') //If the line starts with a '::' token, it's the name of an event.
        {
            eventNum++; //increment the event counter
            if (eventNum > 0) //If we're past the first two metadata things
            {
                stringstream ss; //This stores the characters of the title as we find them
                for (char c : line)
                {
                    if (c == '{') //The title line also has some extra metadata junk after it we're not using. The curly brace tells us where to stop to avoid it.
                    {
                        break;
                    }
                    if (c != ':') //Don't read in the token
                    {
                        ss << c;
                    }
                }
                events[eventNum] = ss.str(); //write down the event name
                inDesc = true; //prepare to read a description
            }
        }
        else if(line[0] == '[') //A '[[' token denotes an action
        {
            inDesc = false; //So, therefore we've reached the end of the description
            actions[eventNum] += line.substr( 2,line.length() - 4) + "/"; //Add the action's name to the list of actions for this event, without the square brackets on either side
        }
        else if (inDesc) //Otherwise, if we're currently reading a description
        {
            prompts[eventNum] += line + "\n"; //Add the current line to the description
        }
    }

    //Last go-through; we have to go through just the action list and turn all their names into event numbers that they point to for the nextEvents array
    for (int i = 0; i < eventNum; i++) //For each event
    {
        string actionsList[MAX_ACTIONS]; //Get its list of actions
        int decisionLen = splitString(actions[i],actionsList,'/',MAX_ACTIONS);
        for (int ii = 0; ii < decisionLen; ii++) //For each action in that list
        {
            for (int iii = 0; iii < eventNum; iii++) //Check its name against the name of every event in the list
            {
                if (events[iii] == (" " + actionsList[ii] + " ")) {
                    nextEvents[i] += to_string(iii) + "/"; //When we find a match, add that resolved event number to the list of possible nextEvents for this action
                    break;
                }
            } //'Oh, but what if there's a collision; more than one event with the same name' you might say. Well, the whole reason we're using the Twine file format is because there are convenient writing tools for it, and the Twine format and every one of those writing tools will not allow duplicate event names, and will throw a fit if you try. The only way a collision would happen was if a user was doing manual editing of the file, at which point I would ask them; why? Twine is free and open source, not very processor intensive, and can be run in a browser or downloaded on any modern OS.
        }
    }

    for (int iii = 0; iii < eventNum; iii++) //Check the name of the first event against the name of every event in the list
    {
        if (events[iii] == (" " + firstEvent + " ")) {
            currentEvent = iii; //When we find a match, add that resolved event number to the first event the user sees
            break;
        }
    }

    fin.close();

    //Mainloop
    while (currentEvent != -1)
    {
        print(events[currentEvent] + "\n"); //Print the name and description of the event
        print(prompts[currentEvent]);

        string curActions[MAX_ACTIONS]; //Find the list of valid actions the user can take at this event
        int actionLen = splitString(actions[currentEvent],curActions,'/', MAX_ACTIONS);

        short choiceNum = -1;
        while (choiceNum == -1) //Wait for the user to input a valid action
        {
            print("You can order the troop to " + actionList(curActions,actionLen) + ".\n");
            cout << "\n";
            print("You order them to ...");
            string chosenAction;


            getline(cin, chosenAction);
            decisionCount++;
            fout << "Decision #" << decisionCount <<": " << chosenAction << endl;
            cout << "\n";
            for (int i = 0; i < actionLen; i++) //Check if the user input matches anything in the list of valid actions
            {
                if (chosenAction == curActions[i])
                {
                    choiceNum = i;
                    break;
                }
            }
            //Special case; when talking to the heart, it talks back in the log. I could write up a whole system for this but ... I can't be bothered.
            if (chosenAction == "Hello?") {
                fout << "Welcome, child." << endl;
            }
            if (chosenAction == "What are you?") {
                fout << "I am the center of the forest. It all connects to me. Except YOU." << endl;
            }
            if (chosenAction == "Why are you here?") {
                fout << "I came here long ago and made this place into my body." << endl;
            }
            if (chosenAction == "What do you want?") {
                fout << "I want to control, just like you. Now, come nearer." << endl;
            }

            if (choiceNum == -1) //If the user didn't choose a valid action, let them know
            {
                print("You give the order, but the troop doesn't seem to understand. Maybe try something else?\n");
            }
        }

        string curNextEvents[MAX_ACTIONS]; //Get the list of next events to go to
        splitString(nextEvents[currentEvent],curNextEvents,'/',MAX_ACTIONS);

        currentEvent = stoi(curNextEvents[choiceNum]); //Set the current event to the event we're going to
    }

    //Wrap up
    fout.close();
    return 0;
}
