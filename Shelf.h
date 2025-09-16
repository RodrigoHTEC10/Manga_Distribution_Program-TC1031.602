/*
Title: Shelf.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: September 15th
Description:
The Shelf class is an object that holds Volumes inside a Bookshelf.
There is a limited number of shelfs per bookshelf each with limited space.
The methods implemented in the present class are designed to work 
coordinately with greater methods of the corresponding Bookshelf Object 
that contains it.
*/

#ifndef SHELF_H_
#define SHELF_H_

#include <iostream>
#include <string>
#include <vector>
#include "Volume.h"

using namespace std;

class Shelf{
private:
    //Private Instance Variables (PIV)
    int number;
    vector<Volume> volumes;
    float length;

public:
    Shelf();
    Shelf(int, float);
    bool avaliableSpace(float);
    vector<string> getVolumes();
    void addVolume(Volume, int);
    void eraseVolume(int);
    int lastIndex();
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Shelf() empty default constructor.
*/
Shelf::Shelf(){
    number = 0;
}

//---------------------------------------------------------------------
/*
Shelf(int number_, float length_) constructor with parameters.

It created a shelf with a capacity of length_ to store volumes,
number_ is its number of the correspondent bookshelf.
*/
Shelf::Shelf(int number_, float length_){
    number = number_;
    length = length_;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Getters

/*
vector<string> getVolumes()

Returns a vector of strings with all the information of all volumes
stored in it.
*/
vector<string> Shelf::getVolumes(){
    vector <string> collection;
    for(int i = 0; i<volumes.size(); i++){
        collection.push_back(volumes[i].getInfo());
    }   
    return collection;
};

//---------------------------------------------------------------------
/*
int lastindex()

Returns the size of the volumes vector stored in the shelf, as this is
the next avaliable index.
*/
int Shelf::lastIndex(){
    return volumes.size();
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Public Function Declaration

/*
void addVolume(Volume newVolume, int index)

Method responsible for addting the volume [newVolume] at the chosen 
index [index] of the volumes stored in the shelf.
*/
void Shelf::addVolume(Volume newVolume, int index){
    volumes.insert(volumes.begin()+index,newVolume);
};

//---------------------------------------------------------------------
/*
void eraseVolume(int index)

Method responsible for eliminating the volume stored at index [index]
in the shelf.
*/
void Shelf::eraseVolume(int index){
    volumes.erase(volumes.begin()+index);
};

//---------------------------------------------------------------------
/*
bool avaliableSpace(float volumeWidth)

Returns a boolean that indicate if there is enough space at the shelf
to store a volume with width [volumeWidth] based on the avaliable 
space and already stored volumes.
*/
bool Shelf::avaliableSpace(float volumeWidth){
    float remainingSpace = length;
    for(int i = 0; i<volumes.size(); i++){
        remainingSpace = remainingSpace - volumes[i].getWidth();
    }
    return (remainingSpace >= volumeWidth);
};

#endif