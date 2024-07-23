#ifndef S21_CALC_MODEL_HPP
#define S21_CALC_MODEL_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmath>
#include <iostream>

#include "s21_exception.hpp"

namespace s21 {

/**
 * @brief Класс определяющий модель калькулятора
 */
class CalcModel {
 public:
  /**
   * @brief Основной метод вызывающий все блоки
   * @param initial введенная строка
   * @param res результат вычислений
   * @return код ошибки 0 - error, 1 - correct
   */
  int calc(const char* initial, const char* x, double* res);

  /**
   * @brief Метод для считывания и проверки поступившего X
   * @param initial строка введенная в поле X
   * @param value переменная для числа
   * @return код ошибки 0 - error, 1 - correct
   */
  int readX(const char* initial, double* value);

 protected:
  /**
   * @brief Структура включающая все необхомые переменные для работы со стэком
   */
  typedef struct StackNode {
    int what = 0;
    int priority = 0;
    double value = 0;
    struct StackNode* next = nullptr;
  } StackNode;

  /**
   * @brief Перечисление для кодификации операций
   */
  typedef enum what {
    INITIA = 0,
    NUMBER = 1,
    X = 2,
    PLUS = 3,
    MINUS = 4,
    DIV = 5,
    MOD = 6,
    MULT = 7,
    POW = 8,
    SIN = 9,
    COS = 10,
    TAN = 11,
    ACOS = 12,
    ASIN = 13,
    ATAN = 14,
    SQRT = 15,
    LN = 16,
    LOG = 17,
    BRACKET_O = 18,
    BRACKET_C = 19,
    MINUS_X = 20
  } what;

  /**
   * @brief Перечисление для выставления приоретата математаческим операциям
   */
  typedef enum priority {
    NUMB = 0,
    ASUB = 1,
    MDM = 2,
    STEP = 3,
    FUNC = 4,
  } priority;

  /**
   * @brief Перечисление для корректной обработки возвратов из функций
   */
  typedef enum codes {
    XCOMING = -1,
    ERROR = 0,
    CORRECT = 1,
  } codes;

  /* Функции для работы со stack */

  /**
   * @brief Метод осуществляющий добавление элемента в стэк
   * @param apex указатель на вершину
   * @return указатель указатель на новую вершину
   */
  StackNode* pushStackNode(StackNode* apex);
  /**
   * @brief Метод осуществляющий удаление элемента с вершины стэка
   * @param apex указатель на вершину
   * @return указатель указатель на новую вершину
   */
  StackNode* popStackNode(StackNode* apex);
  /**
   * @brief Полное удаление стэка
   * @param apex указатель на вершину
   */
  void freeStack(StackNode* apex);
  /**
   * @brief Метод осуществляющий сортировку стэка по полю priority
   * @param apex адрес указателя на вершину
   */
  void sortStackByPriority(StackNode** apex);

  /* Функции валидатора */

  /**
   * @brief Метод осуществляющий полную проверку и форматирование исходной
   * строки
   * @param str указатель на исходную строку
   * @param res указатель на отформатированную строку
   * @return код ошибки 0 - error, 1 - correct
   */
  int checker(const char* str, char* res);

  /**
   * @brief Метод осуществляющий синтаксическую проверку строки
   * @param str указатель на строку
   * @return код ошибки 0 - error, 1 - correct
   */
  int checkSymbol(char* str);

  /**
   * @brief Метод форматирующий строку, выполняет предварительную проверку
   * синтаксиса
   * @param str указатель на исходную строку
   * @param res указатель на результирующую строку
   * @return код ошибки 0 - error, 1 - correct
   */
  int spacesBrackets(const char* str, char* res);

  /**
   * @brief Метод проверяющий правильность написания имен функций
   * @param str указатель на исходную строку
   * @param i указатель на переменную, хранящую позицию символа
   * @param flaf указатель на флаг ошибки
   * @param point параметр отвечающий за валидацию точек в строке
   * @return код ошибки 0 - error, 1 - correct
   */
  int checkLetters(char* str, int* i, int* flaf, int* point);

  /**
   * @brief Метод проверяющий правильность операций и операндов
   * @param str указатель на исходную строку
   * @param i указатель на переменную, хранящую позицию символа
   * @param flaf указатель на флаг ошибки
   * @param point параметр отвечающий за валидацию точек в строке
   * @return код ошибки 0 - error, 1 - correct
   */
  int checkSigns(const char* str, const int* i, int* point, int* flaf);

  /**
   * @brief Метод необходимый для подсчета скобок
   * @param c указатель на исходную строку
   * @param bracket указатель на переменную, валидирующую количество открывающих
   * и закрывающих скобок
   */
  void bracketCounter(char c, int* bracket);

