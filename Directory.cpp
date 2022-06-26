#include "Directory.h"

Directory::Directory(int local_depth, std::string bits, Bucket * bucket_pointer)
{
    this->local_depth = local_depth;
    this->bits = bits;
    this->bucket_pointer = bucket_pointer;
}