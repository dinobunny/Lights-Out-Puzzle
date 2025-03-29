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

//================================================================================
// Function: openBox
// Description: Your task is to implement this function to unlock the SecureBox.
//              Use only the public methods of SecureBox (toggle, getState, isLocked).
//              You must determine the correct sequence of toggle operations to make
//              all values in the box 'false'. The function should return false if
//              the box is successfully unlocked, or true if any cell remains locked.
//================================================================================
// extern bool openBox(uint32_t y, uint32_t x)
// {
//     // Якщо розмір поля менший за 3x3, виводимо повідомлення і повертаємо true (тобто коробка залишається заблокованою),
//     // оскільки за умовою для менших полів рішення неможливе або не має сенсу.
//     if (y < 3 || x < 3) {
//         std::cerr << "Minimum grid size is 3x3. Try again.\n";
//         return true;
//     }//+
//
//     SecureBox box(y, x);
//     auto state = box.getState();
//     for (auto& row : state) {
//         for (bool b : row)
//             std::cout << b << " ";
//         std::cout << "\n";
//     }
//     std::cout << "------\n";
//
//     // Якщо коробка вже відкрита (тобто isLocked() повертає false), то повертаємо false – нічого робити не треба.
//     if (!box.isLocked())
//         return false;//+
//
//     // We'll keep track of the toggles needed
//     std::vector<std::vector<bool>> toggleMap(y, std::vector<bool>(x, false));
//
//     // Step 1: Compute where toggles are needed
//     for (uint32_t i = 0; i < y; ++i) {
//         for (uint32_t j = 0; j < x; ++j) {
//             // Update current state with previous toggles effect
//             bool current = state[i][j];
//             for (uint32_t k = 0; k < i; ++k)
//                 if (toggleMap[k][j]) current = !current;
//             for (uint32_t k = 0; k < j; ++k)
//                 if (toggleMap[i][k]) current = !current;
//             if (toggleMap[i][j]) current = !current;
//
//             // If it's locked, we toggle here
//             if (current) toggleMap[i][j] = true;
//         }
//     }
//
//     // Step 2: Apply the toggles
//     for (uint32_t i = 0; i < y; ++i)
//         for (uint32_t j = 0; j < x; ++j)
//             if (toggleMap[i][j]) box.toggle(i, j);
//
//     // Return final status
//     return box.isLocked();
// }
extern bool openBox(uint32_t y, uint32_t x) {
    if (y < 3 || x < 3) {
        std::cerr << "Minimum grid size is 3x3. Try again.\n";
        return true;
    }

    SecureBox box(y, x);
    auto state = box.getState();
    for (auto& row : state) {
        for (bool b : row)
            std::cout << b << " ";
        std::cout << "\n";
    }
    std::cout << "------\n";

    std::vector<std::vector<bool>> toggled(y, std::vector<bool>(x, false));

    for (uint32_t i = 0; i < y; ++i) {
        for (uint32_t j = 0; j < x; ++j) {
            bool current = state[i][j];

            // Застосовуємо всі попередні toggle-ефекти по колонках
            for (uint32_t row = 0; row < i; ++row)
                if (toggled[row][j]) current = !current;

            // і по рядках
            for (uint32_t col = 0; col < j; ++col)
                if (toggled[i][col]) current = !current;

            if (current)
                toggled[i][j] = true;
        }
    }

    // Застосовуємо toggle-операції
    for (uint32_t i = 0; i < y; ++i)
        for (uint32_t j = 0; j < x; ++j)
            if (toggled[i][j])
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

