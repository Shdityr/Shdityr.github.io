#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx,avx2") 
#include <cstdio>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

int n,m;
const int N=50020,M=500020; int S,T,S0,T0;
int head[N],cur[N],ver[M],nxt[M],edge[M],tot=1;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
} 

int a[N];
int ss,tt; int flow0,flow;
const int INF=0x3f3f3f3f;

queue <int> Q; int d[N];
bool bfs(){
	memset(d,0,sizeof(d));
	Q.push(ss); d[ss]=1;
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]||d[ver[i]]) continue ;
			int v=ver[i]; d[v]=d[x]+1; Q.push(v);
		}
	}
	if(d[tt]) for(int i=1;i<=T0;i++) cur[i]=head[i];
	return d[tt];
} 

int dinic(int x,int Fl){
	if(x==tt) return Fl;
	int rem=Fl;
	for(int &i=cur[x];i;i=nxt[i]){
		if(!edge[i]||d[ver[i]]!=d[x]+1) continue ;
		int v=ver[i]; int tmp=dinic(v,min(rem,edge[i]));
		if(!tmp){ d[v]=0; continue ; }
		edge[i]-=tmp,edge[i^1]+=tmp;
		rem-=tmp;  if(!rem) break ;
	}
	return Fl-rem;
}

int main()
{
	n=gi(),m=gi(),S=gi(),T=gi(); S0=n+1,T0=S0+1; 
	for(int i=1;i<=m;i++){
		int u,v,z1,z2; u=gi(),v=gi(),z1=gi(),z2=gi();
		a[u]-=z1,a[v]+=z1; link(u,v,z2-z1);
	}
	
	int flow1=0;
	for(int i=1;i<=n;i++){
		if(a[i]>0) link(S0,i,a[i]),flow0+=a[i];
		if(a[i]<0) link(i,T0,-a[i]);
	}
	
	ss=S0,tt=T0; while(bfs()) flow+=dinic(ss,INF);
	int ans=flow0-flow;
	link(T,S,INF);
	ss=S0,tt=T0; while(bfs()) flow+=dinic(ss,INF);	
	if(flow!=flow0){ printf("please go home to sleep\n"); return 0; }
	printf("%d\n",ans); return 0;	
}

