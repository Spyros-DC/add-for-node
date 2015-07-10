#include "distance.h"

int main(){
  clean_file("lines.txt");
  populate_trie("clean.txt");
  populate_vecs();
  compute_norm();
  run_search("collins");
  return 0;
}
