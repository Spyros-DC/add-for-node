#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <ctime>
#include <map>
using namespace std;

int populate_vecs();
int compute_norm();
int clean_file(string file_to_clean);
string run_search(string mystr);
pair<int, string> search(string word);
int populate_trie(string some_file);
int populate_stop_words();