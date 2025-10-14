# Manga Distribution and Organization Program - TC1031.602

## Description

### Problematic Identified
Manga specialized stores as Panini Points or Barnes & Noble receive a continous income and outcome of stories as the customers take them and distribution points send them, keeping a continous movement in bookshelves where througout the store every manga is organized alphabetically based on their title. Processes as the restocking, finding and selling specific manga volumes require of a complete understanding of the bookshelf distribution and the mangas' position making in hard for both employees and customers (even if finding the right volume is also part of the fun).

<p align="center">
<img src="https://github.com/user-attachments/assets/e3a45002-cb29-4325-a02e-c097486353bb" width="300" />
</p>

This problems and the desire to implement order can also occur to individual collectionist making difficult to know the location of specific stories and avaliable free space for more stories.
<br>

### Objective
The present system allows to read a series of manga volumes, order them based on different keys, add and eliminate volumes from the collection, and search for specific volumes location based in an infinite number of bookshelfs and its interior shelfs taking into account the standard measurements of a manga volume and the avaliable space in a traditional Panini's bookshelf. As an additional feature this program can store the information once ordered to keep track of the collection without losing the work done.

Measurements of a standard Manga Volume:

Mangas width ranges between 1 - 3 cm depending on the edition, editorial, and story, therefore the user will be able to enter the width of each volume to have a precise calculation.

<p align="center">
<img src="https://github.com/user-attachments/assets/0a6759d0-1346-4479-9f67-e26e9f300613" width="150" />
</p>

Measuments of a standard Panini's manga shelfs:

<p align="center">
<img src="https://github.com/user-attachments/assets/60753ea8-46de-4334-baf3-ebe1927f2c2d" width="300" />
</p>

Total capacity of mangas per individual shelf: 140 volumes ~ 2 m (two sections of 70 each volume with an average width of 1.5 cm or 0.015 m = 1.05 ~ 1 m).

Total capacity of mangas per whole manga's shelf: 560 volumes being a total of 8 m avaliable in one bookshelf.

### Personal interest
This system would allow not only to keep mangas in order in an specified place, but also search for them based on the data. As an amateur manga collector I am interested in keeping my volumes in order and in a specific place.

<br>

## Competences

### SICT0301 -  Problem Evaluation
**Make a correct and complete complexity analysis of the sorting algorithms used on the program.**

The sorting algorithm used for this program was the **Selection Sort.**

This algorithm is iterative and uses two 'for loops': the outer loop goes from 0 to the size of the vector -1, while the inner loop goes from the inner loop counter i to the size of the vector -1.
In the inner loop the manga volume with the first alphabetical order of the key (author or name) is located, otherwise the name of the manga (in case the key is the author) or the manga volume number are factors that determine wheter a volume goes before others. Once this volume is found, it is swapped with the volume at position i, unless this is the next volume in order. As the outer loop continues, the already sorted elements are not modified anymore.

Based on the double loop usage, this algorith has a big O-Notation of (n^2) where n is the total number of elements in the vector. 

Even though this is one of the less efficient methods for sorting, the storage of the volumes in both vectors in the Object Collection: volumes (Vector<Volume>) and bookshelves (Vector<Bookshelf>) and the requirement for a continously updating space in each bookshelf's shelf is the reason this algorithm was implemented, which is explained in detail in the following competence.

<br>

**Makes a correct and complete complexity analysis of all the data structures implemented and each of their use on the program.**

The linear data structures applied on the current program were the **simple linked list** and **vectors** which are explained in each individual section:

<br>

A **Simple Linked List** data structure is formed out of elements linked to each other through a series of pointers that allow each chain ring to know the location of the next element. In this way, the only point to start traversing the list is knowing its start, the head pointer stored within the linked list [Record] class, to afterwards continue traveling through the chain until the last element's pointer goes to null.

This structure allows to add an infinity of elements, eliminate elements in any place of the list, traverse relatively easily through it and allow a simple handling due to its internal functions that allow to find, test, and print all elements that form part of it.

As all the linear data structures, its space complexity equals O(n) as n memory spaces are necessary to store exactly n elements, even though these do not need be next to each other thanks to the pointer traversing.

On the other hand, due to the modification applyied at the add() function, a change on the traditional time complexity might be experienced in the following points:

- Access and Seacrh time complexity equal O(n) as in the worst case scenario, where the whole list must be traversed in order to find the last element. However, as all elements in the implementation adopted are always added to the start of the linked list based on a priority for recent actions, the time might lower for the most recent actions in comparison to the oldest actions that will still keep a time complexity of O(n).

- Insertion and delition have a time complexity of O(1) as it is extremely easy to add or eliminate elements by having a proper pointer control at the previous and following elements of the list.

This data structure was specifically designed based on its application working as the storage of the actions taken by the User during the current work session until the program is either closed or saved; reason why the preference to store recent actions at the start of the list compared to the traditional linked list application where elements are added at the last section.

<br>


A **vector** is a data structure that changes a series of data between arrays of different sizes depending on the necessities of the storage at the moment (more or less space). Due to this factor, it has similarly, a space complexity of O(n) as n spaces in the memory are occupied for n elements. 

