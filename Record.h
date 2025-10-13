/*
Title: Record.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: October 12th
Description: 
The present file includes the Element and Record class, where the 
Record is a simple linked list of Elements which are added in a 
specific order.
*/

#ifndef RECORD_H_
#define RECORD_H_

#include <iostream>
#include <string>
#include <vector>
#include "Volume.h"
#include "Action.h"

using namespace std;

class Record;
class ListIterator;
/*
=====================================================================
CLASS ELEMENT
=====================================================================
Description:
Class that contains the fundamental object Element of the simple linked
list Record. This object is formed of an Action and the pointer to the 
next Element.

As the constructors and variables are declared as private, only the
friend class Record can access and make use of these. This is a safety
measure to keep exclusive the creation of elements of the linked list. 
*/
class Element
{
    private:
        //Private Instance Variables
        Action action;
        Element* next;

        //Constructors
        Element();
        Element(Action);
        Element(Action, Element*);
    
        //Friend Class declaration
        friend class Record;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Element()

Default constructor of the Element object which points the pointer next
to null and stores an empty Action object.
*/
Element::Element(): action(Action()), next(0) {};

//---------------------------------------------------------------------
/*
Element(Action act_)

Constructor with parameters that stored the act_ Action object into with
its pointer next pointing to null.
*/
Element::Element(Action act_): action(act_){};

//---------------------------------------------------------------------
/*
Element(Action act_, Element& next_)

Constructor with parameters that stored the act_ Action object into with
its pointer next pointing to next_.
*/
Element::Element(Action act_, Element* next_): action(act_), next(next_){};




/*
=====================================================================
CLASS RECORD
=====================================================================
Description:
Class that creates, modifies and acess linked lists made out of Element
objects. It is composed of the head pointer and a size to keep record 
of the Elements registered in the list.

Characteristics of the Record:
- It is a simple linked list with only one pointer per element and one 
  head pointer.
- The new elements are added always at the head of the list as is priority
  to keep the most recent actions taken by the user first.
- Actions like Adding and Eliminating are the only ones that can be
  reversed.
- A reversed Action changes the status "reversed" inside the Action 
  stored in the Element, which makes it unavailable to be reversed
  once more.

Data Structure Usage Justification: Simple Linked List 

- Time Complexity 
    - Acess O(n) - might reduce
    - Search O(n) - might reduce
    - Insertion O(1)
    - Deletion O(1)

- Space Complexity O(n)

The application of a simple linked list modified to keep all elements in 
specific execution order (always adding the new element at the front)
relies on its use on the program: to keep a record of the actions
performed by the User that might be available to reverse.

This structure allows to add easily a new element, making it as big as
needed if many actions are taken during the current session, only 
depending on its pointers to orient itself to the next element.

In difference to a Stack which have the same order property, the simple
linked list allows me to access and get previous elements, not only
the last one entered, which allows to modify an action that might not
be necessarily the last one performed, and do not lose data or having the
necessity to create a second stack to store information while consulting 
other.

Additionally, thanks to the order implemented, the more recent the action
to be reversed is, the faster the linked list finds it, as it starts from
recent to past, which might even reduce search and access average time 
complexity.

Note: 
If an action was taken in a different session, this can not be accessed 
as each Record is created everytime the program is started. 
In this way the stored information of eliminated manga Volumes is not 
kept for the next session occuping memory space.
*/
class Record{
    private:
        //Private Instance Variables
        Element* head;
        int size;

    public:
        //Constructor
        Record();

