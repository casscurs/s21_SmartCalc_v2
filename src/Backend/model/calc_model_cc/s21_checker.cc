#include "../s21_calc_model.h"

namespace s21 {
int CalcModel::Checker(const char* str, char* res) {
  if (str == NULL) return ERROR;
  int answer = CORRECT;
  if (strlen(str) > 0) {
    answer = SpacesBrackets(str, res);
    if (answer == CORRECT) {
      answer = CheckSymbol(res);
    }
  } else
    answer = ERROR;
  return answer;
}

int CalcModel::CheckX(const char* str, char* res) {
  if (str == NULL) return ERROR;
  int answer = CORRECT;

  if (strlen(str) > 0) {
    answer = SpacesBrackets(str, res);
    if (answer == CORRECT) {
      answer = CheckSymbolX(res);
    }

  } else
    answer = ERROR;

  return answer;
}

int CalcModel::CheckSymbolX(const char* str) {
  int answer = ERROR;
  int point = 0;
  int count = 0;
  int stop = 1;
  char allowed_arifm[] = ".1234567890+-";

  for (int i = 0; str[i] != '\0' && stop; ++i) {
    if (strchr(allowed_arifm, str[i]) != NULL) {
      if (str[i] == '+' || str[i] == '-') ++count;
      if (!CheckSigns(str, &i, &point, &answer) || count > 1 || point > 1) {
        answer = ERROR;
        stop = 0;
      }
    } else
      stop = 0;
  }

  return answer;
}

int CalcModel::SpacesBrackets(const char* str, char* res) {
  int answer = CORRECT;
  int bracket = 0;

  for (int i = 0, k = 0; str[i] != '\0'; ++i) {
    BracketCounter(str[i], &bracket);
    if (str[i] != ' ') {
      res[k] = str[i];
      res[k + 1] = '\0';
      k++;
    }
  }

  if (bracket != 0) answer = ERROR;
  return answer;
}

int CalcModel::CheckSymbol(char* str) {
  int answer = ERROR;
  int point = 0;
  int stop = 0;
  char allowed_arifm[] = ".1234567890+-x*/()^";
  char allowed_letters[] = "cosintaqrlgmd";
  for (int i = 0; str[i] != '\0' && stop == 0; i++) {
    if (strchr(allowed_arifm, str[i]) == NULL) {
      if (strchr(allowed_letters, str[i]) == NULL)
        stop = 1;
      else {
        /* попадают буквы прошедшие первичную валидацию */
        if (CheckLetters(str, &i, &answer, &point)) {
          if (str[i + 1] == '\0') stop = 1;
          if (!CheckSigns(str, &i, &point, &answer) && stop == 0) stop = 1;
        } else if (CheckMod(str, &i, &answer, &point) && stop == 0) {
          continue;
        } else {
          stop = 1;
        }
      }
      /* попадают цифры и знаки прошедшие первичную валидацию */
    } else if (!CheckSigns(str, &i, &point, &answer))
      break;
  }
  return answer;
}

int CalcModel::CheckLetters(char* str, int* i, int* flaf, int* point) {
  int answer = CORRECT;
  int pos = *i;

  if ((strncmp(str + pos, "sin(", 4) == 0) ||
      (strncmp(str + pos, "cos(", 4) == 0) ||
      (strncmp(str + pos, "tan(", 4) == 0) ||
      (strncmp(str + pos, "log(", 4) == 0)) {
    *i += 3;
    *point = 0;
  } else if ((strncmp(str + pos, "asin(", 4) == 0) ||
             (strncmp(str + pos, "acos(", 4) == 0) ||
             (strncmp(str + pos, "atan(", 4) == 0) ||
             (strncmp(str + pos, "sqrt(", 4) == 0)) {
    *i += 4;
    *point = 0;
  } else if (strncmp(str + pos, "ln(", 3) == 0) {
    *i += 2;
    *point = 0;
  } else {
    answer = ERROR;
  }
  *flaf = answer;
  return (answer);
}

int CalcModel::CheckSigns(const char* str, const int* i, int* point,
                          int* flaf) {
  int answer = CORRECT;
  if (strchr("0123456789", str[*i]) != NULL) {
    /* в окрестности числа */
    if (strchr("0123456789*/+-^.m)", str[*i + 1]) == NULL) answer = ERROR;
  } else if (strchr(".", str[*i]) != NULL) {
    /* в окрестности точки */
    if ((strchr("0123456789", str[*i + 1]) == NULL &&
         strchr("0123456789", str[abs(*i - 1)]) == NULL) ||
        *i == 0 || str[*i + 1] == '\0' || (*point) > 0)
      answer = ERROR;
    (*point)++; /* на две точки в числе*/
  } else if (strchr("+-", str[*i]) != NULL) {
    /* в окрестности операций +- */
    if (*point > 0) (*point)--;
    if (strchr("0123456789cstalmx(", str[*i + 1]) == NULL ||
        str[*i + 1] == '\0')
      answer = ERROR;
  } else if (strchr("x", str[*i]) != NULL) {
    /* в окрестности икса */
    if (strchr("*/+-^m)", str[*i + 1]) == NULL) {
      answer = ERROR;
    }
  } else if (strchr("(", str[*i]) != NULL) {
    /* в окрестности открывающей скобки */
    if (strchr("0123456789(+-cstalx", str[*i + 1]) == NULL) answer = ERROR;
  } else if (strchr(")", str[*i]) != NULL) {
    /* в окрестности закрывающей скобки */
    if ((strchr(")+-*/^m", str[*i + 1]) == NULL && str[*i + 1] != '\0') ||
        str[abs(*i - 1)] == '(')
      answer = ERROR;
  } else if (strchr("^*/", str[*i]) != NULL) {
    /* в окрестности операций /^* */
    if (*point > 0) (*point)--;
    if (strchr("0123456789(+-cstalx", str[*i + 1]) == NULL ||
        str[*i + 1] == '\0')
      answer = ERROR;
  }
  *flaf = answer;
  return answer;
}

void CalcModel::BracketCounter(char c, int* bracket) {
  if (c == '(') (*bracket)++;
  if (c == ')') (*bracket)--;
  return;
}

int CalcModel::CheckMod(char* str, int* i, int* flaf, int* point) {
  int answer = ERROR;
  if (strncmp(str + (*i), "mod", 3) == 0) {
    char allowed_sym[] = "1234567890+-x(";
    *i += 2;
    if (strchr(allowed_sym, str[(*i) + 1]) != NULL && str[(*i) + 1] != '\0')
      answer = CORRECT;
    *point = 0;
  }
  *flaf = answer;
  return answer;
}
}  // namespace s21