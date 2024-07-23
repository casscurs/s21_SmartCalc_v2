#ifndef S21_CREDIT_CONTROLLER_HPP
#define S21_CREDIT_CONTROLLER_HPP

#include "../model/s21_credit_model.hpp"

namespace s21 {
/**
 * @brief Класс определяющий контроллер кредитного калькулятора
 */
class CreditController : CreditModel {
 private:
  CreditModel* creditModel = nullptr;
  CreditModel::creditRes res = {};

 public:
  using CreditModel::ANNUITY;
  using CreditModel::creditRes;
  using CreditModel::DIFFERENTIATED;

  CreditController() = delete;
  /**
   * @brief Конструктор контроллера от модели
   * @param model адрес модели
   */
  explicit CreditController(CreditModel* model) : creditModel(model){};

  /**
   * @brief Деструктор объекта класса кредитного контроллера
   */
  ~CreditController();

  /**
   * @brief Метод контроллера производящий вычисления
   * @param sumStr строка содержащая сумму кредита
   * @param periodStr строка содержащая срок кредита
   * @param percentStr строка содержащая процентную ставку кредита
   * @param type переменная хранящая кодификатор типа кредита
   * @return код ошибки 0 - error, 1 - correct
   */
  int credit(const char* sumStr, const char* periodStr, const char* percentStr,
             int type);

  /**
   * @brief Геттер
   * @return данные
   */
  s21::CreditModel::creditRes getCreditData();

  /**
   * @brief Метод обнуляющий значение результата в классе
   */
  void resetCreditData();

  /**
   * @brief Метод очищающий массив для вывода данных
   */
  void freeCreditArr();
};
}  // namespace s21

#endif  // S21_CREDIT_CONTROLLER_HPP