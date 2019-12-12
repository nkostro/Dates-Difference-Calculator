/* Calc days difference between two dates.
 *
 * @author: Nikolai Kostromitin
 */

#include <iostream>

bool is_valid_date(int day, int month, int year);
int get_days_diff(int days1, int days2, int year1, int year2);
bool is_leap(int year);

enum { FEB = 2, AUG = 8, SEP = 9, NOV = 11 };


int main()
{
    const int avg_days_in_month = 30; // количество дней в месяце, в среднем
    const int ndates = 2; // число дат

    int total_days[ndates] = {}; // число дней с начала года до текущей даты
    int years[ndates] = {};

    // Вычисление числа дней с начала года до каждой из дат, включительно.
    for (int i = 0; i < ndates; ++i) {
        int day, month, year;
        std::cout << "Input date:    ";
        std::cin >> day >> month >> year;

        years[i] = year;

        if (!is_valid_date(day, month, year))
            return 1;

        total_days[i] = day + (month - 1) * avg_days_in_month;

        if (month > FEB) {
            total_days[i] -= 2; // убираем 2 февральских дня
            if (is_leap(year))
                ++total_days[i]; // добавляем обратно 1 февральский день
        }

        total_days[i] += month / 2; // добавляем месяцы с 31 днями

        /* для сентября и ноября наш способ подсчета числа месяцев с 31 днями
           не работает и нужно добавить +1 месяц
        */
        if (month == SEP || month == NOV)
            ++total_days[i];

#ifdef DEBUG
        std::cout << "DEBUG:\ttotal_days = " << total_days[i] << std::endl;
#endif
    }

    int days_diff = get_days_diff(total_days[0], total_days[1], years[0], years[1]);

    std::cout << "\nDays difference: " << days_diff << std::endl;
}


/* Check date for correctness.
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

/* Check if year is leap.
 */
bool is_leap(int year)
{
    return year % 400 == 0 ||
          (year % 4 == 0 && year % 100 != 0);
}
