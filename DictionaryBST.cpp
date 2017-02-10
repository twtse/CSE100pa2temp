#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST()
{
    std::set<std::string> BST;
}
/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
    auto BSTinsert= BST.insert(word);
    return BSTinsert.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
    
    auto BSTiterator= BST.find(word);
    
    //Compares iterator element to end iterator
    if(BSTiterator==BST.end()){
        return false;
    }
    return true;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
