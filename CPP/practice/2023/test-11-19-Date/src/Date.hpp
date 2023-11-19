#ifndef __DATE_HPP__
#define __DATE_HPP__
#include <cstdint>
#include <iostream>
#include <iterator>

static const short month_arr[13]{0,  31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};

class Date {
public:
  // 默认构造
  Date(long long year = 1, short month = 1, short day = 1) {
    if (month <= 0 || month > 12) {
      std::cerr << "非法输入!, 月份不合法" << std::endl;
      exit(1);
    } else {
      if (day != GetMonthDay(year, month)) {
        std::cerr << "非法输入!, 天数不合法" << std::endl;
        exit(1);
      }
    }
  }

  Date(Date &&) = default;
  Date(const Date &d1) { Swap(d1); }
  Date &operator=(const Date &d1) {
    Swap(d1);

    return *this;
  }

  ~Date() {}

  static short GetMonthDay(long long year, short month) {
    short day = month_arr[month];

    if (month == 2 && ((!year % 4 && year % 100) || !year % 400)) {
      day++;
    }

    return day;
  }

  void Swap(const Date &d1) {
    _year = d1._year;
    _month = d1._month;
    _day = d1._day;
  }

private:
  long long _year;
  short _month;
  short _day;
};

#endif // !__DATE_HPP__
