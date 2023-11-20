#include "Date.hpp"
#include <iostream>
#include <ostream>

void Test1() {
  Date d1(2023, 2, 28);
  d1.Print();

  // Date tmp = d1 + 100;
  // d1 = d1 + 100;
  d1 += 100;
  d1.Print();
  // tmp.Print();
  //
  Date d2(2023, 2, 1);
  // std::cout << "day: " << Date::GetMonthDay(2023, 1) << std::endl;
  d2--;

  d2.Print();
  std::cout << d2 << std::endl;
}

void DateAddDay() {
  int flags = 0;
  do {
    Date d;
    long long day = 0;
    std::cout << "请输入起始日期: ";
    std::cin >> d;
    std::cout << "请输入天数: ";
    std::cin >> day;
    d += day;
    std::cout << d << std::endl;
    printf("相差: %ld 天 == %d 个星期 == %d个月%d天\n", day, day / 7, day / 30,
           day % 30);

  } while (flags);
}
void DateSubDay() {
  int flags = 0;
  do {
    Date d;
    long long day = 0;
    std::cout << "请输入起始日期: ";
    std::cin >> d;
    std::cout << "请输入天数: ";
    std::cin >> day;
    d -= day;
    std::cout << d << std::endl;
    printf("相差: %ld 天 == %d 个星期 == %d个月%d天\n", day, day / 7, day / 30,
           day % 30);

  } while (flags);
}

void DateSubDate() {

  int flags = 0;
  do {
    Date d;
    Date d2;
    std::cout << "请输入起始日期: ";
    std::cin >> d;
    std::cout << "请输入日期: ";
    std::cin >> d2;

    long long day = d - d2;

    printf("相差: %ld 天 == %d 个星期 == %d个月%d天\n", day, day / 7, day / 30,
           day % 30);

  } while (flags);
}

void Test2() {
  int flags = 0;
  do {
    printf("************************\n");
    printf("*    1. 加天数测试     *\n");
    printf("*    2. 减天数测试     *\n");
    printf("*    3. 日期减日期测试 *\n");
    printf("*    0. 退出程序       *\n");
    printf("************************\n");
    std::cout << "请选择: ";
    std::cin >> flags;
    if (flags == 1) {
      DateAddDay();
    } else if (flags == 2) {
      DateSubDay();
    } else if (flags == 3) {
      DateSubDate();
    }
    std::cout << "程序退出..." << std::endl;
  } while (flags);
}

int main(int argc, char *argv[]) {
  Test2();
  // Test1();

  return 0;
}
