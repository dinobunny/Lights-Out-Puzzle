#include "OpenBox.h"

#ifndef UNIT_TESTING
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <rows> <cols>\n";
        return 1;
    }

    long inputRows = std::atol(argv[1]);
    long inputCols = std::atol(argv[2]);

    if (inputRows < 3 || inputCols < 3) {
        std::cerr << "Error: minimal allowed size is 3x3.\n";
        return 1;
    }
    if (inputRows > 100 || inputCols > 100) {
        std::cerr << "Error: maximum allowed size is 100x100.\n";
        return 1;
    }

    // Запускаємо алгоритм
    bool locked = openBox(static_cast<uint32_t>(inputRows), static_cast<uint32_t>(inputCols));

    std::cout << "\nBOX: " << (locked ? "LOCKED!" : "OPENED!") << std::endl;
    return locked; // 0 = success, 1 = still locked
}
#endif
