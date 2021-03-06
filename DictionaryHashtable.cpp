#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable()
{
    std::unordered_set<std::string> inner;
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  bool kms = inner.insert(word).second;
  return kms;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  auto itr = inner.find(word);
  
  //Compares iterator element to end iterator
  if(itr == inner.end())
    return false;
  else
    return true;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable()
{
  inner.clear();
}
