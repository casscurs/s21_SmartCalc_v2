#include "test.h"

TEST(CalcModel, test_plus) {
  s21::CalcModel model;
  const char str[256] = "+1.234+3.45+9.877";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(+1.234 + 3.45 + 9.877, res);
}

TEST(CalcModel, test_minus) {
  s21::CalcModel model;
  const char str[256] = "-1.25-(-3.45)-24";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(-1.25 - (-3.45) - 24, res);
}

TEST(CalcModel, test_mult_1) {
  s21::CalcModel model;
  const char str[256] = "-1*-1*-1.28485";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(-1 * -1 * -1.28485, res);
}

TEST(CalcModel, test_mult_2) {
  s21::CalcModel model;
  const char str[256] = "2.35+2.66*2.34 + 7*(8.32323+1)";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(2.35 + 2.66 * 2.34 + 7 * (8.32323 + 1), res);
}

TEST(CalcModel, test_div) {
  s21::CalcModel model;
  const char str[256] = "1.25/(3.45-1)";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(1.25 / (3.45 - 1), res);
}

TEST(CalcModel, test_mod) {
  s21::CalcModel model;
  const char str[256] = "1.25mod3.5";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(fmod(1.25, 3.5), res);
}

TEST(CalcModel, test_pow) {
  s21::CalcModel model;
  const char str[256] = "1.25^3.45+1";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(pow(1.25, 3.45) + 1, res);
}

TEST(CalcModel, test_x) {
  s21::CalcModel model;
  const char str[256] = "(sin(+x)/-x * x*log(cos(cos(x))))";
  const char x[256] = "239";
  double res = 0;
  model.Calc(str, x, &res);
  double eq = (sin(+239) / -239 * 239 * log10(cos(cos(239))));
  EXPECT_DOUBLE_EQ(res, eq);
}

TEST(CalcModel, test_brackets) {
  s21::CalcModel model;
  const char str[256] = "sin(sin(sin(2)))";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(sin(sin(sin(2))), res);
}

TEST(CalcModel, test_sin) {
  s21::CalcModel model;
  const char str[256] = "sin((5.23+1.25)*(0.25+0.001))";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(sin((5.23 + 1.25) * (0.25 + 0.001)), res);
}

TEST(CalcModel, test_cos) {
  s21::CalcModel model;
  const char str[256] = "cos((5.23+1.25)*(0.25+0.001))";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(cos((5.23 + 1.25) * (0.25 + 0.001)), res);
}

TEST(CalcModel, test_tan) {
  s21::CalcModel model;
  const char str[256] = "tan((5.23+1.25)*(0.25+0.001))";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(tan((5.23 + 1.25) * (0.25 + 0.001)), res);
}

TEST(CalcModel, test_asin) {
  s21::CalcModel model;
  const char str[256] = "asin(7/7.7)";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(asin(7 / 7.7), res);
}

TEST(CalcModel, test_acos) {
  s21::CalcModel model;
  const char str[256] = "acos(7/7.7)";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(acos(7 / 7.7), res);
}

TEST(CalcModel, test_atan) {
  s21::CalcModel model;
  const char str[256] = "atan(7/7.7)";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(atan(7 / 7.7), res);
}

TEST(CalcModel, test_sqrt) {
  s21::CalcModel model;
  const char str[256] = "sqrt(1357.1-(-245.23))";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(sqrt(1357.1 - (-245.23)), res);
}

TEST(CalcModel, test_ln) {
  s21::CalcModel model;
  const char str[256] = "ln(1357.24-245.4324)";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(log(1357.24 - 245.4324), res);
}

TEST(CalcModel, test_log) {
  s21::CalcModel model;
  const char str[256] = "log(1357.24-245.4324)";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(log10(1357.24 - 245.4324), res);
}

TEST(CalcModel, test_combo) {
  s21::CalcModel model;
  const char str[256] = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(log10(32 + 1) * 7 / 11 * 432 * (sin(2) * 12 - 45 + 4) / 2,
                   res);
}

