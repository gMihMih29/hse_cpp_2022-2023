#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    for (int i = 1; i < width; ++i) {
        if (i * height == slices_amount) {
            return true;
        }
    }
    for (int i = 1; i < height; ++i) {
        if (i * width == slices_amount) {
            return true;
        }
    }
    return false;
};