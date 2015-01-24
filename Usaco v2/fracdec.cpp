/*
ID: mmmeeed1
PROG: fracdec
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<set>
#define MAXLEN 60000
using namespace std;

int commaLoc = 0;
int arr[MAXLEN];
int karr[100000];

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

int controlForRepr( int c )
{
	for( int i=0; i<c-1; i++ )
		if( karr[i] == karr[c-1] && arr[i] == arr[c-1] )
			return i;
	return -1;
	/*for( int i=1; i<=c/2; i++ ) // len
	{
		bool flag = false;
		for( int j=0; j<i; j++ )
		{
			if( arr[c-j-1] != arr[c-i-j-1] )  // || karr[c-j-1] != karr[c-i-j-1 ]
				flag = true;
				break;
		}
		if( flag == false )
			return i;
	}
	return 0;*/
}


int main()
{
	ifstream in("fracdec.in");
	ofstream out("fracdec.out");
	int a,b;
	in>>a>>b;
	
	//set<struct pairs,struct comp> p;
	
	out<<(a/b)<<".";
	int kalan = a%b;
	int c;
	int st = -1;
	for( c=0; st == -1 ;  )
	{
		kalan*=10;
		arr[c] = kalan/b;
		kalan = kalan%b;
		if( kalan == 0 )
			break;
		if( karr[kalan] != 0 )
			if( arr[c-1] == arr[karr[kalan]] )
				st = karr[kalan];
		c++;
		karr[kalan] = c;
		//cout<<endl<<c-1<<" "<<arr[c-1]<<endl;
	}
	cout<<st<<endl;
	out.flush();
	int currfilesize = filesize("fracdec.out");
	if( st == -1 )
		for( int i=0; i<=c; i++ )
		{
			if( (currfilesize + i)  % 76 == 0 )
				out<<endl;
			out<<arr[i];
			
		}
	else
	{
		st--;
		c--;
		cout<<st<<" "<<c<<" ";
		if( st != 0 )
			st++;
		for( int i=0; i<st; i++ )
		{
			if( (currfilesize + i)  % 76 == 0 )
				out<<endl;
			out<<arr[i];
		}
		out<<"(";
		out.flush();
		currfilesize = filesize("fracdec.out");
		for( int i=st; i<c; i++ )
		{
			if( (currfilesize + i) % 76 == 0 )
				out<<endl;
			out<<arr[i];
		}
		out<<")";
	}
	out<<endl;
	/*for( int i=0; i<c; i++ )
		cout<<arr[i]<<endl;*/
	/*
	cout<<".";
	for( int i=0; i<c-len*2; i++ )
		cout<<arr[i];
	if( len > 0 )
	{		
		cout<<"(";
		for( int i=0; i<len; i++ )
			cout<<arr[c-len*2+i];
		cout<<")";
	}
	cout<<endl;
	*/
	//cout<<c<<" - "<<st<<endl;
	return 0;
}
