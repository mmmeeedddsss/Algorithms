#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

int a[100010];

int main()
{	
	int n,m,k;
	cin>>n>>m>>k;
	for( int i=0; i<n; i++ )
		cin>>a[i];
	vector<int> v;
	int minn = INT_MAX;
	for( int j=0; j<n; j++ )
	{
		for( int i=j; i<m+j; i++ )
			v.push_back(a[i%n]);
		sort( v.begin(),v.end() );
		if( v[k-1] < minn )
			minn = v[k-1];
		v.clear();
	}
	cout<<minn<<endl;
	return 0;
}
