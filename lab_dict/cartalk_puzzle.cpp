/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if(wordsFile.is_open()){
      while(getline(wordsFile, word)){
        string one = word;
        string two = "";
        string three = "";
        two = one.substr(1,one.length());
        three = one[0] + two.substr(1,two.length());
        if(d.homophones(one, two) && d.homophones(one, three)){
          // std::transform(one.begin(), one.end(), one.begin(), ::tolower);
          // std::transform(two.begin(), two.end(), two.begin(), ::tolower);
          // std::transform(three.begin(), three.end(), three.begin(), ::tolower);
          std::tuple<std::string, std::string, std::string>term;
          term = make_tuple(one, two, three);
          //std::cout<<std::get<0>term<<" "<<std::get<1>term<<" "<<std::get<2>term<<std::endl;
          ret.push_back(term);
        }
      }
    }
    return ret;
}
