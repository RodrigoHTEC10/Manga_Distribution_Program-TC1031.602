/*
Title: SortSearch.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: September 15th
Description:
The Class SortSearch is responsible for sorting by name and author all
the volumes of the collection, as well as helping getting the range of
indexes that contain all mangas with the same name.
*/

#ifndef SORT_H_
#define SORT_H_

#include <iostream>
#include <string>
#include <vector>
#include "Collection.h"

using namespace std;

class Sort
{

private:
    // Private Functions
    void swap(vector<Volume>&, int, int);
    void checkSpace(Volume&, Volume&, vector<Bookshelf>&);
    void toString(vector<Volume>&);

public:
    //Public Functions
    Sort();
    void sortByName(vector<Volume>&, vector<Bookshelf>&);
    void sortByAuthor(vector<Volume>&, vector<Bookshelf>&);
    vector<int> searchVolumes(vector<Volume>&, string);

};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Constructors Declaration

/*
Sort() empty default constructor.
*/
Sort::Sort(){};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Private Functions Declaration

/*
void swap(vector<Volume> &source, int a, int b)
Method responsible for changing two element stored in a vector/array
[source] between their location [a & b] aimed from an auxiliar variable. 
*/
void Sort::swap(vector<Volume> &source, int a, int b){
    Volume aux = source[a];
    source[a] = source[b];
    source[b] = aux;

};

//---------------------------------------------------------------------
/*
void checkSpace(Volume& oldVolume, Volume& volume,
 vector<Bookshelf>& books)

Auxiliar method responsible for checking the avaliable space inside each shelf of
all bookshelfs [bookshelf] to add a new volume [volume] based on its 
width and the location of the last volume [oldVolume].
One the place its located the Volume is stored inside that shelf, and
its location its updated.
In case a bookshelf is full, the method can add new bookshelfs to 
continue the storage.
*/
void Sort::checkSpace(Volume& oldVolume, Volume& volume, vector<Bookshelf>& books){
    
    float width = volume.getWidth();
    int actualBook = books.size();
    int chosenShelf;
    int lastIndex;
    
    /*
    If there is no bookshelf, it created the first to obtain the avaliable
    bookshelf.
    */
    if(actualBook == 0){
        Bookshelf book = Bookshelf(1, 4, 100);
        books.push_back(book);
        actualBook++;
    }

    /*Obtention of the avaliable shelf based on the method 
    avaliableSpace(float width) of the Bookshelf class.*/
    int avaliableShelf = books[actualBook-1].avaliableSpace(width);

    //Obtention of the oldVolume location to compare.
    int oldVolumeShelf = oldVolume.getLocation()[1];


    /*Based on the location avaliable, and the location of the last
    volume stored, the new volume is placed either in the same shelf,
    the next shelf or a new bookshelf*/
    if(avaliableShelf < oldVolumeShelf){
        if(avaliableShelf == -1){
            chosenShelf = -1;
        }
        else{
            //Same shelf
            if(books[actualBook-1].avaliableSpace(oldVolumeShelf, volume.getWidth())){
                chosenShelf = oldVolumeShelf;
            }

            else{
                //New bookshelf
                if(oldVolumeShelf == books[actualBook-1].getMax()-1){
                    chosenShelf = -1;
                }

                //Next shelf
                else{
                    chosenShelf = oldVolumeShelf+1;
                }
            }
        }
    }
    //Next shelf
    else{
        chosenShelf = avaliableShelf; 
    }

    //Creation of a new bookshelf if required
    if(chosenShelf == -1){
        Bookshelf book = Bookshelf(actualBook, 4, 100);
        books.push_back(book);
        actualBook++;
        chosenShelf = books[actualBook-1].avaliableSpace(width);
    }
    
    /*Addition of the volume to the shelf and updated location*/
    lastIndex = books[actualBook-1].getShelf(chosenShelf).lastIndex();
    books[actualBook-1].addVolume(chosenShelf, volume, lastIndex);
    volume.setLocation(actualBook-1, chosenShelf, lastIndex);
};

