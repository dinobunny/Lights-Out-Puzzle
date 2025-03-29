#include <iostream>
#include <vector>
#include <random>
#include <time.h>

/*
You are given a locked container represented as a two-dimensional grid of boolean values (true = locked, false = unlocked).
Your task is to write an algorithm that fully unlocks the box, i.e.,
transforms the entire matrix into all false.

Implement the function:
bool openBox(uint32_t y, uint32_t x);
This function should:
    - Use the SecureBox public API (toggle, isLocked, getState).
    - Strategically toggle cells to reach a state where all elements are false.
    - Return true if the box remains locked, false if successfully unlocked.
You are not allowed to path or modify the SecureBox class.

Evaluation Criteria:
    - Functional correctness
    - Computational efficiency
    - Code quality, structure, and comments
    - Algorithmic insight and clarity
*/

class SecureBox
{
private:
    std::vector<std::vector<bool>> box;

public:

    //================================================================================
    // Constructor: SecureBox
    // Description: Initializes the secure box with a given size and
    //              shuffles its state using a pseudo-random number generator
    //              seeded with current time.
    //================================================================================
    SecureBox(uint32_t y, uint32_t x): ySize(y), xSize(x)
    {
        rng.seed(time(0));
        box.resize(y);
        for (auto& it : box)
            it.resize(x);
        shuffle();
    }

    //================================================================================
    // Method: toggle
    // Description: Toggles the state at position (x, y) and also all cells in the
    //              same row above and the same column to the left of it.
    //================================================================================
    void toggle(uint32_t y, uint32_t x)
    {
        box[y][x] = !box[y][x];
        for (uint32_t i = 0; i < xSize; i++)
            box[y][i] = !box[y][i];
        for (uint32_t i = 0; i < ySize; i++)
            box[i][x] = !box[i][x];
    }

    //================================================================================
    // Method: isLocked
    // Description: Returns true if any cell
    //              in the box is true (locked); false otherwise.
    //================================================================================
    bool isLocked()
    {
        for (uint32_t x = 0; x < xSize; x++)
            for (uint32_t y = 0; y < ySize; y++)
                if (box[y][x])
                    return true;

        return false;
    }

    //================================================================================
    // Method: getState
    // Description: Returns a copy of the current state of the box.
    //================================================================================
    std::vector<std::vector<bool>> getState()
    {
        return box;
    }

private:
    std::mt19937_64 rng;
    uint32_t ySize, xSize;

    //================================================================================
    // Method: shuffle
    // Description: Randomly toggles cells in the box to
    // create an initial locked state.
    //================================================================================
    void shuffle()
    {
        for (uint32_t t = rng() % 1000; t > 0; t--)
            toggle(rng() % ySize, rng() % xSize);
    }
};

bool gauss_mod2(std::vector<std::vector<int>>& A, std::vector<int>& b, std::vector<int>& x) {
    int n = A.size();      // к-сть рівнянь
    int m = A[0].size();   // к-сть змінних
    x.assign(m, 0);

    for (int col = 0, row = 0; col < m && row < n; ++col) {
        for (int i = row; i < n; ++i) {
            if (A[i][col]) {
                std::swap(A[i], A[row]);
                std::swap(b[i], b[row]);
                break;
            }
        }

        if (!A[row][col]) continue;

        for (int i = 0; i < n; ++i) {
            if (i != row && A[i][col]) {
                for (int j = col; j < m; ++j)
                    A[i][j] ^= A[row][j];
                b[i] ^= b[row];
            }
        }
        ++row;
    }

    // Відновлення розв’язку
    for (int i = 0; i < n; ++i) {
        int pivot = -1;
        for (int j = 0; j < m; ++j) {
            if (A[i][j]) {
                pivot = j;
                break;
            }
        }
        if (pivot != -1)
            x[pivot] = b[i];
    }

    return true;
}

extern bool openBox(uint32_t y, uint32_t x) {
    SecureBox box(y, x);
    auto state = box.getState();
    for (auto& row : state) {
        for (bool b : row)
            std::cout << b << " ";
        std::cout << "\n";
    }
    std::cout << "------\n";
    int total = y * x;
    std::vector<std::vector<int>> A(total, std::vector<int>(total, 0));
    std::vector<int> b(total);

    // Створюємо матрицю A: як toggle i впливає на j
    for (uint32_t i = 0; i < y; ++i) {
        for (uint32_t j = 0; j < x; ++j) {
            int idx = i * x + j;

            // toggle(i,j) впливає на:
            for (uint32_t k = 0; k < x; ++k)
                A[i * x + k][idx] = 1;
            for (uint32_t k = 0; k < y; ++k)
                A[k * x + j][idx] = 1;
            A[idx][idx] = 1; // вже включено, але для надійності
        }
    }

    // Вектор b: стан коробки
    for (uint32_t i = 0; i < y; ++i)
        for (uint32_t j = 0; j < x; ++j)
            b[i * x + j] = state[i][j] ? 1 : 0;

    std::vector<int> xvec;
    gauss_mod2(A, b, xvec);

    // Застосовуємо розв’язок
    for (uint32_t i = 0; i < y; ++i)
        for (uint32_t j = 0; j < x; ++j)
            if (xvec[i * x + j])
                box.toggle(i, j);

    return box.isLocked();
}


#ifndef UNIT_TESTING
int main(int argc, char* argv[]) {
    uint32_t y = std::atol(argv[1]);
    uint32_t x = std::atol(argv[2]);
    bool state = openBox(y, x);

    if (state)
        std::cout << "BOX: LOCKED!" << std::endl;
    else
        std::cout << "BOX: OPENED!" << std::endl;

    return state;
}
#endif

