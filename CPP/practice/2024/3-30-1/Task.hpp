#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <iostream>
#include <string>

enum ERRCode { DivZero = 1, ModZero, UnknownA };

// 这个Task目前做的是一个简单的计算器
// 未来可以扩展为更复杂的计算器
class Task {
   public:
    //  对于这个任务类，我们需要给两个东西
    // 一、运算符重载
    // 二、构造函数

    Task(int operand_x, int operand_y, char oper)
        : _operand_x(operand_x),
          _operand_y(operand_y),
          _operator(oper),
          _code(1) {}

    // 开始计算任务
    void Run() {
        switch (_operator) {
            case '+':
                _reslut = _operand_x + _operand_y;
                _code = 0;
                break;
            case '-':
                _reslut = _operand_x - _operand_y;
                _code = 0;
                break;
            case '*':
                _reslut = _operand_x * _operand_y;
                _code = 0;
                break;

            case '/':
                if (_operand_y == 0) {
                    _reslut = -1;
                    _code = DivZero;
                    return;
                }
                _reslut = _operand_x / _operand_y;
                _code = 0;
                break;

            case '%':
                if (_operand_y == 0) {
                    _reslut = -1;
                    _code = ModZero;
                    return;
                }
                _reslut = _operand_x % _operand_y;

            default:
                // 错误处理
                _reslut = -1;
                _code = UnknownA;
                break;
        }
    }

    void operator()() {
        Run();
    }

    std::string GetTask() {
        std::string str(std::to_string(_operand_x));
        str += " ";
        str += _operator;
        str += " ";
        str += std::to_string(_operand_y);
        str += " = ?";

        return str;
    }

    std::string GetReslut() {
        std::string str(std::to_string(_operand_x));
        str += " ";
        str += _operator;
        str += " ";
        str += std::to_string(_operand_y);
        str += " = ";
        str += std::to_string(_reslut);

        str += " [code: ";
        str += std::to_string(_code);
        str += "]";

        return str;
    }

   private:
    int _operand_x;  // 操作数1
    int _operand_y;  // 操作数2
    char _operator;  // 操作符

    int _reslut;  // 计算完成之后的结果
    int _code;    // 本次计算是是否 success ，成功0，失败非零
};

#endif