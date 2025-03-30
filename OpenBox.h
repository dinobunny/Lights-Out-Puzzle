
#ifndef OPENBOX_H
#define OPENBOX_H

#include "SecureBox.h"

//================================================================================
// Function: solveWithGauss
// Description: solves the system of linear equations according to module 2
//              Gaussian method. It is used to calculate which
//              buttons you need to press to open the box.
//================================================================================
bool solveWithGauss(
    std::vector<std::vector<int>>& matrix, // матриця впливу (A) — NxN
    std::vector<int>& targetState, // вектор початкового стану (b)
    std::vector<int>& solution // Вектор рішення: які кнопки натискати (x)
);

//================================================================================
// Function: createEquationSystem
// Description: Строит матрицу влияния всех кнопок и вектор
//              текущего состояния ячеек (включено/выключено).
//================================================================================
void createEquationSystem(
    const std::vector<std::vector<bool>>& boxState,// 2D-матриця — поточний стан поля (true = світиться)
    std::vector<std::vector<int>>& influenceMatrix,// Вихід: матриця впливу A (NxN) — яка кнопка на яку клітинку діє
    std::vector<int>& initialStateVector           // Вихід: вектор b — стан лампочок у плоскому вигляді
);
//================================================================================
// Function: openBox
// Description: Основная функция, открывающая коробку. Строит уравнение,
//              решает его, применяет найденные нажатия и возвращает,
//              осталась ли коробка заблокированной.
//================================================================================
bool openBox(uint32_t rows, uint32_t cols);


#endif //OPENBOX_H
