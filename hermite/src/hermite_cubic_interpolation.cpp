#include "hermite_cubic_interpolation.h"

/**
 * Вычислить первые производные в опорных точках методом трёхточечной разности
 * @param dy - вектор, в который нужно записать первые производные
 * @param x_ptr - указатель на x - координаты
 * @param y_ptr - указатель на y - координаты
 * @param size - количество опорных точек траектории
*/
void HermiteCubicInterpolation::calculateDY(
        std::vector<double> &dy, const double *x_ptr, const double *y_ptr, const size_t size
)  {
    // рассчитываем dy методом трёхточечной разности
    std::vector<double> tangents(size, 0);

    for (int i = 0; i < size - 1; ++i) tangents[i] = (y_ptr[i + 1] - y_ptr[i]) / (x_ptr[i + 1] - x_ptr[i]);
    for (int i = 1; i < size - 1; ++i) dy[i] = (tangents[i - 1] + tangents[i]) / 2;

    dy[0] = 0;
    dy[size - 1] = 0;
}