#include<iostream>
using namespace std;

bool isFirst( char* c )
{
	int i=0;
	while( c[i] <= 'Z' && c[i] >= 'A' )
		i++;
	while( c[i] <= '9' && c[i] >= '0' )
		i++;
	if( c[i] == 0 || c[i] == '\n' )
		return true;
	return false;
}

char* inverse( char *a, int len )
{
	int s = 0, e = len;
	while( s < e )
	{
		char t = a[s];
		a[s] = a[e];
		a[e] = t;
		s++;
		e--;
	}
	return a;
}

int main()
{
	int n;
	cin>>n;
	char c[35];
	for( int i=0; i<n; i++ )
	{
		cin>>c;
		if( isFirst(c) )
		{
			long long int row = 0 ,cln = 0;
			int i=0;
			while( c[i] <= 'Z' && c[i] >= 'A' )
			{
				cln *= 26;
				cln += c[i] - 'A' + 1;
				i++;
			}
			while( c[i] <= '9' && c[i] >= '0' )
			{
				row *= 10;
				row += c[i] - '0';
				i++;
			}
			cout<<"R"<<row<<"C"<<cln<<endl;
		}
		else
		{
			long long int row = 0 ,cln = 0;
			int i=1;
			while( c[i] <= '9' && c[i] >= '0' )
			{
				row *= 10;
				row += c[i] - '0';
				i++;
			}
			i++;
			while( c[i] <= '9' && c[i] >= '0' )
			{
				cln *= 10;
				cln += c[i] - '0';
				i++;
			}
			int ind = 0;
			char b[20];
			while( cln > 0 )
			{
				cln--;
				b[ind++] = ((cln%26)+'A');
				cln /= 26;
			}
			b[ind] = 0;
			cout<<inverse(b,ind-1);
			cout<<row<<endl;
		}
	}
}
