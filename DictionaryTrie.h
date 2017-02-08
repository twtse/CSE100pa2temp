/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <utility>
#include <set>
#include <vector>
#include <string>
#include <iostream>

#define ALPHABET_SPACE 27

/**
 *  This class represents the actual node conceptually that each contains
 *  an array of small nodes. 
 */
class Node
{
public:
  Node();

  /*
   * Calculates using an offset to see which index in our container array
   * reflects the char c. Then checks if the small node in that index connects
   * to a bigNode.
   */
  Node* getNext(char c); 

  ~Node();
  
  /* The container in which each index represents a letter in the alphabet */
  Node* container[ALPHABET_SPACE]; //all the letters in the alphabet & space
  
  unsigned int frequency; //frequency needs to be unsigned bc no negatives

  bool word;

private:
  
};

/**
 *  This class represents each indexes inside the array
 *  of all the characters in the alphabet.
 
class smallNode
{
public:
  smallNode();

private:
  bigNode * next; //each index (which is a character) points to the next
                  //big node which contains all the possible characters that
                  //will follow our index.
  int frequency;
}
*/

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  Node* root;

  void deleteNodes(Node* curr);
  
  Node * prefixFind(std::string prefix);
  
  void search(Node* start, std::string input,
              std::set<std::pair<unsigned int, std::string>> & placeholder);
  
  
};
#endif // DICTIONARY_TRIE_H