//---------------------------------------------------------------------
/*
void toString(vector<Volume>& volumes)

Auxiliar method that prints the collection of Volumes entered as a 
parameter [volumes]
This method will not used in any of the submitted versions of the sproject.
*/
void Sort::toString(vector<Volume>& volumes){
    string text = "[";
    for(int i = 0; i<volumes.size(); i++){
        vector<int> location = volumes[i].getLocation();
        text += volumes[i].getName()+"  "+to_string(volumes[i].getVolume())+" \n";
        text += "Bookshelf "+to_string(location[0]) + " Shelf " + to_string(location[1]) + " Index " + to_string(location[2])+"\n";
    }
    text += " ]";
    cout<< text <<endl;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Public Functions Declaration

/*
Both of the following sorts used in this proyect are Selection Sorts 
chosen based on the following reason:
The order of the volumes in the collection is completely dependent only
on its name, or author (depending the function) and its volume's number;
however, its location inside the created Bookshelfs is dependent on the
fact that the previous volume was already placed in the bookshelf and it 
is ocuppying space.

Based on this fact, the selection sort algorithm with complexity O(n^2) 
has been chosen as ordering in a way that the first elements of the 
collection following alphabetical order are located and stored correctly,
the next element will jump over the previous but still use it location.
*/


/*
void sortByName(vector<Volume> &volumes, vector<Bookshelf> &books)

Method responsible for sorting the volumes of the collection in an 
alphabetical order (from A to Z) based on the name of the volume (key)
and the volume number.
Additionally, the location of each volume in order is updated with help
of the checkSpace() private function.
*/
void Sort::sortByName(vector<Volume> &volumes, vector<Bookshelf> &books){
    int size = volumes.size();
    string min;
    int minIndex;

    for(int i = 0; i<size; i++){
        volumes[i].setLocation(0,0,0);
        min = volumes[size-1].getName();
        minIndex = size-1;

        for(int j = i; j<size; j++){
            //Compare name
            if((min.compare(volumes[j].getName())) > 0){
                min = volumes[j].getName();
                minIndex = j;
            }
            //If the name is equal, order based on volume number
            else if((min.compare(volumes[j].getName())) == 0){
                if(volumes[minIndex].getVolume() >= volumes[j].getVolume()){
                    minIndex = j;
                }
            }
        }
        if(minIndex != i){
            swap(volumes, minIndex, i);
        }

        // Updating location with help of checkSpace()
        if(i == 0){
            //Location of the first volume of the collection
            Volume empty = Volume();
            checkSpace(empty, volumes[i], books);
        }
        else{
            //Locate volumes in order
            checkSpace(volumes[i-1], volumes[i], books);
        }
        
    }
};

//---------------------------------------------------------------------
/*
void sortByAuthor(vector<Volume> &volumes, vector<Bookshelf> &books)

Method responsible for sorting the volumes of the collection in an 
alphabetical order (from A to Z) based on the author of the volume (key)
and the volume number.
Additionally, the location of each volume in order is updated with help
of the checkSpace() private function.
*/
void Sort::sortByAuthor(vector<Volume> &volumes, vector<Bookshelf>& books){
    int size = volumes.size();
    Volume min;
    int minIndex;

    for(int i = 0; i<size; i++){
        volumes[i].setLocation(0,0,0);
        min = volumes[size-1];
        minIndex = size-1;

        for(int j = i; j<size; j++){
            //CCompare by the author
            if((min.getAuthor().compare(volumes[j].getAuthor())) > 0){
                min = volumes[j];
                minIndex = j;
            }
            /*If the author is the same, order based on the name of the 
            volume*/
            else if((min.getAuthor().compare(volumes[j].getAuthor())) == 0){
                
                if((min.getName().compare(volumes[j].getName())) > 0){
                    min = volumes[j];
                    minIndex = j; 
                }
                /*If the author and the name are the same, order based on
                the volume number in ascending order*/
                else if((min.getName().compare(volumes[j].getName())) == 0){
                    if(volumes[minIndex].getVolume() >= volumes[j].getVolume()){
                        min = volumes[j];
                        minIndex = j;
                    }
                }
            }
        }
        if(minIndex != i){
            swap(volumes, minIndex, i);
        }

        // Updating location with help of checkSpace()
        if(i == 0){
            Volume empty = Volume();
            checkSpace(empty, volumes[i], books);
        }
        else{
            checkSpace(volumes[i-1], volumes[i], books);
        }
        
    }
};

//---------------------------------------------------------------------
/*
vector<int> searchVolumes(vector<Volume>& volumes, string name)

Method that returns a range of indexes in the Volume collection 
[volumes] that contain all volumes of the name [name]. 
This method is used for the search mechanism of the project.
*/
vector<int> Sort::searchVolumes(vector<Volume>& volumes, string name){
    vector<int> indexes = {-1,-1};
    for(int i = 0; i<volumes.size()-1; i++){
        if((volumes[i].getName().compare(name) != 0) && (volumes[i+1].getName().compare(name) == 0)){
            indexes[0] = i+1;
        }
        
        if((volumes[i].getName().compare(name) == 0) && (volumes[i+1].getName().compare(name) != 0)){
            indexes[1] = i;
        }
    }
    return indexes;
};

#endif