#include <ctime>
#include <vector>
#include <fstream>
#include "base/misc.h"
#include "monotone_cubic_interpolation.h"
#include "hermite_cubic_interpolation.h"


int main(int argc, char *argv[]) {
    srand(time(nullptr));

    // размер выборки данных
    int dataSize = 15;
    // аргументы функции
    std::vector<double> x(dataSize, 0);
    // значения функции
    std::vector<double> y(dataSize, 0);
    x[0] = 0;
    y[0] = randDouble(0, 5);
    for (int i = 1; i < dataSize; i++) {
        y[i] = randDouble(0, 3);
        x[i] = randDouble(0.3, 1.5) + x[i - 1];
    }

    // строим монотонный интерполятор
    MonotoneCubicInterpolation monotoneInterpolation(x.data(), y.data(), x.size());

    // выводим в файл интерполированные значения функции с аргументами от нуля до последнего x
    // с равным шагом, количество значений задаётся в переменной nPoints
    // для каждого аргумента построчно выводятся сам аргумент, значение функции в точке
    // и первые три производных
    std::ofstream fileOut("../../data/cubic/test-monotone.out");
    const int nPoints = 100;
    for (int i = 0; i <= nPoints; ++i) {
        auto xVal = x.back() * i / static_cast<double>(nPoints);
        fileOut << xVal << " " << monotoneInterpolation.getInterpolatedValue(xVal) << " "
                << monotoneInterpolation.getInterpolatedSpeed(xVal) << " "
                << monotoneInterpolation.getInterpolatedAcceleration(xVal) << " "
                << monotoneInterpolation.getInterpolatedJerk(xVal) << "\n";
    }

    // во второй файл выводятся опорные точки интерполяции: x, f(x), f'(x)
    std::ofstream fileIn("../../data/cubic/test-monotone.in");
    for (int i = 0; i < x.size(); ++i)
        fileIn << x.at(i) << " " << y.at(i) << " "
               << monotoneInterpolation.getSpline()->getDY().at(i) << "\n";

    // строим обычный интерполятор
    HermiteCubicInterpolation hermitCubicInterpolation(x.data(), y.data(), x.size());

    // выводим в файл интерполированные значения функции с аргументами от нуля до последнего x
    // с равным шагом, количество значений задаётся в переменной nPoints
    // для каждого аргумента построчно выводятся сам аргумент, значение функции в точке
    // и первые три производных
    std::ofstream fileOut2("../../data/cubic/test-hermite.out");
    for (int i = 0; i <= nPoints; ++i) {
        auto xVal = x.back() * i / static_cast<double>(nPoints);
        fileOut2 << xVal << " " << hermitCubicInterpolation.getInterpolatedValue(xVal) << " "
                 << hermitCubicInterpolation.getInterpolatedSpeed(xVal) << " "
                 << hermitCubicInterpolation.getInterpolatedAcceleration(xVal) << " "
                 << hermitCubicInterpolation.getInterpolatedJerk(xVal) << "\n";
    }

    // во второй файл выводятся опорные точки интерполяции: x, f(x), f'(x)
    std::ofstream fileIn2("../../data/cubic/test-hermite.in");
    for (int i = 0; i < x.size(); ++i)
        fileIn2 << x.at(i) << " " << y.at(i) << " "
                << hermitCubicInterpolation.getSpline()->getDY().at(i) << "\n";

    return 0;
}