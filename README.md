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

The linear data structure applied on the current program was the **simple linked list**.

This particular data structure is formed out of elements linked to each other through a series of pointers that allow each chain ring to know the location of the next element. In this way, the only point to start traversing the list is knowing its start, the head pointer stored within the linked list [Record] class, to afterwards continue traveling through the chain until the last element's pointer goes to null.

This structure allows to add an infinity of elements, eliminate elements in any place of the list, traverse relatively easily through it and allow a simple handling due to its internal functions that allow to find, test, and print all elements that form part of it.

As all the linear data structures, its space complexity equals O(n) as n memory spaces are necessary to store exactly n elements, even though these do not need be next to each other thanks to the pointer traversing.

On the other hand, due to the modification applyied at the add() function, a change on the traditional time complexity might be experienced in the following points:

- Access and Seacrh time complexity equal O(n) as in the worst case scenario, where the whole list must be traversed in order to find the last element. However, as all elements in the implementation adopted are always added to the start of the linked list based on a priority for recent actions, the time might lower for the most recent actions in comparison to the oldest actions that will still keep a time complexity of O(n).

- Insertion and delition have a time complexity of O(1) as it is extremely easy to add or eliminate elements by having a proper pointer control at the previous and following element.

Additionally, a brief analysis over the **vector** data structure is included as this structure is responsible for storing the principal object of the program Volumes.



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

**Implementa mecanismos para consultar información de las estructras correctos.**

////////////////////////////////////

<br>

**Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.**


/////////////////////////////////////

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
