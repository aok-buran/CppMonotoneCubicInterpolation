#pragma once

#include <cmath>
#include <vector>
#include <cassert>
#include <memory>


/**
 * Класс кубических сплайнов
 */
class CubicHermiteSpline {
public:
    /**
     * Конструктор
     * @param x_ptr - указатель на x - координаты
     * @param y_ptr - указатель на y - координаты
     * @param dy_ptr - указатель на y - координаты
     * @param size - количество опорных точек траектории
     */
    CubicHermiteSpline(const double *x_ptr, const double *y_ptr, const double *dy_ptr, const size_t size) :
            _x(x_ptr, x_ptr + size),
            _y(y_ptr, y_ptr + size),
            _dy(dy_ptr, dy_ptr + size),
            _size(size) {}

    /**
     * Получить интерполированные значения
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedValue(double x) const;

    /**
     * Получить интерполированные первые производные
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedSpeed(double x) const;

    /**
     * Получить интерполированные вторые производные
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedAcceleration(double x) const;

    /**
     * Получить интерполированные третьи производные
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedJerk(double x) const;

    /**
     * Получить x-координаты опорных точек траектории
     * @return x-координаты опорных точек траектории
    */
    std::vector<double> getX() const { return _x; }

    /**
     * Получить значения f(x) опорных точек траектории
     * @return значения f(x) опорных точек траектории
    */
    std::vector<double> getY() const { return _y; }

    /**
     * Получить значения f'(x) опорных точек траектории
     * @return значения f'(x) опорных точек траектории
    */
    std::vector<double> getDY() const { return _dy; }


private:

    /**
     * Проверка, что x попадает в диапазон интерполирования
     * @param idx - индекс левой границы интерполирования
     * @param x - значение, которое нужно проверить
     * @return флаг, попадает ли x в диапазон интерполирования
     */
    bool _isXinBoundary(const size_t idx, const double x) const {
        return (_x[idx] <= x) && (x < _x[idx + 1]);
    }

    /**
     * Бинарный поиск диапазона интер, в котором содержится
     * заданная координата x
     * @param x - координата по оси обцисс
     * @return индекс левой границы интервала интерполирования
     */
    size_t _binarySearch(double x) const;

    /**
     * Функция интерполирования
     * @param t - время
     * @param idx - индекс левой границы диапазона интерполирования
     * @return интерполированное значение, соответствующее времени t
     */
    double _interpFunc(double t, size_t idx) const;

    /**
       * Функция интерполирования производной
       * @param t - время
       * @param idx - индекс левой границы диапазона интерполирования
       * @return интерполированное значение, соответствующее времени t
       */
    virtual double _interpDFunc(double t, size_t idx) const;

    /**
    * Функция интерполирования производной
    * @param t - время
    * @param idx - индекс левой границы диапазона интерполирования
    * @return интерполированное значение, соответствующее времени t
    */
    virtual double _interpD2Func(double t, size_t idx) const;

    /**
    * Функция интерполирования производной
    * @param t - время
    * @param idx - индекс левой границы диапазона интерполирования
    * @return интерполированное значение, соответствующее времени t
    */
    virtual double _interpD3Func(double t, size_t idx) const;

    /**
     * координаты интерполируемых точек по оси X
     */
    std::vector<double> _x;
    /**
     * интерполируемые значения
     */
    std::vector<double> _y;
    /**
     * интерполируемые первые производные
     */
    std::vector<double> _dy;
    /**
     * кол-во точек интерполяции
     */
    size_t _size;
};

