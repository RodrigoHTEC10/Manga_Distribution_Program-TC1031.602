/*
Title: Action.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: October 12th
Description: 
The Action class is responsible for creating the object that keeps
record of the different actions taken by the user. Including the addition, 
elimination, sorting, finding and checking of manga volumes.
*/

#ifndef ACTION_H_
#define ACTION_H_

#include <iostream>
#include <string>
#include <ctime>
#include "Volume.h"

using namespace std;

class Action
{
private:
    //Private Instance Variables (PIV)
    string name;
    int id;
    string type;
    Volume storedVolume;
    string description;
    bool reversed;
    time_t now;

public:
    //Constructors
    Action();
    Action(string, int, string, Volume, string);

    //Public Functions
    string getType();
    Volume getVolume();
    int getID();
    string toString();
    bool hasBeenReversed();
    void reverse();
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Action()

Default contructor of the Action object.
*/
Action::Action(): name(""), id(-1), type(""), storedVolume(Volume()), description(""), reversed(false) {
    time(&now);
}

//---------------------------------------------------------------------
/*
Action(string name_, int id_, string type_, Volume vol_, string desc_)

Constructor with parameters of the Action object.
*/

Action::Action(string name_, int id_, string type_, Volume vol_, string desc_){
    name = name_;
    id = id_;
    type = type_;
    storedVolume = vol_;
    description = desc_;
    reversed = false;
    time(&now);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Getters

/*
string getType()

Method that returns the type of the action taken by the user.
*/
string Action::getType(){
    return type;
};

//---------------------------------------------------------------------
/*
Volume getVolume()

Method that returns the Volume involved within the action taken by the 
user.
*/
Volume Action::getVolume(){
    return storedVolume;
};

//---------------------------------------------------------------------
/*
int getID()

Method that returns the ID number related to the action taken by the 
user.
*/
int Action::getID(){
    return id;
};

//---------------------------------------------------------------------
/*
bool hasBeenReversed()

Method that returns a boolean corresponding to the status reversed of
the Action object.
*/
bool Action::hasBeenReversed(){
    return reversed;
};

//---------------------------------------------------------------------
/*
void reverse()

Method that turns the reverse status of an Action object to true.
*/
void Action::reverse(){
    reversed = true;
};


//---------------------------------------------------------------------
/*
string toString()

Method that returns a string that contains all the information related
to the action taken.
*/
string Action::toString(){
    string text = "================================================\n";
    text+= "    Type of Action Taken: "+type+"\n";
    text+= "    ID: "+to_string(id)+"\n";
    text+= "    Name: "+name+"\n";
    text+= "    Description: "+description+"\n";
    string strTime = ctime(&now);
    text+= "    Time: "+ strTime +"\n";
    return text;
};


#endif