#include "util.h"
#include "DictionaryTrie.h"
#include "string"
#include <iostream>
#include <cstdlib>
#include <set>
#include <utility>

#define OFF_SET_MINUS_ONE 96
#define ALPHABET_SPACE 27

Node::Node()
{
  this->word = false;
  this->frequency = 0;
  for(int i = 0; i < ALPHABET_SPACE; i++)
  {
    container[i] = NULL;
  }
}

Node* Node::getNext(char c)
{
  int index;

  if(c == ' ' || c == 32) //just be sure it reads space or space ASCII
  {
    index = 0;
  }
  else
  {
    index = c - OFF_SET_MINUS_ONE; //96 is the offset bc saving 0 for space
  }

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
  bool repeat = false;

  //covers the two false conditions
  if(find(word) == true)
  {
    //std::cout << "Duplicate found" << std::endl;
    repeat = true;
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
    //std::cout << word[wordind] << " is the charcter we're looking at. " <<
    //std::endl;
    
    //first run we are at root node, which is created in constructor
    //see if there is a nodeptr at our current node's array at index 
    //representing *it
    if(current->getNext( word[wordind] ) == NULL)
    {
    //std::cout << "The character doesn't exist yet" << std::endl;
      
      //if there isn't one, make a new node and leave a pointer in the array
      //at that index pointing to our new node
      int index;
      if(word[wordind] == ' ')
      {
        index = 0;
      }
      
      else
      {
        index = word[wordind] - OFF_SET_MINUS_ONE;
      }
      current->container[index] = new Node();
      current = current->container[index];
      //std::cout << word[wordind] << " is inserted at " << index << std::endl;
    }
    else
    {
      //if that letter already exist, move to it, update current
      //std::cout << "CHARACTER EXISTS, TRAVERSE!" << std::endl;
      current = current->getNext(word[wordind]);
    }
  }
  //after u have inserted all the characters, need a word node with frequency
  //at this point, current should be a pointer at the index representing the 
  //last  character. The node current points to should have default 
  //initialization. Mark this as word node
  
  if(repeat == true)
  {
    if(freq > current->frequency) 
    {
      current->frequency = freq;
      //std::cout << "Frequency changed, now: " << freq << std::endl;
    }
    return false;
  }

  current->word = true;
  current->frequency = freq;
  return true;
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

/**
 * Name: prefixFind
 * Description: Helper method that is similar to Find. Searches through to find
 *              where the program should start to use DFS to find all possible
 *              words.
 * Return: Node pointer to the node where we begin DFS
 *
 */
Node * DictionaryTrie::prefixFind(std::string prefix)
{
  Node* current = root;
  for(int i = 0; i < prefix.length(); i++)
  {
    if(current->getNext(prefix[i])== NULL)
    {
      return nullptr; /*-------------------------------------------MAY NEED FIX */
    }
    else
      current = current->getNext(prefix[i]);
  }
  
  //copy pasta'd the find method except instead of returning T/F, we returned 
  //NULL if it was never found (and will error handle in autocomplete) or the
  //a pointer pointing to the node of the last character in the prefix
  return current;
}

/**
 * Name: 
 * Description: Recursive method to search through the tree and then pair up
 *              the string with its frequency. Store the pair into a data
 *              strucutre.
 */
void DictionaryTrie::search(Node* start, std::string input, 
                            std::set< std::pair<unsigned int, std::string> > & placeholder)
{
  for(int i = 0; i < ALPHABET_SPACE; i++)
  {
    if(start->container[i] != NULL)
    {
      std::string added = input;
      char ascii;
      if(i==0)
      {
        ascii=' ';
      }
      else
      {
        ascii='`'+i;
      }
      //std::string temp = std::to_string(i + OFF_SET_MINUS_ONE); 
      //using offset to convert index to char
      added.append(&ascii);
    
      //we use a different string and not passing input everytime because the for loop can append
      //many chars to input word depending on which iteration we're on
      search(start->container[i], added, placeholder);
    }
  }
  
  //if the word is flipped, that means the input thats passed in is already a word
  if(start->word == true)
  {
    std::pair <unsigned int,std::string> combo;
    combo = std::make_pair(start->frequency, input);
    printf("%s",input);
    placeholder.insert(combo);
  }
  
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
  
  bool error = false;
  if(prefix.length() == 0)
  {
    error = true;
    printf("Length is zero\n");
  }
  else
  {
    for(int i = 0; i < prefix.length(); i++)
    {
      if( (prefix[i] < 97 || prefix[i] > 122) && prefix[i] != 32)
      {
        printf("Invalid character\n");
        error = true;
      }
    }  
  }
  if(error == true)
  {
    (void)fprintf(stderr, "Invalid Input. Please retry with correct input.\n");
    return words; //SHOULD BE EMPTY, NEVER INITIALIZED 
  }
  
  Node* start = DictionaryTrie::prefixFind(prefix);
  
  /* Potential Edge Case: prefix not in dictionary */
  if(start == NULL) //prefix not found in dic
  {
    return words; //empty vector 
  }
  
  //make a set of pairs to store the words and call DFS on all its children
  std::set<std::pair<unsigned int, std::string>> placeholder;
  DictionaryTrie::search(start, prefix, placeholder);
  
  /* Edge Case: No possible completions */
  if(placeholder.size() == 0)
  {
    return words; //empty vector
  }
  
  //now placeholder should hold all the possible words, sorted automatically by
  //the unsigned int frequency, so we should take the first num_completion of words
  std::set<std::pair<unsigned int, std::string>>::iterator it = placeholder.begin();
  std::string desired;
  
  for(unsigned int j = 0; j < num_completions; j++)
  {
    desired = (*it).second;
    printf("%s\n",desired);
    words.push_back(desired);
    it++;
  }
  
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
  //Calls helper method 
  deleteNodes(root); 
}

/*Destructor helper method*/
void DictionaryTrie::deleteNodes(Node* curr)
{
  //recursively deletes all children nodes
  for(int i=0;i<ALPHABET_SPACE;i++){
    if(curr->container[i]){
      deleteNodes(curr->container[i]);
    }
  }
  //Deletes itself once all children are deleted
  delete curr;
}
