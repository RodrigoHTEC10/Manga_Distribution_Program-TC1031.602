/*
Title: TextMemory.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: November 12th
Description: 
The class TextMemory() is responsible for reading and saving data from
the text file "volumes.txt" which stores the information of each manga 
volume that forms part of the collection.
*/

#ifndef TEXTMEMORY_H_
#define TEXTMEMORY_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream> 

#include "Volume.h"
#include "Collection.h"
#include "Record.h"


using namespace std;

class TextMemory{
private:
    //Private methods
    Volume readVolume(ifstream&);
    string writeVolume(Volume&);
    Action readAction(ifstream&);
    string writeAction(Action&);

public:
    //Constructor
    TextMemory();
    //Public Methods
    Collection read();
    void write(Collection);
    

};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
TextMemory() empty constructor.
*/
TextMemory::TextMemory(){

};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Private Methods Declaration

/*
Volume readVolume(ifstream);

Method responsible for retuning a Volume objet after collecting its 
variables from a .txt document entered as reference [record] and build
it with its constructor with parameters.

Precondition: The ifstream file must be opened and the reading cursor
must be at the start of the name of the volume (to keep a right count
of the lines to obtain).

Postcondition: The reading cursor in the ifstream file is at the next
line after collecting all Volume variables.
*/
Volume TextMemory::readVolume(ifstream& record){
    string name;
    string volumeString;
    string author;
    string widthString;
    string bookshelfString;
    string shelfString;
    string indexString;
    string favoriteString;

    bool favorite;

    getline(record, name);
    getline(record, volumeString, '$');
    getline(record, author);
    getline(record, widthString, '*');
    getline(record, bookshelfString, '%');
    getline(record, shelfString, '(');
    getline(record, indexString, ')');
    getline(record, favoriteString);

    if(favoriteString == "true"){
        favorite = true;
    }
    else{
        favorite = false;
    }

    /*
    Reference to the original constructor to create a volume
    with the obtained data.

    Volume::Volume(string name_, int volume_, string author_,
    float width_, bool favorite_){
    */
    Volume newVolume = Volume(name, stoi(volumeString), author, stof(widthString), favorite);
    newVolume.setLocation(stoi(bookshelfString), stoi(shelfString), stoi(indexString));
    return newVolume;
};


//---------------------------------------------------------------------
/*
string writeVolume(Volume& volume)

Method responsible for returning the variables of the Volume object 
[volume] as a string in the specific reading format that follows the
method readVolume().
*/

string TextMemory::writeVolume(Volume& volume){
    vector<int> location = volume.getLocation();
    bool favorite = volume.isFavorite();
    string favoriteText;
    if(favorite)
        favoriteText = "true";
    else
        favoriteText = "false";

    /*Write the information of each volume of the collection.
    Example of storing volume line.
    name
    volume$author
    width*bookshelf%shelf(index_shelf)favorites\n
    */

    return volume.getName()+"\n"+to_string(volume.getVolume())+"$"+volume.getAuthor()+"\n"+to_string(volume.getWidth())+"*"+to_string(location[0])+"%"+to_string(location[1])+"("+to_string(location[2])+")"+favoriteText+"\n";
};


//---------------------------------------------------------------------
/*
Action readAction(ifstream&);

Method responsible for retuning an Action objet after collecting its 
variables from a .txt document entered as reference [record] and build
it with its constructor with parameters.

Precondition: The ifstream file must be opened and the reading cursor
must be at the start of the name of the Action (to keep a right count
of the lines to obtain).

Postcondition: The reading cursor in the ifstream file is at the next
line after collecting all Action variables.
*/

Action TextMemory::readAction(ifstream& record){
    Volume storedVolume;
    
    string name;
    string idString;
    string type;
    string description;
    string time;

    int id;

    getline(record, name);
    getline(record, idString, '$');
    getline(record, type);
    storedVolume = readVolume(record);
    getline(record, description);
    getline(record, time);

    return Action(name, stoi(idString), type, storedVolume, description, time);
};


