/* Рассчет разницы в днях между двумя датами.
 *
 * @author: Nikolai Kostromitin
 */

#include <iostream>


/* Объявляю функции. Сами ф-ии находятся под ф-ей main() */
bool is_correct_date(int day, int month, int year);
int get_days_diff(int days1, int days2, int year1, int year2);
bool is_leap(int year);

enum { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };


int main() // <- точка входа в программу
{
    using namespace std;

    const int avg_days_in_month = 30; // количество дней в месяце, в среднем

    int total_days[2] = {}; // число дней с начала года до текущей даты. Для 2 дат.
    // {} - списковая инициализация. Забили массив дефолтными значениями, в данном случае - нулями.

    int day, month;
    int years[2] = {}; // года мне пригодятся за циклом.

    /* В цикле просто считаю число дней с начала года до каждой из дат включительно,
     * потом считаю разницу между ними. Всё. */
    for (int i = 0; i < 2; ++i) { // повторяем для 2 дат
        cout << "Введите дату:    ";
        cin >> day >> month >> years[i];

        if (!is_correct_date(day, month, years[i]))
            return 1; // просто взял и вышел, если дата некорректна. Имею право.

        total_days[i] = day + (month - 1) * avg_days_in_month; // (month - 1) чтобы не учитывать текущий месяц

        if (month > FEB) {
            total_days[i] -= 2; // убираем 2 февральских дня
            if (is_leap(years[i]))
                ++total_days[i]; // добавил обратно 1 февральский день
        }

        total_days[i] += month / 2; // учитываем месяцы с 31 днями
        if (month == NOV) // ноябрь - особый случай (до него было (11/2 + 1) месяцев по 31 дню).
            ++total_days[i];


//#define DEBUG
#ifdef DEBUG // для отладки программы.
        // чтобы увидеть эти сообщения, раскомментируйте #define DEBUG
        cout << "DEBUG:\t";
        cout << "total_days = " << total_days[i] << endl;
#endif
    }

    int days_diff = get_days_diff(total_days[0], total_days[1], years[0], years[1]);
    cout << "\nРазница в днях: " << days_diff << endl;
}


/* Определения функций находятся здесь */


/* Проверка даты на корректность
 */
bool is_correct_date(int d, int m, int y)
{
    if (d <= 0 || m <= 0 || y <= 0 || d > 31 || m > 12)
        return false;

    if (m == FEB)
        return is_leap(y) ? m == 29 : m == 28;

    if (m % 2 == 0) {
        // до августа у четных месяцев - 30 дней
        if (m < AUG && d > 30)
            return false;
    } else {
        // после августа у нечетных месяцев - 30 дней
        if (m > AUG && d > 30)
            return false;
    }

    // если дошли досюда, значит дата корректна (по крайней мере, я на это надеюсь).
    return true;
}

/* Вычисляет разницу дней между двумя датами.
 * Каждая дата представлена в виде количества дней, прошедших с начала года, до этой даты включительно.
 */
int get_days_diff(int days1, int days2, int year1, int year2)
{
    int days_diff = 0;
    int years_diff = year2 - year1;

    if (years_diff == 0)
        days_diff = days2 - days1;
    else {
        days_diff = 365 - days1 + days2;
        if (is_leap(year1))
            ++days_diff;

        for (int i = year1 + 1; i < year2; ++i) {
            days_diff += 365;
            if (is_leap(i))
                ++days_diff;
        }
    }

    return days_diff;
}

/* Определяет, является ли год високосным
 * true  - год високосный
 * false - год невисокосный
 */
bool is_leap(int year) {
    return year % 400 == 0 ||
          (year % 4 == 0 && year % 100 != 0);
}
