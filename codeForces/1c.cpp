#include<iostream>
#include<math.h>
#define eps (1e-4)
using namespace std;

class node{
	public:
		double x,y;
};

double toDegrees( double x )
{
	return (x/3.141592653589793)*180;
}

double getDist( node a, node b )
{
	return (sqrt( (a.x - b.x)*(a.x - b.x) +(a.y - b.y)*(a.y - b.y) ));
}

double gcd(double a, double b)
{
	if(fabs(b-0) <= eps) return a;
	if(fabs(a-0) <= eps) return b;
	return gcd(b,fmod(a,b));
}

int main()
{
	node a,b,c;
	cin>>a.x>>a.y;
	cin>>b.x>>b.y;
	cin>>c.x>>c.y;
	
	double lc = getDist(a,b);
	double lb = getDist(a,c);
	double la = getDist(c,b);


	double angA = acos((lb*lb+lc*lc-la*la)/(2*lb*lc));
	double angB = acos((la*la+lc*lc-lb*lb)/(2*la*lc));
	double angC = (3.141592653589793)-angA-angB;
	
	//cout<<toDegrees(angA)<<" "<<toDegrees(angB)<<" "<<toDegrees(angC)<<endl;
	
	double gcdV = (double)( gcd(gcd(toDegrees(angC),toDegrees(angB)),toDegrees(angA)) );
	
	//cout<<gcdV<<endl;
	int edgeCount = ( (toDegrees(angA)/gcdV)+(toDegrees(angB)/gcdV)+(toDegrees(angC)/gcdV) );
	double r = la/(2*sin(angA));
	double areaForOne = r*r*sin(2*3.141592653589793/edgeCount)/2;
	cout<<areaForOne*edgeCount<<endl;
	
	//cout<<" -> "<<( (toDegrees(angA)/gcdV)+(toDegrees(angB)/gcdV)+(toDegrees(angC)/gcdV) );
	
	return 0;
}
