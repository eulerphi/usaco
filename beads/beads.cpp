/*
ID: eulerphi
PROG: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");

    int num_beads;
    fin >> num_beads;

    char c;
    string colors;
    while (fin >> c) {
      colors += c;
    }

    string hay = colors + colors + colors;

    int max_cnt = 0;
    int cnt = 0, pcnt = 0;
    for (int j = 0; j < hay.size(); ++j) {
      char current = hay[j];
      cnt = 1;
      pcnt = 0;
      for (int i = j + 1; i < hay.size(); i++) {
        if (current != hay[i] && current != 'w' && hay[i] != 'w') {
          max_cnt = max(cnt + pcnt, max_cnt);
          pcnt = cnt;
          cnt = 0;
        }
        current = hay[i] != 'w' ? hay[i] : current;
        ++cnt;
      }
      max_cnt = max(cnt + pcnt, max_cnt);
    }
    max_cnt = max(cnt + pcnt, max_cnt);

    fout << min(num_beads, max_cnt) << endl;

    return 0;
}
