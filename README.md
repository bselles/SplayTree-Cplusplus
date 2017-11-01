# SplayTree-Cplusplus
A C++ SplayTree implementation.

It includes a C++ implementation from an Splay Tree.

There's three files:

-SplayTree.h: Contains the header of the Splay Tree. It's what you have to include to you projects to use the Splay Tree.

-SplayTree.cpp: Real implementation of the Splay Tree. It contains the implementation of all the methods written in SplayTree.h

-test.cpp: Testing file. It uses this SplayTree to execute random operations. It prints all the execution times in "result.dat".

This Splay Tree offers 3 operations:

-Search(int element): It looks for a node with element as the value associated. It returns true if it founds it. False if not.

-Remove(int element): It looks for a node with element as the value associated and it tries to remove it. It return true if it existed.
False if not.

-Insert(int element): It puts inside the tree a node with element as the value associated. If already exists a node like this, we return false.
If everything worked correctly and there's not a node with value=element, we return true.


