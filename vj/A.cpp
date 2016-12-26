#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>//sort（）; 
#include<climits>
using namespace std;
#define debug 0
#define M(a) memset(a,0,sizeof(a))
#define Max(a,b) ((a>b)?a:b)

const int maxn = 1000000+5;
int data[maxn],dp[maxn],temp[maxn];
int n,m;

void Do()
{
	int ans;
	for(int i = 1;i <= n;i++)
	{
		ans = INT_MIN;
		for(int j = i;j <= m;j++)//这里dp[j]表示当前长为j的序列分为i段的最优解
		{
			dp[j] = Max(dp[j-1] + data[j],temp[j-1] + data[j]);//temp[j-1]保存的是长为1->j-1的序列分为
			temp[j-1] = ans;                                   //i-1段的最优解
			ans = Max(ans,dp[j]);//ans保存长为i->j的序列分为i段最优解Max，即为最终最优解
		}
	}
	printf("%d\n",ans);
} 
int main()
{
#if debug
	freopen("in.txt","r",stdin);
#endif//debug
	while(~scanf("%d%d",&n,&m))
	{
		M(dp);
		M(temp);
		for(int i = 1;i <= m;i++)
		{
			scanf("%d",&data[i]);
		}
		Do(); 
	}
	return 0;
}