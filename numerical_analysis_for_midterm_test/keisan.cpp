#include <iostream>
#include <math.h>
using namespace std;
/* jacobie.c : 1999 3 8 by Oguni */
// Modified by T. Kudo 

const int N=3;  //行列の次数
const double PI=4.0*atan(1.0);
const double tol=1e-6;  // 収束を判定する小さい数
const int Itr=100;     //反復の最大値

/* ユーザー定義の型Matrixの定義 */
typedef double Matrix[N+1][N+1];

/* ユーザー定義の型Vectorの定義 */
typedef double Vector[N+1];

void jacobie(Matrix A,double tol,int n,int *itr);
int check_symmetric(Matrix ,int);

int main(void){
  Matrix A={{1,1,1},{1,1,2},{1,2,1}};
  int itr[2]={Itr, 0}, i=0;

  
  for (i=1; i<=N; i++)
    for ( int j=1; j<=N; j++ )
       cin >> A[i][j];

  if ( check_symmetric(A,N)== 0 )
  {
      cerr << "行列が対称ではないので終了します\n";
      return 0;
  }

  jacobie(A,tol,N,itr);
  cout << "反復回数は" << itr[1] << "\n";
  cout << "固有値の近似値は\n";
  for (i=1; i<=N; i++)
    cout << A[i][i] << "\n";
}


/* function jacobie */
void jacobie(Matrix A,double tol,int n,int *itr)
{
   double v=1000000.0, vmax=0, t=0, c=0, s=0, akk=0, all=0, akj=0, alj=0;
   int i=0, j=0, k=0, l=0, m=0;

   for (m=0; m<itr[0]; m++){  //非対角成分の絶対値の最大値をvに格納する処理
     vmax=0.0;
     for (j=1; j<=n; j++){
       for (i=1; i<=n; i++){
         if (vmax<fabs(A[i][j]) && i!=j){
           vmax=fabs(A[i][j]); 
           k=i;
           l=j; 
         }
       }
     }
     v=vmax;

     if (v<tol) //収束したかどうかの判定
        return;

     if (A[k][k]==A[l][l])
       {
        t=PI/4.0;
       }
     else
       {
        t=atan(2.*A[k][l]/(A[k][k]-A[l][l]))/2.0;
       }

     cout << t << endl;

     c=cos(t);
     s=sin(t);
     akk=A[k][k]*c*c+A[l][l]*s*s+2.0*A[k][l]*c*s;
     all=A[k][k]*s*s+A[l][l]*c*c-2.0*A[k][l]*c*s;
     A[k][k]=akk; 
     A[k][l]=0.0;
     A[l][k]=0.0;
     A[l][l]=all;
     for (j=1; j<=n; j++){
       if (j!=k && j!=l){
         akj=A[k][j]*c+A[l][j]*s;
         alj=-s*A[k][j]+c*A[l][j];
         A[j][l]=alj;
         A[l][j]=alj;
         A[k][j]=akj;
         A[j][k]=akj;
       }
     }
     itr[1]=m;
   }
   if (m>itr[0])
     cout << "Not convergent\n";
   return;
}

int check_symmetric(Matrix a,int n)
{
   for( int i=1; i<=n; i++ )for(int j=i+1;j<=n; j++){
      if ( a[i][j] != a[j][i] ) return 0;
   }
   return 1;
}
