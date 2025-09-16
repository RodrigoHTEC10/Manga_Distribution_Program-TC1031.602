/*
Title: main.cpp
Author: Rodrigo Alejandro Hurtado Cortes 
Date: September 15th
Description:
The present file holds the start, use and user interactions of all the
functions and objects previously created in the complementary classes.
*/

#include <iostream>
#include <string>
#include <vector>
#include "Collection.h"
#include "TextMemory.h"

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Auxiliar Functions

/*
int mainMenu()

Returns an integer that correspond to one of the Main Menu options
chosen by the User.
The decision is only accepted if it is within the avaliable
options.
*/
int mainMenu(){
    int decision;
    cout<<""<<endl;
    cout<< "Main Menu: " <<endl;
    cout<< "1. Add a new Manga Volume." <<endl;
    cout<< "2. Search for a Manga Volume." <<endl;
    cout<< "3. Erase a Manga Volume." <<endl;
    cout<< "4. Sort actual collection." <<endl;
    cout<< "5. Show collection." <<endl;
    cout<< "6. Save and Exit" <<endl;
    cout<< "Enter your option: ";
    cin>>decision;
    cout<<""<<endl;
    if(decision > 0 && decision <= 6)
        return decision;
    return -1;
};

//---------------------------------------------------------------------
/*
int SortMenu()

Returns an integer that correspond to one of the Sort Menu options
chosen by the User.
The decision is only accepted if it is within the avaliable options.
*/
int sortMenu(){
    int decision;
    cout<<""<<endl;
    cout<< "1. Sort by Name." <<endl;
    cout<< "2. Sort by Author." <<endl;
    cout<< "3. Back to Main Menu." <<endl;
    cout<< "Enter your option: ";
    cin>>decision;
    cout<<""<<endl;
    if(decision > 0 && decision <= 3)
        return decision;
    return -1;
};

//---------------------------------------------------------------------
/*
int showMenu()

Returns an integer that correspond to one of the Show Menu options
chosen by the User.
The decision is only accepted if it is within the avaliable options.
*/
int showMenu(){
    int decision;
    cout<<""<<endl;
    cout<< "1. Show whole collection." <<endl;
    cout<< "2. Show one bookshelf" <<endl;
    cout<< "3. Show a specific shelf." <<endl;
    cout<< "4. Show all collection names." <<endl;
    cout<< "5. Show all collection authors." <<endl;
    cout<< "6. Show all collection favorites." <<endl;
    cout<< "7. Back to Main Menu." <<endl;
    cout<< "Enter your option: ";
    cin>>decision;
    cout<<""<<endl;
    if(decision > 0 && decision <= 7)
        return decision;
    return -1;
};

//---------------------------------------------------------------------
/*
void printCollection(vector<string> collection)

Auxiliar function responsible for printing all the elements of the 
vector of strings entered as a parameter.
*/
void printCollection(vector<string> collection){
    cout<<"Collection: " <<endl;
    for(int i = 0;  i<collection.size(); i++){
        cout<<"    "<<i+1<<"."<<collection[i]<<endl;
    }
    cout<<""<<endl;
}

//---------------------------------------------------------------------
/*
int withinRange(int min, int max, string object)

Return an integer that is within the min and max entered in the 
parameters. This auxiliar method is used to get a decision based of 
multiple options within a limited range.
*/
int withinRange(int min, int max, string object){
    bool inRange = false;
    int decision;
    while (!inRange){                    
        cin>>decision;
        cout<<""<<endl;
        if(decision>=min && decision<=max){
            inRange = true;
            return decision;
        }
        else{
            cout<<"Enter a "<< object <<" number within the allowed range.\n Enter the "<<object<<" number:"<<endl;
        }   
    }
    return decision;
}

