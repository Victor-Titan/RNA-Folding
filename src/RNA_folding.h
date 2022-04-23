#include <bits/stdc++.h>
#include "RNA_Pair.h"
using namespace std;

/**
 * @brief Main class with functions that run the algorithm
 */
class RNA_folding
{

  RNA_Pair rna_pairs[100];

public:
  // creating an array to store the dynamic programming values
  int OPT[1000][1000];
  int l, n;
  string s;

  RNA_folding(string seq);

  bool isCompatible(char a, char b);

  int getMaxPairs();

  int check_exists(int i);

  void traceback(int i, int j);

  void evaluate();

  void outputPairs();

  void printPairs();
};
