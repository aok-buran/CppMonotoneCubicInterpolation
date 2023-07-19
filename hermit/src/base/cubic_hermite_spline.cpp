#include "base/cubic_hermite_spline.h"

/**
 * Получить интерполированные значения
 * @param x - координата
 * @return значение интерполяционного полинома в заданной точке
 */
double CubicHermiteSpline::getInterpolatedValue(const double x) const {
    const size_t idx = _binarySearch(x);
    if (idx == _size - 1)
        return _y[_size - 1];
    const double t = (x - _x[idx]) / (_x[idx + 1] - _x[idx]);
    return _interpFunc(t, idx);
}

/**
 * Получить интерполированные первые производные
 * @param x - координата
 * @return значение интерполяционного полинома в заданной точке
 */
double CubicHermiteSpline::getInterpolatedSpeed(const double x) const {
    const size_t idx = _binarySearch(x);
    if (idx == _size - 1)
        return _y[_size - 1];
    const double t = (x - _x[idx]) / (_x[idx + 1] - _x[idx]);
    return _interpDFunc(t, idx);
}

/**
 * Получить интерполированные вторые производные
 * @param x - координата
 * @return значение интерполяционного полинома в заданной точке
 */
double CubicHermiteSpline::getInterpolatedAcceleration(const double x) const {
    const size_t idx = _binarySearch(x);
    if (idx == _size - 1)
        return _y[_size - 1];
    const double t = (x - _x[idx]) / (_x[idx + 1] - _x[idx]);
    return _interpD2Func(t, idx);
}

/**
 * Получить интерполированные третьи производные
 * @param x - координата
 * @return значение интерполяционного полинома в заданной точке
 */
double CubicHermiteSpline::getInterpolatedJerk(const double x) const {
    const size_t idx = _binarySearch(x);
    if (idx == _size - 1)
        return _y[_size - 1];
    const double t = (x - _x[idx]) / (_x[idx + 1] - _x[idx]);
    return _interpD3Func(t, idx);
}

/**
 * Бинарный поиск диапазона интер, в котором содержится
 * заданная координата x
 * @param x - координата по оси обцисс
 * @return индекс левой границы интервала интерполирования
 */
size_t CubicHermiteSpline::_binarySearch(const double x) const {
    assert((_x[0] <= x) && (x <= _x[_size - 1]));
    size_t idx_l = 0, idx_r = _size - 1, idx = _size / 2;
    while (true) {
        if (idx_r - idx_l == 1) {
            if (_isXinBoundary(idx, x))
                return idx;
            else
                return (idx + 1);
        }
        if (_isXinBoundary(idx, x))
            return idx;
        else if (_x[idx + 1] <= x) {
            idx_l = idx;
            idx = (idx_r - idx_l) / 2 + idx_l;
        } else {
            idx_r = idx;
            idx = (idx_r - idx_l) / 2 + idx_l;
        }
    }
}

/**
 * Функция интерполирования
 * @param t - время
 * @param idx - индекс левой границы диапазона интерполирования
 * @return интерполированное значение, соответствующее времени t
 */
double CubicHermiteSpline::_interpFunc(const double t, const size_t idx) const {
    return (2 * std::pow(t, 3) - 3 * std::pow(t, 2) + 1) * _y[idx] +
           (std::pow(t, 3) - 2 * std::pow(t, 2) + t) * (_x[idx + 1] - _x[idx]) * _dy[idx] +
           (-2 * std::pow(t, 3) + 3 * std::pow(t, 2)) * _y[idx + 1] +
           (std::pow(t, 3) - std::pow(t, 2)) * (_x[idx + 1] - _x[idx]) * _dy[idx + 1];
}

/**
 * Функция интерполирования
 * @param t - время
 * @param idx - индекс левой границы диапазона интерполирования
 * @return интерполированное значение, соответствующее времени t
 */
double CubicHermiteSpline::_interpDFunc(const double t, const size_t idx) const {
    return (6 * std::pow(t, 2) - 6 * t) * _y[idx] +
           (3 * std::pow(t, 2) - 4 * t + 1) * (_x[idx + 1] - _x[idx]) * _dy[idx] +
           (-6 * std::pow(t, 2) + 6 * t) * _y[idx + 1] +
           (3 * std::pow(t, 2) - 2 * t) * (_x[idx + 1] - _x[idx]) * _dy[idx + 1];
}

/**
 * Функция интерполирования
 * @param t - время
 * @param idx - индекс левой границы диапазона интерполирования
 * @return интерполированное значение, соответствующее времени t
 */
double CubicHermiteSpline::_interpD2Func(const double t, const size_t idx) const {
    return (12 * t - 6) * _y[idx] +
           (6 * t - 4) * (_x[idx + 1] - _x[idx]) * _dy[idx] +
           (-12 * t + 6) * _y[idx + 1] +
           (6 * t - 2) * (_x[idx + 1] - _x[idx]) * _dy[idx + 1];
}

/**
 * Функция интерполирования
 * @param t - время
 * @param idx - индекс левой границы диапазона интерполирования
 * @return интерполированное значение, соответствующее времени t
 */
double CubicHermiteSpline::_interpD3Func(const double t, const size_t idx) const {
    return 12 * _y[idx] +
           6 * (_x[idx + 1] - _x[idx]) * _dy[idx] +
           -12 * _y[idx + 1] +
           6 * (_x[idx + 1] - _x[idx]) * _dy[idx + 1];
}
