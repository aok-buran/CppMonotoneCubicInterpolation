#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include "base/misc.h"
#include "monotone_cubic_interpolation.h"

/**
 * Главный метод
 * @return код возрата
 */
int main() {
    srand(time(NULL));

    for (int testNum = 0; testNum < 10000; testNum++) {

        int dataSize = randInt(10, 20);

        std::cout << "test " << testNum << " " << dataSize << std::endl;

        using T = double;
        std::vector<T> x(dataSize, 0);
        std::vector<T> y(dataSize, 0);

        x[0] = 0;
        y[0] = randDouble(0, 5);
        for (int i = 1; i < dataSize; i++) {
            y[i] = randDouble(0, 5);
            x[i] = randDouble(0.3, 0.5) + x[i - 1];
        }

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

    }

    return 0;
}