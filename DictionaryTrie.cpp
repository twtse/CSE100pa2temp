#include "util.h"
#include "DictionaryTrie.h"
#include "string"

#define OFF_SET 97

Node::Node()
{
  this->word = false;
  this->frequency = 0;
}

Node* Node::getNext(char c)
{
  int index = c - OFF_SET; //97 is the OFF_SET
  Node* current = this->container[index];

  //go to the array of the node that calls get next, and see if there is a
  //non-null pointer at the index representing char c.
  if(current == NULL)
  {
    return NULL; //if there isn't then we don't have a next (or the char c)
  }
  else
  {
    return current; //if there is just return the pointer
  }
}   

Node::~Node(){}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() 
{
  this->root = new Node();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  //covers the two false conditions
  if(find(word) == true)
  {
    return false;
  }
  if(word.length() == 0)
  {
    return false;
  }

  unsigned int wordind = 0; //because str.length() returns unsigned size
  Node* current = root;

  //from beginning to end
  for(wordind = 0; wordind < word.length(); wordind++)
  {
    //first run we are at root node, which is created in constructor
    //see if there is a nodeptr at our current node's array at index 
    //representing *it
    if(current->getNext( word[wordind] ) == NULL)
    {
      //if there isn't one, make a new node and leave a pointer in the array
      //at that index pointing to our new node
      int index = word[wordind] - OFF_SET;
      current->container[index] = new Node();
      current = current->container[index];
    }
    else
    {
      //if that letter already exist, move to it, update current
      current = current->getNext(word[wordind]);
    }
  }
  //after u have inserted all the characters, need a word node with frequency
  //at this point, current should be a pointer at the index representing the 
  //last  character. The node current points to should have default 
  //initialization. Mark this as word node
  current->word = true;
  current->frequency = freq;

  return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  unsigned int inting;
  Node* current = root;
  for(inting = 0; inting < word.length(); inting++)
  {
    if(current->getNext(word[inting]) == NULL)
      return false;
    else
      current = current->getNext(word[inting]);
  }

  if(current->word == true)
    return true;
  else
    return false;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
  
}
