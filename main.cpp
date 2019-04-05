#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "Map.h"
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    int n = RUN_ALL_TESTS();

    RB_Tree<char> map;
    List<size_t>* keys;
    List<char>* values;


    map.Insert('a', 10);    //work example
    map.Insert('c', 4);
    map.Insert('b', 11);
    map.Insert('d', 12);
    map.Insert('e', 13);
    map.Insert('f', 14);
    map.Insert('g', 15);
    map.Insert('d', 45);
    map.Insert('z', 5);
    map.Insert('x', 20);
    map.Insert('w', 21);
    map.Insert('q', 41);
    map.Remove(20);
    map.OutTree();
    keys = map.GetKeys();
    values = map.GetValues();
    std::cout << keys;
    std::cout << values;
    return 0;
}