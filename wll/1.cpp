#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=1100,MAXN=10010*110,M=200020; int S,T;
int head[MAXN],ver[M],nxt[M],tot=1; int edge[M];
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot; edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot; edge[tot]=0;
}

int n,m;
bool ap[1111]; int b[N];
const int INF=0x3f3f3f3f;

queue <int> Q; int d[MAXN];
bool bfs(){
	memset(d,0,sizeof(d)); d[S]=1; Q.push(S);
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int v=ver[i]; if(!edge[i]||d[v]) continue ;
			d[v]=d[x]+1; Q.push(v);
		}
	}
	return d[T];
}
int Ans=0;
int dinic(int x,int Fl){
	if(x==T) return Fl;
	int rem=Fl;
	for(int i=head[x];i;i=nxt[i]){
		int v=ver[i]; if(!edge[i]||d[v]!=d[x]+1) continue ;
		int k=dinic(v,min(rem,edge[i])); if(!k){ d[v]=0; continue ; }
		edge[i]-=k,edge[i^1]+=k,rem-=k; if(!rem) break ;
	}
	return Fl-rem;
}


int main()
{
//	freopen("3.in","r",stdin);
	scanf("%d %d",&n,&m); S=n+m+1,T=S+1;
	FOR(i,1,n){ int w=gi(); link(S,i,w); }
	FOR(i,1,n) b[i]=i;
	FOR(i,1,m){
		int num=gi(); memset(ap,0,sizeof(ap));
		FOR(j,1,num){
			int t=gi(); if(ap[b[t]]) continue ;
//			printf("%d\n"
			ap[b[t]]=1; link(b[t],n+i,INF); b[t]=n+i;
		}
		int B=gi(); link(n+i,T,B);
	}
	while(bfs()) Ans+=dinic(S,INF);
	printf("%d\n",Ans); return 0;
}
