#include "s21_deposit_controller.hpp"

int s21::DepositController::deposit(inputStr str, StackNode** add,
                                    StackNode** with) {
  return depositModel->deposit(str, add, with, &res);
}

s21::DepositModel::output s21::DepositController::getDepositData() {
  return res;
}

void s21::DepositController::resetDepositData() {
  res.percentAward = 0;
  res.taxAmount = 0;
  res.totalAward = 0;
}