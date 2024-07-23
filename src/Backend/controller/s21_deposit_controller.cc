#include "s21_deposit_controller.h"

int s21::DepositController::Deposit() {
  SortAndTransformStack();
  return deposit_model->Deposit(str, &add, &with, &res);
}

s21::DepositModel::output s21::DepositController::GetDepositData() {
  return res;
}

void s21::DepositController::ResetDepositData() {
  res.percent_award = 0;
  res.tax_amount = 0;
  res.total_award = 0;
}

void s21::DepositController::PushToStackAdd(double add_sum, double add_month) {
  add = deposit_model->PushStackNode(add);
  add->priority = add_month;
  add->what = deposit_model->ADDITION;
  add->value = add_sum;
}

void s21::DepositController::PushToStackWith(double with_sum,
                                             double with_month) {
  with = deposit_model->PushStackNode(with);
  with->priority = with_month;
  with->what = deposit_model->WITHRAWAL;
  with->value = with_sum;
}

void s21::DepositController::PopAndClearStack() {
  deposit_model->FreeStack(with);
  with = nullptr;
  deposit_model->FreeStack(add);
  add = nullptr;
}

void s21::DepositController::SortAndTransformStack() {
  deposit_model->SortStackByPriority(&add);
  deposit_model->SortStackByPriority(&with);

  deposit_model->OperationsInMonth(&add);
  deposit_model->OperationsInMonth(&with);
}