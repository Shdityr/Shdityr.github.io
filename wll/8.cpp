#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int n,m,S,T,SUM=0; const int N=110,INF=0x3f3f3f3f;
int val;
// int v0[N][N],v1[N][N];
// int e01[N][N],e02[N][N],e11[N][N],e12[N][N];

//-----Qxx----->
const int MAXN=N*N*6,MAXM=MAXN*12;
int head[MAXN],Next[MAXM],ver[MAXM],tot=1; int edge[MAXM];
void link(int u,int v,int w){
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot; edge[tot]=w;
	ver[++tot]=u,Next[tot]=head[v],head[v]=tot; edge[tot]=0;
}

int p[N][N],cnt=0; //point's rank int the tot graph
void build()
{
	scanf("%d %d",&n,&m); S=++cnt; T=++cnt;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&val); SUM+=val;
			p[i][j]=++cnt; link(S,p[i][j],val);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&val); SUM+=val;
			link(p[i][j],T,val);
		}
	}

	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&val); SUM+=val;
			int tp=++cnt; link(S,tp,val); link(tp,p[i][j],INF); link(tp,p[i+1][j],INF);
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&val); SUM+=val;
			int tp=++cnt; link(tp,T,val); link(p[i][j],tp,INF); link(p[i+1][j],tp,INF);
		}
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			scanf("%d",&val); SUM+=val;
			int tp=++cnt; link(S,tp,val); link(tp,p[i][j],INF); link(tp,p[i][j+1],INF);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			scanf("%d",&val); SUM+=val;
			int tp=++cnt; link(tp,T,val); link(p[i][j],tp,INF); link(p[i][j+1],tp,INF);
		}
	}
}

//-----Dinic----->
int d[MAXN];
queue <int> Q;
bool bfs()
{
	while(!Q.empty()) Q.pop();
	memset(d,0,sizeof(d));
	Q.push(S); d[S]=1;
	while(!Q.empty())
	{
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=Next[i]){
			int v=ver[i];
			if(!d[v]&&edge[i]>0){
				d[v]=d[x]+1;
				if(v==T) return true;
				Q.push(v);
			}
		}
	}
	return false;
}

int cur[MAXN];
int dfs(int x,int Flow)
{
	if(x==T) return Flow;
	int tmp=Flow;
	for(int &i=cur[x];i&&tmp>0;i=Next[i]){
		int v=ver[i];
		if(d[v]==d[x]+1&&edge[i]>0){
			int k=dfs(v,min(edge[i],tmp));
			if(k==0){ d[v]=0; continue ; }
			tmp-=k; edge[i]-=k,edge[i^1]+=k;
		}
	}
	return Flow-tmp;
}

void work()
{
	int minicut=0;
	while(bfs()){
		for(int i=1;i<=cnt;i++) cur[i]=head[i];
		minicut+=dfs(S,INF);
	  }
	printf("%d\n",SUM-minicut);
}


int main()
{
	build();
	work();
	return 0;
}
