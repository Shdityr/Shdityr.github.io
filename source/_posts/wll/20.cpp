#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}
typedef long long ll;

const int N=1010,MAXN=100000,M=1000000;
int head[MAXN],ver[M],nxt[M],tot=1; int edge[M],cost[M];
void link(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot; edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot; edge[tot]=0,cost[tot]=-c;
}

queue <int> Q;
int dis[MAXN]; bool inq[MAXN];
const int INF=0x3f3f3f3f;
bool spfa(int s,int t){
	memset(dis,0x3f,sizeof(dis));
	Q.push(s); inq[s]=1; dis[s]=0;
	while(!Q.empty()){
		int x=Q.front(); Q.pop(); inq[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			int v=ver[i]; if(!edge[i]||dis[v]<=dis[x]+cost[i]) continue ;
			dis[v]=dis[x]+cost[i]; if(!inq[v]) Q.push(v),inq[v]=1;
		}
	}
	return dis[t]<INF;
}

bool mark[MAXN]; int cur[MAXN]; ll RES=0;
int dinic(int x,int t,int Fl){
	if(x==t) return Fl;	mark[x]=1;
	int rem=Fl;
	for(int i=head[x];i;i=nxt[i]){ int v=ver[i];
		if(!mark[v]&&edge[i]&&dis[v]==dis[x]+cost[i]){
			int tmp=dinic(v,t,min(rem,edge[i])); if(!tmp){ dis[v]=INF; continue ; }
			edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp; 
			RES+=(ll)tmp*cost[i]; if(!rem) break ;
		}
	}
	return Fl-rem;
}

int fyl(int s,int t){
	int mxflow=0; RES=0;
	while(spfa(s,t)){
		memset(mark,0,sizeof(mark));
		mxflow+=dinic(s,t,INF);
	}
	return mxflow;
}

int n,W; int S,T; int a[N]; int cnt=0;

void link_edge(int l,int r){
	static int p[N];
	if(l==r) return ; int mid(l+r>>1);
	link_edge(l,mid),link_edge(mid+1,r);
	int t=0; FOR(i,l,r) p[++t]=a[i];
	sort(p+1,p+t+1); t=unique(p+1,p+t+1)-p-1;
	FOR(i,1,t-1){
		link(cnt+i,cnt+i+1,INF,p[i+1]-p[i]);
		link(cnt+i+1,cnt+i,INF,p[i+1]-p[i]);
	}
	FOR(i,l,r){
		int q=lower_bound(p+1,p+t+1,a[i])-p;
		if(i<=mid) link(i,cnt+q,1,0);
		else link(cnt+q,i+n,1,0);
	}
	cnt+=t;
}

int main()
{
	n=gi(),W=gi(); S=n*2+1,T=S+1; cnt=n+n+2;
	FOR(i,1,n) a[i]=gi(),link(S,i,1,0),link(i+n,T,1,0),link(i,T,1,W);
	link_edge(1,n); fyl(S,T); printf("%lld\n",RES);
}

