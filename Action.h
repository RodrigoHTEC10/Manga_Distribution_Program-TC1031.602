/*
Title: Action.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: November 10th
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
    string timeString;

public:
    //Constructors
    Action();
    Action(string, int, string, Volume, string);
    Action(string, int, string, Volume, string, string);

    //Public Functions
    string getName();
    string getType();
    string getDescription();
    string getTime();
    Volume getVolume();
    int getID();
    void setID(int);
    string toString();
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Action()

Default contructor of the Action object.
*/
Action::Action(): name(""), id(-1), type(""), storedVolume(Volume()), description("") {
    time_t now;
    time(&now);
    timeString = ctime(&now);
    timeString.pop_back();
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
    time_t now;
    time(&now);
    timeString = ctime(&now);
    timeString.pop_back();
};


//---------------------------------------------------------------------
/*
Action(string name_, int id_, string type_, Volume vol_, string desc_)

Constructor with parameters of the Action object that allows to add an
action previous to the current work session.
*/

Action::Action(string name_, int id_, string type_, Volume vol_, string desc_, string time_){
    name = name_;
    id = id_;
    type = type_;
    storedVolume = vol_;
    description = desc_;
    timeString = time_;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Getters

/*
string getName()

Method that returns the name of the action taken by the user.
*/
string Action::getName(){
    return name;
};


//---------------------------------------------------------------------
/*
string getType()

Method that returns the type of the action taken by the user.
*/
string Action::getType(){
    return type;
};


//---------------------------------------------------------------------
/*
string getDescription()

Method that returns the description of the action taken by the user.
*/
string Action::getDescription(){
    return description;
};


//---------------------------------------------------------------------
/*
string getTime()

Method that returns the time of the action taken by the user.
*/
string Action::getTime(){
    return timeString;
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
void setID(int num)

Method that modifies the id of the Action as the parameter num_.
*/
void Action::setID(int num_){
    id = num_;
}


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
    text+= "    Time: "+ timeString +"\n";
    return text;
};


#endif