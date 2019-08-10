#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=10010,M=4000020;
int head[N],ver[M],nxt[M],edge[M],tot=1;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
}

int n,m;
const int INF=0x3f3f3f3f; int S,T;
queue <int> Q; int d[N];
bool bfs(){
	memset(d,0,sizeof(d));
	Q.push(S); d[S]=1;
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]||d[ver[i]]) continue ;
			int v=ver[i]; d[v]=d[x]+1; Q.push(v);
		}
	}
	return d[T];
} 

int cur[N]; int flow=0; int sum=0;
int dinic(int x,int Fl){
	if(x==T) return Fl;
	int rem=Fl;
	for(int &i=cur[x];i;i=nxt[i]){
		int v=ver[i]; if(!edge[i]||d[v]!=d[x]+1) continue ;
		int tmp=dinic(v,min(edge[i],rem)); if(!tmp){ d[v]=0; continue ; }
		edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp; if(!rem) break ;
	}
	return Fl-rem;
}

int main()
{
	n=gi(),m=gi(); S=n+m+1,T=S+1;
	for(int i=1;i<=n;i++){
		int v=gi(); int num=gi(); link(i,T,v); sum+=v;
		for(int j=1;j<=num;j++){
			int x=gi(); v=gi(); link(n+x,i,v);
		}
	}
	for(int i=1;i<=m;i++){
		int v=gi(); link(S,n+i,v);
	}

	while(bfs()){
		for(int i=1;i<=T;i++) cur[i]=head[i];
		flow+=dinic(S,INF);
	}
	
	printf("%d\n",sum-flow);	
}

