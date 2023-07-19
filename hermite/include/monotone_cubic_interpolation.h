#pragma once

#include <iostream>
#include "base/cubic_hermite_spline.h"
#include "base/cubic_interpolation.h"

/**
 * Класс монотонной кубической интерполяции,
 * скорости в опорных точках рассчитываются по алгоритму,
 * описанному в статье:
 * Fritsch, F. N.; Carlson, R. E. (1980). "Monotone Piecewise Cubic Interpolation".
 * SIAM Journal on Numerical Analysis. SIAM. 17 (2): 238–246.
 */
class MonotoneCubicInterpolation : public CubicInterpolation {
public:
    /**
     * Конструктор
     * @param x_ptr - указатель на x - координаты
     * @param y_ptr - указатель на y - координаты
     * @param size - количество опорных точек траектории
     */
    MonotoneCubicInterpolation(const double *x_ptr, const double *y_ptr, const size_t size) {
        std::vector<double> dy(size, 0);
        calculateDY(dy, x_ptr, y_ptr, size);
        _spline = std::make_shared<CubicHermiteSpline>(x_ptr, y_ptr, dy.data(), size);
    }

private:
    /**
     * Вычислить первые производные в опорных точках методом трёхточечной разности
     * @param dy - вектор, в который нужно записать первые производные
     * @param x_ptr - указатель на x - координаты
     * @param y_ptr - указатель на y - координаты
     * @param size - количество опорных точек траектории
     */
    static void calculateDY(std::vector<double> &dy, const double *x_ptr, const double *y_ptr, size_t size);

    /**
     * Точность сравнивания вещественных чисел
     */
    static constexpr const double _KEPS = 1e-3;

};

