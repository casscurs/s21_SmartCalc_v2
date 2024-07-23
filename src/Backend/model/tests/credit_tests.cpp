#include "test.hpp"

// EXPECT_NEAR

TEST(CreditModel, test_annuity_calculation) {
  s21::CreditModel model;
  const char sumStr[] = "100000";
  const char periodStr[] = "12";
  const char percentStr[] = "10";
  s21::CreditModel::creditRes res = {};
  int type = model.ANNUITY;

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(8791.59, res.monthly, 0.1);
  EXPECT_NEAR(5499.08, res.overpay, 0.1);
  EXPECT_NEAR(105499.08, res.total, 0.1);
  if (res.valArr) {
    free(res.valArr);
  }
}

TEST(CreditModel, test_differentiated_calculation) {
  s21::CreditModel model;
  const char sumStr[] = "50000";
  const char periodStr[] = "24";
  const char percentStr[] = "8";
  int type = model.DIFFERENTIATED;
  s21::CreditModel::creditRes res = {};

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(2097.22, res.monthly, 0.1);
  EXPECT_NEAR(4166.67, res.overpay, 0.1);
  EXPECT_NEAR(54166.67, res.total, 0.1);
  if (res.valArr) {
    free(res.valArr);
  }
}

TEST(CreditModel, test_negative_sum) {
  s21::CreditModel model;
  const char sumStr[] = "-50000";
  const char periodStr[] = "24";
  const char percentStr[] = "8";
  int type = model.ANNUITY;
  s21::CreditModel::creditRes res = {};

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  if (res.valArr) {
    free(res.valArr);
  }

  EXPECT_EQ(result, 0);
}

TEST(CreditModel, test_fractional_period) {
  s21::CreditModel model;
  const char sumStr[] = "100000";
  const char periodStr[] = "12.5";
  const char percentStr[] = "10";
  int type = model.ANNUITY;
  s21::CreditModel::creditRes res = {};

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  if (res.valArr) {
    free(res.valArr);
  }

  EXPECT_EQ(result, 0);
}

TEST(CreditModel, test_negative_percent) {
  s21::CreditModel model;
  const char sumStr[] = "100000";
  const char periodStr[] = "12";
  const char percentStr[] = "-10";
  int type = model.ANNUITY;
  s21::CreditModel::creditRes res = {};

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  if (res.valArr) {
    free(res.valArr);
  }

  EXPECT_EQ(result, 0);
}

TEST(CreditModel, test_large_annuity_calculation) {
  s21::CreditModel model;
  const char sumStr[] = "1000000";
  const char periodStr[] = "120";
  const char percentStr[] = "5";
  int type = model.ANNUITY;
  s21::CreditModel::creditRes res = {};

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(10606.55, res.monthly, 1);
  EXPECT_NEAR(272786.00, res.overpay, 1);
  EXPECT_NEAR(1272786.00, res.total, 1);
  if (res.valArr) {
    free(res.valArr);
  }
}

TEST(CreditModel, test_large_differentiated_calculation) {
  s21::CreditModel model;
  const char sumStr[] = "5000000";
  const char periodStr[] = "240";
  const char percentStr[] = "8";
  int type = model.DIFFERENTIATED;
  s21::CreditModel::creditRes res = {};

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  EXPECT_EQ(result, 1);
  EXPECT_NEAR(20972.22, res.monthly, 0.1);
  EXPECT_NEAR(4016666.67, res.overpay, 0.1);
  EXPECT_NEAR(9016666.67, res.total, 0.1);
  if (res.valArr) {
    free(res.valArr);
  }
}

TEST(CreditModel, test_null_arguments) {
  s21::CreditModel model;
  int type = model.ANNUITY;
  s21::CreditModel::creditRes res = {};
  int result = model.credit(NULL, NULL, NULL, type, &res);

  EXPECT_EQ(result, 0);
}

TEST(CreditModel, test_zero_arguments) {
  s21::CreditModel model;
  const char sumStr[] = "0";
  const char periodStr[] = "0";
  const char percentStr[] = "0";
  int type = model.ANNUITY;
  s21::CreditModel::creditRes res = {};

  int result = model.credit(sumStr, periodStr, percentStr, type, &res);

  EXPECT_EQ(result, 0);
}