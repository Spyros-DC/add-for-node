#include "distance.h"

unordered_set< string > stop_words;
vector<string> the_titles;
int populate_stop_words(){
  ifstream myfile;
  string word;
  myfile.open("lemur_stopwords.txt");
  if(myfile.is_open()){
    while(!myfile.eof()){
      myfile >> word;
      stop_words.insert(word);
    }
  }else
    cout << "unable to open file lemur_stopwords!" << endl;
  return 0;
}

string to_lowercase(string word){
  int i=0;
  string ret_str;
  char c;
  while (word[i])
    {
      c=word[i];
      ret_str += tolower(c);
      i++;
    }
  return ret_str;
}

int clean_file(string file_to_clean) {
  string line, word, dest_line, dest_word;
  ifstream myfile;
  myfile.open (file_to_clean);
  ofstream destination_file;
  destination_file.open("clean.txt");
  if (myfile.is_open())
    {
      while (! myfile.eof() )
	{
	  getline (myfile,line);
	  istringstream iss(line);
	  while(iss >> word){
	    dest_word =  to_lowercase(word);
	    if(stop_words.count(dest_word) == 0 ){
	      dest_line += dest_word + ' ';
	    }
	  }
	  the_titles.push_back(line);
	  dest_line += '\n';
	}
      destination_file << dest_line;
      myfile.close();
      destination_file.close();
    }

  else cout << "Unable to open file";
    
  return 0;
}
