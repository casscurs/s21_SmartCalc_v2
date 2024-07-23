#include "test.hpp"

TEST(DepositModel, test_monthly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};

  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = ("350000");
  str.percentStr = ("4.7");
  str.periodStr = ("9");

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 500);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 100);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(12350.033, depOut.percentAward, 0.1);
  EXPECT_NEAR(0, depOut.taxAmount, 0.1);
  EXPECT_NEAR(350400.0, depOut.totalAward, 0.1);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_yearly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = ("350000");
  str.percentStr = ("4.7");
  str.periodStr = ("13");
  str.regularity = model.YEARLY;

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 500);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 100);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(16468.8, depOut.percentAward, 0.1);
  EXPECT_NEAR(0, depOut.taxAmount, 0.1);
  EXPECT_NEAR(350400.0, depOut.totalAward, 0.1);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_negative_sum) {
  s21::DepositModel model;

  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};

  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = ("-350000");
  str.percentStr = ("4.7");
  str.periodStr = ("9");

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 500);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 100);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_fractional_period) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};

  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = ("350000");
  str.percentStr = ("4.7");
  str.periodStr = ("9.1");

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 500);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 100);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_negative_percent) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = ("350000");
  str.percentStr = ("-4.7");
  str.periodStr = ("9");

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 500);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 100);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_large_monthly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = ("15000000");
  str.percentStr = ("5");
  str.periodStr = ("14");

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 1000000);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 500000);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(902083.33, depOut.percentAward, 0.1);
  EXPECT_NEAR(106220.833, depOut.taxAmount, 0.1);
  EXPECT_NEAR(15500000.0, depOut.totalAward, 0.1);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_large_yearly_calculation) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = "15000000";
  str.percentStr = "5";
  str.periodStr = "14";
  str.regularity = model.YEARLY;

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 1000000);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 500000);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(775000.0, depOut.percentAward, 0.1);
  EXPECT_NEAR(89700.0, depOut.taxAmount, 0.1);
  EXPECT_NEAR(15500000.0, depOut.totalAward, 0.1);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_null_arguments) {
  s21::DepositModel model;
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = "350000";
  str.percentStr = "-4.7";
  str.periodStr = "9";

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 500);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 100);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, NULL, NULL, NULL);

  EXPECT_EQ(result, 0);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_zero_arguments) {
  s21::DepositModel model;
  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};
  s21::DepositModel::StackNode* add = NULL;
  s21::DepositModel::StackNode* with = NULL;
  str.depositSumStr = "000";
  str.percentStr = "0";
  str.periodStr = "0";

  add = model.pushStackNode(add);
  model.fillFields(add, model.ADDITION, 1, 500);
  with = model.pushStackNode(with);
  model.fillFields(with, model.WITHRAWAL, 2, 100);

  model.sortStackByPriority(&with);
  model.sortStackByPriority(&add);
  int result = model.deposit(str, &add, &with, &depOut);

  EXPECT_EQ(result, 0);

  model.freeStack(add);
  model.freeStack(with);
}

TEST(DepositModel, test_sort_stack_by_priority) {
  s21::DepositModel model;
  s21::DepositModel::StackNode* apex = NULL;
  s21::DepositModel::StackNode* tmp = NULL;

  apex = model.pushStackNode(apex);
  model.fillFields(apex, model.ADDITION, 3, 300);

  apex = model.pushStackNode(apex);
  model.fillFields(apex, model.ADDITION, 1, 100);

  apex = model.pushStackNode(apex);
  model.fillFields(apex, model.ADDITION, 2, 200);

  model.sortStackByPriority(&apex);

  tmp = apex;

  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->priority, 1);

  apex = apex->next;
  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->priority, 2);

  apex = apex->next;
  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->priority, 3);

  model.freeStack(tmp);
}

TEST(DepositModel, test_operations_in_month) {
  s21::DepositModel model;
  s21::DepositModel::StackNode* apex = NULL;

  apex = model.pushStackNode(apex);
  model.fillFields(apex, model.ADDITION, 1, 200);

  apex = model.pushStackNode(apex);
  model.fillFields(apex, model.ADDITION, 3, 300);

  apex = model.pushStackNode(apex);
  model.fillFields(apex, model.ADDITION, 1, 100);

  apex = model.pushStackNode(apex);
  model.fillFields(apex, model.ADDITION, 2, 200);

  model.sortStackByPriority(&apex);
  model.operationsInMonth(&apex);

  EXPECT_TRUE(apex != nullptr);
  EXPECT_EQ(apex->value, 300);

  model.freeStack(apex);
}