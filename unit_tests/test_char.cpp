//
// Created by efg on 05.04.19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Map.h"

using testing::Eq;


namespace {
    class MapTest_ch : public ::testing::Test {
    public:
        RB_Tree<char> *map;

        MapTest_ch() {
            map = new RB_Tree<char>;
        }
    };
}

TEST_F(MapTest_ch, Insert_Root){
    map->Insert('a', 1);
    EXPECT_EQ(map->GetSize(), 1);
}

TEST_F(MapTest_ch, Insert_Two){
    map->Insert('a', 1);
    map->Insert('b', 2);
    EXPECT_EQ(2, map->GetKeys()->at(1));
}

TEST_F(MapTest_ch, Insert_Wrong_Index) {
    try{
        map->Insert('a', 1);
        map->Insert('b', 1);
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("This key is already being used"));
    }
}

TEST_F(MapTest_ch, Find_Empty){
    EXPECT_EQ(map->Find(1), 0);
}

TEST_F(MapTest_ch, Find_Wrong_Index){
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 4);
    EXPECT_EQ(map->Find(10), 0);
}


TEST_F(MapTest_ch, Remove_Empty){
    try{
        map->Remove(1);
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("\nThere is no element with that key\n"));
    }
}

TEST_F(MapTest_ch, Remove_Wrong_Key){
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 4);
    try{
        map->Remove(5);
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("\nThere is no element with that key\n"));
    }
}

TEST_F(MapTest_ch, Remove_no_children){  //remove the element with no children
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 4);
    map->Remove(4);
    EXPECT_EQ(map->GetSize(), 3);
}

TEST_F(MapTest_ch, Remove_two_children){ //remove the element with two children
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 4);
    map->Insert('e', 5);
    map->Remove(4);
    EXPECT_EQ(map->GetValues()->at(3), 'e');
}

TEST_F(MapTest_ch, Remove_one_child){  //remove the element with one child
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 5);
    map->Remove(3);
    EXPECT_EQ(map->GetValues()->at(2), 'd');
}


TEST_F(MapTest_ch, Remove_Root_Empty){
    map->Insert('a', 1);
    map->Remove(1);
    EXPECT_EQ(map->GetRoot(), nullptr);
}

TEST_F(MapTest_ch, Remove_Root){
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 4);
    map->Insert('e', 5);
    map->Insert('f', 6);
    map->Remove(2);
    EXPECT_EQ(map->GetSize(), 5);
}

TEST_F(MapTest_ch, Insert){
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 4);
    map->Insert('e', 5);
    map->Insert('f', 6);
    EXPECT_EQ(map->GetKeys()->get_size(), map->GetValues()->get_size());
}

TEST_F(MapTest_ch, Find){
    map->Insert('a', 1);
    map->Insert('b', 2);
    map->Insert('c', 3);
    map->Insert('d', 4);
    map->Insert('e', 5);
    EXPECT_EQ(map->Find(3), 'c');
}

TEST_F(MapTest_ch, GetKeys_Empty){
    EXPECT_EQ(map->GetKeys()->get_size(), 0);
}

TEST_F(MapTest_ch, GetValues_Empty){
    EXPECT_EQ(map->GetValues()->get_size(), 0);
}



