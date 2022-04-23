#include<bits/stdc++.h>
using namespace std;

#define MAX_INT (int)1e5


bool isCompatible(char a, char b){
    if((a == 'A' && b == 'U')
     || (a == 'U' && b == 'A')
     || (a == 'C' && b == 'G')
     || (a == 'G' && b == 'C')) return 1;
     else return 0;
}
// ACAUGAUGGCCAUGU
int main(){
    cout << "Enter the RNA subsequence: ";
    string s;
    cin >> s;
    int n = s.length();
    int* OPT[n+1];

    for(int i=0;i<=n;i++){
        OPT[i] = (int*)malloc(sizeof (int)*n);
        memset(OPT[i], 0, sizeof (int)*n);
    }

    for(int k=5;k<=n-1;k++){
        for(int i=1;i<=n-k;i++){
            int j=i+k;
            OPT[i][j]=OPT[i][j-1];
            for(int t=i;t<j-4;t++){
                if(isCompatible(s[t-1],s[j-1])){
                    OPT[i][j] = max(OPT[i][j], 1 + OPT[i][t-1] + OPT[t+1][j-1]);
                }
            }
        }
    }

    cout << "Max pairings are: " << OPT[1][n] << endl;

    for(int i=1;i<=4;i++){
        for(int j=6;j<=n;j++){
            cout << OPT[i][j] << " ";
        }
        cout << endl;
    }

}
