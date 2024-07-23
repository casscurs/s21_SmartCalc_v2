#ifndef S21_CALC_CONTROLLER_HPP
#define S21_CALC_CONTROLLER_HPP

#include <vector>

#include "../model/s21_calc_model.hpp"

namespace s21 {
/**
 * @brief Класс определяющий контроллер калькулятора
 */
class CalcController : private CalcModel {
 private:
  CalcModel* calcModel = nullptr;
  double res = 0;

 public:
  CalcController() = delete;
  using CalcModel::readX;
  /**
   * @brief Конструктор контроллера от модели
   * @param model адрес модели
   */
  explicit CalcController(CalcModel* model) : calcModel(model) {}

  /**
   * @brief Метод производящий вычисления
   * @param initial введенная строка
   * @param x введенное значение x
   * @return код ошибки 0 - error, 1 - correct
   */
  int calc(const char* initial, const char* x);

  /**
   * @brief Геттер
   * @return данные
   */
  double getCalcData();
  /**
   * @brief Метод для построения графика
   * @param xBegin начало разбиения по x
   * @param xEnd конец разбиения по x
   * @param x вектор координат по x
   * @param y вектор координат по y
   * @param str функция y(x)
   * @return код ошибки 0 - error, 1 - correct
   */
  int graphCalc(int xBegin, int xEnd, std::vector<double>& x,
                std::vector<double>& y, const char* str);

  /**
   * @brief Метод обнуляющий значение результата в классе
   */
  void resetCalcData();
};
}  // namespace s21

#endif  // S21_CALC_CONTROLLER_HPP