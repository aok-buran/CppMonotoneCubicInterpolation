#include "monotone_cubic_interpolation.h"

/**
 * Вычислить первые производные в опорных точках методом трёхточечной разности
 * @param dy - вектор, в который нужно записать первые производные
 * @param x_ptr - указатель на x - координаты
 * @param y_ptr - указатель на y - координаты
 * @param size - количество опорных точек траектории
*/
void MonotoneCubicInterpolation::calculateDY(
        std::vector<double> &dy, const double *x_ptr, const double *y_ptr, const size_t size
) {
    std::vector<double> tangents(size, 0);

    // рассчитываем dy методом трёхточечной разности
    for (int i = 0; i < size - 1; ++i) tangents[i] = (y_ptr[i + 1] - y_ptr[i]) / (x_ptr[i + 1] - x_ptr[i]);
    for (int i = 1; i < size - 1; ++i) dy[i] = (tangents[i - 1] + tangents[i]) / 2;

    dy[0] = 0;

    for (int i = 1; i < (size - 1); ++i) {
        // значения совпадают
        if (std::abs(tangents[i]) < _KEPS)
            dy[i] = dy[i + 1] = 0;
    }

    // применяем алгоритм Фритча-Карлсона
    for (int i = 0; i < (size - 2); ++i) {
        // тангенсы касательных имеют разные знаки
        if (tangents[i] * tangents[i + 1] <= 0)
            dy[i] = dy[i + 1] = 0;
        else {
            double alpha = dy[i] / tangents[i];
            double betta = dy[i + 1] / tangents[i];

            double distance = alpha * alpha + betta * betta;
            if (distance > 9) {
                double tau = 3 / std::sqrt(distance);
                dy[i] = tau * alpha * tangents[i];
                dy[i + 1] = tau * betta * tangents[i];
            }
        }
    }

    // делаем дополнительную проверку для предпоследней точки
    if (tangents[size - 2] * tangents[size - 1] <= 0)
        dy[size - 2] = 0;

    dy[size - 1] = 0;
}