#include <gtest/gtest.h>
#include <cstdint>

// openBox реалізовано в main.cpp
extern bool openBox(uint32_t y, uint32_t x);

void testBox(uint32_t y, uint32_t x) {
    bool result = openBox(y, x);
    EXPECT_FALSE(result) << "Box should be fully unlocked for " << y << "x" << x;
}

TEST(OpenBoxTest, Basic3x3) {
    testBox(3, 3);
}

TEST(OpenBoxTest, Medium5x5) {
    testBox(5, 5);
}

TEST(OpenBoxTest, Large10x10) {
    testBox(10, 10);
}

TEST(OpenBoxTest, TooSmall) {
    EXPECT_TRUE(openBox(2, 2));  // Має залишитись заблокованою
}
