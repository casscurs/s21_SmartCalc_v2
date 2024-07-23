#include "test.h"

TEST(DepositModel, test_monthly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};

  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = ("350000");
  str.percent_str = ("4.7");
  str.period_str = ("9");

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 500);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 100);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(12350.033, depOut.percent_award, 0.1);
  EXPECT_NEAR(0, depOut.tax_amount, 0.1);
  EXPECT_NEAR(350400.0, depOut.total_award, 0.1);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_yearly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = ("350000");
  str.percent_str = ("4.7");
  str.period_str = ("13");
  str.regularity = model.YEARLY;

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 500);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 100);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(16468.8, depOut.percent_award, 0.1);
  EXPECT_NEAR(0, depOut.tax_amount, 0.1);
  EXPECT_NEAR(350400.0, depOut.total_award, 0.1);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_negative_sum) {
  s21::DepositModel model;

  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};

  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = ("-350000");
  str.percent_str = ("4.7");
  str.period_str = ("9");

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 500);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 100);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_fractional_period) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};

  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = ("350000");
  str.percent_str = ("4.7");
  str.period_str = ("9.1");

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 500);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 100);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_negative_percent) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = ("350000");
  str.percent_str = ("-4.7");
  str.period_str = ("9");

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 500);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 100);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_large_monthly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = ("15000000");
  str.percent_str = ("5");
  str.period_str = ("14");

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 1000000);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 500000);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(902083.33, depOut.percent_award, 0.1);
  EXPECT_NEAR(106220.833, depOut.tax_amount, 0.1);
  EXPECT_NEAR(15500000.0, depOut.total_award, 0.1);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_large_yearly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = "15000000";
  str.percent_str = "5";
  str.period_str = "14";
  str.regularity = model.YEARLY;

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 1000000);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 500000);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(775000.0, depOut.percent_award, 0.1);
  EXPECT_NEAR(89700.0, depOut.tax_amount, 0.1);
  EXPECT_NEAR(15500000.0, depOut.total_award, 0.1);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_null_arguments) {
  s21::DepositModel model;
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = "350000";
  str.percent_str = "-4.7";
  str.period_str = "9";

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 500);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 100);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, nullptr, nullptr, nullptr);

  EXPECT_EQ(result, 0);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_zero_arguments) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = nullptr;
  s21::DepositModel::StackNode* with = nullptr;
  str.deposit_sum_str = "000";
  str.percent_str = "0";
  str.period_str = "0";

  add = model.PushStackNode(add);
  model.FillFields(add, model.ADDITION, 1, 500);
  with = model.PushStackNode(with);
  model.FillFields(with, model.WITHRAWAL, 2, 100);

  model.SortStackByPriority(&with);
  model.SortStackByPriority(&add);
  int result = model.Deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.FreeStack(add);
  model.FreeStack(with);
}

TEST(DepositModel, test_sort_stack_by_priority) {
  s21::DepositModel model;
  s21::DepositModel::StackNode* apex = nullptr;
  s21::DepositModel::StackNode* tmp = nullptr;

  apex = model.PushStackNode(apex);
  model.FillFields(apex, model.ADDITION, 3, 300);

  apex = model.PushStackNode(apex);
  model.FillFields(apex, model.ADDITION, 1, 100);

  apex = model.PushStackNode(apex);
  model.FillFields(apex, model.ADDITION, 2, 200);

  model.SortStackByPriority(&apex);

  tmp = apex;

  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->priority, 1);

  apex = apex->next;
  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->priority, 2);

  apex = apex->next;
  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->priority, 3);

  model.FreeStack(tmp);
}

TEST(DepositModel, test_operations_in_month) {
  s21::DepositModel model;
  s21::DepositModel::StackNode* apex = nullptr;

  apex = model.PushStackNode(apex);
  model.FillFields(apex, model.ADDITION, 1, 200);

  apex = model.PushStackNode(apex);
  model.FillFields(apex, model.ADDITION, 3, 300);

  apex = model.PushStackNode(apex);
  model.FillFields(apex, model.ADDITION, 1, 100);

  apex = model.PushStackNode(apex);
  model.FillFields(apex, model.ADDITION, 2, 200);

  model.SortStackByPriority(&apex);
  model.OperationsInMonth(&apex);

  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->value, 300);

  model.FreeStack(apex);
}