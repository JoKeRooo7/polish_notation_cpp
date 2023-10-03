#include "polish_notation.h"

#include <cmath>
#include <stdexcept>  //throw
#include <string>

namespace s21 {

PolishNotation::PolishNotation(const std::string &other_string) {
  set_in_default_entry(other_string);
}

PolishNotation::PolishNotation(const char &other_string) {
  default_entry_ = other_string;
  Сonversion();
}

void PolishNotation::set_in_default_entry(const std::string &other_string,
                                          const double value_x) {
  default_entry_ = other_string;
  Сonversion();
  get_result(value_x);
}

void PolishNotation::set_in_default_entry(const std::string &other_string) {
  default_entry_ = other_string;
  Сonversion();
  get_result(0.0);
}

std::string PolishNotation::get_postfix_entry(const std::string &other_string) {
  set_in_default_entry(other_string);
  return postfix_entry_;
}

std::string PolishNotation::get_postfix_entry() const noexcept {
  return postfix_entry_;
}

std::string PolishNotation::get_default_entry() const noexcept {
  return default_entry_;
}

double PolishNotation::get_result(const std::string &other_string,
                                  const double value_x) {
  set_in_default_entry(other_string, value_x);
  return res_;
}

double PolishNotation::get_result(const std::string &other_string) {
  set_in_default_entry(other_string);
  return res_;
}

double PolishNotation::get_result(const double value_x) {
  if (postfix_entry_[0] == '\0') {
    Сonversion();
  }
  CalculatingPolishNotation(value_x);
  return res_;
}

double PolishNotation::result() const noexcept { return res_; }

double PolishNotation::get_result() {
  get_result(0.0);
  return res_;
}

PolishNotation &PolishNotation::operator=(const std::string &other_string) {
  set_in_default_entry(other_string);
  return *this;
}

PolishNotation &PolishNotation::operator=(const char &other_string) {
  default_entry_ = other_string;
  Сonversion();
  result();
  return *this;
}

void PolishNotation::Сonversion() {
  bool sign = false;
  RemovingSpaces();
  GarbageCleaning();
  for (size_t i = 0; i < default_entry_.size(); ++i) {
    if (default_entry_[i] == 'x') {
      WritingX(i, sign);
    } else if (IsPi(i, default_entry_)) {
      WritingPi(i, sign);
    } else if (default_entry_[i] == 'E' || default_entry_[i] == 'e') {
      WritingAnExponentialRecord(++i);
    } else if (default_entry_[i] == '.') {
      postfix_entry_ += '0';
      WritingNumbers(i, sign);
    } else if (IsNum(default_entry_[i])) {
      WritingNumbers(i, sign);
    } else if (default_entry_[i] == '(') {
      char_stack_.push('(');
    } else if (WritingFunctions(i)) {
      continue;
    } else if (default_entry_[i] == ')') {
      ClosingBracket();
    } else if (WritingOperators(i, sign)) {
      continue;
    }
  }

  while (!char_stack_.empty()) {
    if (char_stack_.top() == '(') {
      throw std::invalid_argument("No closing parenthesis");
    }
    PullingOutOfTheStack();
  }
}

void PolishNotation::WritingAnExponentialRecord(size_t &i) noexcept {
  if (CheckPriority(default_entry_[i] == '1')) {
    OperatorPriority('*');
    postfix_entry_ += '1';
    postfix_entry_ += '0';
    postfix_entry_ += ' ';
    OperatorPriority('^');
    bool sign = (default_entry_[i] == '-') ? true : false;
    WritingNumbers(++i, sign);
  }
}

void PolishNotation::WritingX(size_t &i, bool &sign) noexcept {
  postfix_entry_ += default_entry_[i];
  CheckWritingMinus(sign);
  postfix_entry_ += ' ';
}

void PolishNotation::CheckWritingMinus(bool &sign) noexcept {
  if (sign == true) {
    postfix_entry_ += "1- ";
    OperatorPriority('*');
    sign = false;
  }
}

void PolishNotation::WritingPi(size_t &i, bool &sign) noexcept {
  postfix_entry_ += 'p';
  postfix_entry_ += 'i';
  CheckWritingMinus(sign);
  postfix_entry_ += ' ';
  ++i;
}

void PolishNotation::WritingNumbers(size_t &i, bool &sign) noexcept {
  while (default_entry_[i] == '.' || (IsNum(default_entry_[i]))) {
    postfix_entry_ += default_entry_[i++];
  }
  --i;
  if (sign) {
    sign = false;
    postfix_entry_ += '-';
  }
  postfix_entry_ += ' ';
}

char PolishNotation::CheckPriority(char symbol) noexcept {
  char priority = '0';
  if (symbol == '+') {
    priority = '1';
  } else if (symbol == '-') {
    priority = '1';
  } else if (symbol == '*') {
    priority = '2';
  } else if (symbol == '/') {
    priority = '2';
  } else if (symbol == '^') {
    priority = '3';
  } else if (IsLetter(symbol)) {
    priority = '4';
  }

  return priority;
}

bool PolishNotation::WritingFunctions(size_t &i) {
  bool was_function = false;
  if (IsSqrtFunction(i, default_entry_)) {
    was_function = PushBackFucntion(i, 4);
  } else if (IsModFunction(i, default_entry_) ||
             IsLogFunction(i, default_entry_)) {
    was_function = PushBackFucntion(i, 3);
  } else if (IsNaturalLogFunction(i, default_entry_)) {
    was_function = PushBackFucntion(i, 2);
  } else if (IsArcFunction(i, default_entry_)) {
    ProcessWritingArcFunction(i, was_function);
  } else {
    TrigonometryFunction(i, was_function);
  }
  if (was_function) --i;
  return was_function;
}

bool PolishNotation::IsPi(size_t &i, std::string str) noexcept {
  return (str[i] == 'p' && str[i + 1] == 'i');
}

bool PolishNotation::IsModFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd');
}

