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
// Function: solveWithGauss
// Description: Решает систему линейных уравнений по модулю 2
//              методом Гаусса. Используется для вычисления, какие
//              кнопки нужно нажать для открытия коробки.
//================================================================================
bool solveWithGauss(
    std::vector<std::vector<int>>& matrix,
    std::vector<int>& targetState,
    std::vector<int>& solution
) {
    const size_t numRows = matrix.size();// кількість Рядків
    const size_t numCols = matrix[0].size();// кількістт колонок
    solution.assign(numCols, 0);//створюю пусту колонку куди буде записуватись кнопка

    size_t rank = 0;

    for (size_t col = 0; col < numCols && rank < numRows; ++col) {
        size_t pivotRow = rank;
        while (pivotRow < numRows && matrix[pivotRow][col] == 0)
            ++pivotRow;
        if (pivotRow == numRows)
            continue;

        std::swap(matrix[pivotRow], matrix[rank]);
        std::swap(targetState[pivotRow], targetState[rank]);

        for (size_t row = 0; row < numRows; ++row) {
            if (row != rank && matrix[row][col] == 1) {
                for (size_t j = col; j < numCols; ++j)
                    matrix[row][j] ^= matrix[rank][j];
                targetState[row] ^= targetState[rank];
            }
        }
        ++rank;
    }

    for (size_t i = rank; i < numRows; ++i) {
        bool isZeroRow = true;
        for (int val : matrix[i]) {
            if (val != 0) {
                isZeroRow = false;
                break;
            }
        }
        if (isZeroRow && targetState[i] == 1)
            return false;
    }

    for (size_t i = rank; i-- > 0;) {
        int pivotCol = -1;
        for (size_t j = 0; j < numCols; ++j) {
            if (matrix[i][j] == 1) {
                pivotCol = static_cast<int>(j);
                break;
            }
        }
        if (pivotCol == -1) continue;

        int xorSum = targetState[i];
        for (size_t j = pivotCol + 1; j < numCols; ++j)
            if (matrix[i][j] == 1)
                xorSum ^= solution[j];
        solution[pivotCol] = xorSum;
    }

    return true;
}

//================================================================================
// Function: createEquationSystem
// Description: Строит матрицу влияния всех кнопок и вектор
//              текущего состояния ячеек (включено/выключено).
//================================================================================
void createEquationSystem(
    const std::vector<std::vector<bool>>& boxState,
    std::vector<std::vector<int>>& influenceMatrix,
    std::vector<int>& initialStateVector
) {
    uint32_t rows = boxState.size();
    uint32_t cols = boxState[0].size();
    uint32_t totalCells = rows * cols;

    influenceMatrix.assign(totalCells, std::vector<int>(totalCells, 0));
    initialStateVector.assign(totalCells, 0);

    for (uint32_t row = 0; row < rows; ++row) {
        for (uint32_t col = 0; col < cols; ++col) {
            int toggleIndex = row * cols + col;

            for (uint32_t k = 0; k < cols; ++k)
                influenceMatrix[row * cols + k][toggleIndex] ^= 1;

            for (uint32_t k = 0; k < rows; ++k)
                influenceMatrix[k * cols + col][toggleIndex] ^= 1;

            influenceMatrix[toggleIndex][toggleIndex] ^= 1;
        }
    }

    for (uint32_t row = 0; row < rows; ++row)
        for (uint32_t col = 0; col < cols; ++col)
            initialStateVector[row * cols + col] = boxState[row][col] ? 1 : 0;
}


//================================================================================
// Function: openBox
// Description: Основная функция, открывающая коробку. Строит уравнение,
//              решает его, применяет найденные нажатия и возвращает,
//              осталась ли коробка заблокированной.
//================================================================================
bool openBox(uint32_t rows, uint32_t cols) {
    SecureBox box(rows, cols);
    int step = 1;

    std::vector<std::pair<int, int>> keySequence; // зберігаємо правильну послідовність

    while (box.isLocked()) {
        auto state = box.getState();

        std::vector<std::vector<int>> A;
        std::vector<int> b;
        createEquationSystem(state, A, b);

        std::vector<int> solution;
        if (!solveWithGauss(A, b, solution)) {
            std::cout << "[!] Рішення неможливе на цьому кроці." << std::endl;
            return true;
        }

        bool moved = false;

        for (uint32_t i = 0; i < solution.size(); ++i) {
            if (solution[i]) {
                uint32_t row = i / cols;
                uint32_t col = i % cols;

                box.toggle(row, col);

                keySequence.emplace_back(row, col);
                step++;
                moved = true;
                break;
            }
        }

        if (!moved) {
            std::cout << "[!] Жодної кнопки не натиснуто — помилка." << std::endl;
            break;
        }
    }

    if (!box.isLocked()) {
        std::cout << "\n The key to opening(a sequence of pressing):" << std::endl;
        for (auto& [row, col] : keySequence) {
            std::cout << "toggle(" << row << ", " << col << ")" << std::endl;
        }
        return false;

    } else {
        return true;
    }
}




int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <rows> <cols>\n";
        return 1;
    }

    long inputRows = std::atol(argv[1]);
    long inputCols = std::atol(argv[2]);

    if (inputRows <= 0 || inputCols <= 0) {
        std::cerr << "Error: rows and columns must be positive integers." << std::endl;
        return 1;
    }
    if (inputRows < 3 || inputCols < 3) {
        std::cerr << "Error: minimal size is 3x3." << std::endl;
        return 1;
    }
    if (inputRows > 100 || inputCols > 100) {
        std::cerr << "Error: max size is 100x100." << std::endl;
        return 1;
    }

    auto rows = static_cast<uint32_t>(inputRows);
    auto cols = static_cast<uint32_t>(inputCols);

    bool locked = openBox(rows, cols);

    if (locked)
        std::cout << "BOX: LOCKED!" << std::endl;
    else
        std::cout << "BOX: OPENED!" << std::endl;

    return locked;
}