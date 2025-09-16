/*
Title: Collection.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: September 15th
Description:
The Class Collection is the center piece that connects classes 
interactions between them and the main as it coordinates and stores all
volumes and bookshelfs.
*/

#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <iostream>
#include <string>
#include <vector>
#include "Volume.h"
#include "Bookshelf.h"
#include "SortSearch.h"

using namespace std;

class Collection{

private:

    //sorted Enum
    enum sorted {
        author,
        name
    };

    //Private Intance Variables (PIV)
    vector<Volume> volumes;
    vector<Bookshelf> bookshelves;
    int bookshelfShelfs;
    float shelfLength;
    sorted sortType;
    Sort sorting;

    //Private Functions
    void emptyBookshelves();

public:
    //Public Functions
    Collection();
    Collection(int, float);
    vector<Volume>& getVolumes();
    vector<Bookshelf>& getBookshelfs();
    void setSortType(string);
    string addVolume(Volume);
    string eraseVolume(int);
    vector <string> consultCollection();
    vector <string> consultBookshelf(int);
    vector <string> consultsShelf(int, int);
    vector<string> getCollectionBy(int);
    vector<int> searchForVolumes(string);
    
    
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Collection() empty default constructor
*/
Collection::Collection(){
    bookshelfShelfs = 4;
    shelfLength = 100;
    sortType = name;
}

//---------------------------------------------------------------------
/*
Collection(int bookshelfShelf_, float shelfLength_)

The constructor with parameters stores the number of shelves and the 
length of each shelf per bookshelf, making the bookshelf size and 
dimensions completely parameterizable.
*/
Collection::Collection(int bookshelfShelf_, float shelfLength_){
    bookshelfShelfs = bookshelfShelf_;
    shelfLength = shelfLength_;
    sortType = name;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Getters

/*
vector <string> getCollectionBy(int key)

Method that returns a vector of strings with either the names of all 
volumes, favorite volumes or authors in the collection.
*/
vector <string> Collection::getCollectionBy(int key){
    vector<string> collected_volumes;
    int counter = 0;

    switch(key)
    {
    // Get Collection Authors.
    case 1:{
        for(int i = 0; i< volumes.size()-1; i++){
            if(volumes[i].getAuthor() != volumes[i+1].getAuthor()){
                counter++;
                collected_volumes.push_back(volumes[i].getAuthor());
            }
        }

        string lastAuthor = collected_volumes[counter-1];
        if((volumes[volumes.size()-1].getAuthor().compare(lastAuthor) != 0)){
            collected_volumes.push_back(volumes[volumes.size()-1].getAuthor());
        }

    }break;

    // Get Collection Favorite Names and Volumes.
    case 2:{
        for(int i = 0; i< volumes.size()-1; i++){
            if((volumes[i].isFavorite())){
                counter++;
                collected_volumes.push_back(volumes[i].getName()+" Volume: "+to_string(volumes[i].getVolume()));
            }
        }
        if(counter > 0){
            string lastName = collected_volumes[counter-1];
            if(volumes[volumes.size()-1].isFavorite()){
                collected_volumes.push_back(volumes[volumes.size()-1].getName()+" Volume: "+to_string(volumes[volumes.size()-1].getVolume()));
            }
        }
        

    }break;

    // Get Collection by Names.
    default:{
        for(int i = 0; i< volumes.size()-1; i++){
            if(volumes[i].getName() != volumes[i+1].getName()){
                counter++;
                collected_volumes.push_back(volumes[i].getName());
            }
        }

        string lastName = collected_volumes[counter-1];
        if(volumes[volumes.size()-1].getName().compare(lastName) != 0){
            collected_volumes.push_back(volumes[volumes.size()-1].getName());
        }

    }break;
    }
    return collected_volumes;
}

//---------------------------------------------------------------------
/*
vector<Volume>& getVolumes()

Method that returns a reference to the volumes vector of the Collection
object.
*/
vector<Volume>& Collection::getVolumes(){
    return volumes;
};

//---------------------------------------------------------------------
/*
vector<Bookshelf>& getBookshelfs()

Method that returns a reference to the bookshelves vector of the 
Collection object.
*/
vector<Bookshelf>& Collection::getBookshelfs(){
    return bookshelves;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Setters

/*
void setSortType(string type)

Depending on the received string, the variable sortType will change 
to either author or name.
*/
void Collection::setSortType(string type){
    emptyBookshelves();
    if(type == "author"){
        sorting.sortByAuthor(volumes, bookshelves);
        sortType = author;
    }
    else{
        sorting.sortByName(volumes, bookshelves);
        sortType = name;
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Private Methods

/*
void emptyBookshelves()

Method responsible for eliminating all the elements inside the 
bookshelves vector, as a method to eliminate all volumes in previous
locations.
*/
void Collection::emptyBookshelves(){
    bookshelves.clear();
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Public Methods

/*
string addVolume(Volume volume_)

Method responsible for adding a new volume [volume_] to the volumes 
vector of the Collection, sorting again all the volumes (depending 
oon which sorting type was the last) and return a sucess message. 
*/
string Collection::addVolume(Volume volume_){
    volumes.push_back(volume_);
    emptyBookshelves();
    if(sortType == author){
        sorting.sortByAuthor(volumes, bookshelves);
    }
    else{
        sorting.sortByName(volumes, bookshelves);
    }
    return "The Volume has been added successfully!";
}

//---------------------------------------------------------------------
/*
string eraseVolume(int index_)

Method responsible for based on the index of the volume to erase [index_]
the volume is erased from both the volumes vector and its respective
location on their specific shelf. To resort the collection again and 
return a sucess message.
*/
string Collection::eraseVolume(int index_){
    //Get Location of the Volume
    vector<int> location = volumes[index_].getLocation();

    //Erase the volume from the bookshelf
    bookshelves[location[0]].eraseVolume(location[1], location[2]);

    //Erase the volume from the collection
    volumes.erase(volumes.begin()+index_);

    //Re-order the remaining manga volumess
    setSortType(to_string(sortType));
    return "The Volume has been erased successfully!";
}


//---------------------------------------------------------------------
/*
vector <string> consultCollection()

Method that returns all the volumes information stored in the Collection.
*/
vector <string> Collection::consultCollection(){
    vector<string> totalVolumes;

    for(int i = 0; i<bookshelves.size(); i++){
        vector<string> temporary;
        temporary = bookshelves[i].getVolumes();
        totalVolumes.insert(totalVolumes.end(), temporary.begin(), temporary.end());
    }
    return totalVolumes;
};

//---------------------------------------------------------------------
/*
vector <string> consultBookshelf(int index)

Method that returns all the volumes information stored in the specified
bookshelf number of the collection.
*/
vector <string> Collection::consultBookshelf(int index){
    return bookshelves[index].getVolumes();
}


//---------------------------------------------------------------------
/*
vector <string> consultsShelf(int index, int shelf)

Method that returns all the volumes information stored in the specified
shelf of a specific bbookshelf number of the collection.
*/
vector <string> Collection::consultsShelf(int index, int shelf){
    return bookshelves[index].getVolumes(shelf);
}

//---------------------------------------------------------------------
/*
vector<int> searchForVolumes(string name)

Method that calls the method searchVolumes() of the SortSearch class 
to obtain the range of indexes of the chosen name volume.
*/
vector<int> Collection::searchForVolumes(string name){
    return sorting.searchVolumes(volumes, name);
};

#endif