bool PolishNotation::IsLogFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g');
}

bool PolishNotation::IsNaturalLogFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 'l' && str[i + 1] == 'n');
}

bool PolishNotation::IsSinFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n');
}

bool PolishNotation::IsCosFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's');
}

bool PolishNotation::IsTanFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n');
}

bool PolishNotation::IsArcFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 'a' && str[i + 1] == 'r' && str[i + 2] == 'c');
}

bool PolishNotation::IsSqrtFunction(size_t &i, std::string str) noexcept {
  return (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
          str[i + 3] == 't');
}

bool PolishNotation::ProcessWritingArcFunction(size_t &i, bool &was_function) {
  PushBackFucntion(i, 3);
  TrigonometryFunction(i, was_function);
  if (!was_function) {
    throw std::invalid_argument("Error on " + std::to_string(i) + " symvol");
  }
  return was_function;
}

void PolishNotation::TrigonometryFunction(size_t &i,
                                          bool &was_function) noexcept {
  if (IsSinFunction(i, default_entry_)) {
    was_function = PushBackFucntion(i, 3);
  } else if (IsCosFunction(i, default_entry_)) {
    was_function = PushBackFucntion(i, 3);
  } else if (IsTanFunction(i, default_entry_)) {
    was_function = PushBackFucntion(i, 3);
  }
}

bool PolishNotation::PushBackFucntion(size_t &i, size_t how_much) noexcept {
  size_t limit = i + how_much;
  while (i != limit) {
    char_stack_.push(default_entry_[i++]);
  }
  return true;
}

void PolishNotation::ClosingBracket() {
  while (!char_stack_.empty() && char_stack_.top() != '(') {
    PullingOutOfTheStack();
  }
  if (char_stack_.empty()) {
    throw std::invalid_argument("No opening parenthesis");
  }
  char_stack_.pop();
}

void PolishNotation::PullingOutOfTheStack() noexcept {
  if (!TakeFunctionsOffTheStack()) {
    postfix_entry_ += char_stack_.top();
    char_stack_.pop();
  }
  postfix_entry_ += ' ';
}

