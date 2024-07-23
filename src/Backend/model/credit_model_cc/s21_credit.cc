#include "../s21_credit_model.h"

namespace s21 {
int CreditModel::Credit(const char* sumStr, const char* period_str,
                        const char* percent_str, int type, creditRes* res) {
  int answer = CORRECT;
  creditParam param = {};

  if (!ReadX(sumStr, &param.sum) || !ReadX(period_str, &param.period) ||
      !ReadX(percent_str, &param.percent)) {
    answer = ERROR;
  }

  if (param.sum <= 0 ||
      (param.period < 1 || param.period - (int)param.period > 0) ||
      param.percent <= 0) {
    answer = ERROR;
  }

  if (answer == CORRECT) {
    try {
      CalcCredit(param, res, type);
    } catch (const CalculatorException& e) {
      throw;
    }
  }
  return (answer);
}

void CreditModel::CalcCredit(creditParam param, creditRes* res, int type) {
  double p = param.percent / (100 * 12);
  if (type == ANNUITY) {
    res->monthly = param.sum * (p + p / (pow(1 + p, param.period) - 1));
    res->total = res->monthly * param.period;
    res->overpay = res->total - param.sum;
  }
  if (type == DIFFERENTIATED) {
    double b = 0;
    double ost = param.sum;
    /* Массив на количество периодов в дифференцированном */
    res->valArr = static_cast<double*>(calloc(param.period, sizeof(double)));
    if (res->valArr == NULL)
      throw CalculatorException("Memory allocation failed");
    b = param.sum / param.period; /* Долговая часть */
    for (int i = 0; i < param.period; ++i) {
      res->monthly = ost * p + b;
      res->total += res->monthly;
      ost -= b;
      (res->valArr)[i] = res->monthly;
    }
    res->overpay = res->total - param.sum;
  }

  return;
}
}  // namespace s21