# Manga Distribution and Organization Program - TC1031.602

## Description

### Problematic Identified
Manga specialized stores as Panini Points or Barnes & Noble receive a continous income and outcome of stories as the customers take them and distribution points send them, keeping a continous movement in bookshelves where througout the store every manga is organized alphabetically based on their title. Processes as the restocking, finding and selling specific manga volumes require of a complete understanding of the bookshelf distribution and the mangas' position making in hard for both employees and customers (even if finding the right volume is also part of the fun).

<p align="center">
<img src="https://github.com/user-attachments/assets/e3a45002-cb29-4325-a02e-c097486353bb" width="300" />
</p>

This problems and the desire to implement order can also occur to individual collectionist making difficult to know the location of specific stories and avaliable free space for more stories.

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

## Competences

### SICT0301 

</p>
### SICT0302

</p>
### SICT0303

</p>
## Program Distribution
The following image shows the UML Class Diagram of the present project which shows the relationships between classes and their respective attributes and methods.

<p align="center">
<img src="https://github.com/user-attachments/assets/9cce40ec-35ec-4019-b1b6-e7e51d14b449" width="500" />
</p>

## Program Usage Indications
The program is responsible for sorting based on an initial key the manga volumes stored initially in the text file "record.txt" which contains in this moment 36 mixed volumes of various collections from different authors. When starting the program with the main.cpp, the sorting will start automatically; all elements of the actual Main Menu and secondary Menus are avaliable and working. After using it, once the user press the 6th option: "6. Save and Exit" all the mangas of the program will be stored based on the last sort. 

Main Menu:

    1. Add a new Manga Volume.
    2. Search for a Manga Volume.
    3. Erase a Manga Volume.
    4. Sort actual collection.
    5. Show collection.
    6. Save and Exit
    Enter your option: 

For testing purposes if desired to keep the mangas mixed in the "record.txt" do not press option 6 of the Main Menu, as no changes will be saved, leaving the original file intact.

</p>

## Program Vulnerabilities
After testing the program, the following vulnerability was identified:

In case of entering a different input type of the expected from the user (entering a word instead of a number) the program will begin looping itself, in which case it must be forced to stop by canceling the process in the console or IDE being used.

As a precaution measure, the instructions that guide the user through the program usage state more clearly the data types required to enter
