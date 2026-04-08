#include "../datastructs/HashTable.hpp"
#include <gtest/gtest.h>

TEST(HashTableTest, InitiallyEmpty) {
  HashTable<int, int> table;
  EXPECT_TRUE(table.empty());
  EXPECT_EQ(table.size(), 0);
}

TEST(HashTableTest, InsertAndContains) {
  HashTable<int, int> table;
  table.insert(1, 100);

  EXPECT_TRUE(table.contains(1));
  EXPECT_EQ(table.size(), 1);
}

TEST(HashTableTest, AtReturnsCorrectValue) {
  HashTable<int, int> table;
  table.insert(5, 50);

  EXPECT_EQ(table.at(5), 50);
}

TEST(HashTableTest, AtThrowsIfMissing) {
  HashTable<int, int> table;
  EXPECT_THROW(table.at(999), std::out_of_range);
}

TEST(HashTableTest, InsertOverwritesValue) {
  HashTable<int, int> table;

  table.insert(1, 10);
  table.insert(1, 20); // overwrite

  EXPECT_EQ(table.size(), 1);
  EXPECT_EQ(table.at(1), 20);
}

TEST(HashTableTest, RemoveExistingKey) {
  HashTable<int, int> table;

  table.insert(1, 100);
  EXPECT_TRUE(table.remove(1));
  EXPECT_FALSE(table.contains(1));
  EXPECT_EQ(table.size(), 0);
}

TEST(HashTableTest, RemoveNonexistentKey) {
  HashTable<int, int> table;
  EXPECT_FALSE(table.remove(42));
}

struct BadHash {
  size_t operator()(int) const {
    return 0; // everything goes to bucket 0
  }
};

TEST(HashTableTest, HandlesCollisions) {
  HashTable<int, int, BadHash> table(4);

  table.insert(1, 10);
  table.insert(2, 20);
  table.insert(3, 30);

  EXPECT_EQ(table.at(1), 10);
  EXPECT_EQ(table.at(2), 20);
  EXPECT_EQ(table.at(3), 30);

  EXPECT_EQ(table.size(), 3);
}

TEST(HashTableTest, RehashPreservesData) {
  HashTable<int, int> table(2); // small initial bucket count

  for (int i = 0; i < 100; i++) {
    table.insert(i, i * 10);
  }

  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(table.contains(i));
    EXPECT_EQ(table.at(i), i * 10);
  }

  EXPECT_EQ(table.size(), 100);
}

TEST(HashTableTest, LoadFactorIncreases) {
  HashTable<int, int> table(4);

  table.insert(1, 1);
  table.insert(2, 2);

  EXPECT_GT(table.load_factor(), 0.0);
}

TEST(HashTableTest, CopyConstructor) {
  HashTable<int, int> table;
  table.insert(1, 10);
  table.insert(2, 20);

  HashTable<int, int> copy = table;

  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(1), 10);
  EXPECT_EQ(copy.at(2), 20);
}

TEST(HashTableTest, CopyAssignment) {
  HashTable<int, int> table1;
  table1.insert(5, 50);

  HashTable<int, int> table2;
  table2 = table1;

  EXPECT_EQ(table2.size(), 1);
  EXPECT_EQ(table2.at(5), 50);
}

TEST(HashTableTest, MoveConstructor) {
  HashTable<int, int> table;
  table.insert(7, 70);

  HashTable<int, int> moved = std::move(table);

  EXPECT_EQ(moved.size(), 1);
  EXPECT_EQ(moved.at(7), 70);
}

TEST(HashTableTest, MoveAssignment) {
  HashTable<int, int> table1;
  table1.insert(8, 80);

  HashTable<int, int> table2;
  table2 = std::move(table1);

  EXPECT_EQ(table2.size(), 1);
  EXPECT_EQ(table2.at(8), 80);
}

TEST(HashTableTest, WorksWithCustomStringKey) {
  HashTable<String, int> table;

  table.insert(String("x"), 42);
  table.insert(String("y"), 84);

  EXPECT_TRUE(table.contains(String("x")));
  EXPECT_EQ(table.at(String("x")), 42);
  EXPECT_EQ(table.at(String("y")), 84);
}
