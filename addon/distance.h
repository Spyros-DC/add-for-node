#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <ctime>
#include <assert.h>
using namespace std;

int populate_vecs();
int compute_norm();
int clean_file();
string run_search(string mystr);
pair<int, string> search(string word);
int populate_trie();
int populate_stop_words();
string to_lowercase(string word);
int populate_db();
