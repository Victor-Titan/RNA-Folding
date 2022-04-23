#include <bits/stdc++.h>
using namespace std;
int OPT[100][100];
int l;
string s;
bool isCompatible(char a, char b)
{
    if ((a == 'A' && b == 'U') || (a == 'U' && b == 'A') || (a == 'C' && b == 'G') || (a == 'G' && b == 'C'))
        return 1;
    else
        return 0;
}
struct Print{
    char a;
    char b;
    int a1 ;
    int b1 ;
};
Print printvalues[100];

int check_exists(int i){
    for(int k = 0 ; k < l ; k++){
        if(i == printvalues[k].a1 || i == printvalues[k].b1)return 1;
    }
    return 0;
}

void traceback(int i, int j){
    
    if( j <= i) return ;
   
    if (OPT[i][j] == OPT[i][j-1]) // if the basis in j is unpaired
    {
        
        
        traceback(i, j-1) ;
    }
    else{
        // if j forms a pair with index towards the left
        
        for(int k = i ; k < j - 4 ; k++){
            
            int check = isCompatible(s[k-1], s[j-1]) ;
            if( check == 1){ 
                
                if(k-1 <0){
                    if(OPT[i][j] == OPT[k+1][j-1] +1){
                        int checkK = check_exists(k) ;
                        int checkJ = check_exists(j) ;
                        if(checkK == 0 && checkJ == 0){
                            printvalues[l].a = s[k-1] ;
                            printvalues[l].a1 = k ;
                            printvalues[l].b = s[j-1] ;
                            printvalues[l].b1 = j ;
                            l++ ;
                            
                        }
                        traceback(k+1, j-1) ;
                        
                    }
                }
                else if(OPT[i][j] == OPT[i][k-1] + OPT[k+1][j-1] +1){
                    int checkK = check_exists(k) ;
                    int checkJ = check_exists(j) ;
                    if(checkK == 0 && checkJ == 0){
                        printvalues[l].a = s[k-1] ;
                        printvalues[l].a1 = k ;
                        printvalues[l].b = s[j-1] ;
                        printvalues[l].b1 = j ;
                        l++;  
                        
                    }
                    traceback(i, k-1) ;
                    traceback(k+1 , j-1) ;
                    
                }
            }
            
        }
    }

}

// ACAUGAUGGCCAUGU
int main()
{
    cout << "Enter the RNA subsequence: ";
    cin >> s;
    int n = s.length();
    l=0;
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

    traceback(1,n);
    for (auto it : rna_pairs[1][n])
        cout << "(" << it.first << " " << it.second << "), ";
    cout << endl;
    for(int  a = 0 ; a < l ; a++){
        cout<<"(" << printvalues[a].a << " , " << printvalues[a].b << ") at indices " << printvalues[a].a1 << " " << printvalues[a].b1 << endl;
    }
}

