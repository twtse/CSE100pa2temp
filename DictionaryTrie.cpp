#include "util.h"
#include "DictionaryTrie.h"

#define OFF_SET 97

DictionaryTrie::Node()
{
  bool word = false;
  int frequency = -1;
  Node.container = new Node[26]; //Initializes array of Nodes
}

Node* DictionaryTrie::getNext(char c)
{
  int index = c - OFF_SET; //97 is the OFF_SET
  Node* current = this.container[index];

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

DictionaryTrie::~Node()
{
  delete [] container;
}

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
  if(this.find(word) == true)
  {
    return false;
  }
  if(word.empty() == true)
  {
    return false;
  }

  //iterator allows us to traverse through a string
  string::iterator it;
  Node* current = root;

  //from beginning to end
  for(it = word.begin(); it < str.end(); it++)
  {
    //first run we are at root node, which is created in constructor
    //see if there is a nodeptr at our current node's array at index 
    //representing *it
    if(current.getNext(*it) == NULL)
    {
      //if there isn't one, make a new node and leave a pointer in the array
      //at that index pointing to our new node
      int index = *it - OFF_SET;
      current.container[index] = new Node();
      current = current.container[index];
    }
    else
    {
      //if that letter already exist, move to it, update current
      current = current.getNext(*it);
    }
  }
  //after u have inserted all the characters, need a word node with frequency
  //at this point, current should be a pointer at the index representing the 
  //last  character. The node current points to should have default 
  //initialization. Mark this as word node
  current->word = true;
  current->frequency = freq;

  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  Node* current = root;
  string::iterator it;

  //Traverses MWT for every letter in the word
  for(it = word.begin(); it < str.end(); it++){
    //Returns false if path is invalid
    if(!current.getNext(*it)){
       return false;
    }
    //Iterates
    current = container.container[*it-OFF_SET];
  }
  
  //Returns true if the last letter results in a word node
  if(current->word == true){
    return true;
  }

  //Returns false otherwise
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
DictionaryTrie::~DictionaryTrie(){}
