/**
 * Name: Timothy Bian & Truman Tse
 * Description: Bench marks our various data stucture on the run-time for
 *              searching through our dictionaries
 *
 */
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryHashtable.h"
#include "DictionaryBST.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>  // Usually this is not allowed in your code!

using std::vector;
using std::ostream;
using std::ifstream;
using std::string;
using std::find;
using std::endl;
using std::cout;

// Simple benchmarking program
int main(int argc, char** argv)
{

  cout << "program begins \n" << endl;
  if (argc != 5 ) {
    cout << "Please enter a valid input" << endl;
    return -1;
  }
  
  std::ifstream dictFile;
  string s = argv[4];
  dictFile.open(s.c_str());
   
  //Saves user input
  int min_size= std::stoi(argv[1], nullptr);
  int step_size= std::stoi(argv[2], nullptr);
  int num_iterations=std::stoi(argv[3], nullptr);
  
  Timer t;
  Utils utils;
  int size; //Reflects number of elements inserted at any iteration
  int testSize = 100; //Number of words searched
 
   cout << "Now testing with DictionaryBST" << endl;
 
  //Runs tests num_iterations times
  for (int i = 0; i < num_iterations; i++) {
    DictionaryBST* lexicon = new DictionaryBST();
    vector<string> wordsToFind;
    
    size=min_size+(i*step_size);
    
    //Loads words into Dictionary as well as Vector
    Utils::load_dict(*lexicon, dictFile, size);
    Utils::load_vector(wordsToFind, dictFile, 100);
    
    //Times 100 find functions
    t.begin_timer();
    for(int j = 0; j < 100; j++)
    {
      lexicon->find(wordsToFind[j]);
    }
    long long time = t.end_timer();
 /*
    for(int i=0;i<size;i++){
        string temp;
        
        dictFile >> temp;
        lexicon->insert(temp);
        
    }
    // get the next 100 words to look for.
    for(int i=0; i<testSize; i++){
        string temp;
        dictFile >> temp;
        wordsToFind.push_back(temp);
    }
    
    // Start the timer, look for the words
    t.begin_timer();
    for (string w: wordsToFind) {
      lexicon->find(w);
    }
    long long time = t.end_timer();
  */ 

    //Prints results
    cout << size << "\t" << time << endl;
    
    //resets ifstream
    dictFile.clear();
    dictFile.seekg(0, std::ios::beg);
    
    delete(lexicon);
  }
  
  cout << "Now testing with Hashtable" << endl;
  
  for (int i = 0; i < num_iterations; i++) {
   
    //Creates dictionary as well as vector
    DictionaryHashtable* lexicon = new DictionaryHashtable();
    vector<string> wordsToFind;
    
    size=min_size+(i*step_size);
    
    //Loads words into dictionary as well as vector
    Utils::load_dict(*lexicon, dictFile, size);
    Utils::load_vector(wordsToFind, dictFile, 100);
    
    //Times 100 finds
    t.begin_timer();
    for(int j = 0; j < 100; j++)
    {
      lexicon->find(wordsToFind[j]);
    }
    long long time = t.end_timer();
 /*
    for(int i=0;i<size;i++){
        string temp;
        
        dictFile >> temp;
        lexicon->insert(temp);
        
    }
    // get the next 100 words to look for.
    for(int i=0; i<testSize; i++){
        string temp;
        dictFile >> temp;
        wordsToFind.push_back(temp);
    }
    
    // Start the timer, look for the words
    t.begin_timer();
    for (string w: wordsToFind) {
      lexicon->find(w);
    }
    long long time = t.end_timer();
 */   
    cout << size << "\t" << time << endl;
    
    //resets ifstream
    dictFile.clear();
    dictFile.seekg(0, std::ios::beg);
    
    delete(lexicon);
  }
  
  cout << "Now testing with DictionaryTrie" << endl;
  
  for (int i = 0; i < num_iterations; i++) {
    
    //Creates Dictionary as well as vector
    DictionaryTrie* lexicon = new DictionaryTrie();
    vector<string> wordsToFind;
    
    size=min_size+(i*step_size);
    string temp;

    dictFile.clear();
    dictFile.seekg(0, std::ios::beg);
    //utils.load_dict(*lexicon, dictFile, size);
    
    //Loads words into dictionary, util load causes errors
    for( int i = 0; i<size; i++) {
      dictFile >> temp;
      while(temp[0]>=48&&temp[0]<=57){
        dictFile >> temp;
      }
      lexicon->insert(temp, 1);
    }
        //lexicon->insert(temp, 1);
        
    // get the next 100 words to look for.
    for(int i=0; i<testSize; i++){
        string temp;
        dictFile >> temp;
        while(temp[0]>=48&&temp[0]<=57){
          dictFile >> temp;
        }
        wordsToFind.push_back(temp);
    }
    
    // Start the timer, look for the words
    t.begin_timer();
    for (string w: wordsToFind) {
      lexicon->find(w);
    }
    long long time = t.end_timer();
    
    cout << size << "\t" << time << endl;
    
    //resets ifstream
    dictFile.clear();
    dictFile.seekg(0, std::ios::beg);
    
    delete(lexicon);
  }
}
