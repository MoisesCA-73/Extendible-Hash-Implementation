#include <bits/stdc++.h>
#include "ExtendibleHash.h"

int main()
{
    ExtendibleHash my_hash(3);
    my_hash.insert(50);

    my_hash.insert(700);
    my_hash.insert(76);

    my_hash.insert(85);
    my_hash.insert(92);
    my_hash.insert(73);
    my_hash.insert(101);


    my_hash.print_to_console();


    return 0;
}