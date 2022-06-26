#include "ExtendibleHash.h"


ExtendibleHash::ExtendibleHash(int bucket_size)
{
    this->bucket_size = bucket_size;
    this->global_depth = 0;
    this->bits_directories.push_back(Directory(0,"",new Bucket()));
}
/*
    Hash function that works with module 7
*/
int ExtendibleHash::hash(int data)
{
    int hashed_data = data % 7;
    return hashed_data;
}

void ExtendibleHash::hash_global_overflow()
{
    const int directories_prev_size = std::pow(2,global_depth);
    for (int i = 0; i < directories_prev_size; i++)
    {
        bits_directories.push_back(bits_directories[i]);
        bits_directories[i].bits.insert(0,"0");
        
        bits_directories[i + directories_prev_size].bits.insert(0,"1");
    }
    this->global_depth++;
}

void ExtendibleHash::hash_local_overflow(int overflown_directory_pos)
{
    auto & directory = this->bits_directories[overflown_directory_pos];
    const int prev_local_depth = directory.local_depth;

    std::vector<int> aux_bucket_saver = directory.bucket_pointer->data_content;
    delete directory.bucket_pointer;
    int start_pos = overflown_directory_pos;
    // Finding start position
    for (int i = overflown_directory_pos; i >= 0; i -= std::pow(2,prev_local_depth))
    {
        start_pos = i;
    }

    for (int i = start_pos; i < std::pow(2,prev_local_depth + 1); i += std::pow(2,prev_local_depth))
    {
        Bucket * new_bucket = new Bucket();
        for (int j = i; j < std::pow(2,global_depth); j += std::pow(2,prev_local_depth + 1))
        {
            this->bits_directories[j].bucket_pointer = new_bucket;
            this->bits_directories[j].local_depth++;
        }
    }
    // Redistributing it all
    for (auto data : aux_bucket_saver)
    {
        this->insert(data);
    }

}

void ExtendibleHash::insert(int data_to_insert)
{
    std::string hashed_data_bin = std::bitset<32>(hash(data_to_insert)).to_string();
    std::string lsv = hashed_data_bin.substr(hashed_data_bin.size() - global_depth, global_depth);
    int pos = std::bitset<32>(lsv).to_ulong();
    auto & directory = this->bits_directories[pos];
    if (directory.bucket_pointer->data_content.size() < bucket_size)
    {
        directory.bucket_pointer->data_content.push_back(data_to_insert);
    }
    else
    {
        if (directory.local_depth < global_depth)
        {
            this->hash_local_overflow(pos);
            this->insert(data_to_insert);
        }
        else
        {
            this->hash_global_overflow();
            this->hash_local_overflow(pos);
            this->insert(data_to_insert);
        }
    }
}

bool ExtendibleHash::search(int data_to_search)
{
    std::string hashed_data_bin = std::bitset<32>(hash(data_to_search)).to_string();
    std::string lsv = hashed_data_bin.substr(hashed_data_bin.size() - global_depth, global_depth);
    int pos = std::bitset<32>(lsv).to_ulong();
    auto & directory = this->bits_directories[pos];
    for (int data : directory.bucket_pointer->data_content)
    {
        if (data == data_to_search) return true;
    }
    return false;
}

void ExtendibleHash::remove(int data_to_remove)
{
    std::string hashed_data_bin = std::bitset<32>(hash(data_to_remove)).to_string();
    std::string lsv = hashed_data_bin.substr(hashed_data_bin.size() - global_depth, global_depth);
    int pos = std::bitset<32>(lsv).to_ulong();
    auto & directory = this->bits_directories[pos];
    for (int i = 0; i < directory.bucket_pointer->data_content.size(); i++)
    {
        if (directory.bucket_pointer->data_content[i] == data_to_remove) 
            directory.bucket_pointer->data_content.erase(directory.bucket_pointer->data_content.begin() + i);
    }
}

void ExtendibleHash::print_to_console()
{
    for (int i = 0; i < this->bits_directories.size(); i++)
    {
        std::cout << this->bits_directories[i].bits << " --> ";
        for (int j = 0; j < this->bits_directories[i].bucket_pointer->data_content.size(); j++)
        {
            std::cout <<  this->bits_directories[i].bucket_pointer->data_content[j] << ' ';
        }
        std::cout << '\n';
    }
}