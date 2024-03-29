#ifndef __DATE_HPP__
#define __DATE_HPP__
#include <assert.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>

class Date {
public:
  friend std::ostream &operator<<(std::ostream &out, const Date &d);
  friend std::istream &operator>>(std::istream &in, Date &d);
  // 默认构造
  Date(long long year = 1, short month = 1, short day = 1) {
    if (month <= 0 || month > 12) {
      std::cerr << "非法输入!, 月份不合法, month: " << month << std::endl;
      exit(1);
    } else {
      if (day < 1 || day > GetMonthDay(year, month)) {
        std::cerr << "非法输入!, 天数不合法, day: " << day << std::endl;
        exit(1);
      }
    }

    _year = year;
    _month = month;
    _day = day;
  }

  Date(Date &&) = default;
  Date(const Date &d1) { Swap(d1); }
  Date &operator=(const Date &d1) {
    Swap(d1);

    return *this;
  }

  ~Date() {}

  static short GetMonthDay(long long year, short month) {
    static const short month_arr[13]{0,  31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};
    short day = month_arr[month];

    // 1. 只有是 2 月份才需要判断是否是闰年
    // 2. 闰年的判断规则：
    //    2.1 普通年能被 4 整除且普通年不能被 100 整除
    //    2.2 世纪年能被 400 整除的就是闰年， 如 2000 年是闰年而 1900 年不是闰年
    if (month == 2 && ((!(year % 4) && year % 100) || !(year % 400))) {
      day++;
    }

    return day;
  }

  Date &operator++() {
    (*this) += 1;

    return *this;
  }

  Date operator++(int) {
    Date tmp(*this);
    (*this) += 1;

    return tmp;
  }

  Date &operator+=(long long day) {
    if (day < 0) {
      return *this -= -day;
    }

    long long day_tmp = _day;
    // _day += day;
    // while (_day > GetMonthDay(_year, _month)) {
    //   _day -= GetMonthDay(_year, _month);
    //   _month++;
    //   if (_month == 13) {
    //     ++_year;
    //     _month = 1;
    //   }
    // }

    // 因为 _day 是 short 类型会溢出所以先用 day_tmp 去计算好再放入
    day_tmp += day;
    while (day_tmp > GetMonthDay(_year, _month)) {
      day_tmp -= GetMonthDay(_year, _month);
      _month++;
      if (_month == 13) {
        ++_year;
        _month = 1;
      }
    }

    _day = day_tmp;

    return *this;
  }

  Date operator+(long long day) {
    Date tmp(*this);
    tmp += day;

    return tmp;
  }

  Date &operator--() {
    (*this) -= 1;

    return *this;
  }

  Date operator--(int) {
    Date tmp(*this);

    (*this) -= 1;

    return tmp;
  }

  Date &operator-=(long long day) {
    if (day < 0) {
      return *this += -day;
    }

    long long day_tmp = _day;
    day_tmp -= day;
    // _day -= day;
    //
    // while (_day <= 0) {
    //   --_month;
    //   if (_month == 0) {
    //     _month = 12;
    //     _year--;
    //   }
    //
    //   _day += GetMonthDay(_year, _month);
    // }

    // 因为 _day 是 short 类型会溢出所以先用 day_tmp 去计算好再放入
    while (day_tmp <= 0) {
      --_month;
      if (_month == 0) {
        _month = 12;
        _year--;
      }

      day_tmp += GetMonthDay(_year, _month);
    }

    _day = day_tmp;

    return *this;
  }

  Date operator-(long long day) {
    Date tmp(*this);
    tmp -= day;

    return tmp;
  }

  long long operator-(const Date &d) {
    long long day = DateSubDate(d);

    return day;
  }

  long long DateSubDate(const Date &d) {
    Date max_date(*this);
    Date min_date(d);
    if ((*this) < d) {
      max_date = d;
      min_date = (*this);
    }

    long long day = 0;
    while (max_date != min_date) {
      day++;
      min_date++;
    }

    return day;
  }

  bool operator==(const Date &d) {
    return (_year == d._year) && (_month == d._month) && (_day == d._day);
  }

  bool operator!=(const Date &d) { return !((*this) == d); }

  bool operator<(const Date &d) {
    if (_year != d._year) {
      return _year < d._year;
    }

    if (_month != d._month) {
      return _month < d._month;
    }

    return _day < d._day;
  }

  static void Print(long long day) {
    long long day_tmp = day;
    long long year_tmp = day_tmp / 365;
    day_tmp %= 365;
    short month_tmp = day_tmp / 30;
    day_tmp %= 30;

    printf("相差: %ld 天 == %d 个星期 == %d个月%d天 == %ld年%d个月%d天\n",
           abs(day), abs(day / 7), abs(day / 30), abs(day % 30), abs(year_tmp),
           abs(month_tmp), abs(day_tmp));
  }

  bool operator>(const Date &d) { return !((*this) <= d); }

  bool operator<=(const Date &d) { return (*this) < d || (*this) == d; }

  bool operator>=(const Date &d) { return !((*this) < d); }

  void Swap(const Date &d1) {
    _year = d1._year;
    _month = d1._month;
    _day = d1._day;
  }

  void Print() { printf("%ld年%d月%d日\n", _year, _month, _day); }

private:
  long long _year;
  short _month;
  short _day;
};

std::ostream &operator<<(std::ostream &out, const Date &d) {
  out << d._year << "年" << d._month << "月" << d._day << "日" << std::endl;

  return out;
}

std::istream &operator>>(std::istream &in, Date &d) {
  long long year;
  short month;
  short day;

  in >> year >> month >> day;

  if (month > 0 && month < 13) {
    d._year = year;
    d._month = month;
    d._day = day;
  } else {
    std::cerr << "非法日期" << std::endl;
    assert(false);
  }

  return in;
}

#endif // !__DATE_HPP__
