# Manga Distribution and Organization Program - TC1031.602

# Description

### Problematic Identified

Manga specialized stores as Panini Points or Barnes & Noble receive a continuous income and outcome of stories as the customers take them and distribution points send them, keeping a continuous movement in bookshelves where throughout the store every manga is organized alphabetically based on their title. Processes as the restocking, finding and selling specific manga volumes require of a complete understanding of the bookshelf distribution and the mangas' position making in hard for both employees and customers (even if finding the right volume is also part of the fun).

<p align="center">
<img src="https://github.com/user-attachments/assets/e3a45002-cb29-4325-a02e-c097486353bb" width="300" />
</p>

This problems and the desire to implement order can also occur to individual collectionist making difficult to know the location of specific stories and available free space for more stories.
<br>

### Objective

The present system allows to read a series of manga volumes, order them based on different keys, add and eliminate volumes from the collection, and search for specific volumes location based in an infinite number of bookshelves and its interior shelfs taking into account the standard measurements of a manga volume and the available space in a traditional Panini's bookshelf. As an additional feature this program can store the information once ordered to keep track of the collection without losing the work done.

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

Total capacity of mangas per whole manga's shelf: 560 volumes being a total of 8 m available in one bookshelf.

### Personal interest

This system would allow not only to keep mangas in order in an specified place, but also search for them based on the data. As an amateur manga collector I am interested in keeping my volumes in order and in a specific place.

<br>

# Competences

## SICT0301 -  Problem Evaluation

### **Make a correct and complete complexity analysis of the sorting algorithms used on the program.**

The sorting algorithm used for this program was the **Heap Sort.**

This algorithm makes use of a heap tree data structure in order to obtain a series of data ordered in ascendent or descendent order depending on the priority of the heap and comparison established inside the heapify() method.

Heap Sort Time Complexity: O(n log n)

Heap Sort Space Complexity: O(n) usually O(1)

The actual algorithm creates a new heap structure every time the vector requires to be sorted, this can be caused either for the addition or elimination of an element or a change of the sorting method. [Space complexity of O(n)]. Even though this approach is not the traditional one, it is still faster than other sorting algorithms as the previously implemented Selection Sort.

After the creation of the heap structure each element of volumes is added [O(n)] and afterwards removed from the heap and added to a clean volumes vector [O(n log n)].

Additionally, the consideration of the sorting process while adding each element [O(n log n)] leads to a total time complexity of O(n log n) where its initial n might be higher than other heap sort implementations.

<br>

### **Makes a correct and complete complexity analysis of all the data structures implemented and each of their use on the program.**

The linear data structure applied on the current program was the **double linked list**.

<br>

A **Double Linked List** data structure is formed out of elements linked to each other through a series of pointers that allow each chain ring to know the location of the next and previous element. In this way, the only points to start traversing the list are its start or finish, the head and tail pointer stored within the linked list [Record] class; either of which can be chosen based on closeness to the objective element.

This structure allows to add an infinity of elements, eliminate elements in any place of the list (as long as the involved pointers are correctly connected), traverse relatively easily through it and allow a simple handling due to its internal functions that allow to find, test, and print all elements in both orders that form part of it.

As all the linear data structures, its space complexity equals O(n) as n memory spaces are necessary to store exactly n elements, even though these do not need be next to each other thanks to the pointer traversing.

On the other hand, its time complexity is explained in the following points:

- Access and Search time complexity equal O(n/2) as both processed are based on the ID of the Actions stored, which are proportional to the length of the list, allowing to start the access or search processes from the closest end of the list, having a maximum time in the worst case scenario at the middle of the structure. Additionally, as all elements in the implementation adopted are always added to the start of the linked list based on a priority for recent actions, by the user knowing the number of actions taken in a determined time, a quickest way to find the element is chosen directly by the user but still checked by the algorithm by deciding to check Actions from Recent to Old or vice versa. 

- Insertion and deletion have a time complexity of O(1) as it is relatively simple to add or eliminate elements by having a proper pointer control at the previous and following elements of the list, as well as the consideration of the head and tail pointers.

