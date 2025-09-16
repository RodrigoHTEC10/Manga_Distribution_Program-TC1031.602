/*
Title: TextMemory.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: September 15th
Description: 
The class TextMemory() is responsible for reading and saving data from
the text file "record.txt" which stores the information of each manga 
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


using namespace std;

class TextMemory{
public:
    TextMemory();
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
//Function Declaration

/*
Collection read()

This method is responsible for reading the file "record.txt" and obtain
the information to fill an empty Collection everytime the program starts,
returning this filled collection afterwards.
In case the file does not exist or does not contain any Volume stored,
it will return an empty Collection ready to be filled.
*/
Collection TextMemory::read(){
    ifstream record;
    Collection collection = Collection();
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
                
                /*
                Example of storing volume line.
                name#volume$author!width*bookshelf%shelf(index_shelf)favorites\n
                */

                string name;
                string volumeString;
                string author;
                string widthString;
                string bookshelfString;
                string shelfString;
                string indexString;
                string favoriteString;

                int volume;
                float width;
                int bookshelf;
                int shelf;
                int index;
                bool favorite;

                getline(record, name, '#');
                getline(record, volumeString, '$');
                getline(record, author, '!');
                getline(record, widthString, '*');
                getline(record, bookshelfString, '%');
                getline(record, shelfString, '(');
                getline(record, indexString, ')');
                getline(record, favoriteString);


                volume = stoi(volumeString);
                width = stof(widthString);
                bookshelf = stoi(bookshelfString);
                shelf = stoi(shelfString);
                index = stoi(indexString);
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
                Volume newVolume = Volume(name, volume, author, width, favorite);
                newVolume.setLocation(bookshelf, shelf, index);
                collection.addVolume(newVolume);
            }
        }
        record.close();
    }
    else{
        ofstream record("record.txt");
    }
    return collection;
};

//---------------------------------------------------------------------
/*
void write(Collection collection)

Method responsible for reading the actual volumes stored in the Collection
and save them into a txt file called "record.txt" which formar fits the 
reading mechanism of the function read() of the same class.
*/
void TextMemory::write(Collection collection_){
    ofstream record;
    record.open("record.txt");
    if(record.is_open()){}
    else{
         ofstream record("record.txt");
    }

    vector<Volume> volumes = collection_.getVolumes();
    if(volumes.size() > 0){
        /*
        Example of File Introduction: 
        INFO@52
        */
        record<<"INFO@"+ to_string(volumes.size())+"\n";
        
        for(int i = 0; i<volumes.size(); i++){

            /*Write the information of each volume of the collection.
            Example of storing volume line.
            name#volume$author!width*bookshelf%shelf(index_shelf)favorites\n
            */
            vector<int> location = volumes[i].getLocation();
            bool favorite = volumes[i].isFavorite();
            string favoriteText;
            if(favorite)
                favoriteText = "true";
            else
                favoriteText = "false";

            record<<volumes[i].getName()+"#"+to_string(volumes[i].getVolume())+"$"+volumes[i].getAuthor()+"!"+to_string(volumes[i].getWidth())+"*"+to_string(location[0])+"%"+to_string(location[1])+"("+to_string(location[2])+")"+favoriteText+"\n";
        }
    }
    record.close();
};

#endif