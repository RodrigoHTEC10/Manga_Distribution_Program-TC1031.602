/*
Title: Record.h
Author: Rodrigo Alejandro Hurtado Cortes 
Date: October 18th
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
Class that contains the fundamental object Element of the double linked
list Record. This object is formed of an Action and two pointers, next
and previous.

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
        Element* previous;

        //Constructors
        Element();
        Element(Action);
        Element(Action, Element*, Element*);
    
        //Friend Class declaration
        friend class Record;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Element()

Default constructor of the Element object which points the pointers next
and previous to null and stores an empty Action object.
*/
Element::Element(): action(Action()), next(0), previous(0) {};

//---------------------------------------------------------------------
/*
Element(Action act_)

Constructor with parameters that stored the act_ Action object into with
its pointers next and previous pointing to null.
*/
Element::Element(Action act_): action(act_), next(0), previous(0){};

//---------------------------------------------------------------------
/*
Element(Action act_, Element& next_,  Element* prev_)

Constructor with parameters that stores the act_ Action object into 
the PIV action, and sets the parameters next and previous to the
pointers given by the parameters next_ and prev_ respectively.
*/
Element::Element(Action act_, Element* next_, Element* prev_): action(act_), next(next_), previous(prev_) {};




/*
=====================================================================
CLASS RECORD
=====================================================================
Description:
Class that creates, modifies and acess a double linked list made out
of Element objects. It is composed of the head and tail pointers and
a size to keep record of the Elements registered in the list.

Characteristics of the Record:
- It is a double linked list with two pointers per element, one head
    and one tail pointer.
-   The new elements are added always at the head of the list as is priority
    to keep the most recent actions taken by the user first.
- Actions like Adding and Eliminating are the only ones that can be
    reversed.
- A reversed Action is eliminated inmediately from the list.

Data Structure Usage Justification: Double Linked List 

- Time Complexity 
    - Access O(n/2)
    - Search O(n) or O(n/2) if its greater or smaller than the middle
    known element
    - Insertion O(1)
    - Deletion O(1)

- Space Complexity O(n)

The application of a double linked list modified to keep all elements in 
specific execution order (always adding the new element at the front)
relies on its use on the program: to keep a record of the actions
performed by the User that might be available to reverse.

This structure allows to add easily a new element, making it as big as
needed if many actions are taken during the current session, only 
depending on its pointers to orient itself to the next element.

In difference to a Stack which have the same order property, the double
linked list allows me to access and get previous elements, not only
the last one entered, which allows to modify an action that might not
be necessarily the last one performed, and do not lose data or having the
necessity to create a second stack to store information while consulting 
other; additionally lowering search and access times by being able to
traverse it from start to end or viceversa.

Additionally, thanks to the order implemented, the more recent the action
to be reversed is, the faster the linked list finds it, as it starts from
recent to past. On the contrary, if the action was taken a long time ago,
by being able to access the list from opposite order by starting a search
or access from the tail, the time complexity is considerably low as well.

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
        Element* tail;
        int size;

    public:
        //Constructor
        Record();

        //Public Functions
        void add(Action);
        int length();
        bool empty();
        void remove(int);
        vector<string> toString(string);
        vector<string> getModifiable(string);
        vector<int> getModifiableInt();
        Action get(int);
        int getFirst();
        void correctId();
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Record()

Default constructor of the object Record.
*/
Record::Record(): head(0), tail(0), size(0) {};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Functions Declaration

