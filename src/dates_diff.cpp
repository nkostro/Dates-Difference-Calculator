/* Calc days difference between two dates.
 *
 * @author: Nikolai Kostromitin
 */

#include <iostream>


bool is_valid_date(int day, int month, int year);
int get_days_from_start_of_year(int day, int month, int year);
int get_days_diff(int days1, int days2, int year1, int year2);
bool is_leap(int year);


int main()
{
    const int ndates = 2;

    int total_days[ndates] = {}; // days number since the beginning of year to each date
    int years[ndates] = {};

    for (int i = 0; i < ndates; ++i) {
        int day, month, year;
        std::cout << "Input date:    ";
        std::cin >> day >> month >> year;

        years[i] = year;

        if (!is_valid_date(day, month, year))
            return 1;

        total_days[i] = get_days_from_start_of_year(day, month, year);

#ifdef DEBUG
        std::cout << "DEBUG:\ttotal_days = " << total_days[i] << std::endl;
#endif
    }

    for (int i = 1; i < ndates; i += 2) {
        int days_diff = get_days_diff(total_days[i-1], total_days[i],
                                      years[i-1], years[i]);
        std::cout << "\nDays difference: " << days_diff << std::endl;
    }
}


enum { FEB = 2, AUG = 8, SEP = 9, NOV = 11 };


/* Check date for correctness.
 */
bool is_valid_date(int d, int m, int y)
{
    if (d <= 0 || m <= 0 || y <= 0 || d > 31 || m > 12)
        return false;

    if (m == FEB)
        return is_leap(y) ? d <= 29 : d <= 28;

    if (m % 2 == 0) {
        if (m < AUG && d > 30) // even months before august have 30 days
            return false;
    } else {
        if (m > AUG && d > 30) // odd months after august have 30 days
            return false;
    }

    return true;
}


/* Get days from beginning of @year.
 *
 * @returns days number from beginning of @year to @day of @month.
 */
int get_days_from_start_of_year(int day, int month, int year)
{
    const int avg_days_in_month = 30;

    int days = day + (month - 1) * avg_days_in_month;

    if (month > FEB) {
        days -= 2; // remove 2 feb days
        if (is_leap(year))
            ++days; // add 1 feb day for leap years
    }

    days += month / 2; // add +1 day for each month with 31 days that preceeds this `month`

    // For september or november we must add +1 additional day.
    if (month == SEP || month == NOV)
        ++days;

    return days;
}


/* Calc days difference between two dates.
 * Each date is represented as number of days passed since the beginning of year
 * to that date inclusive.
 *
 * @returns days difference between two dates.
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
