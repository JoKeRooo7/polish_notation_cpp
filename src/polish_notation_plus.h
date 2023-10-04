#ifndef POLISH_NOTATION_CPP_POLISH_NOTATION_PLUS_H_
#define POLISH_NOTATION_CPP_POLISH_NOTATION_PLUS_H_

#include <stack>
#include <string>
#include <cmath>
#include <map>

namespace jokerooo7 {

const double kPi = std::acos(-1.0);
const double kEuler = std::exp(1.0);

class PolishNotation {
 public:
  PolishNotation() = default;
  explicit PolishNotation(const std::string &other_string);
  explicit PolishNotation(const std::wstring &other_string);
  explicit PolishNotation(const wchar_t &other_string);
  explicit PolishNotation(const char &other_string);
  PolishNotation(const PolishNotation &other) = default;
  PolishNotation(PolishNotation &&other) = default;
  ~PolishNotation() = default;

  void set_in_default_entry(const std::string &other_string,
                            const std::map<char, double>& arg_values);
  void set_in_default_entry(const std::wstring &other_string,
                            const std::map<char, double>& arg_values);
  void set_in_default_entry(const std::wstring &other_string);
  void set_in_default_entry(const std::string &other_string);
  std::wstring get_postfix_entry(const std::string &other_string);
  std::wstring get_postfix_entry(const std::wstring &other_string);
  std::wstring get_postfix_entry() const noexcept;
  std::wstring get_default_entry() const noexcept;
  double get_result(const std::wstring &other_string, const std::map<char, double>& arg_values);
  double get_result(const std::string &other_string, const std::map<char, double>& arg_values);
  double get_result(const std::wstring &other_string);
  double get_result(const std::string &other_string);
  double get_result(const std::map<char, double>& arg_values);
  double get_result();
  double result() const noexcept;

  PolishNotation &operator=(const std::wstring &other_string);
  PolishNotation &operator=(const std::string &other_string);
  PolishNotation &operator=(const wchar_t &other_string);
  PolishNotation &operator=(const char &other_string);
  PolishNotation &operator=(const PolishNotation &other) = default;
  PolishNotation &operator=(PolishNotation &&other) = default;

 private:
  std::stack<wchar_t> char_stack_{};
  std::stack<double> num_stack_{};
  std::wstring default_entry_;
  std::wstring postfix_entry_;
  double res_{0};
  
  // for writing in postfix_entry_
  void Сonversion();
  void WritingAnExponentialRecord(size_t &i) noexcept;
  void WritingLetter(size_t &i, bool &sign) noexcept;
  void CheckWritingMinus(bool &sign) noexcept;
  void WritingNumbers(size_t &i, bool &sign) noexcept;
  void WritingPi(size_t &i, bool &sign) noexcept;
  char CheckPriority(char symbol) noexcept;
  bool WritingFunctions(size_t &i);
  bool IsPi(size_t &i, std::wstring& str) noexcept;
  bool IsSingleСharacter(size_t &i, std::wstring& str) noexcept;
  bool IsExponent(size_t &i, std::wstring& str) noexcept;
  bool IsModFunction(size_t &i, std::wstring& str) noexcept;
  bool IsLogFunction(size_t &i, std::wstring& str) noexcept;
  bool IsNaturalLogFunction(size_t &i, std::wstring& str) noexcept;
  bool IsSinFunction(size_t &i, std::wstring& str) noexcept;
  bool IsCosFunction(size_t &i, std::wstring& str) noexcept;
  bool IsTanFunction(size_t &i, std::wstring& str) noexcept;
  bool IsArcFunction(size_t &i, std::wstring& str) noexcept;
  bool IsSqrtFunction(size_t &i, std::wstring& str) noexcept;
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
  void CalculatingPolishNotation(const std::map<char, double>& arg_values);
  void ReadingNumbers(size_t &i) noexcept;
  void ConversionToNumbers(size_t &i, bool integers) noexcept;
  bool ReadingOperators(size_t &i);
  bool ProcessReadingOperator(size_t &i);
  double TakingFromTheStack();
  bool ReadingFunctions(size_t &i);
  bool ProcessReadingFunctions(size_t &i);
  void ProcessReadingArcFunctions(size_t &i, double &number) noexcept;
  // convert 
  void ConvertInString(const std::string& other_string);
};

}  // namespace jokerooo7

#endif  // POLISH_NOTATION_CPP_POLISH_NOTATION_PLUS_H_
