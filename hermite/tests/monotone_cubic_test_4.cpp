#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include "base/misc.h"
#include "monotone_cubic_interpolation.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));

    using T = double;



    // 12 not monotone [0.066095 0.0498123 0.059835]
    //[3.64426 3.80326 3.94823]
    std::vector<T> x = {0, 0.304698, 0.60859, 0.915105, 1.21965, 1.52405, 1.83045, 2.13267, 2.43548, 2.73558, 3.03785,
                        3.34159, 3.64426, 3.94823, 4.25365};
    std::vector<T> y = {0.141935, 0.05861, 0.130945, 0.00348, 0.121755, 0.024305, 0.085175, 0.05605, 0.108705, 0.0602,
                        0.11156, 0.06305, 0.066095, 0.059835, 0.159445};

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