/*
ID: mmmeeed1
PROG: concom
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<set>
using namespace std;

struct sortt {
    bool operator()(int x, int y) {return ((x<y)?true:false);}
};

int arr[102][102];// x, y'nin z kadarýný
int arr2[102][102];
set<int,sortt> usedComNames;



int updatePercents( int a, int b )// a ya b yi ekle
{
	if( arr2[a][b] != 0 )
		return 0;
	arr2[a][b] = 1;
	for( set<int>::iterator it3 = usedComNames.begin(); it3 != usedComNames.end(); it3++ ) // b nin sahip olduðu tüm hisseleri a ya kopyala
	{
		if( a != *it3 )
		{
			arr[a][*it3] += arr[b][*it3];
			if( ( arr[a][*it3] - arr[b][*it3] <= 50 ) && (( arr[a][*it3] > 50 ) ))
				updatePercents(a,*it3);
			if( arr[a][*it3] > 100 ) arr[a][*it3] = 100;
		}
	}
}

int calc()
{
	for( set<int>::iterator it1 = usedComNames.begin(); it1 != usedComNames.end(); it1++ ) // tüm a ve b çiftleri için
	{
		for( set<int>::iterator it2 = usedComNames.begin(); it2 != usedComNames.end(); it2++ )
		{
			int a = *it1;
			int b = *it2;
			if( a != b && arr[a][b] > 50 )
				updatePercents(a,b);
		}
	}
}

int printPairs()
{
	ofstream out("concom.out");
	for( set<int>::iterator it1 = usedComNames.begin(); it1 != usedComNames.end(); it1++ )
	{
		for( set<int>::iterator it2 = usedComNames.begin(); it2 != usedComNames.end(); it2++ )
		{
			int a = *it1;
			int b = *it2;
			if( a != b && arr[a][b] > 50 )
				out<<a<<" "<<b<<endl;
		}
	}
	out.close();
}

int main()
{
	ifstream in("concom.in");
	
	int n; 
	in>>n;
	for( int i=0; i<n; i++ )
	{
		int a,b,p;
		in>>a>>b>>p;
		usedComNames.insert(a);
		usedComNames.insert(b);
		arr[a][b] = p;
	}
	
	calc();
	//cout<<arr[27][59];
	printPairs();
	
	return 0;
}
