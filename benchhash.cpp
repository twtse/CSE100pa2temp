#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using std::cout;
using std::endl;
int main(int argc, char** argv){
    std::vector<int> words;
  
    //Checks for valid input
    std::ifstream dictFile;
    if(argc!=3){
        return -1;
    }
    dictFile.open(argv[1]);
    int nNumbers=std::stoi(argv[2]);
    
    //Initializes hash arrays
    int hash1[2*nNumbers];
    for(int a = 0; a < 2*nNumbers; a++)
    {
      hash1[a] = 0;
    }
    int hash2[2*nNumbers];
    for(int a = 0; a < 2*nNumbers; a++)
    {
      hash2[a] = 0;
    }
    
    //Berenstein Hash
    for(int i=0; i<nNumbers; i++){
        std::string temp;
        unsigned int h=0;
        dictFile >> temp;

        //Hashes ascii values using Berenstein hash
        for (int j = 0; j < temp.length(); j++)
        {
          char x = temp.at(j);
          h= 33*h + x;
        }

        //Mods to prevent overflow
        h=h% (2*nNumbers);
        hash1[h]++;
    }
    
    //Additive Hash
    for(int i=0; i<nNumbers; i++){
        std::string temp;
        unsigned int h=0;
        dictFile >> temp;
        
        //Hashes ascii values by adding them together
        for (int j=0; j<temp.length(); j++)
        {
          char x = temp.at(j);
          h+=x;
        }

        //Mods to prevent overflow
        h=h% (2*nNumbers);
        hash2[h]++;
    }
    

    //Calculates highest value
    int firstMax=*std::max_element(hash1,hash1+(2*nNumbers));
    int secondMax=*std::max_element(hash2,hash2+(2*nNumbers));


    //Create arrays to store results
    int results1[firstMax+1];
    int results2[secondMax+1];
    for(int a = 0; a < firstMax + 1; a++)
    {
      results1[a] = 0;
    }
    for(int a = 0; a < secondMax + 1; a++)
    {
      results2[a] = 0;
    }
    //Stores results into array
    for(int i=0; i<(2*nNumbers) ; i++) 
    {
      results1[hash1[i]]++;
    }
    
    //Stores function 2's results into array
    for(int i=0; i<(2*nNumbers) ; i++) 
    {
      results2[hash2[i]]++;
    }
    

    cout << "Printing the statistics for hashFunction1 with Hashtable size of " <<  (2*nNumbers) << endl;

    cout << "#hits" << "      " << "#slots receiving the #hits" << endl;
    
    //Prints individual results
    for(int i=0; i<firstMax+1; i++){
      cout << i << "        " << results1[i] << endl;
    }
    
    //Calculates average values
    float average1=0;
    int counter=0;  
    for(int j=firstMax; j>=0; j--){
      counter+=results1[j];
      average1+=(counter*j);
    }
    average1=average1/nNumbers;
    
    
    cout << "The average number of steps for a successful find for function 1 is: "
        << average1 << endl;
    cout << "The worst case steps that would be needed to find a word is " 
        << firstMax << endl;
    
    

    //Hash function 2

    cout << "Printing the statistics for hashFunction2 with Hashtable size of " << (2*nNumbers) << endl;

    cout << "#hits" << "      " << "#slots receiving the #hits" << endl;
    
    //Prints individual reseults
    for(int i=0; i<secondMax+1; i++){
      cout << i << "        " << results2[i] << endl;
    }
     

    //Calculates average step value
    float average2=0;
    int counter2=0;  
    for(int j=secondMax; j>=0; j--){
      counter2+=results1[j];
      average2+=(counter2*j);
    }
    average2=average2/nNumbers;



    cout << "The average number of steps for a successful find for function 2 is: "
        << average2 << endl;

    cout << "The worst case steps that would be needed to find a word is "
        << secondMax << endl;
}
