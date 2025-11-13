/*
Title: Heap.h
Author: Rodrigo Alejandro Hurtado Cortés - A01713854
Date: November 11th, 2025.
Description:
File that contains the Sort and Heap class. 
Together these classes are responsible for handling the Sort and Search
functions related to the vector volumes.

Heap is a tree data structure used to sort the volumes by a specific 
chosen hierarchy while Sort s used to handle the movement of Volume
objects in and out of the Heap to sort them.
*/

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>
#include "Collection.h"

using namespace std;

/*
=======================================================================
Heap Class
=======================================================================
Description: 
Tree Data Structure characterized for sorting the elements inside based
on a priority. This organization allows to use it as a sorting method by
adding elements and always obtaining the greater element on the priority
when taking the root element of the heap.
*/

class Heap {
private:
    //PIV
	Volume *data;
	unsigned int size;
	unsigned int count;
    string sorting;

    //Private methods
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);
	
    

public:
    //Constructor
	Heap(unsigned int, string) ;

    //Public methods
	bool compareVolume(Volume&, Volume&);
    bool empty() const;
	bool full() const;
	void add(Volume);
	Volume remove();
	void clear();
	std::string toString() const;
	
    //Friend class declaration
	friend class Sort;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Constructors Declaration

/*
Heap(unsigned int sze, string sort)

Constructor with parameters that sets the limit of elements that can be
contained inside the Heap [sze] and the priority to be taken [sort]. 
*/

Heap::Heap(unsigned int sze, string sort)  {
	size = sze;
	data = new Volume[size];
	count = 0;
    if(sort == "name")
        sorting = "name";
    else    
        sorting = "author";
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Private Methods

/*
bool empty() const

Method responsible for returning a boolean that indicates if the heap is
empty.
*/
bool Heap::empty() const {
	return (count == 0);
}


//---------------------------------------------------------------------
/*
bool full() const

Method responsible for returning a boolean that indicates if the heap is
full.
*/

bool Heap::full() const {
	return (size == count);
}


//---------------------------------------------------------------------
/*
unsigned int parent(unsigned int pos) const

Method responsible for returning an insigned integer that indicates the
index of the parent of the element in index [pos].
*/

unsigned int Heap::parent(unsigned int pos) const {
	return (pos-1)/2;
}


//---------------------------------------------------------------------
/*
unsigned int left(unsigned int pos) const

Method responsible for returning an insigned integer that indicates the
index of the left children of the element in index [pos].
*/

unsigned int Heap::left(unsigned int pos) const {
	return (pos*2)+1;
}


//---------------------------------------------------------------------
/*
unsigned int right(unsigned int pos) const

Method responsible for returning an insigned integer that indicates the
index of the right children of the element in index [pos].
*/

unsigned int Heap::right(unsigned int pos) const {
	return (pos*2)+2;
}


//---------------------------------------------------------------------
/*
void swap(unsigned int i, unsigned int j)

Method responsible for swaping the elements contained in the indexes 
[i,j].
*/

void Heap::swap(unsigned int i, unsigned int j) {
	Volume aux = data[i];
	data[i] = data[j];
	data[j] = aux;
	return ;
}


//---------------------------------------------------------------------
/*
void Heap::heapify(unsigned int pos){

Method responsible for checking the priority of the element compared to
the element itself. In case an element has a greater priority, their place
is swapped with the function swap() and the function is called recursively
over the changed element.
*/

void Heap::heapify(unsigned int pos){
    unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;

	if (le < count && compareVolume(data[min],data[le])){
		min = le;
	}

	if (ri < count && compareVolume(data[min],data[ri])){
		min = ri;
	}

	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}

    return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Public Methods

/*
bool compareVolume(Volume& a, Volume& b)

Method responsible for returning a bool that indicates if the Volume [a]
has a lower priority than Volume [b] based on the type of sorting 
declared during the construction of the heap data structure:
This can be either:
- Sort by Name
- Sort by Author
*/

bool Heap::compareVolume(Volume& a, Volume& b){
    //Sort by Author
    if(sorting == "author"){

        string author_a;
        string author_b;

        //Error handling in case one of the Volumes is null.
        try{
            author_a = a.getAuthor();
        }
        catch(std::length_error){
            return true;
        }

        try{
            author_b = b.getAuthor();
        }
        catch(std::length_error){
            return false;
        }

        //If the author's name of b is less than the author's name of a.
        if(((a.getAuthor()).compare(b.getAuthor())) > 0){
            return true;
        }

        //If the author is equal, order based on volume name
        else if(((a.getAuthor()).compare(b.getAuthor())) == 0){
            //If the name of b is less than the name of a.
            if(((a.getName()).compare(b.getName())) > 0){
                return true;
            }

            /*If both name and author are equal order based on volume
            number.*/
            else if(((a.getName()).compare(b.getName())) == 0){
                /*If the volume of b is smaller or equal to the volume
                of a.*/
                if(a.getVolume() > b.getVolume()){
                    return true;
                }
                return false;
            }
            return false;
        }
        else{
            return false;
        }
    }
    //Sort by Name
    else{
        string name_a;
        string name_b;

        //Error handling in case one of the Volumes is null.
        try{
            name_a = a.getName();
        }
        catch(std::length_error){
            return true;
        }
        try{
            name_b = b.getName();
        }
        catch(std::length_error){
            return false;
        }

        //If the name of b is less than the name of a.
        if(((a.getName()).compare(b.getName())) > 0){
            return true;
        }
        //If the name is equal, order based on volume number
        else if(((a.getName()).compare(b.getName())) == 0){
            /*If the volume of b is smaller or equal to the volume of a.*/
            if(a.getVolume() > b.getVolume()){
                return true;
            }
            return false;
        }
        else{
            return false;
        }
    }
	return false;
};


//---------------------------------------------------------------------
/*
void add(Volume val)

Method responsible for adding a Volume at the end of the heap data 
structure and move it until its priority is not greater than its parents.
*/

void Heap::add(Volume val)  {
	if(!full()){
        unsigned int pos = count++;

        while (pos > 0 && compareVolume(data[parent(pos)], val)) {
            data[pos] = data[parent(pos)];
            pos = parent(pos);
        }
        data[pos] = val;
	}
}


//---------------------------------------------------------------------
/*
Volume remove()

Method responsible for removing the root element of the head data 
structure and reorder the elements inside of it with the use of
the function heapify() in order to obtain the root elements with the
greatest priority. 
*/

Volume Heap::remove()  {
	if(!empty()){
		Volume aux;
		aux = data[0];
		data[0] = data[--count];
		heapify(0);
		return aux;
	}
    else
        return Volume();
}


//---------------------------------------------------------------------
/*
void clear() 

Method responsible for erasing the elements inside the heap and setting
its variables data, size and count to 0.
*/

void Heap::clear() {
	delete [] data;
	data = 0;
	size = 0;
	count = 0;
}


//---------------------------------------------------------------------
/*
string toString() const 

Method responsible for returning all the Volumes contained inside the
heap data structure as a string.

This method was developed for testing purposes uniquely and it is not
actually used on the program.
*/

std::string Heap::toString() const {
	std::stringstream aux;

	aux << "[";
	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << data[i].getName() <<" Volume: "<<data[i].getVolume();
	}
	aux << "]";
	return aux.str();
}