        //Public Functions
        void add(Action);
        int length();
        bool empty();
        void remove(int);
        vector<string> toString();
        vector<string> getModifiable();
        vector<int> getModifiableInt();
        Action get(int);
        int getFirst();
        void reverse(int);
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Record()

Default constructor of the object Record.
*/
Record::Record(): head(0), size(0) {};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Functions Declaration

/*
void add(Action act_)

Function that creates a new Element object from the Action [act_] entered
as a parameter and adds it to the list, always as the first element.
*/
void Record::add(Action act_){
    Element *newAction;
    
    if(empty()){
        //Adding the first element of the list.
        newAction = new Element(act_,0);
        head = newAction;
        size++;
    }
    else{
        //Adding an additional element to the list.
        newAction = new Element(act_,0);
        newAction->next = head;
        head = newAction;
        size++;
    }
};

//---------------------------------------------------------------------
/*
int length()

Function responsible for returning the size of the list (number of 
Elements linked to each other).
*/
int Record::length(){
    return size;
};

//---------------------------------------------------------------------
/*
bool empty()

Function responsible for returning a boolean that answers if the list
is empty as its head is pointing to null.
*/
bool Record::empty(){
    return (head==0);
};

//---------------------------------------------------------------------
/*
void remove(int id_)

Function responsible for eliminating the Element object whose Action's
ID is equal to the id_ from the linked list Record, making the reconnection
of pointers necessary to keep the flow of Elements.

Even though this function has not been used in the implementation of the
Record linked list, it will be kept as an available resource to be used.
*/
void Record::remove(int id_){
    if(!empty()){
        Element* ptr, *borrar;
        ptr = head;

        /*Eliminating the first element if its Action's id matches the 
        parameter id_.*/
        if(ptr->action.getID() == id_){
            head = ptr->next;
            ptr->next = 0;
            delete ptr;
        }
        else{
            /*Eliminating an element whose Action's id matches the
            parameter id_*/
            while(ptr->next!=0){
                if(ptr->next->action.getID() == id_){
                    borrar = ptr->next;
                    ptr->next = borrar->next;
                    borrar->next = 0;
                    delete borrar;
                }
                else{
                    ptr= ptr->next;
                }
            }
        }
    }
};


//---------------------------------------------------------------------
/*
Action get(int id_)

Function responsible for returning the Action object of the Element whose 
Action's ID matches the parameter id_; otherwise, returining an empty
Action object.
*/
Action Record::get(int id_){
    if(!empty()){
        Element* ptr;
        ptr = head;

        while(ptr!=0){
            if(ptr->action.getID() == id_){
                return ptr->action;
            }
            else{
                ptr= ptr->next;
            }
        }
    }
    return Action();
};

//---------------------------------------------------------------------
/*
vector<string> toString()

Function responsible for returning a vector<string> filled with the
information of the Action's of each Element within the Record linked
list.
*/
vector<string> Record::toString(){
    Element* ptr;
    ptr = head;
    vector<string> text;

    if(!empty()){
        while(ptr != 0){
            text.push_back(ptr->action.toString());
            ptr = ptr->next;
        }
    }
    return text;
};

//---------------------------------------------------------------------
/*
vector<string> getModifiable()

Function responsible for returning a vector<string> filled with the
information of the Action's of all Elements within the Record linked
list whose type is either "Adding" or "Eliminating" and reversed 
conditional equals false.
*/
vector<string> Record::getModifiable(){
    Element* ptr;
    ptr = head;
    vector<string> text;

    if(!empty()){
        while(ptr != 0){
            string type = ptr->action.getType();
            if((type == "Adding" || type == "Eliminating") && (ptr->action.hasBeenReversed() == false)){
                text.push_back(ptr->action.toString());
            }
            ptr = ptr->next;
        }
    }
    return text;
};


//---------------------------------------------------------------------
/*
vector<int> getModifiableInt()

Function responsible for returning a vector<int> filled with the ids of 
the Action's of all Elements within the Record linked list whose type 
is either "Adding" or "Eliminating" and reversed conditional equals 
false.
*/
vector<int> Record::getModifiableInt(){
    Element* ptr;
    ptr = head;
    vector<int> ids;

    if(!empty()){
        while(ptr != 0){
            string type = ptr->action.getType();
            if((type == "Adding" || type == "Eliminating") && (ptr->action.hasBeenReversed() == false)){
                ids.push_back(ptr->action.getID());
            }
            ptr = ptr->next;
        }
    }
    return ids;
};


//---------------------------------------------------------------------
/*
int getFirst()

Function responsible for returning the ID of the first element of the
linked list Record.

Even though this function has not been used in the implementation of the
Record linked list, it was used for testing.
*/

int Record::getFirst(){
    if(!empty()){
        return head->action.getID();
    }
    else
        return 0;
}

//---------------------------------------------------------------------
/*
void reverse(int id_)

Function responsible for changing the status of the Action whose ID 
matches the parameter id_ within the Record linked list.
*/

void Record::reverse(int id_){
    if(!empty()){
        Element* ptr;
        ptr = head;

        while(ptr!=0){
            if(ptr->action.getID() == id_){
                ptr->action.reverse();
                return;
            }
            else{
                ptr= ptr->next;
            }
        }
    }
    return;
}


#endif