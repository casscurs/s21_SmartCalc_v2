#include "../s21_deposit_model.hpp"

namespace s21 {
int DepositModel::deposit(inputStr str, StackNode** add, StackNode** with,
                          output* depOut) {
  int answer = CORRECT;
  input depIn = {};

  if (!readX(str.depositSumStr, &depIn.depositSum) ||
      !readX(str.periodStr, &depIn.period) ||
      !readX(str.percentStr, &depIn.percent)) {
    answer = ERROR;
  }

  if (depIn.depositSum <= 0 ||
      (depIn.period < 1 || depIn.period - (int)depIn.period > 0) ||
      depIn.percent <= 0) {
    answer = ERROR;
  }

  if (answer == CORRECT) {
    answer = calcDeposit(str, depIn, depOut, add, with);
    if (answer == CORRECT) {
      tax(depOut);
    }
  }
  return (answer);
}

int DepositModel::calcDeposit(inputStr str, input depIn, output* depOut,
                              StackNode** add, StackNode** with) {
  int answer = CORRECT;
  int period = str.regularity == MONTHLY ? 12 : 1;

  for (int i = 1; i <= depIn.period && answer; ++i) {
    if (*with && i == (*with)->priority) {
      if (depIn.depositSum - (*with)->value <= 0) answer = ERROR;
      depIn.depositSum -= (*with)->value;
      *with = popStackNode(*with);
    }
    double monthPercent = 0;
    if (str.regularity == YEARLY) {
      if (i % 11 == 0 && i != 0) {
        monthPercent = depIn.depositSum * depIn.percent / (100 * period);
      }
    } else
      monthPercent = depIn.depositSum * depIn.percent / (100 * period);
    /* monthPercent = depIn.depositSum*depIn.percent*30.41/(365*100); */

    if (str.capital) depIn.depositSum += monthPercent;

    if (*add && i == (*add)->priority) {
      depIn.depositSum += (*add)->value;
      *add = popStackNode(*add);
    }
    depOut->percentAward += monthPercent;
    depOut->totalAward = depIn.depositSum;
  }
  return answer;
}

void DepositModel::tax(output* depOut) {
  double res = depOut->percentAward - 1000000 * 8.5 / 100;
  if (res > 0)
    res *= 0.13;
  else
    res = 0;
  depOut->taxAmount = res;
  return;
}

void DepositModel::operationsInMonth(StackNode** apex) {
  if (!(*apex) || !((*apex)->next)) {
    return;
  }

  StackNode* apexBuf = *apex;
  StackNode* apexRet = *apex;

  while (apexBuf) {
    if ((apexBuf->next) && ((apexBuf->next)->priority) == apexBuf->priority) {
      (apexBuf->next)->value += apexBuf->value;
      apexBuf = popStackNode(apexBuf);
      apexRet = apexBuf;
    } else {
      apexBuf = apexBuf->next;
    }
  }
  *apex = apexRet;
}
}  // namespace s21