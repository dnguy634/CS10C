#include <list>
#include <string>

using std::list;
using std::string;

class WordLadder {

  private:
  list<string> dict;        //list of possible words in ladder

  bool misMatchByOne(const string& word1, const string& word2);   // helper function to compare word differences

  public:
    WordLadder(const string& filename);

    void outputLadder(const string &start, const string &end, const string &outputFile);
};

