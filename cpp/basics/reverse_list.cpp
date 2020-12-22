#include <iostream>

class List {
 public:
  List(int element, List* next) : element_(element), next_(next) {}
  int element_;
  List* next_;

  // check this?
  ~List() {
    if (next_ != nullptr) {
      delete next_;
    }
  }
};

void print_list(List* list) {
  while (list) {
    std::cout << list->element_ << ' ';
    list = list->next_;
  }
  std::cout << '\n';
}

List* reverse_list(List* list) {
  List* prev = nullptr;
  List* curr = list;
  List* next = curr->next_;
  while (next) {
    curr->next_ = prev;
    prev = curr;
    curr = next;
    next = curr->next_;
  }
  curr->next_ = prev;
  return curr;
}

int main() {
  // create the list
  List* root = new List(0, nullptr);
  List* prev = root;
  for (int i = 1; i != 10; ++i) {
    List* curr = new List(i, nullptr);
    prev->next_ = curr;
    prev = curr;
  }

  // reverse
  print_list(root);
  root = reverse_list(root);
  print_list(root);
  delete root;
  std::cout << "cleaned\n";
}
