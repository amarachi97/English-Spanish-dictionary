# English-Spanish-dictionary
The code uses four different methods to find the most 'cost effective' way to search for a Spanish word.
The four method are:
i. using a random binary tree.
ii. using a non-random binary tree.
iii. using a good hashtable (quadratic probing).
iv. using a bad hashtable (linear probing).

i. The total cost refers to the total number of nodes used to store all the words.
    After every search, the BTS nodes refer to the number of nodes accessed before reaching the entered word.
ii. The table analysis for the hashtables represents:
    PROBES - the number of times to search for a slot on the hash table in order to insert a word.
    KEYS - The number of words that needed that amount of hashing.
    e.g. Probes | keys
            1   | 3345
        This means that 3345 words needed only 1 search to find a slot on the hash table .
        
    NOTE: hashing refers to the searching of a slot for an item on the hash table.
