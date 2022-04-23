#include <bits/stdc++.h>
#include "RNA_folding.h"
using namespace std;

ofstream out("output.txt");
/**
 * @brief driver function
 */
int main()
{
    chrono::duration<double, milli> executionTime;

    double time;
    int maxPairs;

    ifstream nameFileout;
    nameFileout.open("./input2.txt");
    string s;
    // taking RNA sequences from a text file
    while (getline(nameFileout, s))
    {   
        auto start = chrono::high_resolution_clock::now(); // starting the timer
        // running the algorithm
        RNA_folding rna_folding(s);
        rna_folding.evaluate();
        maxPairs = rna_folding.getMaxPairs();
        auto stop = chrono::high_resolution_clock::now();                          // ending the timer
        executionTime = chrono::duration_cast<chrono::microseconds>(stop - start); // calculating the time taken for that particular sequence

        time = executionTime.count();
        out << maxPairs << " " << time << endl;
    }
}
