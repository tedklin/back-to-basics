#include <iostream>
#include <stack>
#include <string>

bool is_balanced(const std::string& s) {
  std::stack<char> stack_;
  for (auto iter = s.cbegin(); iter != s.cend(); ++iter) {
    if (*iter == '(') {
      stack_.push('(');  // meaningless, should probably change?
    } else if (*iter == ')') {
      if (!stack_.empty()) {
        stack_.pop();
      } else {
        std::cout << "offending closing parenthesis found at index "
                  << iter - s.cbegin() << '\n';
        return false;
      }
    }
  }
  if (!stack_.empty()) {
    std::cout << "unclosed parentheses exist\n";
  }
  return stack_.empty();
}

void run(const std::string& s) {
  std::cout << "is " << s << " balanced?\n" << is_balanced(s) << "\n\n";
}

int main() {
  std::string proper("((())())()");
  std::string improper1(")()(");
  std::string improper2("())");
  std::string improper3("(()");

  run(proper);
  run(improper1);
  run(improper2);
  run(improper3);
}
