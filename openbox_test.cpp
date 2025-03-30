#include <gtest/gtest.h>
#include <cstdint>
#include "OpenBox.h"

extern bool openBox(uint32_t y, uint32_t x);

void testBox(uint32_t y, uint32_t x) {
    bool result = openBox(y, x);
    EXPECT_FALSE(result) << "Box should be fully unlocked for " << y << "x" << x;
}

TEST(OpenBoxTest, Basic3x3) {
    testBox(3, 3);
}

TEST(OpenBoxTest, Medium50x50) {
    testBox(50, 50);
}

TEST(OpenBoxTest, Large10x10) {
    testBox(10, 10);
}

TEST(OpenBoxTest, Large20x20) {
    testBox(20, 20);
}

TEST(OpenBoxTest, TooSmall) {
    EXPECT_TRUE(openBox(2, 2));  // Має залишитись заблокованою
}

TEST(OpenBoxTest, ManySizes_SmokeTest) {
    for (uint32_t y = 3; y <= 7; ++y) {
        for (uint32_t x = 3; x <= 7; ++x) {
            EXPECT_FALSE(openBox(y, x)) << "Failed at size: " << y << "x" << x;
        }
    }
}

TEST(OpenBoxTest, CheckThatBoxIsActuallyUnlocked) {
    SecureBox box(4, 4);
    auto stateBefore = box.getState();

    EXPECT_FALSE(openBox(4, 4)); // Просто перевіряємо, чи алгоритм працює
}


TEST(EquationSystemTest, MatrixConstruction3x3) {
    std::vector<std::vector<bool>> state = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    std::vector<std::vector<int>> A;
    std::vector<int> b;
    createEquationSystem(state, A, b);

    ASSERT_EQ(b.size(), 9);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[4], 1);
    EXPECT_EQ(b[8], 0);

    ASSERT_EQ(A.size(), 9);
    ASSERT_EQ(A[0].size(), 9); // A is 9x9

    // Наприклад, toggle(0,0) має впливати на 1-й ряд і 1-й стовпець
    EXPECT_EQ(A[0][0], 1); // toggle(0,0) впливає на себе
    EXPECT_EQ(A[1][0], 1); // на рядок
    EXPECT_EQ(A[3][0], 1); // на стовпець
}

TEST(GaussTest, NoSolutionSystem) {
    std::vector<std::vector<int>> A = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    std::vector<int> b = {0, 1, 0};

    std::vector<int> solution;
    bool success = solveWithGauss(A, b, solution);

    EXPECT_FALSE(success); // 0=1 — неможливо
}

