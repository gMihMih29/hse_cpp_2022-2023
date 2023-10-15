#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    int current_number = 0;
    for (int i = 1; i <= COLUMNS; ++i) {
        for (int j = 0; j < i; ++j) {
            table[j][i - j - 1] = current_number++;
        }
    }
    for (int i = LINES - 1; i >= 1; --i) {
        for (int j = 0; j < i; ++j) {
            table[LINES - i + j][LINES - j - 1] = current_number++;
        }
    }
}
