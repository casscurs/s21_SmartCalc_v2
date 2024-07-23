#ifndef S21_CREDIT_MODEL_H
#define S21_CREDIT_MODEL_H

#include "s21_calc_model.h"

namespace s21 {
/**
 * @brief Класс определяющий модель кредитного калькулятора
 */
class CreditModel : public CalcModel {
 public:
  /**
   * @brief Структура хранящая значения конечный параметров
   */
  typedef struct CreditRes {
    double monthly = 0;
    double overpay = 0;
    double total = 0;
    double* valArr = nullptr;
  } creditRes;

  /**
   * @brief Перечисление для кодификации типа кредита
   */
  typedef enum Credit_type {
    DIFFERENTIATED = 0,
    ANNUITY = 1,
  } credit_type;

  /**
   * @brief Основной метод кредитного калькулятора
   * @param sumStr строка содержащая сумму кредита
   * @param period_str строка содержащая срок кредита
   * @param percent_str строка содержащая процентную ставку кредита
   * @param type переменная хранящая кодификатор типа кредита
   * @param res результирующая структура
   * @return код ошибки 0 - error, 1 - correct
   */
  int Credit(const char* sumStr, const char* period_str,
             const char* percent_str, int type, creditRes* res);

  /**
   * @brief Метод необходимый для очистики массива после вывода информации
   * @param myStruct адрес структуры для вывода данных
   */
  void FreeValArr(creditRes* myStruct) {
    if ((myStruct)->valArr != nullptr) free((myStruct)->valArr);
  }

 private:
  /**
   * @brief Структура хранящая значения начальных параметров
   */
  typedef struct CreditParam {
    double sum = 0;
    double period = 0;
    double percent = 0;
  } creditParam;
  /**
   * @brief Метод содержащий матечатический блок
   * @param param структура с входными данными
   * @param res указатель на результирующую строку
   * @param type переменная хранящая кодификатор типа кредита
   */
  void CalcCredit(creditParam param, creditRes* res, int type);
};

}  // namespace s21

#endif  // S21_CREDIT_MODEL_HPP