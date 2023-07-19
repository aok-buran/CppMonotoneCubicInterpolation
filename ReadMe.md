## Монотонная кубическая интерполяция


Монотонная интерполяция кубическими полиномами с помощью алгоритма,
описанного в [статье](https://epubs.siam.org/doi/10.1137/0717021)
Fritsch, F. N.; Carlson, R. E. (1980). "Monotone Piecewise Cubic Interpolation".
SIAM Journal on Numerical Analysis. SIAM. 17 (2): 238–246.

![](img/title.png)


### Структура библиотеки

Исходники программы для сравнивания обычной кубической интерполяции
и монотонной лежат в `hermit\demo\hermite_demo.cpp`

Эта программа формирует случайные опорные точки ( `x` и `y` координаты),
после чего создаёт обычный кубический интерполятор и монотонный.

Для каждого интерполятора перебирается заданное количество значений
от первой до последней координат `x` с равным шагом. Для каждого
аргумента вычисляются значение интерполированной функции, а также
первые три её производные: скорость(speed), усорение(acceleration) и рывок(jerk).

Результаты записываются в 4 файла в папке `data\cubic\source`:
- `test-hermit.in` опорные точки траектории при обычной кубической интерполяции
- `test-hermit.out` интерполированные данные при обычной кубической интерполяции
- `test-monotone.in` опорные точки траектории при монотонной кубической интерполяции
- `test-monotone.out` интерполированные данные при монотонной кубической интерполяции

В папке `matlab` лежат скрипты на этом языке для создания графиков
интерполированных данных:
- `f_my_plot.m` - вспомогательная функция для рисования графиков
- `plot_results.m` - непосредственный скрипт, создающий три графика

графики сохраняются в папку `matlab/out`

### Тесты

Чтобы запустить тесты в `CLion`, нужно 

Выбрать пункт `Edit Configuraions...`

![](img/i1.png)

После этого нажать на `+`

![](img/i2.png)

И выбрать `CTest Application`

![](img/i3.png)