bool PolishNotation::TakeFunctionsOffTheStack() noexcept {
  if (!IsLetter(char_stack_.top())) {
    return false;
  }
  std::string new_str;
  while (!char_stack_.empty() && IsLetter(char_stack_.top())) {
    new_str += char_stack_.top();
    char_stack_.pop();
  }
  for (int i = new_str.size() - 1; i >= 0; --i) {
    postfix_entry_ += new_str[i];
  }

  return true;
}

bool PolishNotation::IsLetter(char symbol) noexcept {
  return (symbol >= 'a' && symbol <= 'z');
}

bool PolishNotation::IsNum(char symbol) noexcept {
  return (symbol >= '0' && symbol <= '9');
}

bool PolishNotation::IsMoreOneS(
    size_t &i) noexcept {  // it's more than one character
  return i == 0 && default_entry_.size() > 1;
}

bool PolishNotation::WritingOperators(size_t &i, bool &sign) noexcept {
  if (CheckPriority(default_entry_[i]) == '0') {
    return false;
  }

  if (IsMoreOneS(i) && !(CheckNextElement(i))) {
    if (default_entry_[i] == '-') {
      sign = true;
    }
  } else if ((IsMoreOneS(i) && CheckNextElement(i)) || ConditionOne(i)) {
    if (default_entry_[i] == '-') {
      char_stack_.push('*');
      postfix_entry_ += "1- ";
    }
  } else if (ConditionTwo(i)) {
    sign = (default_entry_[i] == '-') ? true : false;
  } else {
    OperatorPriority(default_entry_[i]);
  }

  return true;
}

bool PolishNotation::CheckLastElement(size_t &i) noexcept {
  return (CheckPriority(default_entry_[i - 1]) != '0' &&
          CheckPriority(default_entry_[i - 1]) != '4') ||
         default_entry_[i - 1] == '(';
}

bool PolishNotation::CheckNextElement(size_t &i) noexcept {
  return ((default_entry_[i + 1] == '(' || IsLetter(default_entry_[i + 1])) &&
          !IsNum(default_entry_[i + 1]));
}

bool PolishNotation::ConditionOne(size_t &i) noexcept {
  return CheckLastElement(i) && CheckNextElement(i);
}

bool PolishNotation::ConditionTwo(size_t &i) noexcept {
  return CheckLastElement(i) && CheckPriority(default_entry_[i]) == '1';
}

bool PolishNotation::NeedTakeSymbol(
    char element) noexcept {  // do I need to pull out the symbol
  return !char_stack_.empty() &&
         !(element == '^' && element == char_stack_.top()) &&
         CheckPriority(char_stack_.top()) >= CheckPriority(element);
}

void PolishNotation::OperatorPriority(char element) noexcept {
  while (NeedTakeSymbol(element)) {
    PullingOutOfTheStack();
  }
  char_stack_.push(element);
}

void PolishNotation::RemovingSpaces() noexcept {
  for (size_t i = 0; i < default_entry_.size(); ++i) {
    if (default_entry_[i] == ' ') {
      default_entry_.erase(i--, 1);
    }
  }
}

void PolishNotation::GarbageCleaning() noexcept {
  postfix_entry_.clear();
  while (!char_stack_.empty()) char_stack_.pop();
  while (!num_stack_.empty()) num_stack_.pop();
}

void PolishNotation::CalculatingPolishNotation(const double value_x) {
  for (size_t i = 0; i < postfix_entry_.size(); ++i) {
    if (postfix_entry_[i] == ' ') {
      continue;
    } else if (postfix_entry_[i] == 'x') {
      num_stack_.push(value_x);
    } else if (IsPi(i, postfix_entry_)) {
      num_stack_.push(kPi);
      i++;
    } else if (IsNum(postfix_entry_[i])) {
      ReadingNumbers(i);
    } else {
      ReadingFunctionsAndOperator(i);
    }
  }
  if (postfix_entry_.size() != 0) {
    res_ = TakingFromTheStack();
  }
  if (!num_stack_.empty()) {
    throw std::invalid_argument("Not enough operators or functions");
  }
}

