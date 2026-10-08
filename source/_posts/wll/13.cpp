#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=20000,M=150000;
int head[N],ver[M],nxt[M],tot=1; int edge[M];
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot; edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot; edge[tot]=0;
}

int n,m; int S,T;
const int INF=0x3f3f3f3f;
#define id(i,j) ((i-1)*m+j)

const int px[4]={-1,-0,+0,+1};
const int py[4]={-0,-1,+1,+0};
bool ok(int x,int y){ return 1<=x&&x<=n&&1<=y&&y<=m; }

queue <int> Q; int d[N]; int flow[N];
bool bfs(){
	memset(d,0,sizeof(d));
	d[S]=1; Q.push(S); 
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]||d[ver[i]]) continue ;
			int v=ver[i]; d[v]=d[x]+1,Q.push(v);
		}
	}
	return d[T];
}
int FLOW=0;
int dinic(int x,int Fl){
	if(x==T) return Fl;
	int rem=Fl;
	for(int i=head[x];i;i=nxt[i]){
		int v=ver[i]; if(!edge[i]||d[v]!=d[x]+1) continue ;
		int tmp=dinic(v,min(rem,edge[i])); if(!tmp){d[v]=0;continue ;}
		edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp; if(!rem) break ;
	}
	return Fl-rem;
}

int main()
{
	n=gi(),m=gi(); S=n*m+1,T=S+1;
	FOR(i,1,n) FOR(j,1,m) {
		int x=gi();
		if(x==1) link(S,id(i,j),INF);
		else if(x==2) link(id(i,j),T,INF);
	
		FOR(k,0,3){
			int nx=i+px[k]; int ny=j+py[k];
			if(ok(nx,ny)) link(id(i,j),id(nx,ny),1); 
		}
	}

	while(bfs()) FLOW+=dinic(S,INF);
	printf("%d\n",FLOW);
	
}
