#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=2000,M=100000;
int head[N],ver[M],nxt[M],edge[M],cost[M],tot=1;
void link(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0,cost[tot]=-c;
}

int n,m; int S,T;
int dis[N]; bool inq[N];
queue <int> Q;
const int INF=0x3f3f3f3f;
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	dis[S]=0; Q.push(S); inq[S]=1;
	while(!Q.empty()){
		int x=Q.front(); Q.pop(); inq[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			int v=ver[i]; if(!edge[i]||dis[v]<=dis[x]+cost[i]) continue ;
			dis[v]=dis[x]+cost[i]; if(!inq[v]) Q.push(v),inq[v]=1;
		}
	}
	return dis[T]<INF;
}

int Ans=0;
bool mark[N]; int cur[N];
int dinic(int x,int Fl){
	mark[x]=1;
	if(x==T) return Fl;
	int rem=Fl;
	for(int &i=cur[x];i;i=nxt[i]){
		if(!mark[ver[i]]&&edge[i]&&dis[ver[i]]==dis[x]+cost[i]){
			int v=ver[i]; int tmp=dinic(v,min(rem,edge[i]));
			if(!tmp){ dis[v]=INF; continue ; }
			edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp; Ans+=cost[i]*tmp;
			if(!rem) break ;
		}
	}
	return Fl-rem;
}

int main()
{
	scanf("%d %d",&n,&m); S=n+n+1,T=S+1;
	FOR(i,1,n) link(S,i+n,1,gi());
	FOR(i,1,n) link(S,i,1,0);
	FOR(i,1,m){
		int u,v,w; scanf("%d %d %d",&u,&v,&w);
		if(u>v) swap(u,v);
		link(u,v+n,1,w);
	}
	FOR(i,1,n) link(i+n,T,1,0);
	
	while(spfa()){
		FOR(i,1,T) cur[i]=head[i]; memset(mark,0,sizeof(mark));
		do mark[T]=0,dinic(S,INF); while(mark[T]);
	}
	
	printf("%d\n",Ans);
}