TEST(CalcModel, test_combo_func) {
  s21::CalcModel model;
  const char str[256] = "cos(sin(tan(-0.005)))";
  const char x[256] = "";
  double res = 0;
  model.Calc(str, x, &res);
  EXPECT_DOUBLE_EQ(cos(sin(tan(-0.005))), res);
}

TEST(CalcModel, test_invalid_input) {
  s21::CalcModel model;
  const char str0[] = "log(32+1)*7/11*432*(sin(2)*12-45+4/2";
  double res = 0;
  EXPECT_EQ(model.Calc(str0, "", &res), 0);

  const char str1[] = "cos(cos(cos(2))";
  EXPECT_EQ(model.Calc(str1, "", &res), 0);

  const char str2[] = "cos(3cos(2))";
  EXPECT_EQ(model.Calc(str2, "", &res), 0);

  const char str3[] = "1.234+";
  EXPECT_EQ(model.Calc(str3, "", &res), 0);

  const char str4[] = "1()";
  EXPECT_EQ(model.Calc(str4, "", &res), 0);

  const char str5[] = "1.2.3";
  EXPECT_EQ(model.Calc(str5, "", &res), 0);

  const char str7[] = "cos(*2)";
  EXPECT_EQ(model.Calc(str7, "", &res), 0);

  const char str8[] = ".cos(2)";
  EXPECT_EQ(model.Calc(str8, "", &res), 0);

  const char str9[] = "cos(2)sin(3)";
  EXPECT_EQ(model.Calc(str9, "", &res), 0);

  const char str10[] = "mod(2)(";
  EXPECT_EQ(model.Calc(str10, "", &res), 0);

  const char str11[] = "mod+";
  EXPECT_EQ(model.Calc(str11, "", &res), 0);

  const char str12[] = "1+ 2      -3";
  EXPECT_EQ(model.Calc(str12, "", &res), 1);

  const char str13[] = "x2";
  EXPECT_EQ(model.Calc(str13, "", &res), 0);

  const char str14[] = "x^2";
  EXPECT_EQ(model.Calc(str14, "2", &res), 1);

  const char str15[] = "x^- ";
  EXPECT_EQ(model.Calc(str15, "", &res), 0);

  const char str16[] = "cos(cos(x))";
  EXPECT_EQ(model.Calc(str16, "2", &res), 1);

  const char str17[] =
      "cos((20.2 - 10) * (10mod5 - 10^2) / 10.10 + 1 - cos(x - (10*9+ "
      "sin(2-10 - tan(x)))))";
  EXPECT_EQ(model.Calc(str17, "2", &res), 1);

  const char str18[] =
      "cos((20..2 - 10) * (10mod.5 - 10.^2) / 10.10 + 1 - cos(x - (10*9+ "
      "sin(2-10))))";
  EXPECT_EQ(model.Calc(str18, "2", &res), 0);

  const char str19[] =
      "cos((20.2 - 10) * (10mod5 - 10^2) / 10.10^ + 1 - cos(x - (10*9+ "
      "sin(2-10))))";
  EXPECT_EQ(model.Calc(str19, "2", &res), 1);

  const char str20[] = "()+2";
  EXPECT_EQ(model.Calc(str20, "", &res), 0);

  const char str21[] = "ln(2)";
  EXPECT_EQ(model.Calc(str21, "", &res), 1);

  const char str22[] = "asin(2)";
  EXPECT_EQ(model.Calc(str22, "", &res), 1);

  const char str23[] = "2 + (2 - 2) *";
  EXPECT_EQ(model.Calc(str23, "", &res), 0);

  const char str24[] = "x1";
  EXPECT_EQ(model.Calc(str24, "2", &res), 0);

  const char str25[] = "tan(2 - x^^-)";
  EXPECT_EQ(model.Calc(str25, "2", &res), 0);

  const char str26[] = "2^-";
  EXPECT_EQ(model.Calc(str26, "", &res), 0);
}