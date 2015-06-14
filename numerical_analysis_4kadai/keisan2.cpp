#include <iostream>
#include <math.h>
using namespace std;
/* power.c : 1999 3 8 by Oguni */
// Modified by T. KUDO

const int N = 3;        // 行列の次数
const double tol=1e-6;  // 収束を判定する小さい数
const int Itr=100;     //反復の最大値

/* ユーザー定義の型Matrixの定義 */
typedef double Matrix[N+1][N+1];

/* ユーザー定義の型Vectorの定義 */
typedef double Vector[N+1];

double power(Matrix ,Vector ,int,int *);
void mvsub(Matrix ,Vector,Vector,int);
void normarize(Vector x,int n);

int main(void ){
  int n=N, itr[2]={Itr, 0};
  Matrix A;     
  Vector x;
  double lambda=0.0;

  for ( int i=1; i<=n; i++ )
      for( int j=1; j<=n; j++ )
          cin >> A[i][j];
  for ( int i=1; i<=n; i++ )
      cin >> x[i];

  lambda = power(A,x,n,itr);
  cout << itr[1] << "回の反復。絶対値最大固有値は " << lambda << "\n";
  cout << "固有ベクトルの近似値は\n";
  for (int i=1; i<=n; i++)
    cout << x[i] << "\n";
}
/* function power */
double power(Matrix A,Vector x,int n,int *itr)
{
  int i=0, m=0;
  double c=0.0, s=0.0, lambda=0.0, xmax=0.0;
  Vector y;

  normarize(x,n); //xを正規化する。
  for (m=0; m<itr[0]; m++){
    mvsub(A,x,y,n);
    s=0.0; c=0.0;
    for (i=1; i<=n; i++){
      s+=y[i]*y[i];
      c+=y[i]*x[i]; 
    }
    lambda=s/c;
    itr[1]=m;
    if (fabs(xmax-lambda)<tol)
       return lambda;
    xmax=lambda;
//  cout << m << " " << lambda << "\n" ;
    for (i=1; i<=n; i++)
        x[i]=y[i]/sqrt(s);  //x←y ,更に正規化する。
  }
  return lambda;
}

// multmv , 
void mvsub(Matrix A,Vector b,Vector c,int n)
{
  // c = A・bを計算する部分
  for (int i=1; i<=n; i++){
    c[i]=0.0;
    for (int j=1; j<=n; j++){
      c[i]+=A[i][j]*b[j];
    }
  }
}

//大きさを１にする変換
void normarize(Vector x, int n)
{
  double c=0.0;

  for (int i=1; i<=n; i++)
     c+=x[i]*x[i]; 
  c = sqrt(c);
  for (int i=1; i<=n; i++)
     x[i]/=c; 
}
