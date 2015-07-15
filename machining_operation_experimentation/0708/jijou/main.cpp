/*-----------------------------------------------------
title:最小二乗法プログラム
author:yusaku sakamoto
last update:2015.07.10
mail:n104069y@mail.kyuteck.jp
how to use:
このプログラムは、第1列に横軸データ、2列目以降に縦軸データが入っているデータファイルを読み取ることを前提として作った最小二乗法の計算プログラムです。

コンパイルは、g++を用いて行います。
$ make clean
$ make

で行って下さい。
実行方法は、行数×列数を引数として設定して下さい。
$ ./main 行数 列数 ファイル名
[例]
$ ./main 5 5 ../data.dat
------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#define BUF 20

int main(int argc,char *argv[])
{
  //引数の文字列を数字に変換
  //------------------------------------------------------
  const int row = atoi(argv[1]);
  const int column = atoi(argv[2]);
  const char *filename = argv[3];

  //ファイル読み取り用プログラム
  //------------------------------------------------------
  int i,j;
  double figure[row*column];
  fstream file;
  char character;
  char str[ row*column ][BUF];

  file.open(filename,ios::in);
  if( !file.is_open() ) perror("file open error");

  i=j=0;

  while(  file.read(&character, sizeof(character)) )
	{
	  if(character == '\t' || character == '\n'){
		figure[i] = atof(str[i]);
		i++;
		j=0;
	  }
	  else str[i][j++] = character;
	}
  file.close();

  //最小二乗法計算
  //------------------------------------------------------
  double x[row];
  double y[column-1][row];
  double A=0,B=0,C=0,D=0,E=0;
  double a[column-1];
  double b[column-1];
  int k;
  i=j=0;

  for(i=0;i<row;i++){
	x[i] = figure[j++];
	for(k=0;k<column-1;k++) y[k][i] = figure[j++];
  }

  for(j=0;j<column-1;j++){
	A=0;
	B=0;
	C=0;
	D=0;
	E=0;

	for(i=0;i<row;i++){
	  A += y[j][i]*y[j][i];
	  B += x[i]*x[i];
	  C += y[j][i];
	  D += x[i]*y[j][i];
	  E += x[i];
	}

	a[j] = (row*D-C*E)/(row*B-E*E);
	b[j] = (B*C-D*E)/(row*B-E*E);

	cout << "第" << j+2 << "列目の計算結果" << endl;
	cout << "\t---->>a:" << a[j] << endl;
	cout << "\t---->>b:" << b[j] << endl;
  }

  return 0;
}
