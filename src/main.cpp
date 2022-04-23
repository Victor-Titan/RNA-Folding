#include <bits/stdc++.h>
#include "./RNA_folding.h"
using namespace std;

/**
 * @brief driver function
 */
int main()
{
  chrono::duration<double, milli> executionTime;

  double time;
  int maxPairs;
  string s;
  cin >> s;

  // running the algorithm
  auto start = chrono::high_resolution_clock::now(); // starting the timer
  RNA_folding rna_folding(s);
  rna_folding.evaluate();
  maxPairs = rna_folding.getMaxPairs();
  cout << "Predicted pairs: " << maxPairs << endl;
  rna_folding.printPairs();
  auto stop = chrono::high_resolution_clock::now();
  executionTime = chrono::duration_cast<chrono::microseconds>(stop - start); // calculating the time taken for that particular sequence
  time = executionTime.count();
  cout << endl;
  cout << "Time: \n" << time << " s" << endl;
}
