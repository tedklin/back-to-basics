#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void print_vector(const std::vector<double>& v) {
  for (const auto& i : v) {
    std::cout << i << " ";
  }
  std::cout << '\n';
}

int main() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(1, 10);

  std::vector<double> v;
  for (int i = 0; i != 11; ++i) {
    v.push_back(dist(mt));
  }

  std::vector<double> v_increasing = v;  // copy
  std::sort(v_increasing.begin(), v_increasing.end());
  std::vector<double> v_decreasing = v;  // copy
  std::sort(v_decreasing.begin(), v_decreasing.end(), std::greater<double>());

  print_vector(v);
  print_vector(v_increasing);
  print_vector(v_decreasing);
  std::cout << '\n';

  std::string s = "welcome to the carushow";
  std::string s_increasing = s;  // copy
  std::sort(s_increasing.begin(), s_increasing.end());
  std::string s_decreasing = s;  // copy
  std::sort(s_decreasing.begin(), s_decreasing.end(), std::greater<double>());

  std::cout << s << '\n' << s_increasing << '\n' << s_decreasing << "\n\n";
}
