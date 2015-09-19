#include "distance.h"

class trie{
public:
  string word;
  map<char, trie*> children;
  // this function works
  // with the argument flag set to zero
  int insert(string w, int flag, string remaining_w){ 
    char the_char;
    //the first time we call insert
    if(flag == 0)
      remaining_w = w;
    int the_size = remaining_w.size();

    if(the_size == 0){
      word = w;
      return 0;
    }else{
      if(children.count(remaining_w[0]) == 0){
	children[remaining_w[0]] = new trie();
	assert(children[remaining_w[0]] != 0);
      }
      //the recursive calls with flag one
      the_char = remaining_w[0];
      remaining_w.erase(0, 1);
      children[the_char]->insert(w, 1, remaining_w);
      return 0;
    }
  }
};


 
// The tree
trie tree;
 
// The cost for vector initialization and the edit distance(max_cost)
const int too_big_distance = 10;
const int max_cost = 1;


int search_recursive(trie* p_tree, char ch, const string& word, vector<int>& previous_row, int max_cost, map<string, int>& results)
{
    int sz = previous_row.size();
    int min_row = 12;
 
    vector<int> current_row(sz, too_big_distance);
    current_row[0] = previous_row[0] + 1;
 
    // Calculate the min cost of insertion, deletion, match or substution
    int insert_or_del, replace;
    for (int i = 1; i < sz; i++) {
        insert_or_del = min(current_row[i-1] + 1, previous_row[i] + 1);
        replace = (word[i-1] == ch) ? previous_row[i-1] : (previous_row[i-1] + 1);
 
        current_row[i] = min(insert_or_del, replace);
    }
 

    if ((current_row[sz-1] <= max_cost) && (p_tree->word != "") ) {
	results[p_tree->word] = current_row[sz-1];
	return 0;
    }

    for(vector<int>::iterator it = current_row.begin();it!=current_row.end();++it){
      if((*it) < min_row)
	min_row = *it;
    }
    if(min_row <= max_cost){
      for(map<char, trie*>::iterator  it = (p_tree->children).begin(); it!= (p_tree->children).end();++it){
	search_recursive((*it).second, (*it).first, word, current_row, max_cost, results);
      }
    }
    
    return 0;
    
}

 
pair<int, string> search(string word)
{
  pair <int, string> res_pair;
  res_pair = make_pair(0, "");
  map <string, int> results;
     
  int sz = word.size();
 
  vector<int> current_row(sz + 1);
 
  for (int i = 0; i <= sz; ++i){ 
    current_row[i] = i;
  }
 
  for(map<char, trie*>::iterator it = tree.children.begin(); it!= tree.children.end();++it){
    search_recursive((*it).second, (*it).first, word, current_row, max_cost, results);
  }

  for(map<string, int>::iterator p = results.begin();p!=results.end();++p){
    res_pair.first = 1;
    res_pair.second = (*p).first;
  }

  return res_pair;
}

int populate_trie(){
  string word;
  pair <int, string> res_pair;
  ifstream ifp("clean.txt");
  if(ifp.is_open()){
    while(ifp >> word){
      tree.insert(word, 0, "");
    }
    ifp.close();
  }
  return 0;
}