/*
void add(Action act_)

Function responsible for adding a new Element to the double list Record
in this process, there is a special care for the location of the head
and tail pointers.

If the first Element is added, both the head and tail pointer point to
this element.

If an additional Element is added, then the head pointer is modified,
the connection between Elements is established and the tail stays with
the previous first element due to the addition order. 
*/
void Record::add(Action act_){
    Element *newAction;
    
    if(empty()){
        //Adding the first element of the list.
        newAction = new Element(act_,0,0);
        head = newAction;
        tail = newAction;
        size++;
    }
    else{
        //Adding an additional element to the list.
        newAction = new Element(act_);
        newAction->next = head;
        newAction->next->previous = newAction;
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
is empty as its head and tail are pointing to null.
*/
bool Record::empty(){
    return (head==0 && tail == 0);
};

//---------------------------------------------------------------------
/*
void remove(int id_)

Function responsible for eliminating the Element object whose Action's
ID is equal to the id_ from the linked list Record, making the reconnection
of pointers necessary to keep the flow of Elements.
*/
void Record::remove(int id_){
    if(!empty()){
        Element* ptr, *borrar;
        ptr = head;

        /*Eliminating the first element if its Action's id matches the 
        parameter id_.*/
        if(ptr->action.getID() == id_){
            borrar = head;
            head = ptr->next;
            head->previous = 0;

            borrar->previous = 0;
            borrar->next = 0;
            delete borrar;
            size--;
            return;
        }
        /*Eliminating the last element if its Action's id matches the 
        parameter id_.*/
        else if(tail->action.getID() == id_){
            borrar = tail;
            tail = tail->previous;
            tail->next = 0;

            borrar->next = 0;
            borrar->previous = 0;
            delete borrar;
            size--;
            return;
        }
        /*Eliminating an intermediate eleent of the Record.*/
        else{
            /*If the id_ is creater than the half of the Actions taken, it
            is located within the first half of the Double List.*/
            if(id_ > (size/2)){
                while(ptr->next!=0){
                    if(ptr->next->action.getID() == id_){
                        borrar = ptr->next;

                        ptr->next = borrar->next;
                        ptr->next->previous = ptr;

                        borrar->previous = 0;
                        borrar->next = 0;
                        delete borrar;
                        size--;
                        return;
                    }
                    else{
                        ptr= ptr->next;
                    }
                }
            }
            /*Id the id_ is less than the half of the Actions taken, it is
            located within the second half of the Double List.*/
            else{
                ptr = tail;
                while(ptr->previous!=0){
                    if(ptr->previous->action.getID() == id_){
                        borrar = ptr->previous;

                        ptr->previous = borrar->previous;
                        borrar->previous->next = ptr;

                        borrar->previous = 0;
                        borrar->next = 0;
                        delete borrar;
                        size--;
                        return;
                    }
                    else{
                        ptr = ptr->previous;
                    }
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
        

        /*If the id_ is creater than the half of the Actions taken, it
        is located within the first half of the Double List.*/
        if(id_ > (size/2)){
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
        /*Id the id_ is less than the half of the Actions taken, it is
        located within the second half of the Double List.*/
        else{
            ptr = tail;
            while(ptr!=0){
                if(ptr->action.getID() == id_){
                    return ptr->action;
                }
                else{
                    ptr= ptr->previous;
                }
            }
        }

        
    }
    return Action();
};

//---------------------------------------------------------------------
/*
vector<string> toString(string aux)

Function responsible for returning a vector<string> filled with the
information of the Action's of each Element within the Record linked
list in the specified order by the string aux.
*/
vector<string> Record::toString(string aux){
    Element* ptr;
    vector<string> text;

    if(aux == "reverse"){
        ptr = tail;
        if(!empty()){
            while(ptr != 0){
                text.push_back(ptr->action.toString());
                ptr = ptr->previous;
            }
        }
    }
    else{
        ptr = head;
        if(!empty()){
            while(ptr != 0){
                text.push_back(ptr->action.toString());
                ptr = ptr->next;
            }
        }
    }
    return text;
};




//---------------------------------------------------------------------
/*
vector<string> getModifiable(string aux)

Function responsible for returning a vector<string> filled with the
information of the Action's of all Elements within the Record linked
list whose type is either "Adding" or "Eliminating", in the order
specified by the string aux.
*/
vector<string> Record::getModifiable(string aux){
    Element* ptr;
    
    vector<string> text;

    if(!empty()){
        if(aux == "normal"){
            ptr = head;
            while(ptr != 0){
                string type = ptr->action.getType();
                if(type == "Adding" || type == "Eliminating"){
                    text.push_back(ptr->action.toString());
                }
                ptr = ptr->next;
            }
        }
        else{
            ptr = tail;
            while(ptr != 0){
                string type = ptr->action.getType();
                if((type == "Adding" || type == "Eliminating")){
                    text.push_back(ptr->action.toString());
                }
                ptr = ptr->previous;
            }
        }
    }
    return text;
};


//---------------------------------------------------------------------
/*
vector<int> getModifiableInt()

Function responsible for returning a vector<int> filled with the ids of 
the Action's of all Elements within the Record linked list whose type 
is either "Adding" or "Eliminating".
*/
vector<int> Record::getModifiableInt(){
    Element* ptr;
    ptr = head;
    vector<int> ids;
    string type;

    if(!empty()){
        while(ptr != 0){
            type = ptr->action.getType();
            if(type == "Adding" || type == "Eliminating"){
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
void correctId()

Function responsible for starting from the tail of the Record linked list
and check that the id of the Actions taken matches a counter that increase
in one with every action, if it does not match it, it starts a correction
setting the counter itself as the id of the Action.

This function is used after the elimination of an Element of the list has
taken place.
*/

void Record::correctId(){
    Element* ptr;
    ptr = tail;
    int count = 1;
    int temp;

    while(ptr != 0){
        temp = ptr->action.getID();
        if(temp != count){
            ptr->action.setID(count);
        }
        count++;
        ptr = ptr->previous;
    }
}

#endif