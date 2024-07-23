#ifndef S21_DEPOSIT_CONTROLLER_H
#define S21_DEPOSIT_CONTROLLER_H

#include "../model/s21_deposit_model.h"
#include "s21_calc_controller.h"

namespace s21 {
/**
 * @brief Класс определяющий контроллер депозитного калькулятора
 */
class DepositController : public CalcController {
 private:
  DepositModel* deposit_model = nullptr;
  DepositModel::output res = {};

 public:
  DepositModel::StackNode* add = nullptr;
  DepositModel::StackNode* with = nullptr;

  const int kmonthly = DepositModel::MONTHLY;
  const int kyearly = DepositModel::YEARLY;

 public:
  DepositController() = delete;
  DepositModel::InputStr str;
  /**
   * @brief Конструктор контроллера от модели
   * @param model адрес модели
   */
  explicit DepositController(DepositModel* model)
      : CalcController(model), deposit_model(model){};

  /**
   * @brief Метод производящий вычисления
   * @param str структура с исходными данными
   * @param add стэк с пополнениями
   * @param with стэк со снятиями
   * @return код ошибки 0 - error, 1 - correct
   */
  int Deposit();

  /**
   * @brief Геттер
   * @return данные
   */
  s21::DepositModel::output GetDepositData();

  /**
   * @brief Добавление данных во внутренний стэк добавлений
   */
  void PushToStackAdd(double add_sum, double add_month);

  /**
   * @brief Добавление данных во внутренний стэк добавлений
   */
  void PushToStackWith(double add_sum, double add_month);

  /**
   * @brief Очистка стэков
   */
  void PopAndClearStack();

  /**
   * @brief Сортировка и преобразование стеков
   */
  void SortAndTransformStack();

  /**
   * @brief Метод обнуляющий значение результата в классе
   */
  void ResetDepositData();
};
}  // namespace s21

#endif  // S21_DEPOSIT_CONTROLLER_H