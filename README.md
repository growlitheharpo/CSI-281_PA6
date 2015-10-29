## CSI-281_PA6

### Description:
A program for QUICKLY encrypting a given file based on a code word file.

### My Data Structure (CSI-281 req):
My structure, AlphabetTree, is sort of a combination of an array, Linked List, and a tree. This
structure uses a LOT of memory, but that's "okay" because speed is the only thing that matters for
this assignment.

Each individual instance of AlphabetTree is essentially a node. Every node is a letter,
and the branches of the trees are paths through which letters can be combined. I.e., the A in C->A
is a different node than the A in D->A. Every node contains an array of pointers to its children.
I chose to use an array rather than a list for the fast random access; I take advantage of this
by using the ASCII values of the search key as indexes.
