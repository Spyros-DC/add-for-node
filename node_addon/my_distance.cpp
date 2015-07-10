#include "distance.h"

class trie{
public:
  string word;
  unordered_map<char, trie*> children;

  // this function works
  // with the argument flag set to zero
  int insert(string w, int flag, string remaining_w = ""){ 
    //the first time we call insert
    if(flag == 0)
      remaining_w = w;
    int the_size = remaining_w.size();

    if(children.count(remaining_w[0]) == 0){
      children[remaining_w[0]] = new trie();
    }
    if(the_size == 0){
      word = w;
      return 0;
    }else{
      //the recursive calls with flag one
      children[remaining_w[0]]->insert(w, 1, remaining_w.erase(0, 1));
      return 0;
    }
  }
};


 
// The tree
trie tree;
 
// The cost and a distance for vector initialization
const int too_big_distance = 10;
const int max_cost = 1;


int search_recursive(trie* p_tree, char ch, const string& word, vector<int>& previous_row, int max_cost, unordered_map <string, int>& results)
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
 

    if ((current_row[sz-1] <= max_cost) && (p_tree->word != "")) {
	results[p_tree->word] = current_row[sz-1];
	return 0;
    }

    for(auto& it: current_row){
      if(it < min_row)
	min_row = it;
    }
    if(min_row <= max_cost){
      for(auto& it: p_tree->children){
	search_recursive(it.second, it.first, word, current_row, max_cost, results);
      }
    }
    
    return 0;
    
}

 
pair<int, string> search(string word)
{
  pair <int, string> res_pair;
  res_pair = make_pair(0, "");
  unordered_map <string, int> results;
     
  int sz = word.size();
 
  vector<int> current_row(sz + 1);
 
  for (int i = 0; i <= sz; ++i){ 
    current_row[i] = i;
  }
 
  for(auto& it: tree.children){
    search_recursive(it.second, it.first, word, current_row, max_cost, results);
  }

  for(auto& p:results){
    res_pair.first = 1;
    res_pair.second = p.first;
  }

  return res_pair;
}

int populate_trie(string some_file){
  string word;
  ifstream ifp(some_file);
  while(ifp >> word){
    tree.insert(word, 0);
  }
  return 0;
}
