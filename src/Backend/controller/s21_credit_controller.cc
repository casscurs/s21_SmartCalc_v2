#include "s21_credit_controller.h"

int s21::CreditController::Credit(const char* sumStr, const char* period_str,
                                  const char* percent_str, int type) {
  return credit_model->Credit(sumStr, period_str, percent_str, type, &res);
}
s21::CreditModel::creditRes s21::CreditController::GetCreditData() {
  return res;
}
void s21::CreditController::ResetCreditData() {
  res.monthly = 0;
  res.overpay = 0;
  res.total = 0;
  credit_model->FreeValArr(&res);
}

void s21::CreditController::FreeCreditArr() { credit_model->FreeValArr(&res); }

s21::CreditController::~CreditController() {
  res.monthly = 0;
  res.overpay = 0;
  res.total = 0;
  credit_model->FreeValArr(&res);
}