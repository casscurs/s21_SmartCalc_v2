#include "s21_credit_controller.hpp"

int s21::CreditController::credit(const char* sumStr, const char* periodStr,
                                  const char* percentStr, int type) {
  return creditModel->credit(sumStr, periodStr, percentStr, type, &res);
}
s21::CreditModel::creditRes s21::CreditController::getCreditData() {
  return res;
}
void s21::CreditController::resetCreditData() {
  res.monthly = 0;
  res.overpay = 0;
  res.total = 0;
  CreditController::freeValArr(&res);
}

void s21::CreditController::freeCreditArr() {
  CreditController::freeValArr(&res);
}

s21::CreditController::~CreditController() {
  res.monthly = 0;
  res.overpay = 0;
  res.total = 0;
  CreditController::freeValArr(&res);
}