Talking about its different time complexities:
- Access time complexity is considerably low as O(1) thanks to the use of the indexes.
- Adding and Eliminate elements from a vector  relies on the creation of a bigger or smaller array as needed, which is known as a relocation process, not achieving an exact time complexity of O(1) but getting close to it.
- Search time complexity equals O(n) as traversing through all elements is tipically the standard procedure to find an element within it.

Based on the previous standards we can appreciate how the simple linked list is more efficient thanks to the fact that the recolation process is avoided; however, vectors are easier to implement in multiple short sections of the program, therefore used in more classes, as they are used to get a series of returns, ease the sort processing, element finding, and storing.



<br>

### SICT0302 - Decision Making
**Choose a proper sorting algorithm for the problem and use it correctly.**

To explain the usage of the **Selection Sort** as the sorting algorithm of the system, it is required to explain first the distribution of manga volumes.

Mangas in the program are stored in two places simultaneously:
1. volumes: Vector<Volume> in a Collection object. This vector is used to be able to efficiently access and sort the manga volumes with less complexity that extracting all volumes from each shelf in all used bookshelves.
2. bookshelves: Vector<Bookshelf> in a Collection object. This vector holds bookshelves each with a limited number of shelfs, each of these with a limited length in cm to store manga volumes based on their width and sorted order. To keep track of their "physical location" in a bookshelf, the Volume object has three PIV: Bookshelf, Shelf and Shelf Index that reference this location.


During the sorting algorithm, the volumes vector is used. All physical locations and bookshelves are erased, and as each volume is found in its correct order (outer loop), the ideal space in the bookshelf is found and updated by the auxiliar method of the SortSearch class "checkSpace(Volume&, Volume&, vector<Bookshelf>&)". This is done in the order from A-Z alphabetically to be able to take into account the space already occupied by previous volumes, remaining space in each shelf and bookshelf, while keeping the order already established. 

As one volume at a time is found and put in the correct order in the Selection Sort, its "physical" location would be updated, keeping a real account of the remaining space for the next volume. Being this the main reason why the Selection Sort algorithm was chosen and implemented.

<br>

**Selecciona una estructura de datos adecuada al problema y lo usa correctamente.**

//////////////////////////////////////////


<br>

### SICT0303 - Action Implementation

**Implements mechanisms of proper data consulting from the data structures**

The usage of the Record class (which is the Simple Linked List) is done completely through the use of the Collection class functions. 

The Action objects that form the Record of actions are created inside the Collection functions of addVolume(), setSortType() and eraseVolume(), and inmediately added to the Record which is created at the declaration of the Collection object. In this way, the creation is automatic and based on user actions taken on the Main Menu.

The only information that the User needs from the Record are its elements and modifiable elements, which are string vectors that show the information of either all the Actions of the Record, or only modifiable Actions which are "Adding" or "Eliminating" whose status "reversed" = false; these are obtained through functions from Collection which are equally obtained from the inner traversing of the Record elements through its functions. At no moment, the user moves freely through the structure as the linked list; but rather, the program obtains the required elements from it with very punctual functions. 

By taking the previous actions, the data consulting is performed automatically and show to the User, which may or may not modify modifiable actions based on free will and appreciate its impact both on the Record of Actions as the Volumes Collection.

<br>

**Implements file reading mechanisms to load data to data structures in a proper way**

The class responsible for reading and saving the manga Volume's data from and to the text file "record.txt" is called TextMemory.h. Through the function read() it gets creates a new Collection object, obtains the information of each manga volume which is stored in the following format:

        name
        volume$author
        width*bookshelf%shelf(index_shelf)favorites\n

To finally create each Volume object before adding to the collection with the function addVolume() creating directly an Action object which is added to the Record linked list achieving succesfully the automatic load of data as long as the 'record.txt' is present. At the end, the function returns the created Collection which is the one over which we work.

On the other hand, the function write() writes the information of every manga Volume stored within the parameter Collection into the document "record.txt" in the previous shown format. This function is called once the work session with the program has finished, by pressing the option No. 7 on the Main Menu.

<br>

## Program Distribution
The following image shows the UML Class Diagram of the present project which shows the relationships between classes and their respective attributes and methods.

<p align="center">
<img src="https://github.com/user-attachments/assets/8de82952-26c9-4644-ba6b-41c308330a3e" width="800" />
</p>



<br>

## Program Usage Indications
The program is responsible for sorting based on an initial key the manga volumes stored initially in the text file "record.txt" which contains in this moment 35 mixed volumes of various collections from different authors. When starting the program with the main.cpp, the sorting will start automatically; all elements of the actual Main Menu and secondary Menus are avaliable and working. After using it, once the user press the 7th option: "7. Save and Exit" all the mangas of the program will be stored based on the last sort. 

Main Menu:

    1. Add a new Manga Volume.
    2. Search for a Manga Volume.
    3. Erase a Manga Volume.
    4. Sort actual collection.
    5. Show collection.
    6. Access collection actions record.
    7. Save and Exit.
    Enter your option: 

For testing purposes if desired to keep the mangas mixed in the "record.txt" do not press option 6 of the Main Menu, as no changes will be saved, leaving the original file intact.

<br>

## Program Vulnerabilities
After implementing the function validateAnswerInteger() in the main.cpp to catch invalid inputs from the user, no more vulnerabilities have been identified.
