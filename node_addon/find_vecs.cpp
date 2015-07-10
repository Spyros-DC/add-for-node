#include "distance.h"

// every title is a dimension in the vector space
// every word that belong to some title
// is a unit vector 
// every query is just the addition
// of vector words

// every word appears at most once 
// in every title
// so we can simplify the calculations
// and compute the norms with just one line of code 

extern vector <string> the_titles;
unordered_map<string, unordered_set<int> > the_ints;
unordered_map<string, float > the_norms;
struct show_greater{
  bool operator()(const float& first, const float& second) const{
    return first > second;
  }
};
unordered_map< int, float > the_stats;
multimap<float, string, show_greater> the_results; // multimap allow same keys
 
int populate_vecs() {
  string line, word;
  ifstream myfile ("clean.txt");
  int counter = 1;
  if (myfile.is_open())
    {
      while (! myfile.eof() )
	{
	  getline (myfile,line);
	  istringstream iss(line);
	  while(iss >> word){
	    the_ints[word].insert(counter);
	    the_norms[word] = 1;
	  }
	  counter++;
	}
      myfile.close();
    }

  else cout << "Unable to open file";
    
  return 0;
}

int compute_norm(){
  for(auto& p: the_norms){
    the_norms[p.first] = 1 / sqrt(the_ints[p.first].size());
  }
  return 0;
}

int compute_stats(string word){
  for(auto& p: the_ints[word]){
    if(the_stats.count(p) == 0){
      the_stats[p] = the_norms[word];
    }
    else
      the_stats[p] += the_norms[word];
  }
  return 0;
}

string begin_stats(string mystr){
  int  counter = 0;		
  pair<int, string> res;
  string new_line("\n");
  string word, string_ret;
  string noresult = "no results found";
  res = make_pair(0, "");
  istringstream iss(mystr);
  while(iss >> word){
    compute_stats(word);
  }
  if(the_stats.size() != 0){
    for(auto& p: the_stats){
      the_results.insert(make_pair(p.second, the_titles[p.first - 1]));
    }
  }else{
    istringstream iss(mystr);
    while(iss >> word){
      res = search(word);
      if(res.first == 1){
	compute_stats(res.second);
      }
    }
    for(auto& p: the_stats)
      the_results.insert(make_pair(p.second, the_titles[p.first - 1]));
  }

  for(auto&  it : the_results){
    if(counter == 20) // max number of titles to return
      break;
    cout << it.second << ", " << it.first << endl;
    string_ret += it.second;
    string_ret += new_line;
    counter += 1;
  }
  return string_ret;
}

string run_search(string mystr){
  the_stats.clear();
  the_results.clear();
  return    begin_stats(mystr);
}
