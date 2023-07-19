#pragma once

#include "cubic_hermite_spline.h"

/**
 * Базовый класс для всех интерполяций
 */
class CubicInterpolation {
public:

    /**
     * Получить интерполированные значения
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedValue(const double x) const {
        return _spline->getInterpolatedValue(x);
    }

    /**
     * Получить интерполированные первые производные
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedSpeed(const double x) const {
        return _spline->getInterpolatedSpeed(x);
    }

    /**
     * Получить интерполированные вторые производные
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedAcceleration(const double x) const {
        return _spline->getInterpolatedAcceleration(x);
    }

    /**
     * Получить интерполированные третьи производные
     * @param x - координата
     * @return значение интерполяционного полинома в заданной точке
     */
    double getInterpolatedJerk(const double x) const {
        return _spline->getInterpolatedJerk(x);
    }

    /**
     * Получить сплайн, с которым работает интерполяция
     * @return сплайн, с которым работает интерполяция
     */
    std::shared_ptr<CubicHermiteSpline> getSpline() const {
        return _spline;
    }

protected:
    /**
     * Сплайн, с которым работает интерполяция
     */
    std::shared_ptr<CubicHermiteSpline> _spline;
};