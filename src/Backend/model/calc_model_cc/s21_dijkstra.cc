#include "../s21_calc_model.h"

namespace s21 {
int CalcModel::Calc(const char* initial, const char* x, double* res) {
  StackNode lexeme[256] = {};
  double x_value = 1;

  int answer = GetLexemsArr(initial, lexeme);

  if (answer == XCOMING) answer = ReadX(x, &x_value);

  try {
    if (answer == CORRECT) *res = Calculating(lexeme, x_value);
  } catch (const CalculatorException& e) {
    throw;
  }
  return (answer);
}

double CalcModel::Calculating(StackNode* lexeme, double x) {
  StackNode* numbers = NULL;
  StackNode* signs = NULL;
  double k = -1;
  try {
    DijkstraLogic(&numbers, &signs, lexeme, x);
    while (signs) {
      Operation(&numbers, &signs, signs->what);
    }
    k = numbers->value;
    FreeStack(numbers);
    FreeStack(signs);
  } catch (const CalculatorException& e) {
    FreeStack(numbers);
    FreeStack(signs);
    throw;
  }
  return k;
}

void CalcModel::DijkstraLogic(StackNode** numbers, StackNode** signs,
                              StackNode* lexeme, double x) {
  try {
    int bracket = 0;
    for (int i = 0; lexeme[i].what != INITIA; ++i) {
      if (lexeme[i].what == X) {
        /* Икс */
        *numbers = PushStackNode(*numbers);
        FillFields(*numbers, NUMBER, NUMB, x);
      } else if (lexeme[i].what == MINUS_X) {
        /* -Икс */
        *numbers = PushStackNode(*numbers);
        FillFields(*numbers, NUMBER, NUMB, -1 * x);
      } else if (lexeme[i].what == NUMBER) {
        /* Число */
        *numbers = PushStackNode(*numbers);
        FillFields(*numbers, NUMBER, NUMB, lexeme[i].value);
      } else if (lexeme[i].priority > 0) {
        /* Операция */
        if (bracket == 1) {
          *signs = PushStackNode(*signs);
          FillFields(*signs, lexeme[i].what, lexeme[i].priority, 0);
          bracket = 0;
        } else {
          int pos = CheckPriority(*signs, lexeme[i].priority);
          if (pos == -1) {
            *signs = PushStackNode(*signs);
            FillFields(*signs, lexeme[i].what, lexeme[i].priority, 0);
          } else if (pos >= 0) {
            Operation(numbers, signs, (*signs)->what);
            *signs = PushStackNode(*signs);
            FillFields(*signs, lexeme[i].what, lexeme[i].priority, 0);
          }
        }
      } else if (lexeme[i].what == BRACKET_O) {
        /* Открывающая скобка */
        *signs = PushStackNode(*signs);
        FillFields(*signs, BRACKET_O, 0, 0);
        bracket = 1;
      } else if (lexeme[i].what == BRACKET_C) {
        /* Закрывающая скобка */
        while ((*signs)->what != BRACKET_O) {
          Operation(numbers, signs, (*signs)->what);
        }
        *signs = PopStackNode(*signs); /* удалили BRACKET_O */
        bracket = 0;
      }
    }
  } catch (const CalculatorException& e) {
    throw;
  }
}

void CalcModel::Operation(StackNode** number, StackNode** signs, int oper) {
  switch (oper) {
    case PLUS: {
      double a = 0, b = 0;
      TwoElements(number, &a, &b);
      FillFields(*number, NUMBER, NUMB, a + b);
      *signs = PopStackNode(*signs);
      break;
    }
    case MINUS: {
      double a = 0, b = 0;
      TwoElements(number, &a, &b);
      FillFields(*number, NUMBER, NUMB, a - b);
      *signs = PopStackNode(*signs);
      break;
    }
    case DIV: {
      double a = 0, b = 0;
      TwoElements(number, &a, &b);
      FillFields(*number, NUMBER, NUMB, a / b);
      *signs = PopStackNode(*signs);
      break;
    }
    case MOD: {
      double a = 0, b = 0;
      TwoElements(number, &a, &b);
      FillFields(*number, NUMBER, NUMB, fmod(a, b));
      *signs = PopStackNode(*signs);
      break;
    }
    case MULT: {
      double a = 0, b = 0;
      TwoElements(number, &a, &b);
      FillFields(*number, NUMBER, NUMB, a * b);
      *signs = PopStackNode(*signs);
      break;
    }
    case POW: {
      double a = 0, b = 0;
      TwoElements(number, &a, &b);
      FillFields(*number, NUMBER, NUMB, pow(a, b));
      *signs = PopStackNode(*signs);
      break;
    }
    case SIN: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, sin(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case COS: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, cos(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case TAN: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, tan(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case ACOS: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, acos(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case ASIN: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, asin(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case ATAN: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, atan(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case SQRT: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, sqrt(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case LN: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, log(a));
      *signs = PopStackNode(*signs);
      break;
    }
    case LOG: {
      double a = 0;
      OneElement(number, &a);
      FillFields(*number, NUMBER, NUMB, log10(a));
      *signs = PopStackNode(*signs);
      break;
    }
    default:
      break;
  }
  return;
}

void CalcModel::TwoElements(StackNode** number, double* a, double* b) {
  if (*number) *b = (*number)->value;
  *number = PopStackNode(*number);
  if (*number) *a = (*number)->value;
  *number = PopStackNode(*number);

  try {
    *number = PushStackNode(*number);
  } catch (const CalculatorException& e) {
    throw;
  }
  return;
}

void CalcModel::FillFields(StackNode* number, int what, int priority,
                           double value) {
  number->what = what;
  number->priority = priority;
  number->value = value;
  return;
}

void CalcModel::OneElement(StackNode** number, double* a) {
  *a = (*number)->value;
  *number = PopStackNode(*number);
  try {
    *number = PushStackNode(*number);
  } catch (const CalculatorException& e) {
    throw;
  }
  return;
}

int CalcModel::CheckPriority(StackNode* signs, int priority) {
  int answer = -1;
  int counter = 0;
  StackNode* i = NULL;
  for (i = signs; i && answer == -1; i = i->next, ++counter) {
    if (i->what == BRACKET_O || i->what == BRACKET_C) {
      break;
    }
    if (i->priority >= priority) {
      answer = counter;
    }
  }
  return (answer);
}
}  // namespace s21
