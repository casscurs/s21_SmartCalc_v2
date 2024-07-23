#include "../s21_calc_model.hpp"
namespace s21 {
int CalcModel::getLexemsArr(const char* initial, StackNode* lexeme) {
  char str[256] = {0};
  int unar = 0;
  if (!checker(initial, str)) return (ERROR);

  int answer = CORRECT;
  char buf[256] = {0};
  for (int i = 0, bufCount = 0, lexCount = 0; str[i] != '\0'; ++i) {
    if (strchr("0123456789.", str[i]) != NULL) {
      buf[bufCount++] = str[i];
      if ((strchr("0123456789.", str[i + 1]) == NULL) || (str[i + 1] == '\0')) {
        numbToLexeme(lexeme, &lexCount, buf, &bufCount, &i, &unar);
        continue;
      }
    } else {
      signToLexeme(lexeme, str, &lexCount, &i, &unar, &answer);
    }
  }
  return (answer);
}

void CalcModel::XtoNumb(char* buf, double* value, int* unar) {
  *value = atof(buf);
  if (*unar) {
    (*value) *= -1;
    *unar = 0;
  }
  memset(buf, 0, 256);
  return;
}

int CalcModel::readX(const char* initial, double* value) {
  char str[256] = {0};
  if (!check_x(initial, str)) return (ERROR);
  char buf[256] = {0};
  int unar = 0;
  for (int i = 0, bufCount = 0; str[i] != '\0'; ++i) {
    if (str[i] == '+') continue;
    if (str[i] == '-') unar = 1;
    if (strchr("0123456789.", str[i]) != NULL) {
      buf[bufCount++] = str[i];
      if ((strchr("0123456789.", str[i + 1]) == NULL) || (str[i + 1] == '\0')) {
        XtoNumb(buf, value, &unar);
        continue;
      }
    }
  }
  return (CORRECT);
}

void CalcModel::numbToLexeme(StackNode* lexeme, int* lexCount, char* buf,
                             int* bufCount, int* i, int* unar) {
  lexeme[*lexCount].value = atof(buf);
  if (*unar) {
    lexeme[*lexCount].value *= -1;
    *unar = 0;
  }
  memset(buf, 0, 256);
  *bufCount = 0;
  fillFunc(lexeme, lexCount, i, 0, NUMBER, NUMB);
  return;
}

void CalcModel::signToLexeme(StackNode* lexeme, char* str, int* lexCount,
                             int* i, int* unar, int* checker) {
  if (str[*i] == 'x') {
    if (*unar == 1) {
      fillFunc(lexeme, lexCount, i, 0, MINUS_X, NUMB);
      *unar = 0;
    } else
      fillFunc(lexeme, lexCount, i, 0, X, NUMB);
    *checker = XCOMING;
  } else if (str[*i] == '(')
    fillFunc(lexeme, lexCount, i, 0, BRACKET_O, 0);
  else if (str[*i] == ')')
    fillFunc(lexeme, lexCount, i, 0, BRACKET_C, 0);
  else if (str[*i] == '+') {
    if ((strchr("0123456789)x", str[abs((*i) - 1)]) != NULL) && ((*i) != 0)) {
      /* не унарная операция на + */
      fillFunc(lexeme, lexCount, i, 0, PLUS, ASUB);
    }
  } else if (str[*i] == '-') {
    if (((strchr("1234567890)x", str[abs((*i) - 1)]) == NULL) || ((*i) == 0)) &&
        (strchr("1234567890x", str[abs((*i) + 1)]) != NULL)) {
      /* унарная операция на - */
      *unar = 1;
    } else
      fillFunc(lexeme, lexCount, i, 0, MINUS, ASUB);
  } else if (str[*i] == '*')
    fillFunc(lexeme, lexCount, i, 0, MULT, MDM);
  else if (str[*i] == '/')
    fillFunc(lexeme, lexCount, i, 0, DIV, MDM);
  else if (str[*i] == '^')
    fillFunc(lexeme, lexCount, i, 0, POW, STEP);
  else if (strncmp(str + *i, "sin", 3) == 0)
    fillFunc(lexeme, lexCount, i, 2, SIN, FUNC);
  else if (strncmp(str + *i, "cos", 3) == 0)
    fillFunc(lexeme, lexCount, i, 2, COS, FUNC);
  else if (strncmp(str + *i, "tan", 3) == 0)
    fillFunc(lexeme, lexCount, i, 2, TAN, FUNC);
  else if (strncmp(str + *i, "asin", 4) == 0)
    fillFunc(lexeme, lexCount, i, 3, ASIN, FUNC);
  else if (strncmp(str + *i, "acos", 4) == 0)
    fillFunc(lexeme, lexCount, i, 3, ACOS, FUNC);
  else if (strncmp(str + *i, "atan", 4) == 0)
    fillFunc(lexeme, lexCount, i, 3, ATAN, FUNC);
  else if (strncmp(str + *i, "sqrt", 4) == 0)
    fillFunc(lexeme, lexCount, i, 3, SQRT, FUNC);
  else if (strncmp(str + *i, "ln", 2) == 0)
    fillFunc(lexeme, lexCount, i, 1, LN, FUNC);
  else if (strncmp(str + *i, "log", 3) == 0)
    fillFunc(lexeme, lexCount, i, 2, LOG, FUNC);
  else if (strncmp(str + *i, "mod", 3) == 0)
    fillFunc(lexeme, lexCount, i, 2, MOD, FUNC);
  return;
}

void CalcModel::fillFunc(StackNode* lexeme, int* lexCount, int* step,
                         int stepVal, int what, int priority) {
  lexeme[*lexCount].what = what;
  lexeme[*lexCount].priority = priority;
  (*step) += stepVal; /* перескок счетчика по исходному массиву*/
  (*lexCount)++;
  return;
}
}  // namespace s21
