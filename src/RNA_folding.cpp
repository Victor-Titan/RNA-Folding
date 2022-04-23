#include <bits/stdc++.h>
#include "./RNA_folding.h"
using namespace std;

/**
 * @brief Construct a new RNA sequence object
 *
 * @param seq The RNA sequence
 */
RNA_folding ::RNA_folding(string seq)
{
  s = " " + seq;
  n = seq.length();
  memset(OPT, 0, sizeof(OPT));
}

/**
 * @brief Checks rule 1 of the algorithm
 *
 * @param a used to check compatibility with b
 * @param b check compatibility with a
 * 
 * @return true if compatible, false if not
 */
bool RNA_folding :: isCompatible(char a, char b)
{
  if ((a == 'A' && b == 'U') || (a == 'U' && b == 'A') || (a == 'C' && b == 'G') || (a == 'G' && b == 'C'))
    return 1;
  else
    return 0;
}

/**
 * @brief Get the maximum number of base pairs that can be formed.
 *
 * @return int The maximum number of base pairs for the RNA sequence
 */
int RNA_folding ::getMaxPairs()
{
  return OPT[1][n];
}
/**
 * @brief Check if base is already in a pair
 * @param i index of the current base
 * @return int 1 if already in a pair, else 0
 */
int RNA_folding ::check_exists(int i)
{
  for (int k = 0; k < l; k++)
  {
    if (i == rna_pairs[k].a1 || i == rna_pairs[k].b1)
      return 1;
  }
  return 0;
}
/**
 * @brief Get the joined pairs of bases of in the RNA sequence
 * @param i start of the index under consideration
 * @param j end of the index under consideration
 */
void RNA_folding ::traceback(int i, int j)
{

  if (j <= i)
    return;

  if (OPT[i][j] == OPT[i][j - 1]) // if the basis in j is unpaired
  {

    traceback(i, j - 1);
  }
  else
  {
    // if j forms a pair with index towards the left

    for (int k = i; k < j - 4; k++)
    {

      int check = isCompatible(s[k], s[j]);
      if (check == 1)
      {

        if (k - 1 < 0)
        {
          if (OPT[i][j] == OPT[k + 1][j - 1] + 1)
          {
            int checkK = check_exists(k);
            int checkJ = check_exists(j);
            if (checkK == 0 && checkJ == 0)
            {
              rna_pairs[l].a = s[k];
              rna_pairs[l].a1 = k;
              rna_pairs[l].b = s[j];
              rna_pairs[l].b1 = j;
              l++;
            }
            traceback(k + 1, j - 1);
          }
        }
        else if (OPT[i][j] == OPT[i][k - 1] + OPT[k + 1][j - 1] + 1)
        {
          int checkK = check_exists(k);
          int checkJ = check_exists(j);
          if (checkK == 0 && checkJ == 0)
          {
            rna_pairs[l].a = s[k];
            rna_pairs[l].a1 = k;
            rna_pairs[l].b = s[j];
            rna_pairs[l].b1 = j;
            l++;
          }
          traceback(i, k - 1);
          traceback(k + 1, j - 1);
        }
      }
    }
  }
}
/**
 * @brief This function calculates the maximum possible pairs of the sequence based on the rules given
 * The value is stored in OPT(1,n)
 *
 */
void RNA_folding ::evaluate()
{
  for (int k = 5; k <= n - 1; k++)
  {
    for (int i = 1; i <= n - k; i++)
    {
      int j = i + k;
      OPT[i][j] = OPT[i][j - 1];
      for (int t = i; t < j - 4; t++)
      {
        if (isCompatible(s[t], s[j]))
        {
          OPT[i][j] = max(OPT[i][j], 1 + OPT[i][t - 1] + OPT[t + 1][j - 1]);
        }
      }
    }
  }

  traceback(1, n);
}
/**
 * @brief Print all the possible pairs of the sequence
 */
void RNA_folding ::outputPairs()
{
  fstream fs;
  fs.open ("output.txt", std::fstream::app);
  for (int a = 3; a < l; a++){
    cout << rna_pairs[a].a1 << "-" << rna_pairs[a].b1 << " (" << rna_pairs[a].a << "-" << rna_pairs[a].b << ")" << endl;
  }
  fs.close();
}

void RNA_folding ::printPairs()
{
  for (int a = 3; a < l; a++){
    cout << rna_pairs[a].a1 << "-" << rna_pairs[a].b1 << " (" << rna_pairs[a].a << "-" << rna_pairs[a].b << ")" << endl;
  }
}