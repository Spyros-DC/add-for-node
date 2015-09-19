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
map<string, set<int> > the_ints;
map<string, float > the_norms;
struct show_greater{
    bool operator()(const float& first, const float& second) const{
        return first > second;
    }
};
map< int, float > the_stats;
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
                if(word == "wb"){
                    the_ints["workbook"].insert(counter);
                    the_norms["workbook"] = 1;
                }else if(word == "sb"){
                    the_ints["student"].insert(counter); 
                    the_norms["student"] = 1;
                    the_ints["student's"].insert(counter); 
                    the_norms["student's"] = 1;
                    the_ints["student 's"].insert(counter); 
                    the_norms["student 's"] = 1;
                }else{
                    the_ints[word].insert(counter);
                    the_norms[word] = 1;
                }
            }
            counter++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}

int compute_norm(){
    for(map<string,float > ::iterator p = the_norms.begin(); p!= the_norms.end(); p++){
        the_norms[(*p).first] = 1 / sqrt(the_ints[(*p).first].size());
    }
    return 0;
}

int compute_stats(string word){
    for(set<int> ::iterator p = the_ints[word].begin(); p!= the_ints[word].end(); ++p){
        if(the_stats.count(*p) == 0){
            the_stats[*p] = the_norms[word];
        }
        else
            the_stats[*p] += the_norms[word];
    }
    return 0;
}

string begin_stats(string mystr){
    int  counter = 0;
    int boolian = 0;
    pair<int, string> res;
    string word, string_ret, new_line("\n");
    res = make_pair(0, "");
    istringstream iss(mystr);
    while(iss >> word){
        if(the_ints.count(word) == 1){ //if there is such word 
            compute_stats(word);
            if(word.size() > 3) //and if that word is bigger than 3 bytes
                boolian = 1;
        }
    }
    if(boolian == 1){
        for(map<int, float>::iterator p = the_stats.begin();p!= the_stats.end(); ++p){
            the_results.insert(make_pair((*p).second, the_titles[(*p).first - 1]));
        }
    }else{ //else search for word in edit distance of one and bigger than 3 bytes
        istringstream isd(mystr);
        while(isd >> word){
            if(word.size() > 3){
                res = search(word);
                if(res.first == 1){
                    compute_stats(res.second);
                }
            }
        }
        for(map<int, float>::iterator p = the_stats.begin(); p != the_stats.end(); ++p)
            the_results.insert(make_pair((*p).second, the_titles[(*p).first - 1]));
    }
    float temp = 0.0;
    for(multimap<float, string>::iterator it = the_results.begin();it!= the_results.end();++it){
        if(temp != 0.0 && temp != (*it).first) // return only the titles with the highest score  
            break;
        if(counter == 32) // max number of titles to return
            break;
        string_ret += (*it).second;
        string_ret.pop_back();
        string_ret += new_line;
        temp = (*it).first;
        counter+= 1;
    }
    //if counter == 32 and boolian == 1 than do generic search and suggest for another title
    if(counter == 32 && boolian == 1){
        int flag = 0;
        string sugestion("{Τίτλος: ");
        istringstream isf(mystr);
        while(isf >> word){
            if(word.size() > 3 && the_ints.count(word) == 0){
                res = search(word);
                if(res.first == 1){
                    word = res.second;
                    flag = 1;
                }
            }
            sugestion += word;
            sugestion += " ";
        }
        if(flag == 1){
            sugestion += "}\n";
            string_ret += sugestion;
        }
    }
    string_ret.pop_back();
    string_ret.pop_back();
    return string_ret;
}

string run_search(string mystr){
    the_stats.clear();
    the_results.clear();
    return    begin_stats(to_lowercase(mystr));
}
