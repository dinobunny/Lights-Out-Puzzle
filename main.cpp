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

class SecureBox {
private:
    std::vector<std::vector<bool> > box;

public:
    //================================================================================
    // Constructor: SecureBox
    // Description: Initializes the secure box with a given size and
    //              shuffles its state using a pseudo-random number generator
    //              seeded with current time.
    //================================================================================
    SecureBox(uint32_t y, uint32_t x): ySize(y), xSize(x) {
        rng.seed(time(0));
        box.resize(y);
        for (auto &it: box)
            it.resize(x);
        shuffle();
    }

    //================================================================================
    // Method: toggle
    // Description: Toggles the state at position (x, y) and also all cells in the
    //              same row above and the same column to the left of it.
    //================================================================================
    void toggle(uint32_t y, uint32_t x) {
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
    bool isLocked() {
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
    std::vector<std::vector<bool> > getState() {
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
    void shuffle() {
        for (uint32_t t = rng() % 1000; t > 0; t--)
            toggle(rng() % ySize, rng() % xSize);
    }
};

//================================================================================
// Function: gauss_mod2
// Description: Solves a system of linear equations over GF(2) (mod 2)
//              using Gaussian elimination. Operates on binary (0/1)
//              coefficient matrices and right-hand side vectors, relying
//              solely on XOR operations. Used to determine the toggle positions
//              needed to reach the unlocked (all false) state in SecureBox.
//================================================================================

bool gauss_mod2(std::vector<std::vector<int> > &A, std::vector<int> &b, std::vector<int> &x) {
    const int n = A.size(); // Number of equations
    const int m = A[0].size();  // Number of variables
    x.assign(m, 0);  // Initialize solution vector with zeroes

    // Step 1: Forward elimination (bring A to row echelon form)
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        // Find a pivot row with a 1 in the current column and swap to current row
        for (int i = row; i < n; ++i) {
            if (A[i][col]) {
                std::swap(A[i], A[row]);
                std::swap(b[i], b[row]);
                break;
            }
        }

        // If there's no pivot in this column, skip it
        if (!A[row][col]) continue;

        // Eliminate the current column from all other rows using XOR
        for (int i = 0; i < n; ++i) {
            if (i != row && A[i][col]) {
                for (int j = col; j < m; ++j)
                    A[i][j] ^= A[row][j];  // Subtract rows (mod 2)
                b[i] ^= b[row];        // Adjust the right-hand side
            }
        }
        ++row; // Move to the next row
    }

    // Step 2: Back-substitution to reconstruct solution vector
    for (int i = 0; i < n; ++i) {
        int pivot = -1;
        // Find pivot position in current row
        for (int j = 0; j < m; ++j) {
            if (A[i][j]) {
                pivot = j;
                break;
            }
        }
        // Assign the corresponding value from b to the solution
        if (pivot != -1)
            x[pivot] = b[i];
    }

    // Note: We assume the system is always consistent (no 0 = 1 rows)
    return true;
}

//================================================================================
// Function: openBox
// Description: Your task is to implement this function to unlock the SecureBox.
//              Use only the public methods of SecureBox (toggle, getState, isLocked).
//              You must determine the correct sequence of toggle operations to make
//              all values in the box 'false'. The function should return false if
//              the box is successfully unlocked, or true if any cell remains locked.
//================================================================================
bool openBox(uint32_t y, uint32_t x) {

    if (y < 3 || x < 3) return true;

    SecureBox box(y, x);

    // Get current box state
    auto state = box.getState();

    // Print initial state for debug
    // for (auto &row: state) {
    //     for (bool b: row)
    //         std::cout << b << " ";
    //     std::cout << "\n";
    // }
    // std::cout << "------\n";

    int total = y * x;
    auto A = std::vector(total, std::vector<int>(total, 0));
    std::vector<int> b(total);

    // Step 1: Build matrix A — each column represents a toggle at (i, j)
    //         Each toggle affects its row, column, and itself
    for (uint32_t i = 0; i < y; ++i) {
        for (uint32_t j = 0; j < x; ++j) {
            const int idx = i * x + j;

            // Toggle affects entire row i
            for (uint32_t k = 0; k < x; ++k)
                A[i * x + k][idx] = 1;

            // Toggle affects entire column j
            for (uint32_t k = 0; k < y; ++k)
                A[k * x + j][idx] = 1;

            // Redundant, but explicitly mark (i, j)
            A[idx][idx] = 1;
        }
    }

    // Step 2: Build vector b — flatten initial state into 1D vector
    for (uint32_t i = 0; i < y; ++i)
        for (uint32_t j = 0; j < x; ++j)
            b[i * x + j] = state[i][j] ? 1 : 0;

    // Step 3: Solve Ax = b over GF(2) to get toggle decisions
    std::vector<int> xvec;
    gauss_mod2(A, b, xvec);

    // Step 4: Apply the solution — toggle where xvec[i] == 1
    for (uint32_t i = 0; i < y; ++i)
        for (uint32_t j = 0; j < x; ++j)
            if (xvec[i * x + j])
                box.toggle(i, j);

    // Return whether the box is still locked
    return box.isLocked();
}


#ifndef UNIT_TESTING
int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage:" << argv[0] << " <rows> <columns>\n";
        return 1;
    }
    
    long ly = std::atol(argv[1]);
    long lx = std::atol(argv[2]);
    
    if (ly <= 0 || lx <= 0) {
        std::cerr << "Error: rows and columns must be positive integers." << std::endl;
        return 1;
    }
    if (ly < 3 || lx < 3) {
        std::cerr << "Error: minimal size is 3x3." << std::endl;
        return 1;
    }
    
    auto y = static_cast<uint32_t>(ly);
    auto x = static_cast<uint32_t>(lx);

    bool state = openBox(y, x);


    if (state)
        std::cout << "BOX: LOCKED!" << std::endl;
    else
        std::cout << "BOX: OPENED!" << std::endl;

    return state;
}
#endif
