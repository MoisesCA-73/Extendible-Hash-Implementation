#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <bits/stdc++.h>
#include "Bucket.h"

class Directory
{
public:
    int local_depth;
    std::string bits;
    Bucket * bucket_pointer;
public:
    Directory(int local_depth, std::string bits, Bucket * bucket_pointer);
    void overflow();
};

#endif