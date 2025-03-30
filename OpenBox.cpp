#include "OpenBox.h"

// Розв’язання системи лінійних рівнянь A * x = b в GF(2)
bool solveWithGauss(
    std::vector<std::vector<int>>& matrix,//A
    std::vector<int>& targetState,//x
    std::vector<int>& solution//b
) {
    const size_t numRows = matrix.size();
    const size_t numCols = matrix[0].size();
    solution.assign(numCols, 0);

    size_t rank = 0;

    // Прямий хід Гаусса
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

    // Зворотній хід: витягуємо розв’язок
    for (size_t i = rank; i-- > 0;) {
        int pivotCol = -1;
        for (size_t j = 0; j < numCols; ++j) {
            if (matrix[i][j] == 1) {
                pivotCol = static_cast<int>(j);
                break;
            }
        }

        if (pivotCol == -1)
            continue;

        int xorSum = targetState[i];
        for (size_t j = pivotCol + 1; j < numCols; ++j)
            if (matrix[i][j] == 1)
                xorSum ^= solution[j];
        solution[pivotCol] = xorSum;
    }

    return true;
}

// Побудова матриці впливу A і вектора стану b
void createEquationSystem(
    const std::vector<std::vector<bool>>& boxState,
    std::vector<std::vector<int>>& influenceMatrix,
    std::vector<int>& initialStateVector
) {
    uint32_t rows = boxState.size();
    uint32_t cols = boxState[0].size();
    uint32_t totalCells = rows * cols;// Загальна кількість клітинок (для перетворення 2D -> 1D)

    // Виводимо початковий стан коробки
    std::cout << "[Initial Box State]\n";
    for (const auto& row : boxState) {
        for (bool cell : row) {
            std::cout << (cell ? "1 " : "0 ");
        }
        std::cout << '\n';
    }

    // Ініціалізуємо матрицю A (впливу кнопок) і вектор b (стан лампочок)
    influenceMatrix.assign(totalCells, std::vector<int>(totalCells, 0));
    initialStateVector.assign(totalCells, 0);

    // Побудова матриці A — кожен стовпець відповідає одній кнопці
    for (uint32_t row = 0; row < rows; ++row) {
        for (uint32_t col = 0; col < cols; ++col) {
            int toggleIndex = row * cols + col;// 1D-індекс кнопки

            for (uint32_t k = 0; k < cols; ++k)
                influenceMatrix[row * cols + k][toggleIndex] ^= 1;
            for (uint32_t k = 0; k < rows; ++k)
                influenceMatrix[k * cols + col][toggleIndex] ^= 1;
            influenceMatrix[toggleIndex][toggleIndex] ^= 1;
        }
    }

    //  Побудова вектора b — поточний стан лампочок (1 = горить, 0 = вимкнено)
    for (uint32_t row = 0; row < rows; ++row)
        for (uint32_t col = 0; col < cols; ++col)
            initialStateVector[row * cols + col] = boxState[row][col] ? 1 : 0;
}

// Основна функція: будує систему, знаходить рішення, відкриває коробку
bool openBox(uint32_t rows, uint32_t cols) {
    SecureBox box(rows, cols);

    std::vector<std::vector<int>> A;
    std::vector<int> b;
    createEquationSystem(box.getState(), A, b);

    std::vector<int> solution;

    solveWithGauss(A, b, solution);

    //Перевірка нашого рішення
    std::vector<std::pair<int, int>> keySequence;
    for (size_t i = 0; i < solution.size(); ++i) {
        if (solution[i]) {
            uint32_t row = i / cols;
            uint32_t col = i % cols;
            box.toggle(row, col);
            keySequence.emplace_back(row, col);
        }
    }

    if (box.isLocked()) return true;

    std::cout << "\n The key to opening:\n";
    for (const auto& [row, col] : keySequence)
        std::cout << "toggle(" << row << ", " << col << ")\n";
    return false;
}

