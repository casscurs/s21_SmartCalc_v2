#include "../s21_calc_model.h"
namespace s21 {
CalcModel::StackNode* CalcModel::PushStackNode(StackNode* apex) {
  StackNode* item = (StackNode*)calloc(1, sizeof(StackNode));
  if (!item) {
    throw CalculatorException("Memory allocation failed for StackNode");
  } else {
    item->what = 0;
    item->priority = 0;
    item->value = 0.0;
    item->next = apex;
  }
  return (item);
}

CalcModel::StackNode* CalcModel::PopStackNode(StackNode* apex) {
  if (!apex) return (nullptr);
  apex->what = 0;
  apex->priority = 0;
  apex->value = 0.0;
  StackNode* following = apex->next;
  free(apex);
  apex = nullptr;
  return (following);
}

void CalcModel::FreeStack(StackNode* apex) {
  while (apex) apex = PopStackNode(apex);
  return;
}

void CalcModel::SortStackByPriority(StackNode** apex) {
  if (!(*apex) || !((*apex)->next)) {
    return;
  }

  StackNode* sorted_stack = nullptr;

  while (*apex) {
    StackNode* current = *apex;
    *apex = (*apex)->next;

    if (!sorted_stack || current->priority <= sorted_stack->priority) {
      /* Входящий меньше, чем лежащий */
      current->next = sorted_stack;
      sorted_stack = current;
    } else {
      /* Входящий больше, чем лежащий */
      StackNode* temp = sorted_stack;

      while (temp->next && current->priority > temp->next->priority) {
        temp = temp->next;
      }

      current->next = temp->next;
      temp->next = current;
    }
  }

  *apex = sorted_stack;
  return;
}
}  // namespace s21