This data structure was specifically chosen based on its application: working as the storage of the actions taken by the User during the current work session, until the program is either closed or saved; reason why the preference to store recent actions at the start of the list compared to the traditional linked list application where elements are added at the last section. The usage of the double linked list compared to the simple linked list allows the user to obtain actions in the opposite order if required and lower time complexity to access and modify data based on its implementation.

<br>

#### **Additional section:**

A **vector** is a data structure that changes a series of data between arrays of different sizes depending on the necessities of the storage at the moment (more or less space). Due to this factor, it has similarly, a space complexity of O(n) as n spaces in the memory are occupied for n elements. 

Talking about its different time complexities:
- Access time complexity is considerably low as O(1) thanks to the use of the indexes.
- Adding and Eliminate elements from a vector  relies on the creation of a bigger or smaller array as needed, which is known as a relocation process, not achieving an exact time complexity of O(1) but getting close to it.
- Search time complexity equals O(n) as traversing through all elements is typically the standard procedure to find an element within it.

Based on the previous standards we can appreciate how the double linked list is more efficient thanks to the fact that the relocation process is avoided; however, vectors are easier to implement in multiple short sections of the program, therefore used in more classes, as they are used to get a series of returns, ease the sort processing, element finding, and storing. Nonetheless, as this structure is not considered by the course as a linear data structure, its analysis is completely additional and has no effect over the overall grading.

<br>

### **Makes a proper and complete complexity analysis of the remaining components of the program and determines a final program complexity.**

To create an objective time and space complexity analysis of the remaining program functionalities these will be divided into the initial procedures for the program to run and each of the available functionalities in the program menu:

<br>

**Initial functionalities**

Once the program is started the creation of the TextMemory object is followed by the creation of the Collection object though the method read().

read() time complexity: 
As both files must be traversed completely to be able to add every Volume and Action element into the new collection, a proper time complexity would be O(n), considering n as the addition of both volume and action elements; however, an initial sort is performed therefore adding a time complexity of O(n log n).

As between multiple complexities the worst case is the one to consider, the final time complexity is **O(n log n)**.

<br>

**Menu Available Options**

*1. Add a new Manga Volume.*

The addition of a new volume to the vector volumes involves a time complexity of O(n) as the functionality of a vector requires to create a new resized array that fits the number of elements inside of it. Additionally, an automatic sort is performed leading to a final time complexity of **O(n log n)**.

*2. Search for a Manga Volume.*

The search functionality developed in the main file is supported by the method getCollectionBy() which traverses through the entire volumes vector in order to collect only the names of different manga volumes without repeating one, leading to a time complexity of O(n).
Similarly, uses the method searchVolumes() from Sort which traverses through the entire vector in order to find all the available volumes of a title. Time complexity of O(n).

Final time complexity O(2n) moved by theory to **O(n)**.

*3. Erase a Manga Volume.*

Supported by the search functionality O(n) previously declared; together with the use of methods of O(1) as eraseVolume() and add() [from Record], the erase from a vector O(n) and the final sorting of the volumes vector O(n log n) ends up with a time complexity of **O(n log n)**.

*4. Sort actual collection.*

Based on the Heap Sort algorithms previously analized **O(n log n)**.

*5. Show collection.*

1. Show whole collection.

The method consultCollection() traverses through all bookshelves shelves getting each of the stored volumes information, getting a total time complexity of **O(n log n)** as not only every volume is collected, but each of the shelves in each bookshelf is also consulted.

3. Show one bookshelf.

Usage of a method that only refers to one bookshelf, therefore **>O(n)**

3. Show a specific shelf.

Usage of a method that only refers to one shelf in a bookshelf, therefore **>O(n)**

4. Show all collection names.
5. Show all collection authors.
6. Show all collection favorites.

As previously analyzed the function getCollectionBy() independently of the key parameter, these options have an overall time complexity of **O(n)**.


*6. Access collection actions record.*

1. Show actions record.

Option that traverses all elements inside Record, therefore leading to a time complexity of **O(n).**

2. Modify an action.

This functionality is composed of:

