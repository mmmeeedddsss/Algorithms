/*
ID: mmmeeed1
PROG: checker
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int colLimit, diagLimit;
int diag1[25]; // sola yatýk 
int diag2[25]; // /
int cols[13];
int currLoc[13];

int counter = 0;

ofstream fout ("checker.out");

bool canPlace(int currRow, int currCol) // y-1,x-1
{
	if( diag1[currCol+colLimit-currRow-1] == 0 && diag2[currCol+currRow] == 0 && cols[currCol] == 0 )
		return true;
	return false;
}


int rec( int currRow )
{
	if( currRow == colLimit )
	{
		counter++;
		if(counter <= 3 )
		{
			
			for( int i=0; i<colLimit-1; i++ )
				fout<<currLoc[i]+1<<" ";
			fout<<currLoc[colLimit-1]+1<<endl;
		}
	}
	
	for( int i=0; i<colLimit; i++ )
	{
		if(canPlace(currRow,i))
		{
			currLoc[currRow] = i; // deðiþiklikleri yapýyorum
			cols[i] = 1;
			diag1[i+colLimit-currRow-1] = 1; // 6x6 da 0 a 0 iken 5 olmalý içi , i=0, row = 5 için içi 0
			diag2[i+currRow] = 1; 
			
			rec( currRow + 1 );
			
			currLoc[currRow] = 0; // geri aliyorum
			cols[i] = 0;
			diag1[i+colLimit-currRow-1] = 0; // 6x6 da 0 a 0 iken 5 olmalý içi , i=0, row = 5 için içi 0
			diag2[i+currRow] = 0; 
			
		}		
	}
}

int main()
{
	ifstream fin ("checker.in");
	int n;
	fin>>n;
	colLimit = n;
	diagLimit = 2*n -1;
	
	rec( 0 );
	fout<<counter<<endl;
	
	return 0;
}
