#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include "base/misc.h"
#include "monotone_cubic_interpolation.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));

    using T = double;

    // 14 not monotone [0.14365 0.153921 0.14388]
    //[4.23689 4.31489 4.54277]
    //0.0102709 0.0100409
    std::vector<T> x = {0, 0.300501, 0.603501, 0.904478, 1.20483, 1.50886, 1.81487, 2.1194, 2.4232, 2.72523, 3.02532,
                        3.32891, 3.63402, 3.93523, 4.23689, 4.54277};
    std::vector<T> y = {0.11389, 0.13829, 0.09084, 0.10592, 0.105005, 0.162845, 0.16277, 0.018305, 0.12811, 0.13143,
                        0.11418, 0.083345, 0.12726, 0.001105, 0.14365, 0.14388};

    MonotoneCubicInterpolation tester(x.data(), y.data(), x.size());
    // проверяем интерполяцию опорных точек
    for (int i = 0; i < x.size(); i++) {
        assert(std::abs(tester.getInterpolatedValue(x[i]) - y[i]) < 0.0001);
    }
    // проверяем монотонность в промежуточных значениях
    for (int i = 0; i < x.size() - 1; i++) {
        //    std::cout << x[i] << " " << x[i + 1] << std::endl;
        for (double j = x[i]; j < x[i + 1]; j += 0.001) {

            double d1 = tester.getInterpolatedValue(j) - y[i];
            if (std::abs(d1) < 0.01)
                d1 = 0;

            double d2 = tester.getInterpolatedValue(j) - y[i + 1];
            if (std::abs(d2) < 0.01)
                d2 = 0;

            // проверяем, что интерполированные промежуточные значения
            // лежат между y_i и _y{i-1}, это будет выполнено тогда
            // и только тогда, когда разности будут иметь разный знак
            if (d1 * d2 > 0) {
                std::cout << i << " not monotone [" << y[i] << " " << tester.getInterpolatedValue(j) <<
                          " " << y[i + 1] << "] " << std::endl;
                std::cout << "[" << x[i] << " " << j << " " << x[i + 1] << "] " << std::endl;
                std::cout << tester.getInterpolatedValue(j) - y[i] << " " << tester.getInterpolatedValue(j) - y[i + 1] << std::endl;

                for (double v: x)
                    std::cout << v << " ";

                std::cout << std::endl;
                for (double v: y)
                    std::cout << v << " ";

                std::cout << std::endl;

                assert(false);
            }
        }
    }
    return 0;
}