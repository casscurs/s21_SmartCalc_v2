#ifndef S21_CREDIT_CONTROLLER_H
#define S21_CREDIT_CONTROLLER_H

#include "../model/s21_credit_model.h"
#include "s21_calc_controller.h"

namespace s21 {
/**
 * @brief Класс определяющий контроллер кредитного калькулятора
 */
class CreditController : public CalcController {
 private:
  CreditModel* credit_model = nullptr;
  CreditModel::creditRes res = {};

 public:
  const int kannuity = CreditModel::ANNUITY;
  const int kdiff = CreditModel::DIFFERENTIATED;

  CreditController() = delete;
  /**
   * @brief Конструктор контроллера от модели
   * @param model адрес модели
   */
  explicit CreditController(CreditModel* model)
      : CalcController(model), credit_model(model){};

  /**
   * @brief Деструктор объекта класса кредитного контроллера
   */
  ~CreditController();

  /**
   * @brief Метод контроллера производящий вычисления
   * @param sum_str строка содержащая сумму кредита
   * @param period_str строка содержащая срок кредита
   * @param percent_str строка содержащая процентную ставку кредита
   * @param type переменная хранящая кодификатор типа кредита
   * @return код ошибки 0 - error, 1 - correct
   */
  int Credit(const char* sum_str, const char* period_str,
             const char* percent_str, int type);

  /**
   * @brief Геттер
   * @return данные
   */
  s21::CreditModel::creditRes GetCreditData();

  /**
   * @brief Метод обнуляющий значение результата в классе
   */
  void ResetCreditData();

  /**
   * @brief Метод очищающий массив для вывода данных
   */
  void FreeCreditArr();
};
}  // namespace s21

#endif  // S21_CREDIT_CONTROLLER_H