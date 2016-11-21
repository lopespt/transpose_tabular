#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool validade(string str) {
  return str.find("\\begin{tabular}") && str.find("\\end{tabular}");
}

string read_all() {
  char temp[300];
  string s;
  while (cin.getline(temp, 300)) {
    s = s + "\n" + temp;
  }
  return s;
}

void replace_inplace(std::string &subject, const std::string &search,
                     const std::string &replace) {
  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
}

void remove_keywords(string &s) {
  replace_inplace(s, "\\hline", "");
  int idx = s.find("\\end");
  s.erase(idx, s.length() - idx);
  //  replace_inplace(s, "\\\\", "");
  replace_inplace(s, "\r\n", "");
  replace_inplace(s, "\n", "");
}

string transpose_tabular(string str) {
  remove_keywords(str);
  vector<vector<string>> cells;
  cells.emplace_back();

  int actual_pos = str.find("tabular");
  int next_pos;
  actual_pos = str.find("}", actual_pos + 8);

  while (actual_pos > 0) {
    next_pos = min(str.find("&", actual_pos), str.find("\\\\", actual_pos));
    string c = str.substr(actual_pos + 1, next_pos - actual_pos - 1);
    // cout << actual_pos << "  " << next_pos << endl;
    cells.back().push_back(c);

    if (str.find("\\\\", next_pos) == next_pos)
      cells.emplace_back();

    actual_pos = next_pos + 1;
  }
  cells.pop_back();
  cells.pop_back();

  int h = cells.size();
  int w = cells[0].size();
  stringstream sout;

  int j = 0;
  for (int i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      if (i < cells[j].size()) {
        sout << cells[j][i];
        if (j == h - 1)
          sout << "\\\\\n";
        else
          sout << " & ";
      }
    }
  }

  return sout.str();
  for (auto a : cells) {
    for (auto b : a) {
      //     cout << b << " |  ";
    }
    //    cout << "\n===\n" << endl;
  }
  return "";
}

int main(int argc, const char *argv[]) {
  string s = read_all();
  if (validade(s)) {

    s = transpose_tabular(s);
  }
  cout << s << endl;

  return 0;
}
