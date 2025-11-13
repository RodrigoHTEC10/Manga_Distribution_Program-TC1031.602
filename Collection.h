/*
Title: Collection.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: November 11th
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
#include "Heap.h"
#include "Record.h"

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
    Record modif;

    //Private Functions
    void emptyBookshelves();

public:
    //Public Functions
    Collection();
    Collection(int, float);
    vector<Volume>& getVolumes();
    vector<Bookshelf>& getBookshelfs();
    Record& getRecord();
    void setSortType(string, bool);
    string addVolume(Volume);
    void primitiveAddVolume(Volume);
    void addAction(Action);
    string eraseVolume(int);
    vector <string> consultCollection();
    vector <string> consultBookshelf(int);
    vector <string> consultsShelf(int, int);
    vector<string> getCollectionBy(int);
    vector<int> searchForVolumes(string);
    vector <string> consultActions(string);
    vector<int> modifActions();
    string reverseAction(int);
    
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
    modif = Record();
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
    modif = Record();
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


//---------------------------------------------------------------------
/*
Record& getRecord()

Method that returns a reference to the Record object modif stored in
the Collection object.
*/
Record& Collection::getRecord(){
    return modif;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Setters

/*
void setSortType(string type)

Depending on the received string, the variable sortType will change 
to either author or name.
*/
void Collection::setSortType(string type, bool initial){
    emptyBookshelves();
    if(initial){
        Action action = Action("Inicial loading of Volumes", modif.length()+1, "Initial", Volume(), "Initial loading of all stored Volumes.");
        modif.add(action);
    }
    if(type == "author"){
        sorting.sortBy(volumes, bookshelves, "author");
        sortType = author;
        Action action = Action("Sort Modification: By Author", modif.length()+1, "Sorting", Volume(), "The user sorted the collection by Author.");
        modif.add(action);
    }
    else{
        sorting.sortBy(volumes, bookshelves, "name");
        sortType = name;
        Action action = Action("Sort Modification: By Name", modif.length()+1, "Sorting", Volume(), "The user sorted the collection by Name.");
        modif.add(action);
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
    Action action = Action("Addition of Volume:"+volume_.getName() , modif.length()+1, "Adding", volume_, "Addition of the new Volume: "+volume_.getName()+" - Volume: "+to_string(volume_.getVolume()));
    modif.add(action);
    emptyBookshelves();
    if(sortType == author){
        sorting.sortBy(volumes, bookshelves, "author");
    }
    else{
        sorting.sortBy(volumes, bookshelves, "name");
    }
    return "The Volume has been added successfully!";
}

//---------------------------------------------------------------------
/*
void primitiveAddVolume(Volume volume_)

Method responsible for adding a new volume [volume_] to the volumes 
vector of the Collection without sorting again all the volumes.
*/

void Collection::primitiveAddVolume(Volume volume_){
    volumes.push_back(volume_);
};


//---------------------------------------------------------------------
/*
void addAction(Action)

Method responsible for adding a new Action [action_] to the modif 
Record of the Collection.
*/

void Collection::addAction(Action action_){
    modif.add(action_);
};


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

    Action action = Action("Elimination of the Volume: "+volumes[index_].getName(), modif.length()+1, "Eliminating", volumes[index_] , "Elimination of the manga Volume: "+volumes[index_].getName()+"  - Volume: "+to_string(volumes[index_].getVolume()));
    modif.add(action);

    //Erase the volume from the collection
    volumes.erase(volumes.begin()+index_);

    //Re-order the remaining manga volumess
    setSortType(to_string(sortType), false);
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


//---------------------------------------------------------------------
/*
vector<string> consultActions(string type)

Function responsible for returning a vector<string> that holds the
information of the Action objects contained in the Record linked list
that might be either all the Actions of all the elements in the list
or only those who are modifiable (in both normal and reverse order) 
depending on the parameter [type].
*/

vector<string> Collection::consultActions(string type){
    if(type == "normal"){
        return modif.toString("normal");
    }
    else if(type == "reverse"){
        return modif.toString("reverse");
    }
    else if(type == "normal_modif"){
        return modif.getModifiable("normal");
    }
    else{
        return modif.getModifiable("reverse");
    }  
};


//---------------------------------------------------------------------
/*
vector<int> modifActions()

Function responsible for returning a vector of all the ids of the Actions
that are modifiable based on the filters established on the Record 
function getModifiableInt().
*/

vector<int> Collection::modifActions(){
    return modif.getModifiableInt();  
};


//---------------------------------------------------------------------
/*
string reverseAction(int id)

Function responsible for reversing a specific action taken by the user 
whose algoritm depends on its type:
- Adding: 
    Obtains the index of the specific volume added to the collection 
    which has been stored in the Action object.
    Eliminates the volume from the volumes vector and its location
    in the bookshelfs.

- Eliminating:
    Adds the volume stored in the Action object into the collection.

Once the actions have been performed, a new Action is added to the Record
linked list, the reversed action is eliminated and the ids of the Record
are modified to follow a straight count from old to recent Actions.
*/

string Collection::reverseAction(int id){
    
    Action toReverse = modif.get(id);
    modif.remove(id);
    modif.correctId();

    //Reversing an Adding Action
    if(toReverse.getType() == "Adding"){
        int index = sorting.searchVolume(volumes, toReverse.getVolume());
        eraseVolume(index);
        return "Volume "+toReverse.getVolume().getName()+" has been eliminated from the collection.";
    }
    //Reversing an Eliminating Action
    else if(toReverse.getType() == "Eliminating"){
        addVolume(toReverse.getVolume());
        return "Volume "+toReverse.getVolume().getName()+" has been added from the collection.";
    }
    return "";
}


#endif