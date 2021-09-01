/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

/**
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if (pronun_dict_file.is_open()) {
        while (getline(pronun_dict_file, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator<string> line_begin(line_ss);
            istream_iterator<string> line_end;
            if (line[0] != '#' && *line_begin != ";;;") {
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
                istream_iterator<string> temp_itr = line_begin;
                dict[*temp_itr] = vector<string>(++line_begin, line_end);
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/**
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const map<string, vector<string>>& pronun_dict)
    : dict(pronun_dict)
{
    /* Nothing to see here. */
}

/**
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
    /* Your code goes here! */
    string one = "";
    string two = "";
    for(unsigned i = 0; i < word1.length(); i++){
      one += std::toupper(word1[i]);
    }
    for(unsigned i = 0; i < word2.length(); i++){
      two += std::toupper(word2[i]);
    }
    if(dict.find(one) == dict.end() || dict.find(two) == dict.end()){
      return false;
    }
    else{
      auto first = dict.find(one)->second.begin();
      auto second = dict.find(two)->second.begin();
      while(first != dict.find(one)->second.end() && second != dict.find(two)->second.end()){
        if(*first != *second)
          return false;
        else{
          ++first;
          ++second;
        }
      }
      if((first != dict.find(one)->second.end() && second == dict.find(two)->second.end()) ||
        (first == dict.find(one)->second.end() && second != dict.find(two)->second.end())){
          return false;
        }
      return true;
    }
    // string word11 = one.substr(1,one.length());
    // string word21 = two.substr(1,two.length());
    // string word12 = word11.substr(1,word11.length());
    // string word22 = word21.substr(1,word21.length());
    // std::cout<<one<<" "<<two<<std::endl<<word11<<" "<<word21<<std::endl<<word12<<" "<<word22<<std::endl;

   //  if(dict.find(one) == dict.end() || dict.find(two) == dict.end() ||
   //     dict.find(word11) == dict.end() || dict.find(word21) == dict.end() ||
   //     dict.find(word12) == dict.end() || dict.find(word22) == dict.end()){
   //      std::cout<<"fuck";
   //     return false;
   //   }
   // else if(dict.find(one)->second != dict.find(two)->second ||
   //         dict.find(word11)->second != dict.find(word21)->second ||
   //         dict.find(word12)->second != dict.find(word22)->second)
   //         {
   //     std::cout<<"shit";
   //     return false;
   //   }
}
