#ifndef LIST_HH
#define LIST_HH

#include <string>

using namespace std;

class List {
public:
  List();

  void add_back(const string& task_to_be_added);
  bool remove_front(string& removed_task);
  bool is_empty() const;
  void print() const;

  ~List();

private:
  struct List_item {
     string task;
     List_item* next;
  };

  List_item* first_;
  List_item* last_;
};

#endif