//---------------------------------------------------------------------
/*
string writeAction(Action&);

Method responsible for returning the variables of the Action object 
[action] as a string in the specific reading format that follows the
method readAction().
*/

string TextMemory::writeAction(Action& action){
    Volume volumen = action.getVolume();
    /*
    Example of storing action line.
    name
    id$type
    name
    volume$author
    width*bookshelf%shelf(index_shelf)favorites\n
    description
    timeString
    */
    
    return action.getName()+"\n"+to_string(action.getID())+"$"+action.getType()+"\n"+writeVolume(volumen)+action.getDescription()+"\n"+action.getTime()+"\n";
};



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Public Methods Declaration

/*
Collection read()

This method is responsible for reading the files "volumes.txt" and 
"record.txt" and obtain the information to fill both the volumes of
an empty collection and the actions done in previous saved sessions.

In case the file(s) does not exist or does not contain any information
stored,it will return an empty Collection or an empty Record ready to be
filled.
*/
Collection TextMemory::read(){
    ifstream record;
    Collection collection = Collection();


        //Llamada a la funcion de lectura del record.
    record.open("record.txt");

    /*Check if the file is open after opening it. In case it is open
    it will read it otherwise it will create a new one and return an
    empty Collection*/
    if(record.is_open()){
    
        string info;
        getline(record, info,'@');

        if( info == "INFO"){

            //Obtain how many volumes are stored.
            string limitString;
            getline(record, limitString);
            int limit = stoi(limitString);

            for(int i = 0; i<limit; i++){
                collection.addAction(readAction(record));
            }
        }
        record.close();
    }
    else{
        ofstream record("record.txt");
    }


    record.open("volumes.txt");

    /*Check if the file is open after opening it. In case it is open
    it will read it otherwise it will create a new one and return an
    empty Collection*/
    if(record.is_open()){
    
        string info;
        getline(record, info,'@');

        if( info == "INFO"){

            //Obtain how many volumes are stored.
            string limitString;
            getline(record, limitString);
            int limit = stoi(limitString);

            for(int i = 0; i<limit; i++){
                Volume newVolume = readVolume(record);
                collection.primitiveAddVolume(newVolume);
            }
        }
        record.close();
        collection.setSortType("name", true);
    }
    else{
        ofstream record("volumes.txt");
    }

    return collection;
};



//---------------------------------------------------------------------
/*
void write(Collection collection)

Method responsible for reading the actual volumes stored in the Collection
and Actions stored in the Collection's Record and save them into their 
respective txt files called "volumes.txt" and "record.txt" respectively
in a format that fits the reading mechanism of the methods readVolume()
and readAction().
*/

void TextMemory::write(Collection collection_){
    ofstream record;
    //Writing Volumes - volumes.txt

    record.open("volumes.txt");
    if(record.is_open()){}
    else{
        ofstream record("volumes.txt");
    }

    vector<Volume> volumes = collection_.getVolumes();
    if(volumes.size() > 0){
        /*
        Example of File Introduction: 
        INFO@52
        */
        record<<"INFO@"+ to_string(volumes.size())+"\n";
        
        for(int i = 0; i<volumes.size(); i++){            
            record<<writeVolume(volumes[i]);
        }
    }
    record.close();


    //Writing Actions - record.txt

    record.open("record.txt");
    if(record.is_open()){}
    else{
        ofstream record("record.txt");
    }

    //Obtention of all the records information
    Record modif = collection_.getRecord();
    int modifSize = modif.length();

    if(modifSize > 0){
        /*
        Example of File Introduction: 
        INFO@52
        */
        record<<"INFO@"+ to_string(modifSize)+"\n";

        for(int i = 1; i<=modifSize; i++){
        Action action = modif.get(i);
        record<<writeAction(action);
        }
    }

    //Writing of the elements in record.txt
    record.close();

};

#endif