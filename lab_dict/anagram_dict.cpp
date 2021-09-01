/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    std::map<string, vector<string>> words;
    ifstream wordsFile(filename);
    string word;
    if(wordsFile.is_open()){
      while(getline(wordsFile, word)){
        string sorted = word;
        sort(sorted.begin(), sorted.end());
        words[sorted].push_back(word);
      }
    }
    for(auto i = words.begin(); i != words.end(); ++i){
      for(auto j = i->second.begin(); j != i->second.end(); ++j){
        dict[*j] = i->second;
        //dict[*j].erase(j);
      }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    std::map<string, vector<string>> sortedlist;
    for(auto it = words.begin(); it != words.end(); ++it){
      string word = *it;
      string sorted = word;
      sort(sorted.begin(), sorted.end());
      sortedlist[sorted].push_back(word);
    }
    for(auto i = sortedlist.begin(); i != sortedlist.end(); ++i){
      for(auto j = i->second.begin(); j != i->second.end(); ++j){
        dict[*j] = i->second;
        //dict[*j].erase(j);
      }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> words;
    auto strings = dict.find(word);
    if(strings == dict.end())
      return vector<string>();
    for(auto it = strings->second.begin(); it != strings->second.end(); ++it){
      words.push_back(*it);
    }
    return words;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> strings;
    vector<string> used;
    for(auto i = dict.begin(); i != dict.end(); ++i){
      if(i->second.size() > 1){
        bool repeated = false;
        if(!used.empty()){
          for(auto k = used.begin(); k != used.end(); ++k){
            if(*k == i->first){
              repeated = true;
              break;
            }
          }
        }
        if(repeated == false){
          vector<string> words;
          words.push_back(i->first);
          for(auto j = i->second.begin(); j != i->second.end(); ++j){
            words.push_back(*j);
            used.push_back(*j);
          }
          strings.push_back(words);
        }
      }
    }
    return strings;
}
