/*
ID:mmmeeed1
PROG:fracdec
LANG:C++
*/
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXDIGIT = 100010;
char ans[MAXDIGIT];
char dec[MAXDIGIT];
int last[MAXDIGIT];

int num, den, rem, k;

int main()
{
   freopen("fracdec.in", "r", stdin);
   freopen("fracdec.out", "w", stdout);
   memset(last, -1, sizeof(last));
   scanf("%d%d", &num, &den);
   sprintf(ans, "%d.", num/den);
   rem = num % den;
   for (int i = 0;;i++)
   {
       if (rem == 0)
       {
           if (i == 0)
               sprintf(ans+strlen(ans), "%d", 0);
           else
               sprintf(ans+strlen(ans), "%s", dec);
           break;
       }
       if (last[rem] != -1)
       {
           k = last[rem];
           sprintf(ans+strlen(ans), "%.*s(%s)", k, dec, dec+k);
           break;
       }
       last[rem] = i;
       num = rem * 10;
       dec[i] =  num/den + '0';
       rem = num % den;
   }
   for (int i = 0;i < strlen(ans);i += 76)
       printf("%.76s\n", ans+i);
}

