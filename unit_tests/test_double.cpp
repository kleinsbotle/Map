//
// Created by efg on 05.04.19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Map.h"

using testing::Eq;


namespace {
    class MapTest_d : public ::testing::Test {
    public:
        RB_Tree<double> *map;

        MapTest_d() {
            map = new RB_Tree<double>;
        }
    };
}

TEST_F(MapTest_d, Insert_Root){
    map->Insert(1.5, 1);
    EXPECT_EQ(map->GetSize(), 1);
}

TEST_F(MapTest_d, Insert_Two){
    map->Insert(1.5, 1);
    map->Insert(2.5, 2);
    EXPECT_EQ(2, map->GetKeys()->at(1));
}

TEST_F(MapTest_d, Insert_Wrong_Index) {
    try{
        map->Insert(1.23, 1);
        map->Insert(2.23, 1);
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("This key is already being used"));
    }
}

TEST_F(MapTest_d, Find_Empty){
    EXPECT_EQ(map->Find(1), 0);
}

TEST_F(MapTest_d, Find_Wrong_Index){
    map->Insert(1.5, 1);
    map->Insert(2.5, 2);
    map->Insert(3.5, 3);
    map->Insert(4.5, 4);
    EXPECT_EQ(map->Find(10), 0);
}


TEST_F(MapTest_d, Remove_Empty){
    try{
        map->Remove(1);
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("\nThere is no element with that key\n"));
    }
}

TEST_F(MapTest_d, Remove_Wrong_Key){
    map->Insert(1.123, 1);
    map->Insert(2.123, 2);
    map->Insert(3.123, 3);
    map->Insert(4.123, 4);
    try{
        map->Remove(5);
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("\nThere is no element with that key\n"));
    }
}

TEST_F(MapTest_d, Remove_no_children){  //remove the element with no children
    map->Insert(1.5, 1);
    map->Insert(2.5, 2);
    map->Insert(3.5, 3);
    map->Insert(4.5, 4);
    map->Remove(4);
    EXPECT_EQ(map->GetSize(), 3);
}

TEST_F(MapTest_d, Remove_two_children){ //remove the element with two children
    map->Insert(1.123, 1);
    map->Insert(2.123, 2);
    map->Insert(3.123, 3);
    map->Insert(4.123, 4);
    map->Insert(5.123, 5);
    map->Remove(4);
    EXPECT_EQ(map->GetValues()->at(3), 5.123);
}

TEST_F(MapTest_d, Remove_one_child){  //remove the element with one child
    map->Insert(1.5, 1);
    map->Insert(2.5, 2);
    map->Insert(3.5, 3);
    map->Insert(4.5, 5);
    map->Remove(3);
    EXPECT_EQ(map->GetValues()->at(2), 4.5);
}


TEST_F(MapTest_d, Remove_Root_Empty){
    map->Insert(1.5, 1);
    map->Remove(1);
    EXPECT_EQ(map->GetRoot(), nullptr);
}

TEST_F(MapTest_d, Remove_Root){
    map->Insert(1.5, 1);
    map->Insert(2.5, 2);
    map->Insert(3.5, 3);
    map->Insert(4.5, 4);
    map->Insert(5.5, 5);
    map->Insert(6.5, 6);
    map->Remove(2);
    EXPECT_EQ(map->GetSize(), 5);
}

TEST_F(MapTest_d, Insert){
    map->Insert(1.5, 1);
    map->Insert(2.5, 2);
    map->Insert(3.5, 3);
    map->Insert(4.5, 4);
    map->Insert(5.5, 5);
    map->Insert(6.5, 6);
    EXPECT_EQ(map->GetKeys()->get_size(), map->GetValues()->get_size());
}

TEST_F(MapTest_d, Find){
    map->Insert(1.123, 1);
    map->Insert(2.123, 2);
    map->Insert(3.123, 3);
    map->Insert(4.123, 4);
    map->Insert(5.123, 5);
    EXPECT_EQ(map->Find(3), 3.123);
}

TEST_F(MapTest_d, GetKeys_Empty){
    EXPECT_EQ(map->GetKeys()->get_size(), 0);
}

TEST_F(MapTest_d, GetValues_Empty){
    EXPECT_EQ(map->GetValues()->get_size(), 0);
}