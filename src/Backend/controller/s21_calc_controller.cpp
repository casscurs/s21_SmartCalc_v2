#include "s21_calc_controller.hpp"

int s21::CalcController::calc(const char* initial, const char* x) {
  return calcModel->calc(initial, x, &res);
}
double s21::CalcController::getCalcData() { return res; }

void s21::CalcController::resetCalcData() { res = 0; }

int s21::CalcController::graphCalc(int xBegin, int xEnd, std::vector<double>& x,
                                   std::vector<double>& y, const char* str) {
  int answer = 1;
  CalcModel::StackNode lexeme[256] = {};
  if (!getLexemsArr(str, lexeme)) answer = 0;

  double step = 0.1;

  for (double X = xBegin; X <= xEnd; X += step) {
    x.push_back(X);
    res = calculating(lexeme, X);
    y.push_back(res);
  }
  return answer;
}