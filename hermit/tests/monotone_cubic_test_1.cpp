#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include "base/misc.h"
#include "monotone_cubic_interpolation.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));

    using T = double;

    // 13 not monotone [0.15751 0.167726 0.157695]
    // [3.94554 4.01354 4.24789]
    std::vector<T> x = {0, 0.302899, 0.606508, 0.908134, 1.21395, 1.51935, 1.81996, 2.12524, 2.42706, 2.73156, 3.03559,
                        3.33916, 3.63975, 3.94554, 4.24789};
    std::vector<T> y = {0.089955, 0.00997, 0.139505, 0.067155, 0.020865, 0.02872, 0.03142, 0.00528, 0.1077, 0.05238,
                        0.000255, 0.02873, 0.00501, 0.15751, 0.157695};

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