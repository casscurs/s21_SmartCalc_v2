#ifndef S21_CREDIT_MODEL_HPP
#define S21_CREDIT_MODEL_HPP

#include "s21_calc_model.hpp"

namespace s21 {
/**
 * @brief Класс определяющий модель кредитного калькулятора
 */
class CreditModel : private CalcModel {
 public:
  /**
   * @brief Структура хранящая значения конечный параметров
   */
  typedef struct creditRes {
    double monthly = 0;
    double overpay = 0;
    double total = 0;
    double* valArr = nullptr;
  } creditRes;

  /**
   * @brief Перечисление для кодификации типа кредита
   */
  typedef enum credit_type {
    DIFFERENTIATED = 0,
    ANNUITY = 1,
  } credit_type;

  /**
   * @brief Основной метод кредитного калькулятора
   * @param sumStr строка содержащая сумму кредита
   * @param periodStr строка содержащая срок кредита
   * @param percentStr строка содержащая процентную ставку кредита
   * @param type переменная хранящая кодификатор типа кредита
   * @param res результирующая структура
   * @return код ошибки 0 - error, 1 - correct
   */
  int credit(const char* sumStr, const char* periodStr, const char* percentStr,
             int type, creditRes* res);

  /**
   * @brief Метод необходимый для очистики массива после вывода информации
   * @param myStruct адрес структуры для вывода данных
   */
  void freeValArr(creditRes* myStruct) {
    if ((myStruct)->valArr != nullptr) free((myStruct)->valArr);
  }

 private:
  /**
   * @brief Структура хранящая значения начальных параметров
   */
  typedef struct creditParam {
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
  void calcCredit(creditParam param, creditRes* res, int type);
};

}  // namespace s21

#endif  // S21_CREDIT_MODEL_HPP