/*
=======================================================================
Sort Class
=======================================================================
Description:
Class responsible for handling the sorting and search methods of concrete
volumes making use of the heap data structure and iterative traversing.

----------------------------------------------------------------------

HeapSort Analysis:
As mentioned before, the present program makes use of a heap tree data
structure in order to obtain a series of data ordered in ascendent or
descendent order depending on the priority of the heap and comparison 
established inside the heapify() function.

HeapSort Time Complexity: O(n log n)
HeapSort Space Complexity: O(n) usually O(1)

The algorithm implemented creates a new heap structure everytime the
vector requires to be sorted, this can be caused either for the addition
or elimination of an element or a change of the sorting method.
[Space complexity of O(n)].

After the creation of the heap structure each element of volumes is
added [O(n)] and afterwards removed from the heap and added to a clean
volumes vector [O(n log n)].

Additionally, the consideration of the sorting process while adding each
element [O(n log n)] leads to a time complexity of O(n log n) where its
scalar to be multiplied is higher than the standard HeapSort, but still
faster than other methods.

----------------------------------------------------------------------

Usage Justification:
The sorting algorithm was changed from Selection Sort to Heap Sort due
to the efficiency and lower time consumption of the second algorithm
as the number of elements inside volumes increases.

Similarly, the implementation of Heap is relatively simple and allows for
more than one sorting criteria that can be established based on the 
comparison inside the heeapify() function instead of the creation of
two separated methods as required for the Selection Sort.

Unfortunately, the heap can not be used as a substitution of the volumes
vector due to its unstability and the fact that the contained data is not
sorted in order as traversing through the nodes, as only the root element
is the one completely following the criteria. Due to this factor, heaps
are created everytime the sorting algorithm is used instead of keeping 
a permanent one.
*/


class Sort
{

private:
    // Private Functions
    void checkSpace(Volume&, Volume&, vector<Bookshelf>&);

public:
    //Public Functions
    Sort();
	void sortBy(vector<Volume>&, vector<Bookshelf>&, string);
    vector<int> searchVolumes(vector<Volume>&, string);
    int searchVolume(vector<Volume>&, Volume);
};


/*
Sort() 

Empty default constructor of the Sort object.
*/
Sort::Sort(){};


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




/*
void sortBy(vector<Volume> &volumes, vector<Bookshelf> &books, string type)

Method responsible for handling both sorting types using the Heap Sort
by initially creating a specific Heap depending on the sort [type],
adding all elements through a for loop into the heap, clearing volumes,
and afterwards removing each element from the heap while adding it to
volumes once more.

This void method allows to modify the volumes vector by ending up with 
all its elements on the chosen or preestablished sort (author or name).
*/

void Sort::sortBy(vector<Volume> &volumes, vector<Bookshelf> &books, string type){
	int size = volumes.size();
	//Creation of the heap data structure
    Heap heap(size, type);

    //Addition of all elements contained within volumes
	for(int i = 0; i<size; i++){
		heap.add(volumes[i]);
	}
    
    //Clearing of volumes.
	volumes.clear();

    /*Extraction of all elements from the heap while adding them into
    volumes*/
	int j = 0;
	while(!heap.empty()){
		volumes.push_back(heap.remove());

        /*Depending on the number of element, the function checkSpace()
        is called to establish the location of each volume based on
        available space and volume's width.*/
		if(j == 0){
			Volume empty = Volume();
            checkSpace(empty, volumes[j], books);
		}
		else{
			checkSpace(volumes[j-1], volumes[j], books);
		}
		j++;
	}
	
	heap.clear();
}



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

//---------------------------------------------------------------------
/*
int searchVolume(vector<Volume>& volumes, Volume lookingFor)

Method that returns the index of the Volume object [lookingFor] within
the Volume vector [volumes]. 
This method is used as a search mechanism of one existing element within
the vector.
*/

int Sort::searchVolume(vector<Volume>& volumes, Volume lookingFor){
    int index = -1;
    for(int i = 0; i<volumes.size(); i++){
        if((volumes[i].getName() == lookingFor.getName()) && (volumes[i].getVolume() == lookingFor.getVolume())){
            index = i;
        }
    }
    return index;
}


#endif