//---------------------------------------------------------------------
/*
int searchVolume(Collection collectionName)

Returns an integer that represents the index in the volumes of the 
Collection entered as a parameter [collectionName] that has been chosen
by the user based on the options given.
*/
int searchVolume(Collection collectionName){
    int  chosenIndex;

    //Get all the names of volumes stored in the collection
    vector<string> names = collectionName.getCollectionBy(0);
    for(int i = 0; i<names.size(); i++){
        cout<<i+1<<". "<<names[i]<<endl;
    }
    int decision = withinRange(1,names.size(),"Volume's Name");
    string name = names[decision-1];
    
    /*Based on the chosen name, the range of its volumes is searched 
    through the collection*/
    vector<int> avaliableVol = collectionName.searchForVolumes(name);

    int start = avaliableVol[0];
    int end = avaliableVol[1];
    if(start==-1 || end==-1){
        if(start==-1){
            start = 0;
        }
        else{
            end = collectionName.getVolumes().size()-1;
        }
    }
    
    //The named collection has more than one volume.
    if(start != end){
        int countVolume = 0;
        for(int j = start; j<=end; j++){
            cout<<countVolume+1<<". Volume No. "<<collectionName.getVolumes()[j].getVolume()<<endl;
            countVolume++;
        }
        int volume = withinRange(1,end-start+1,"Volume's Volume");

        chosenIndex = start+(volume-1);
    }
    //There is only one volume with that name
    else{
        chosenIndex = start;
    }
    return chosenIndex;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Main Function

/*
Function responsible for starting and running the program, interacting
with the user and showing results and options in the console.

The following sections are divided based on the given options of the 
previously shown menus.
*/
int main()
{
    cout<< "--- Welcome to the Manga Control ---" <<endl;

    //Reading of the file.
    TextMemory memoria = TextMemory();
    Collection general = memoria.read();

    //Start of the Main Menu cycle.
    bool finish = false;
    while(!finish){
        switch (mainMenu()){
            /**********************************************************/
            //1. Add a new Manga Volume.
            case 1:{
            
                string name;
                int number;
                string author;
                float width;
                int decision;
                bool favorite;

                cout<<"Please enter your volume's name: "<<endl;
                cin.ignore();
                getline(cin, name);
                                
                cout<<"Please enter your volume's number: "<<endl;
                cin>>number;

                cout<<"Please enter your volume's author: "<<endl;
                cin.ignore();
                getline(cin, author);

                cout<<"Please enter your volume's width (cm): "<<endl;
                cin>>width;

                cout<<"Is this volume a favorite?\n 1. Yes\n 2. No\n Enter your numeric answer: "<<endl;
                cin>>decision;
                
                if(decision == 1){
                    favorite = true;
                }
                else{
                    favorite = false;
                }

                Volume newVolume = Volume(name, number, author, width, favorite);
                cout<<general.addVolume(newVolume)<<endl;
            }break;
            
            /**********************************************************/
            //2. Search for a Manga Volume.
            case 2:{
                int chosenIndex = searchVolume(general);
                cout<<general.getVolumes()[chosenIndex].getInfo()<<endl;
            }break;

            /**********************************************************/
            //3. Erase a Manga Volume.
            case 3:{
                cout<<"To be able to eliminate a Volume you need to find it first: \n "<<endl;
                int chosenIndex = searchVolume(general);
                cout<<general.eraseVolume(chosenIndex)<<endl;
            }break;            
            /**********************************************************/
            //4. Sort actual collection.
            case 4:{
                switch(sortMenu()){
                    //1. Sort by Name.
                    case 1:{
                        general.setSortType("name");
                        cout<<"Collection has been sorted Alphabetically by Name."<<endl;
                    }break;

                    //2. Sort by Author
                    case 2:{
                        general.setSortType("author");
                        cout<<"Collection has been sorted Alphabetically by Author."<<endl;
                    }break;

                    //3. Back to Main Menu
                    case 3:{
                        cout<<"Going back to Main Menu..."<<endl;
                    }break;

                    default:{
                        cout<<"Not avaliable option.\nGoing back to Main Menu...\n"<<endl;
                    }break;
                }
            
            }break;
            

            /**********************************************************/
            //5. Show collection.
            case 5:{
                switch (showMenu()){
                    //1. Show whole collection.
                    case 1:{
                        printCollection(general.consultCollection());
                    }break;
                    
                    //2. Show collection stored in one bookshelf
                    case 2:{
                        cout<<"Which one of the following bookshelfs you would like to check: " <<endl;
                        vector<Bookshelf> bookshelves = general.getBookshelfs();
                        cout<<"Enter a bookshelf between 1 - "<<bookshelves.size()<<": \n"<<endl;
                        
                        int decision = withinRange(1, bookshelves.size(), "Bookshelf");

                        printCollection(general.consultBookshelf(decision-1));   
                    }break;

                    //3. Show collection stored in a specific shelf.
                    case 3:{
                    
                        //Getting the Bookshelf Number
                        cout<<"Which one of the following bookshelfs you would like to check: " <<endl;
                        vector<Bookshelf> bookshelves = general.getBookshelfs();
                        cout<<"Enter a bookshelf between 1 - "<<bookshelves.size()<<": \n"<<endl;
                        
                        int decisionBook = withinRange(1, bookshelves.size(), "Bookshelf");

                        //Getting the shelf number
                        cout<<"Which one of the following shelfs from bookshelf No. "<< decisionBook <<" you would like to check: " <<endl;
                        cout<<"Enter a shelf between 1 - "<<bookshelves[decisionBook-1].getMax()<<" : \n"<<endl;
                        bool inRange = false;
                        
                        int decisionShelf = withinRange(1, bookshelves[decisionBook-1].getMax(), "Shelf");
                        printCollection(general.consultsShelf(decisionBook-1, decisionShelf-1));

                    }break;

                    //4. Show all collection names.
                    case 4:{
                        printCollection(general.getCollectionBy(0));
                    }break;

                    //5. Show all collection authors.
                    case 5:{
                        printCollection(general.getCollectionBy(1));
                    }break;

                    //6. Show all collection favorites.
                    case 6:{
                        printCollection(general.getCollectionBy(2));
                    }break;

                    //7. Back to Main Menu
                    case 7:{
                        cout<<"Going back to Main Menu..."<<endl; 
                    }break;

                    default:{
                        cout<<"Not avaliable option.\nGoing back to Main Menu...\n"<<endl;                        
                    }break;
                }        
            }break;
            
            /**********************************************************/
            //6. Save and Exit
            case 6:{
                memoria.write(general);
                cout<<"Data saved.\n Thank you for using the program."<<endl;
                finish = true;
            }break;

            /**********************************************************/
            default:{
                cout<<"Not avaliable option. Choose again."<<endl;
            }break;
        }
    }    
}