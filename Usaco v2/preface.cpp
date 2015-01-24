/*
ID: mmmeeed1
PROG: preface
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int op[7];

int nums[11]; // for every number, array keeps needed char types and counts

char chars[] = {'I','V','X','L','C','D','M'};
int pows[] = {1,10,100,1000,10000,100000};
int amip[][2][2] =  // x0 -> basamak, x1 miktar, y0 ve y1 sayýlar
			{
				{{0,0},{0,0}},
				{{1,1},{0,0}},
				{{1,2},{0,0}},
				{{1,3},{0,0}},
				{{1,1},{2,1}},
				{{2,1},{0,0}},
				{{1,1},{2,1}},
				{{1,2},{2,1}},
				{{1,3},{2,1}},
				{{3,1},{1,1}}
			};
				

int addNums( int x, int d )
{
	int n = x/pows[d-1];
	//cout<<n<<endl;
	
	int a[2][2];
	a[0][0] = amip[n][0][0];
	a[0][1] = amip[n][0][1];
	a[1][0] = amip[n][1][0];
	a[1][1] = amip[n][1][1];
	
	// basamaklarý arttýr
	a[0][0] += (d-1)*2;
	a[1][0] += (d-1)*2;
	nums[a[0][0]] += a[0][1];
	nums[a[1][0]] += a[1][1];
}

int calc( int x )
{
	int d=1;
	while( x )
	{
		addNums(x%pows[d],d);
		x-=(x%pows[d]);
		d++;
	}
}

int main()
{
	ifstream in("preface.in");
	ofstream out("preface.out");
	
	int n;
	in>>n;
	
	for(int i=1; i<=n; i++ )
	{
		calc(i);
	}
	
	for( int i=1; i<11; i++ )
		if( nums[i] != 0 )
			out<<chars[i-1]<<" "<<nums[i]<<endl;
	return 0;
}
