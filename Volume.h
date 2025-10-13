/*
Title: Volume.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: October 12th
Description: 
The Volume Class is the pilar of the present project as this object holds
the information of each volume. These manga Volumes will be sorted, 
ordered and stored in specific bookshelf dimensions.
*/

#ifndef VOLUME_H_
#define VOLUME_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Volume
{

private:
    //Private Instance Variables (PIV)
    float width;  
    string name;
    int volume;
    string author;
    bool favorite;
    int bookshelf;
    int shelf;
    int shelfIndex;

public:
    //Constructors
    Volume();
    Volume(string, int, string, float, bool);

    //Public Functions
    void setLocation(int, int, int);
    vector<int> getLocation();
    string getName();
    string getAuthor();
    int getVolume();
    bool isFavorite();
    float getWidth();
    string getInfo();
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Volume() default constructor.

This constructor creates a default Volume without any specific
characteristics or location.
*/
Volume::Volume(){
    width = 0.0;
    name = "Forgotten Volume";
    volume = 0;
    author = "Unknown";
    favorite = false;
    bookshelf = 0;
    shelf = 0;
    shelfIndex = 0;
};

//---------------------------------------------------------------------
/*
Volume(string name_, int volume_, string author_, float width_, 
bool favorite_)

Constructor with parameters that passes each of the showed parameters to
its correspondant PIV; however, its location in null (0,0,0) as the order 
is established by the sort algorithm. 
*/
Volume::Volume(string name_, int volume_, string author_, float width_, bool favorite_){
    width = width_;
    name = name_;
    volume = volume_;
    author = author_;
    favorite = favorite_;
    bookshelf = 0;
    shelf = 0;
    shelfIndex = 0;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Setters

/*
void setLocation(int bookshelf_, int shelf_, int shelfIndex_)

Establish the location of the volume at a specific bookshelf, shelf and
corresponding index inside the mentioned shelf.
*/
void Volume::setLocation(int bookshelf_, int shelf_, int shelfIndex_){
    bookshelf = bookshelf_;
    shelf = shelf_;
    shelfIndex = shelfIndex_;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Getters

/*
vector<int> getLocation()

Returns a vector of integers that show the location of a volume in a 
specific order: {bookshelf, shelf, shelfIndex}
*/
vector<int> Volume::getLocation(){
    vector <int> location = {bookshelf, shelf, shelfIndex};
    return location;
}

//---------------------------------------------------------------------
/*
string getName()

Returns the name of the volume as a string.
*/
string Volume::getName(){
    return name; 
};

//---------------------------------------------------------------------
/*
string getAuthor()

Returns the name of the author as a string.
*/
string Volume::getAuthor(){
    return author;
};

//---------------------------------------------------------------------
/*
int getVolume()

Returns the volume number of the volume as an integer.
*/
int Volume::getVolume(){
    return volume;
};

//---------------------------------------------------------------------
/*
bool isFavorite()

Returns the boolean of the volume that shows if it is a favorite volume
of the collection.
*/
bool Volume::isFavorite(){
    return favorite;
};

//---------------------------------------------------------------------
/*
float getWidth()

Returns the width of the volume as a float.
*/
float Volume::getWidth(){
    return width;
};

//---------------------------------------------------------------------
/*
string getInfo()

Returns the overall information of the volume as a whole string with
a specific distribution and dimensions.
*/
string Volume::getInfo(){
    string info = "";
    info += "    --------------------------------------------------\n   Title: "+name+"\n   Volume: "+to_string(volume);
    info += "\n   Author: "+author+"\n   Status: ";
    if(favorite){
        info+= "Favorite\n";
    }
    else{
        info += "Normal\n";
    }
    return info;
};

#endif