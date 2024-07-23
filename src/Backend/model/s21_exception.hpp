#ifndef S21_EXCEPTION_HPP
#define S21_EXCEPTION_HPP

#include <exception>
#include <string>

namespace s21 {

class CalculatorException : public std::exception {
 private:
  std::string message;

 public:
  /**
   * @brief Конструктор для исключений
   * @param message сообщение об ошибке
   */
  explicit CalculatorException(const std::string& message) : message(message) {}
  const char* what() const noexcept override { return message.c_str(); }
};

}  // namespace s21

#endif  // S21_EXCEPTION_HPP