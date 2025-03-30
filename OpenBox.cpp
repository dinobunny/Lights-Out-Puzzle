#include "OpenBox.h"

bool solveWithGauss(
    std::vector<std::vector<int>>& matrix, // матриця впливу (A) — NxN
    std::vector<int>& targetState, // вектор початкового стану (b)
    std::vector<int>& solution // Вектор рішення: які кнопки натискати (x)
) {
    const size_t numRows = matrix.size();// Скільки лампочок = скільки рівнянь
    const size_t numCols = matrix[0].size();// Скільки кнопок = скільки змінних (невідомих)
    solution.assign(numCols, 0);//створюю пусту колонку куди буде записуватись кнопка

    size_t rank = 0; // це індекс рядка, з якого треба працювати далі в методі Гаусса(Стартова позиція пошуку півотів)

    for (size_t col = 0; col < numCols && rank < numRows; ++col) {
        size_t pivotRow = rank; // Починаємо пошук півота з поточного rank-рядка

        // 🔍 Шукаємо рядок із 1 у поточному стовпці
        while (pivotRow < numRows && matrix[pivotRow][col] == 0)
            ++pivotRow;

        if (pivotRow == numRows)
            continue; // Якщо не знайшли півота у цьому стовпці — переходимо до наступного

        // 🔃 Ставимо знайдений півотний рядок на позицію rank
        std::swap(matrix[pivotRow], matrix[rank]);
        std::swap(targetState[pivotRow], targetState[rank]);

        // ❌ Обнуляємо всі інші 1 в цьому стовпці (елімінація)
        for (size_t row = 0; row < numRows; ++row) {
            if (row != rank && matrix[row][col] == 1) {
                for (size_t j = col; j < numCols; ++j)
                    matrix[row][j] ^= matrix[rank][j]; // XOR — обнуляємо рядок
                targetState[row] ^= targetState[rank]; // Так само оновлюємо праву частину
            }
        }

        ++rank; // ✅ Знайшли ще одне незалежне рівняння
    }

    // ❗ Перевіряємо, чи система сумісна
    for (size_t i = rank; i < numRows; ++i) {
        bool isZeroRow = true;
        for (int val : matrix[i]) {
            if (val != 0) {
                isZeroRow = false;
                break;
            }
        }
        if (isZeroRow && targetState[i] == 1)
            return false; // Несумісна система: 0 = 1
    }

    // ↩️ Зворотній хід Гаусса — витягуємо значення змінних у x
    for (size_t i = rank; i-- > 0;) {
        int pivotCol = -1;

        // 🔍 Знаходимо стовпець півота (першу 1 в рядку)
        for (size_t j = 0; j < numCols; ++j) {
            if (matrix[i][j] == 1) {
                pivotCol = static_cast<int>(j);
                break;
            }
        }

        if (pivotCol == -1)
            continue; // Якщо не знайшли півота — пропускаємо (рідко буває)

        // 🧠 Обчислюємо значення x[pivotCol], віднімаючи відому частину
        int xorSum = targetState[i];
        for (size_t j = pivotCol + 1; j < numCols; ++j)
            if (matrix[i][j] == 1)
                xorSum ^= solution[j]; // Віднімаємо вплив відомих x[j]
        solution[pivotCol] = xorSum; // Записуємо рішення
    }

    return true; // ✅ Система має розв’язок, він у solution
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
    uint32_t rows = boxState.size();// кількість рядків
    uint32_t cols = boxState[0].size();//кількість ствобців
    uint32_t totalCells = rows * cols;// Загальна кількість клітинок (для перетворення 2D -> 1D)

    influenceMatrix.assign(totalCells, std::vector<int>(totalCells, 0));//Матриця, яка показує, як кожна кнопка впливає на кожну клітинку = 2D, початково всі нулі
    initialStateVector.assign(totalCells, 0);// Вектор з поточним станом лампочок, початково всі нулі

    // 💡 Проходимо по кожній кнопці поля
    for (uint32_t row = 0; row < rows; ++row) {
        for (uint32_t col = 0; col < cols; ++col) {
            int toggleIndex = row * cols + col;//  Вираховуємо індекс кнопки в 1D масиві (flattened)

            //  Кнопка впливає на ВЕСЬ СВІЙ РЯДОК
            for (uint32_t k = 0; k < cols; ++k)
                influenceMatrix[row * cols + k][toggleIndex] ^= 1;

            //  Кнопка впливає на ВЕСЬ СВІЙ СТОВПЕЦЬ
            for (uint32_t k = 0; k < rows; ++k)
                influenceMatrix[k * cols + col][toggleIndex] ^= 1;

            //  Кнопка змінює САМУ СЕБЕ
            influenceMatrix[toggleIndex][toggleIndex] ^= 1;
        }
    }

    // Формуємо вектор b (initialStateVector) з 2D boxState
    // Кожен елемент: 1 якщо лампочка в цій клітинці горить, 0 — якщо вимкнена
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
    SecureBox box(rows, cols); // Створюємо коробку
    int step = 1; // змінна для мойого пошагового вирішення алгоритму

    std::vector<std::pair<int, int>> keySequence; // зберігаємо правильну послідовність

    while (box.isLocked()) {
        auto state = box.getState(); // створюємо копію моєї коробки

        std::vector<std::vector<int>> A;//ствоюємо таблицю розміром який ми задали
        std::vector<int> b;//поточний стан поля, “де зараз світло увімкнено”
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
