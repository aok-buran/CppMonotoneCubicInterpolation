#pragma once

#include <iostream>
#include "base/cubic_hermite_spline.h"
#include "base/cubic_interpolation.h"


/**
 * Класс кубической интерполяции Эрмита, скорости
 * в опорных точках рассчитываются методом трёхточечной разности
 */
class HermiteCubicInterpolation : public CubicInterpolation {
public:

    /**
     * Конструктор
     * @param x_ptr - указатель на x - координаты
     * @param y_ptr - указатель на y - координаты
     * @param size - количество опорных точек траектории
     */
    HermiteCubicInterpolation(const double *x_ptr, const double *y_ptr, const size_t size) {
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

};

