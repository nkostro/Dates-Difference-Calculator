/* Рассчет разницы в днях между двумя датами.
 *
 * @author: Nikolai Kostromitin
 */

#include <iostream>


/* Объявляю функции. Сами ф-ии находятся под ф-ей main() */
bool is_valid_date(int day, int month, int year);
int get_days_diff(int days1, int days2, int year1, int year2);
bool is_leap(int year);

enum { FEB = 2, AUG = 8, SEP = 9, NOV = 11 };


int main() // <- точка входа в программу
{
    const int avg_days_in_month = 30; // количество дней в месяце, в среднем

    int total_days[2] = {}; // число дней с начала года до текущей даты. Для 2 дат.
    // {} - списковая инициализация. Забили массив дефолтными значениями, в данном случае - нулями.

    int years[2] = {}; // года мне пригодятся за циклом

    // В цикле просто вычисляю число дней с начала года до каждой из дат, включительно.
    for (int i = 0; i < 2; ++i) { // повторяем для 2 дат
        int day, month, year; // эти переменные видны только внутри цикла
        std::cout << "Введите дату:    ";
        std::cin >> day >> month >> year;

        years[i] = year;

        if (!is_valid_date(day, month, year))
            return 1; // просто взял и вышел, если дата некорректна. Имею право.

        total_days[i] = day + (month - 1) * avg_days_in_month;

        if (month > FEB) {
            total_days[i] -= 2; // убираем 2 февральских дня
            if (is_leap(year))
                ++total_days[i]; // добавляем обратно 1 февральский день
        }

        total_days[i] += month / 2; // добавляем месяцы с 31 днями
        if (month == SEP || month == NOV) // 2 особых случая
            ++total_days[i];

//#define DEBUG // отладочная инфа
#ifdef DEBUG
        // чтобы увидеть эти сообщения, раскомментируйте #define DEBUG
        std::cout << "DEBUG:\ttotal_days = " << total_days[i] << std::endl;
#endif
    }

    int days_diff = get_days_diff(total_days[0], total_days[1], years[0], years[1]);

    std::cout << "\nРазница в днях: " << days_diff << std::endl;
} // <- точка выхода из программы


/* Определения функций находятся здесь */


/* Проверка даты на корректность
 */
bool is_valid_date(int d, int m, int y)
{
    if (d <= 0 || m <= 0 || y <= 0 || d > 31 || m > 12)
        return false;

    if (m == FEB)
        return is_leap(y) ? d <= 29 : d <= 28;

    if (m % 2 == 0) {
        if (m < AUG && d > 30) // у четных месяцев перед августом - 30 дней
            return false;
    } else {
        if (m > AUG && d > 30) // у нечетных месяцев после августа - 30 дней
            return false;
    }

    // Если мы здесь - значит дата корректна (по крайней мере, я на это надеюсь)
    // (корректность февральских дат проверяется выше)
    return true;
}

/* Вычисляет разницу дней между двумя датами.
 * Каждая дата представлена в виде количества дней, прошедших с начала года,
 * до этой даты включительно.
 */
int get_days_diff(int days1, int days2, int year1, int year2)
{
    int days_diff = days2 - days1;

    for (int i = year1; i < year2; ++i) {
        days_diff += 365;
        if (is_leap(i))
            ++days_diff;
    }

    return days_diff;
}

/* Определяет, является ли год високосным.
 */
bool is_leap(int year)
{
    return year % 400 == 0 ||
          (year % 4 == 0 && year % 100 != 0);
}
