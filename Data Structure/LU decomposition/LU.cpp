#include<bits/stdc++.h>
using namespace std;
float a[10][10], l[10][10], u[10][10];
int main() {
   int n ;
   cin >> n;
   //input
   for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        cin >> a[i][j];

    //decomposition
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         if (j < i)
         l[j][i] = 0;
         else {
            l[j][i] = a[j][i];
            for (int k = 0; k < i; k++) {
               l[j][i] = l[j][i] - l[j][k] * u[k][i];
            }
         }
      }
      for (int j = 0; j < n; j++) {
         if (j < i)
         u[i][j] = 0;
         else if (j == i)
         u[i][j] = 1;
         else {
            u[i][j] = a[i][j] / l[i][i];
            for (int k = 0; k < i; k++) {
               u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
            }
         }
      }
   }

   //output
   cout << "L Decomposition:"<<endl;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         cout<<l[i][j]<<" ";
      }
      cout << endl;
   }

   cout << "U Decomposition:"<<endl;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         cout<<u[i][j]<<" ";
      }
      cout << endl;
   }
   return 0;
}