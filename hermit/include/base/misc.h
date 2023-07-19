#pragma once

#include <cstdlib>

/**
 * Получить случайное вещественное число из заданного диапазона
 * @param lower_bound - нижняя граница
 * @param upper_bound - верхняя граница
 * @return случайное вещественное число
 */
static double randDouble(double lower_bound, double upper_bound) {
    const long max_rand = 1000000L;
    // Using random function to
    // get random double value
    return lower_bound
           + (upper_bound - lower_bound)
             * (std::rand() % max_rand)
             / max_rand;
}

/**
 * Получить случайное целое число из заданного диапазона
 * @param lower_bound - нижняя граница
 * @param upper_bound - верхняя граница
 * @return случайное целое число
 */
static int randInt(int lower_bound, int upper_bound) {
    return lower_bound + (std::rand() % (upper_bound - lower_bound));
}


