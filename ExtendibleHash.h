#ifndef _EXTENDIBLE_HASH_
#define _EXTENDIBLE_HASH_

#include <bits/stdc++.h>
#include "Bucket.h"
#include "Directory.h"

class ExtendibleHash
{
private:
    int bucket_size; 
    int global_depth;
    std::vector<Directory> bits_directories;
public:
    int hash(int data);
    int bin_to_decimal(); // Will allow us to transform 
    void hash_global_overflow();
    void hash_local_overflow(int overflown_directory_pos);
public:
    ExtendibleHash(int bucket_size);
    void insert(int);
    bool search(int);
    void remove(int);
    void print_to_console();
};

#endif // _EXTENDIBLE_HASH_