- Obtention of modifiable options (obtained through a for loop inside the Record class O(n))
- Validation of the answer obtained within the list of available answers (O(n)).
- Reverse the chosen action which may add or eliminate an specific volume from Record into volumes which directly makes the use of the heap sort once more O(n log n).

As the collection of the previous actions, the worst considered time complexity equals **O(n log n)**.


*7. Save and Exit*

Call of the write() method from TextMemory which traverses both the Record and volumes vector would end up giving a final time complexity of O(n).

<br>

#### Overall consideration

Many of the algorithms implemented though the program are dependent of traversing through the whole collection of objects looking for a series of specific conditions with iteration, leading to a complexity of O(n); however, as any action that imply the addition, elimination or sorting of volumes lead to the greater time of O(n log n), the overall program time complexity would be **O(n log n)**. 

As no algorithm in the program goes higher in time complexity than the previous methods, the previous conclusion is a good approximation; although, it is necessary to consider that the number of times the first n would be multiplied is moderate, but still more efficient than a O(n^2).

On the space complexity aspect, no data structure adopted had a smaller space complexity than O(n), and some functionalities like the Heap Sort are innefient as it requires them to create a data structure everytime they are being used, therefore an overall space complexity **>O(n)** is seriously considered.

Room for improvement:
- Development of algorithms that restrict their searching range, specially when previous used methods may allow to obtain information to perform their functionalities easier.
- Improvement of the Heap Sort algorithm in order to lower even more its time and space complexity().


<br>

## SICT0302 - Decision Making
### **Choose a proper sorting algorithm for the problem and use it correctly.**

The sorting algorithm was changed from Selection Sort to Heap Sort due to the efficiency and lower time consumption of the second algorithm as the number of elements inside volumes increases.

Moreover, the implementation of Heap is relatively simple and allows for more than one sorting criteria that can be established based on the comparison inside the heapify() method instead of the creation of two separated methods as required for the Selection Sort, keeping its benefits as the availability to update the "physical" location of each Volume once it has been removed from the Heap structure using the method checkSpace(Volume&, Volume&, vector&) independently of the sorting applied.

Unfortunately, the heap can not be used as a substitution of the volumes vector due to its instability and the fact that the contained data is not sorted in order as traversing through the nodes, as only the root element is the one completely following the criteria. Due to this factor, heaps are created every time the sorting algorithm is used instead of keeping a permanent one.

As an improvement to the future (out of the present project criteria as a sorting algorithm must be implemented) both the sorting and vector volumes could be replaced with an AVL tree  adapting its sorting criteria based on the Name and Author order.

<br>

### **Chooses an adequate data structure to solve the problem and use it correctly.**

To explain the usage of the **double linked list** it is necessary to understand its application as the Record of actions of the user.

The feature Record is an addition to the Manga Collection and Distribution program that stores the actions taken by the User during a working session divided into categories:

1. Creation of the Collection (Initial Action).
2. Adding a Manga Volume.
3. Eliminating a Manga Volume.
4. Modifying the Sorting Algorithms of Volumes.

By keeping and storing these actions, the User is able to appreciate his/her progress through each working session, and overall be able to reverse actions taken by mistake. These are called as Modifiable Actions, and by being chosen / selected by the user, the program will automatically execute the opposite action based on the stored Volume information inside the Action object.

Based on the previous behavior and user interaction, the double linked list was chosen as the linear data structure applied to the present project due to the following characteristics:

- The list allows to store an infinity of actions (not limited as an Array, to store as much actions as taken).
- It does not require a second structure to keep the data when consulting (as it would be required if a Stack was used).
- It allows to keep a specific order by adding every element to the start of the list (by having a specific order the User is able to know where to check the last actions performed easily).
- Even though its not possible to traverse it from a foreign class, it is possible to obtain and consult information from it through the use of public functions or if needed, a ListIterator can be developed in a future.
- It allows to modify and access the information stored within the structure independently of the element position in the chain.
- Based on the order and structure, the user is able to obtain its actions from recent to old actions or vice versa, allowing for a more interactive reviewing process.
- Reversed actions are eliminated from the List; by having a way to traverse the list from tail to head, a reorganization of the Action ID's is possible. 

