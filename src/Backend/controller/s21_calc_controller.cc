#include "s21_calc_controller.h"

int s21::CalcController::Calc(const char* initial, const char* x) {
  return calc_model->Calc(initial, x, &res);
}
double s21::CalcController::GetCalcData() { return res; }

void s21::CalcController::ResetCalcData() { res = 0; }

int s21::CalcController::GraphCalc(int xBegin, int xEnd, std::vector<double>& x,
                                   std::vector<double>& y, const char* str) {
  int answer = 1;
  CalcModel::StackNode lexeme[256] = {};
  if (!(calc_model->GetLexemsArr(str, lexeme))) answer = 0;

  double step = 0.1;

  for (double X = xBegin; X <= xEnd; X += step) {
    x.push_back(X);
    res = calc_model->Calculating(lexeme, X);
    y.push_back(res);
  }
  return answer;
}

int s21::CalcController::XReader(const char* initial, double* value) {
  return calc_model->ReadX(initial, value);
}