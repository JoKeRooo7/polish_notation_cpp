#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_POLISH_NOTATION_H_
#define CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_POLISH_NOTATION_H_

#include <stack>
#include <string>

namespace s21 {

const double kPi = 3.1415926535897932;

class PolishNotation {
 public:
  PolishNotation() = default;
  explicit PolishNotation(const std::string &other_string);
  explicit PolishNotation(const char &other_string);
  PolishNotation(const PolishNotation &other) = default;
  PolishNotation(PolishNotation &&other) = default;
  ~PolishNotation() = default;

  void set_in_default_entry(const std::string &other_string,
                            const double value_x);
  void set_in_default_entry(const std::string &other_string);
  std::string get_postfix_entry(const std::string &other_string);
  std::string get_postfix_entry() const noexcept;
  std::string get_default_entry() const noexcept;
  double get_result(const std::string &other_string, const double value_x);
  double get_result(const std::string &other_string);
  double get_result(const double value_x);
  double get_result();
  double result() const noexcept;

  PolishNotation &operator=(const std::string &other_string);
  PolishNotation &operator=(const char &other_string);
  PolishNotation &operator=(const PolishNotation &other) = default;
  PolishNotation &operator=(PolishNotation &&other) = default;

 private:
  std::stack<char> char_stack_{};
  std::stack<double> num_stack_{};
  std::string default_entry_;
  std::string postfix_entry_;
  double res_{0};

  // for writing in postfix_entry_
  void Сonversion();
  void WritingAnExponentialRecord(size_t &i) noexcept;
  void WritingX(size_t &i, bool &sign) noexcept;
  void CheckWritingMinus(bool &sign) noexcept;
  void WritingNumbers(size_t &i, bool &sign) noexcept;
  void WritingPi(size_t &i, bool &sign) noexcept;
  char CheckPriority(char symbol) noexcept;
  bool WritingFunctions(size_t &i);
  bool IsPi(size_t &i, std::string str) noexcept;
  bool IsModFunction(size_t &i, std::string str) noexcept;
  bool IsLogFunction(size_t &i, std::string str) noexcept;
  bool IsNaturalLogFunction(size_t &i, std::string str) noexcept;
  bool IsSinFunction(size_t &i, std::string str) noexcept;
  bool IsCosFunction(size_t &i, std::string str) noexcept;
  bool IsTanFunction(size_t &i, std::string str) noexcept;
  bool IsArcFunction(size_t &i, std::string str) noexcept;
  bool IsSqrtFunction(size_t &i, std::string str) noexcept;
  bool ProcessWritingArcFunction(size_t &i, bool &was_function);
  void TrigonometryFunction(size_t &i, bool &sign) noexcept;
  bool PushBackFucntion(size_t &i, size_t how_much) noexcept;
  void ClosingBracket();
  void PullingOutOfTheStack() noexcept;
  bool TakeFunctionsOffTheStack() noexcept;
  bool IsLetter(char symbol) noexcept;
  bool IsNum(char symbol) noexcept;
  bool IsMoreOneS(size_t &i) noexcept;
  bool WritingOperators(size_t &i, bool &sign) noexcept;
  bool CheckLastElement(size_t &i) noexcept;
  bool CheckNextElement(size_t &i) noexcept;
  bool ConditionOne(size_t &i) noexcept;
  bool ConditionTwo(size_t &i) noexcept;
  bool NeedTakeSymbol(char element) noexcept;
  void OperatorPriority(char element) noexcept;
  void RemovingSpaces() noexcept;
  void GarbageCleaning() noexcept;

  // reading from Polish notation
  void CalculatingPolishNotation(const double value_x);
  void ReadingNumbers(size_t &i) noexcept;
  void ConversionToNumbers(size_t &i, bool integers) noexcept;
  void ReadingFunctionsAndOperator(size_t &i);
  bool ReadingOperators(size_t &i);
  bool ProcessReadingOperator(size_t &i);
  double TakingFromTheStack();
  bool ReadingFunctions(size_t &i);
  bool ProcessReadingFunctions(size_t &i);
  void ProcessReadingArcFunctions(size_t &i, double &number) noexcept;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_POLISH_NOTATION_H_