  /**
   * @brief Метод проверяющий операцию MOD
   * @param str указатель на исходную строку
   * @param i указатель на переменную, хранящую позицию символа
   * @param flaf указатель на флаг ошибки
   * @param point параметр отвечающий за валидацию точек в строке
   * @return код ошибки 0 - error, 1 - correct
   */
  int checkMod(char* str, int* i, int* flaf, int* point);

  /**
   * @brief Метод проверяющий строку параметра x
   * @param str указатель на исходную строку
   * @param res указатель на результирующую строку
   * @return код ошибки 0 - error, 1 - correct
   */
  int check_x(const char* str, char* res);

  /**
   * @brief Метод проверяющий синтаксис в строке x
   * @param str указатель на исходную строку
   * @return код ошибки 0 - error, 1 - correct
   */
  int checkSymbol_x(const char* str);

  /* Функции для создания массива лексем */

  /**
   * @brief Метод заполняющий поля лексем для чисел
   * @param lexeme структура хранящая поля
   * @param m итератор по массиву хранящему лексемы
   * @param buf буфферный массив
   * @param k итератор по буфферному массиву
   * @param i итератор по исходной строке
   * @param unar переменная-флаг для унарных операций
   */
  void numbToLexeme(StackNode* lexeme, int* m, char* buf, int* k, int* i,
                    int* unar);

  /**
   * @brief Метод выставляющий значения в полях лексем
   * @param lexeme структура хранящая поля
   * @param pos итератор по массиву хранящему лексемы
   * @param step итератор по строке
   * @param stepVal перескок для итератора по строке
   * @param what значение для поля what
   * @param priority значение для поля priority
   */
  void fillFunc(StackNode* lexeme, int* pos, int* step, int stepVal, int what,
                int priority);

  /**
   * @brief Метод заполняющий поля конкретными значениями
   * @param numbers стэк с числами
   * @param what значение для поля what
   * @param priority значение для поля priority
   * @param value значение для поля value
   */
  void fillFields(StackNode* number, int what, int priority, double value);

  /**
   * @brief Метод заполняющий поля лексем для символов
   * @param lexeme структура хранящая поля
   * @param m итератор по массиву хранящему лексемы
   * @param buf буфферный массив
   * @param k итератор по буфферному массиву
   * @param i итератор по исходной строке
   * @param unar переменная-флаг для унарных операций
   * @param checker переменная-флаг для X
   */
  void signToLexeme(StackNode* lexeme, char* str, int* m, int* i, int* unar,
                    int* checker);

  /**
   * @brief Метод перевода поступившей последователности символов в числовой
   * формат
   * @param buf буфферный массив
   * @param value переменная для числа
   * @param unar переменная-флаг для унарных операций
   */
  void XtoNumb(char* buf, double* value, int* unar);

  /* Вычислительная часть */

  /**
   * @brief Метод выполняющий вычисления
   * @param lexeme массив лексем
   * @param x значение X
   * @return результат вычислений
   */
  double calculating(StackNode* lexeme, double x);

  /**
   * @brief Метод заполняющий массив лексем
   * @param str указатель на строку
   * @param lexeme структура хранящая поля
   * @return код ошибки 0 - error, 1 - correct
   */
  int getLexemsArr(const char* str, StackNode* lexeme);

  /**
   * @brief Метод разделяющий лексемы на 2 стека
   * @param numbers стэк с числами
   * @param signs стэк с операциями
   * @param lexeme массив лексем
   * @param x значение X
   */
  void dijkstraLogic(StackNode** numbers, StackNode** signs, StackNode* lexeme,
                     double x);

  /**
   * @brief Метод выполняющий математические операции
   * @param numbers стэк с числами
   * @param signs стэк с операциями
   * @param oper код операции
   */
  void operation(StackNode** number, StackNode** signs, int oper);

  /**
   * @brief Метод извлекающий числа из стека для выполнения операции
   * @param numbers стэк с числами
   * @param a первое число
   * @param b второе число
   */
  void twoElements(StackNode** number, double* a, double* b);

  /**
   * @brief Метод извлекающий число из стека для выполнения операции
   * @param numbers стэк с числами
   * @param a число
   */
  void oneElement(StackNode** number, double* a);

  /**
   * @brief Метод возвращающий индентификатор в зависимости от приоритета
   * операции
   * @param signs стэк с операциями
   * @param priority приоритет входящей операции
   * @note -1 - приоритет входящей выше, чем в лежащей, >=0 - ниже или равен
   */
  int checkPriority(StackNode* signs, int priority);
};
}  // namespace s21

#endif  // S21_CALC_MODEL_HPP