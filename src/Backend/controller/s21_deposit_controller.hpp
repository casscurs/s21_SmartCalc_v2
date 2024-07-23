#ifndef S21_DEPOSIT_CONTROLLER_HPP
#define S21_DEPOSIT_CONTROLLER_HPP

#include "../model/s21_deposit_model.hpp"

namespace s21 {
/**
 * @brief Класс определяющий контроллер депозитного калькулятора
 */
class DepositController : public DepositModel {
 private:
  DepositModel* depositModel = nullptr;
  DepositModel::output res = {};

 public:
  using DepositModel::ADDITION, DepositModel::WITHRAWAL;
  using DepositModel::MONTHLY, DepositModel::YEARLY;
  using DepositModel::output, DepositModel::inputStr;

  DepositController() = delete;
  /**
   * @brief Конструктор контроллера от модели
   * @param model адрес модели
   */
  explicit DepositController(DepositModel* model) : depositModel(model){};

  /**
   * @brief Метод производящий вычисления
   * @param str структура с исходными данными
   * @param add стэк с пополнениями
   * @param with стэк со снятиями
   * @return код ошибки 0 - error, 1 - correct
   */
  int deposit(inputStr str, StackNode** add, StackNode** with);

  /**
   * @brief Геттер
   * @return данные
   */
  s21::DepositModel::output getDepositData();

  /**
   * @brief Метод обнуляющий значение результата в классе
   */
  void resetDepositData();
};
}  // namespace s21

#endif  // S21_DEPOSIT_CONTROLLER_HPP