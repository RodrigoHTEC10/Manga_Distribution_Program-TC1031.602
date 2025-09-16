/*
Title: Bookshelf.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: September 16th
Description:
The Class Bookshelf is the container of shelves that similarly contain
manga volumes. The Bookshelf and Shelf organization allow to obtain 
manga volumes easily by location and have a more precise spatial 
awareness.
The functions located in this class are connected with the Shelf functions
to give a coordinated answer about the volumes, conditions or space still
available.
*/

#ifndef BOOKSHELF_H_
#define BOOKSHELF_H_

#include <iostream>
#include <string>
#include <vector>
#include "Shelf.h"

using namespace std;

class Bookshelf
{

private:
    //Private Instance Variables (PIV)
    int number;
    vector<Shelf> shelves;
    int max;


public:
    Bookshelf();
    Bookshelf(int, int, float);
    vector<string> getVolumes();
    vector<string> getVolumes(int);
    int avaliableSpace(float);
    bool avaliableSpace(int, float);
    void addVolume(int, Volume, int);
    void eraseVolume(int, int);
    int getMax();
    Shelf& getShelf(int);

};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Bookshelf() empty default constructor
*/
Bookshelf::Bookshelf(){
    number = 0;
    max = 0;
}

//---------------------------------------------------------------------

/*
Bookshelf(int number_, int max_, float length_)

Constructor responsible for setting the name, maximum number or shelves
and shelf length of the specific bookshelf.
Inmediately, all shelves in order with the specified characteristics
are created and stored in the inner vector shelves.
*/
Bookshelf::Bookshelf(int number_, int max_, float length_){
    number = number_;
    max = max_;

    for(int i = 0; i<max; i++){
        shelves.push_back(Shelf(i, length_));
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Getters

/*
vector<string> getVolumes()

Returns a vector of strings that collects the information of all the 
volumes stored in the shelves of the Bookshelf.
*/
vector<string> Bookshelf::getVolumes(){
    vector<string> totalVolumes;

    for(int i = 0; i<shelves.size(); i++){
        vector<string> temporary;
        temporary = shelves[i].getVolumes();
        totalVolumes.insert(totalVolumes.end(), temporary.begin(), temporary.end());
    }

    return totalVolumes;
};

//---------------------------------------------------------------------
/*
int getMax()

Returns the maximum number of shelves in the Bookshelf.
*/
int Bookshelf::getMax(){
    return max;
};

//---------------------------------------------------------------------
/*
Shelf& getShelf(int number)

Returns the Shelve object reference to the shelf number entered as a
parameter [number].
*/
Shelf& Bookshelf::getShelf(int number){
    return shelves[number];
};

//---------------------------------------------------------------------
/*
vector<string> getVolumes(int shelfNo)

Returns a vector of strings with all the volumes stored in the specific
shelf [shelfNo] inside the Bookshelf.
*/
vector<string> Bookshelf::getVolumes(int shelfNo){
    return shelves[shelfNo].getVolumes();
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Public Function Declaration

/*
int avaliableSpace(float width)

Returns an integer with the first shelf of the bookshelf with enough
space to store the volume based on its width [width].
*/
int Bookshelf::avaliableSpace(float width){
    for(int i = 0; i<max; i++){
        if (shelves[i].avaliableSpace(width))
            return i;
    }
    return -1;
};

//---------------------------------------------------------------------
/*
bool avaliableSpace(int shelf, float width)

Returns a true boolean if the shelf [shelf] has enough space to store 
the manga volume based on its width [width].
*/
bool Bookshelf::avaliableSpace(int shelf, float width){
    return shelves[shelf].avaliableSpace(width);
};

//---------------------------------------------------------------------
/*
void addVolume(int shelfNumber, Volume newVolume, int index)

Function responsible for adding the volume [newVolume] into the shelf
[shelfNumber] vector of volumes at the index [index].
*/
void Bookshelf::addVolume(int shelfNumber, Volume newVolume, int index){
    shelves[shelfNumber].addVolume(newVolume, index);
};

//---------------------------------------------------------------------
/*
void eraseVolume(int shelfNumber, int index)

Function responsible for erasing the manga volume located at the shelf
[shelfNumber] at the volumes index [index].
*/
void Bookshelf::eraseVolume(int shelfNumber, int index){
    shelves[shelfNumber].eraseVolume(index);
};


#endif