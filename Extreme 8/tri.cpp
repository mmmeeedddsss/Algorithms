#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
bool arr[150][1010];


int main(){
	int l[200][1010];

	l[0][0]=5;
	l[1][0]=13;
	l[2][0]=17;
	l[3][0]=25;
	l[4][0]=29;
	l[5][0]=37;
	l[6][0]=41;
	l[7][0]=53;
	l[8][0]=61;
	l[9][0]=65;
	l[10][0]=73;
	l[11][0]=85;
	l[12][0]=89;
	l[13][0]=97;
	l[14][0]=101;
	l[15][0]=109;
	l[16][0]=113;
	l[17][0]=125;
	l[18][0]=137;
	l[19][0]=145;
	l[20][0]=149;
	l[21][0]=157;
	l[22][0]=169;
	l[23][0]=173;
	l[24][0]=181;
	l[25][0]=185;
	l[26][0]=193;
	l[27][0]=197;
	l[28][0]=205;
	l[29][0]=221;
	l[30][0]=229;
	l[31][0]=233;
	l[32][0]=241;
	l[33][0]=257;
	l[34][0]=265;
	l[35][0]=269;
	l[36][0]=277;
	l[37][0]=281;
	l[38][0]=289;
	l[39][0]=293;
	l[40][0]=305;
	l[41][0]=313;
	l[42][0]=317;
	l[43][0]=325;
	l[44][0]=337;
	l[45][0]=349;
	l[46][0]=353;
	l[47][0]=365;
	l[48][0]=373;
	l[49][0]=377;
	l[50][0]=389;
	l[51][0]=397;
	l[52][0]=401;
	l[53][0]=409;
	l[54][0]=421;
	l[55][0]=425;
	l[56][0]=433;
	l[57][0]=445;
	l[58][0]=449;
	l[59][0]=457;
	l[60][0]=461;
	l[61][0]=481;
	l[62][0]=485;
	l[63][0]=493;
	l[64][0]=505;
	l[65][0]=509;
	l[66][0]=521;
	l[67][0]=533;
	l[68][0]=541;
	l[69][0]=545;
	l[70][0]=557;
	l[71][0]=565;
	l[72][0]=569;
	l[73][0]=577;
	l[74][0]=593;
	l[75][0]=601;
	l[76][0]=613;
	l[77][0]=617;
	l[78][0]=625;
	l[79][0]=629;
	l[80][0]=641;
	l[81][0]=653;
	l[82][0]=661;
	l[83][0]=673;
	l[84][0]=677;
	l[85][0]=685;
	l[86][0]=689;
	l[87][0]=697;
	l[88][0]=701;
	l[89][0]=709;
	l[90][0]=725;
	l[91][0]=733;
	l[92][0]=745;
	l[93][0]=757;
	l[94][0]=761;
	l[95][0]=769;
	l[96][0]=773;
	l[97][0]=785;
	l[98][0]=793;
	l[99][0]=797;
	l[100][0]=809;
	l[101][0]=821;
	l[102][0]=829;
	l[103][0]=841;
	l[104][0]=845;
	l[105][0]=853;
	l[106][0]=857;
	l[107][0]=865;
	l[108][0]=877;
	l[109][0]=881;
	l[110][0]=901;
	l[111][0]=905;
	l[112][0]=925;
	l[113][0]=929;
	l[114][0]=937;
	l[115][0]=941;
	l[116][0]=949;
	l[117][0]=953;
	l[118][0]=965;
	l[119][0]=985;
	l[120][0]=997;
	l[121][0]=1009;

	for(int ii=0;ii<122;ii++){
		for(int jj=1;l[ii][0]*jj<1010;jj++){
			arr[ii][l[ii][0]*jj]=true;
			}
		}
		int n,t1,t2;
		cin>>n;
		for(int ii=0;ii<n;ii++){
			cin>>t1>>t2;
			bool f=false;
			for(int jj=0;jj<122;jj++){
			if(arr[jj][t1] && arr[jj][t2]){ 
				cout<<"TRUE"<<endl; f=true; break; 
			}
		}
		if(!f) cout<<"FALSE"<<endl;
	}
	return 0;
}


/*#include<iostream>
#include<vector>
#include<set>
#include<math.h>
using namespace std;

bool abs( double x )
{
	if( x < 0 )
		return -x;
	return x;
}

int main()
{
	int n;
	cin>>n;
	for( int i=0; i<n; i++ )
	{
		double a,b;
		cin>>a>>b;
		
		bool flag1 = false;
		bool flag2 = false;
		set<double> rs;
		
		int x1,x2,y1,y2;
		for( int j=1; j<a; j++ )
			if( (a*a)-(j*j) == ((int)sqrt( (a*a)-(j*j) ))*((int)sqrt( (a*a)-(j*j) )) )
			{
				double k = (sqrt( (a*a)-(j*j) ));
				rs.insert( k/j );
				rs.insert( j/k );
				flag1 = true;
			}
		//cout<<endl;
		for( int j=b-1; j>0; j-- )
			if( (b*b)-(j*j) == ((int)sqrt( (b*b)-(j*j) ))*((int)sqrt( (b*b)-(j*j) )) )
			{
				double k = (sqrt( (b*b)-(j*j) ));
				if( rs.count(k/j) != 0 )
					cout<<"TRUE"<<endl;
						goto asdf;
				flag2 = true;
			}
		if( flag1 == true && flag2 == true )
		{
			if( ((y1-y2)*(y1-y2))+((x1+x2)*(x1+x2)) == a*a + b*b )
					{
						cout<<"TRUE"<<endl;
						goto asdf;
					}
		}
		else
			cout<<"FALSE"<<endl;
		asdf:
		continue;
	}
	return 0;
}*/
