#ifndef S21_CALC_CONTROLLER_H
#define S21_CALC_CONTROLLER_H

#include <vector>

#include "../model/s21_calc_model.h"

namespace s21 {
/**
 * @brief Класс определяющий контроллер калькулятора
 */
class CalcController {
 private:
  CalcModel* calc_model = nullptr;
  double res = 0;

 public:
  CalcController() = delete;
  /**
   * @brief Конструктор контроллера от модели
   * @param model адрес модели
   */

  CalcController(CalcModel* model) : calc_model(model) {}

  /**
   * @brief Метод производящий вычисления
   * @param initial введенная строка
   * @param x введенное значение x
   * @return код ошибки 0 - error, 1 - correct
   */
  int Calc(const char* initial, const char* x);

  /**
   * @brief Геттер
   * @return данные
   */
  double GetCalcData();
  /**
   * @brief Метод для построения графика
   * @param x_begin начало разбиения по x
   * @param x_end конец разбиения по x
   * @param x вектор координат по x
   * @param y вектор координат по y
   * @param str функция y(x)
   * @return код ошибки 0 - error, 1 - correct
   */
  int GraphCalc(int x_begin, int x_end, std::vector<double>& x,
                std::vector<double>& y, const char* str);

  /**
   * @brief Метод обнуляющий значение результата в классе
   */
  void ResetCalcData();

  /**
   * @brief Метод для считывания и проверки поступившего X
   * @param initial строка введенная в поле X
   * @param value переменная для числа
   * @return код ошибки 0 - error, 1 - correct
   */
  int XReader(const char* initial, double* value);
};
}  // namespace s21

#endif  // S21_CALC_CONTROLLER_H