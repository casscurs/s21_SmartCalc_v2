#include "../s21_deposit_model.h"

namespace s21 {
int DepositModel::Deposit(inputStr str, StackNode** add, StackNode** with,
                          output* depOut) {
  int answer = CORRECT;
  input dep_in = {};

  if (!ReadX(str.deposit_sum_str, &dep_in.deposit_sum) ||
      !ReadX(str.period_str, &dep_in.period) ||
      !ReadX(str.percent_str, &dep_in.percent)) {
    answer = ERROR;
  }

  if (dep_in.deposit_sum <= 0 ||
      (dep_in.period < 1 || dep_in.period - (int)dep_in.period > 0) ||
      dep_in.percent <= 0) {
    answer = ERROR;
  }

  if (answer == CORRECT) {
    answer = CalcDeposit(str, dep_in, depOut, add, with);
    if (answer == CORRECT) {
      Tax(depOut);
    }
  }
  return (answer);
}

int DepositModel::CalcDeposit(inputStr str, input dep_in, output* depOut,
                              StackNode** add, StackNode** with) {
  int answer = CORRECT;
  int period = str.regularity == MONTHLY ? 12 : 1;

  for (int i = 1; i <= dep_in.period && answer; ++i) {
    if (*with && i == (*with)->priority) {
      if (dep_in.deposit_sum - (*with)->value <= 0) answer = ERROR;
      dep_in.deposit_sum -= (*with)->value;
      *with = PopStackNode(*with);
    }
    double month_percent = 0;
    if (str.regularity == YEARLY) {
      if (i % 11 == 0 && i != 0) {
        month_percent = dep_in.deposit_sum * dep_in.percent / (100 * period);
      }
    } else
      month_percent = dep_in.deposit_sum * dep_in.percent / (100 * period);
    /* month_percent = dep_in.deposit_sum*dep_in.percent*30.41/(365*100); */

    if (str.capital) dep_in.deposit_sum += month_percent;

    if (*add && i == (*add)->priority) {
      dep_in.deposit_sum += (*add)->value;
      *add = PopStackNode(*add);
    }
    depOut->percent_award += month_percent;
    depOut->total_award = dep_in.deposit_sum;
  }
  return answer;
}

void DepositModel::Tax(output* depOut) {
  double res = depOut->percent_award - 1000000 * 8.5 / 100;
  if (res > 0)
    res *= 0.13;
  else
    res = 0;
  depOut->tax_amount = res;
  return;
}

void DepositModel::OperationsInMonth(StackNode** apex) {
  if (!(*apex) || !((*apex)->next)) {
    return;
  }

  StackNode* apex_buf = *apex;
  StackNode* apex_ret = *apex;

  while (apex_buf) {
    if ((apex_buf->next) &&
        ((apex_buf->next)->priority) == apex_buf->priority) {
      (apex_buf->next)->value += apex_buf->value;
      apex_buf = PopStackNode(apex_buf);
      apex_ret = apex_buf;
    } else {
      apex_buf = apex_buf->next;
    }
  }
  *apex = apex_ret;
}
}  // namespace s21