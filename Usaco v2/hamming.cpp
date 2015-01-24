/*
ID: mmmeeed1
PROG: hamming
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

const int lim = 256 + 1;

int dists[lim][lim];
int chosedOnes[65];

void calc()
{
	int dist;
	for( int i=0; i<lim; i++ )
		for( int j=i; j<lim; j++ )
		{
			dist = 0;
			for( int k=0; k<8; k++ ) // 8 bitin tümü için
				if( ( i & ( 1 << k )) ^ ( j & ( 1 << k )) ) dist++;
			dists[i][j] = dists[j][i] = dist;
		}
}

int main()
{
	ifstream in("hamming.in");
	ofstream out("hamming.out");
	
	calc();
	
	int n,b,d;
	in>>n>>b>>d;
	
	int ind = 1;
	bool flag;
	
	/*for( int i=0; i<100; i++ )
		for( int j=0; j<100; j++ )
			cout<<dists[i][j];*/
	
	chosedOnes[0] = 0;
	for( int j=0; n != ind; j++ ) 
	{
		flag = true;
		for( int i=0; i<ind; i++ ) // tüm seçililer için
		{
			if( dists[chosedOnes[i]][j] < d )
			{
				flag = false;
				break;
			}
		}
		if( flag )
			chosedOnes[ind++] = j;
	}
	out<<0<<" ";
	for( int i=2; i<n; i++ )
	{
		if( (i-1) % 10 == 0  )
			out<<endl;
		out<<chosedOnes[i-1];
		if( (i) % 10 != 0 )
			out<<" ";
	}
	out<<chosedOnes[n-1]<<endl;
	
	return 0;
}
