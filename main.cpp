#include <bits/stdc++.h>
using namespace std;

bool isCompatible(char a, char b)
{
    if ((a == 'A' && b == 'U') || (a == 'U' && b == 'A') || (a == 'C' && b == 'G') || (a == 'G' && b == 'C'))
        return 1;
    else
        return 0;
}
// ACAUGAUGGCCAUGU
int main()
{
    cout << "Enter the RNA subsequence: ";
    string s;
    cin >> s;
    int n = s.length();
    int OPT[n + 1][n + 1];

    memset(OPT, 0, sizeof(OPT));

    vector<pair<int, int>> rna_pairs[n + 1][n + 1];

    for (int k = 5; k <= n - 1; k++)
    {
        for (int i = 1; i <= n - k; i++)
        {
            int j = i + k;
            int m = -1;
            vector<pair<int, int>> temp;
            OPT[i][j] = OPT[i][j - 1];
            for (int t = i; t < j - 4; t++)
            {
                if (isCompatible(s[t - 1], s[j - 1]))
                {
                    int l = 1 + OPT[i][t - 1] + OPT[t + 1][j - 1];
                    if (m < l)
                    {
                        m = l;
                        temp.erase(temp.begin(), temp.end());
                        for (auto it : rna_pairs[i][t - 1])
                            temp.push_back(it);
                        temp.push_back(make_pair(t, j));
                        for (auto it : rna_pairs[t + 1][j - 1])
                            temp.push_back(it);
                    }
                }
            }

            if (m > OPT[i][j - 1])
            {
                OPT[i][j] = m;
                for (auto it : temp)
                    rna_pairs[i][j].push_back(it);
            }
            else
            {
                OPT[i][j] = OPT[i][j - 1];
                for (auto it : rna_pairs[i][j - 1])
                    rna_pairs[i][j].push_back(it);
            }
        }
    }

    cout << "Max pairings are: " << OPT[1][n] << endl;

    for (int i = 1; i <= 4; i++)
    {
        for (int j = 6; j <= n; j++)
        {
            cout << OPT[i][j] << " ";
        }
        cout << endl;
    }

    for (auto it : rna_pairs[1][n])
        cout << "(" << it.first << " " << it.second << "), ";
}
