#include <iostream>
#include <map>
#include <memory>
#include "Item.hpp"
#include "memory-dump.hpp"

int main()
{
    std::map<int, std::unique_ptr<Item>> map;
    dump_instance("Map of unique_ptr created on the stack:", map, 0);    
    {
        std::unique_ptr<Item> item1{new Item(1,"LEAD",0x03)};
        dump_instance("item1 unique_ptr:", item1, 0);

        std::unique_ptr<Item> item2 = std::move(item1);
        dump_instance("item2 unique_ptr:", item2, 0);

        // Compiler error -> need to use emplace
        //map.insert({1,std::move(item2)});
        map.emplace(1,std::move(item2));

        dump_instance("Map filled in the {} block:", map, 0);
        dump_instance("Item in map in the {} block:", map.at(1)->_itemId, 0);

    }
    
    dump_instance("Map filled outside the {} block:", map, 0);
    dump_instance("Item in map outside the {} block:", map.at(1)->_itemId, 0);
    
    return 0;
}

