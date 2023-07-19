#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include "base/misc.h"
#include "monotone_cubic_interpolation.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));

    using T = double;



    // 16 not monotone [0.15482 0.167167 0.157135]
    //  [4.86059 5.04359 5.16446]
    std::vector<T> x = {0, 0.303555, 0.608064, 0.910488, 1.21585, 1.51868, 1.82434, 2.12519, 2.42842, 2.73416, 3.03837,
                        3.34, 3.64154, 3.94706, 4.2535, 4.55791, 4.86059, 5.16446, 5.46927};
    std::vector<T> y = {0.120465, 0.04902, 0.079875, 0.04896, 0.05328, 0.02693, 0.14311, 0.050515, 0.081645, 0.148125,
                        0.11132, 0.08838, 0.02314, 0.10573, 0.15767, 0.11982, 0.15482, 0.157135, 0.00408};

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