void PolishNotation::ReadingNumbers(size_t &i) noexcept {
  num_stack_.push(0.0);
  ConversionToNumbers(i, true);
  if (postfix_entry_[i] == '.') {
    ConversionToNumbers(++i, false);
  }
  if (postfix_entry_[i] == '-') {
    num_stack_.top() *= (-1);
  }
}

void PolishNotation::ConversionToNumbers(size_t &i, bool integers) noexcept {
  for (int j = 1; IsNum(postfix_entry_[i]); ++j) {
    if (integers) {
      num_stack_.top() *= 10;
      num_stack_.top() += postfix_entry_[i++] - 48;
    } else {
      num_stack_.top() += (postfix_entry_[i++] - 48) * std::pow(10, -j);
    }
  }
}

void PolishNotation::ReadingFunctionsAndOperator(size_t &i) {
  if (!ReadingOperators(i)) {
    if (!ReadingFunctions(i)) {
      throw std::invalid_argument(std::string("Unknown symvol - ") +
                                  postfix_entry_[i]);
    }
  }
}

bool PolishNotation::ReadingOperators(size_t &i) {
  char s = postfix_entry_[i];  // symvol
  if (s == '^' || s == '*' || s == '/' || s == '+' || s == '-') {
    return ProcessReadingOperator(i);
  }
  return false;
}

bool PolishNotation::ProcessReadingOperator(size_t &i) {
  double number_one = TakingFromTheStack();
  double number_two = TakingFromTheStack();

  switch (postfix_entry_[i]) {
    case '^':
      num_stack_.push(std::pow(number_two, number_one));
      break;
    case '*':
      num_stack_.push(number_two * number_one);
      break;
    case '/':
      num_stack_.push(number_two / number_one);
      break;
    case '+':
      num_stack_.push(number_two + number_one);
      break;
    case '-':
      num_stack_.push(number_two - number_one);
      break;
  }

  return true;
}

double PolishNotation::TakingFromTheStack() {
  if (num_stack_.empty()) {
    throw std::invalid_argument("Not enough numbers");
  }
  double number = num_stack_.top();
  num_stack_.pop();
  return number;
}

bool PolishNotation::ReadingFunctions(size_t &i) {
  if (IsLetter(postfix_entry_[i])) {
    return ProcessReadingFunctions(i);
  }

  return false;
}

bool PolishNotation::ProcessReadingFunctions(size_t &i) {
  double number = TakingFromTheStack();
  if (IsNaturalLogFunction(i, postfix_entry_)) {
    num_stack_.push(std::log(number));
    i += 2;
  } else if (IsLogFunction(i, postfix_entry_)) {
    num_stack_.push(std::log10(number));
    i += 3;
  } else if (IsModFunction(i, postfix_entry_)) {
    double number_two = TakingFromTheStack();
    num_stack_.push(std::fmod(number_two, number));
    i += 3;
  } else if (IsSinFunction(i, postfix_entry_)) {
    num_stack_.push(std::sin(number));
    i += 3;
  } else if (IsCosFunction(i, postfix_entry_)) {
    num_stack_.push(std::cos(number));
    i += 3;
  } else if (IsTanFunction(i, postfix_entry_)) {
    num_stack_.push(std::tan(number));
    i += 3;
  } else if (IsSqrtFunction(i, postfix_entry_)) {
    num_stack_.push(std::sqrt(number));
    i += 4;
  } else if (IsArcFunction(i, postfix_entry_)) {
    i += 3;
    ProcessReadingArcFunctions(i, number);
  } else {
    return false;
  }

  return true;
}

void PolishNotation::ProcessReadingArcFunctions(size_t &i,
                                                double &number) noexcept {
  if (IsSinFunction(i, postfix_entry_)) {
    i += 3;
    num_stack_.push(std::asin(number));
  } else if (IsCosFunction(i, postfix_entry_)) {
    i += 3;
    num_stack_.push(std::acos(number));
  } else if (IsTanFunction(i, postfix_entry_)) {
    i += 3;
    num_stack_.push(std::atan(number));
  }
}

}  // namespace s21
