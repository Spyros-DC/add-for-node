#include "distance.h"

int main(){
  string mystr;
  populate_stop_words();
  clean_file();
  populate_trie();
  populate_vecs();
  compute_norm();
  populate_db();
  cout << "a title please!" << endl;
  getline(cin, mystr);
  cout << run_search(mystr) << endl;
  return 0;
}
