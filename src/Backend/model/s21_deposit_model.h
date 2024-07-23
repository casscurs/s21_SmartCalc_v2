#ifndef S21_DEPOSIT_MODEL_H
#define S21_DEPOSIT_MODEL_H

#include "s21_calc_model.h"

namespace s21 {

class DepositModel : public CalcModel {
 public:
  using CalcModel::PushStackNode, CalcModel::SortStackByPriority,
      CalcModel::FreeStack, CalcModel::FillFields, CalcModel::StackNode;

  /**
   * @brief Перечисление для кодификации типа вклада
   */
  typedef enum deposit_type {
    MONTHLY = 0,
    YEARLY = 1,
  } deposit_type;

  enum what { ADDITION = 21, WITHRAWAL = 22 };

  /**
   * @brief Структура с входными данными
   */
  typedef struct InputStr {
    const char* deposit_sum_str = nullptr;
    const char* period_str = nullptr;
    const char* percent_str = nullptr;
    int capital = 0;
    int regularity = 0;
  } inputStr;
  /**
   * @brief Структура с выходными данными
   */
  typedef struct Output {
    double percent_award = 0;
    double tax_amount = 0;
    double total_award = 0;
  } output;

  /**
   * @brief Основной метод вызывающий все блоки
   * @param str структура с исходными данными
   * @param add стэк с пополнениями
   * @param with стэк со снятиями
   * @param dep_out результирующая структура
   * @return код ошибки 0 - error, 1 - correct
   */
  int Deposit(inputStr str, StackNode** add, StackNode** with, output* dep_out);

  /**
   * @brief Метод cуммирующий операции в одном месяце
   * @param apex вершина стека
   * @note Стэк на вход подавать отсортированным
   */
  void OperationsInMonth(StackNode** apex);

 private:
  /**
   * @brief Внутренняя структура для входных данных
   */
  typedef struct Input {
    double deposit_sum = 0;
    double period = 0;
    double percent = 0;
    double tax = 0;
  } input;

  /**
   * @brief Метод отвечающий за вычисления
   * @param str структура с исходными данными
   * @param dep_in структура хранящая исходные данные в числовом формате
   * @param dep_out результирующая структура
   * @param add стэк с пополнениями
   * @param with стэк со снятиями
   * @return код ошибки 0 - error, 1 - correct
   */
  int CalcDeposit(inputStr str, input dep_in, output* dep_out, StackNode** add,
                  StackNode** with);
  /**
   * @brief Метод вычисляющий сумму налога
   * @param dep_out результирующая структура
   */
  void Tax(output* dep_out);
};

}  // namespace s21

#endif  // S21_DEPOSIT_MODEL_H