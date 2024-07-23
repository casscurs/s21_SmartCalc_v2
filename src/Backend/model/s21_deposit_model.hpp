#ifndef S21_DEPOSIT_MODEL_HPP
#define S21_DEPOSIT_MODEL_HPP

#include "s21_calc_model.hpp"

namespace s21 {

class DepositModel : private CalcModel {
 public:
  using CalcModel::pushStackNode, CalcModel::sortStackByPriority,
      CalcModel::freeStack, CalcModel::fillFields, CalcModel::StackNode;
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
  typedef struct inputStr {
    const char* depositSumStr = nullptr;
    const char* periodStr = nullptr;
    const char* percentStr = nullptr;
    int capital = 0;
    int regularity = 0;
  } inputStr;
  /**
   * @brief Структура с выходными данными
   */
  typedef struct output {
    double percentAward = 0;
    double taxAmount = 0;
    double totalAward = 0;
  } output;

  /**
   * @brief Основной метод вызывающий все блоки
   * @param str структура с исходными данными
   * @param add стэк с пополнениями
   * @param with стэк со снятиями
   * @param depOut результирующая структура
   * @return код ошибки 0 - error, 1 - correct
   */
  int deposit(inputStr str, StackNode** add, StackNode** with, output* depOut);

  /**
   * @brief Метод cуммирующий операции в одном месяце
   * @param apex вершина стека
   * @note Стэк на вход подавать отсортированным
   */
  void operationsInMonth(StackNode** apex);

 private:
  /**
   * @brief Внутренняя структура для входных данных
   */
  typedef struct input {
    double depositSum = 0;
    double period = 0;
    double percent = 0;
    double tax = 0;
  } input;

  /**
   * @brief Метод отвечающий за вычисления
   * @param str структура с исходными данными
   * @param depIn структура хранящая исходные данные в числовом формате
   * @param depOut результирующая структура
   * @param add стэк с пополнениями
   * @param with стэк со снятиями
   * @return код ошибки 0 - error, 1 - correct
   */
  int calcDeposit(inputStr str, input depIn, output* depOut, StackNode** add,
                  StackNode** with);
  /**
   * @brief Метод вычисляющий сумму налога
   * @param depOut результирующая структура
   */
  void tax(output* depOut);
};

}  // namespace s21

#endif  // S21_DEPOSIT_MODEL_HPP