On the other hand, the implementation of the **vector** data structure was based mainly due to its easy application, access and element modification as these data structures are used within the previously explained sorting algorithm, storing of multiple data in different objects (as applied in Collection, Bookshelf or Shelf), and function returns for prints or comparison in the main.cpp file.

<br>

## SICT0303 - Action Implementation

### **Implements mechanisms of proper data consulting from the data structures**

The usage of the Record class (which is a Double Linked List) is done completely through the use of the Collection class functions. 

The Action objects that form the Record are created inside the Collection functions of addVolume(), setSortType() and eraseVolume(), and inmediately added to the Record which is created at the declaration of the Collection object. In this way, the creation is automatic and based on user actions taken on the Main Menu.

The only information that the User needs from the Record are its elements and modifiable elements, which are string vectors that show the information of either all the Actions of the Record, or only modifiable Actions which are "Adding" or "Eliminating" in the chosen order from Recent to Old, or vice versa; these are obtained through functions from Collection which are equally obtained from the inner traversing of the Record elements through its functions from head to tail, or vice versa depending on the user input. At no moment, the user moves freely through the linked list; but rather, the program obtains the required elements from it with punctual functions. 

By taking the previous actions, the data consulting is performed automatically and show to the User, which may or may not modify actions based on free will and appreciate its impact both on the Record of Actions as the Volumes Collection.

<br>

### **Implements file reading mechanisms to load data to structures in a proper way**

The class responsible for reading and saving the manga Volume's and Action's data from and to the text files "volumes.txt" and "record.txt"  respectively is called TextMemory.

Through its function read() it creates a new Collection object, which obtains the information of each manga volume and previous actions stored in the following text format:


	Volume Writing Format - "volumes.txt"

        name
        volume$author
        width*bookshelf%shelf(index_shelf)favorites\n



	Action Writing Format - "record.txt"

	name
   	id$type
    	name
    	volume$author
    	width*bookshelf%shelf(index_shelf)favorites\n
    	description
    	timeString
	


This reading algorithm is divided into two main section:
Each section is responsible for opening its respective file and checking the number of elements inside such file showed by the 

	
	INFO@[Number of elements]
	
 
- The first section reads the Actions through the method readAction() and is added to the modif Record by addAction(). This is the first section as the addition and sorting of Volumes from the second section generate Actions automatically which may generate conflict.

- The second section reads each Volume object with readVolume() before adding it to the Collection with the function primitiveAddVolume() which does not sort the elements of volumes automatically, instead a unique sort is called after all Volumes have been added.

The addition of both sections finally return a Collection object with Volumes stored inside the vector volumes and Actions inside the modif Record.

<br>

### **Implements file writing mechanisms to save data to structures in a proper way**

As a complementary functionality to the reading methods presented above, the principal method write() was developed to register the Volume's and Action's information into the previously presented writing format.

In a similar way to the one presented previously, the algorithm is divided into two sections sharing a text file cleaning and opening section, or creation if necessary before starting their respective filling:

- The first section obtains each Volume's information through a for loop and add it to the text file after being formatted by the method writeVolume().

- The second section performs the same actions using the method writeAction() with each of the elements inside the modif Record object.

Afterwards both files are closed and the register of both the volumes and actions of the working session are saved. As this method is called before closing the program, it is secured that no additional volumes or actions will be performed after the last saving procedure.

<br>

# Program Distribution

The following image shows the UML Class Diagram of the present project which shows the relationships between classes and their respective attributes and methods.

<p align="center">
<img src="https://github.com/user-attachments/assets/e442210c-f3d7-4f05-88f7-872103c6f084" width="800" />
</p>

<br>

# Program Usage Indications
The program is responsible for sorting based on an initial key the manga volumes stored initially in the text file "record.txt" which contains in this moment 35 mixed volumes of various collections from different authors. When starting the program with the main.cpp, the sorting will start automatically; all elements of the actual Main Menu and secondary Menus are available and working. After using it, once the user press the 7th option: "7. Save and Exit" all the mangas of the program will be stored based on the last sort. 

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
