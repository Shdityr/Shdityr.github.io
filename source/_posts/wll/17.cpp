#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=50,MAXN=N*N*N,M=1250000;
int head[MAXN],ver[M],nxt[M],edge[M],tot=1;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
}

int n,m,k,nm; int D;
int a[N][N][N]; int S,T;
#define p(i,j,k) ((k-1)*nm+(i-1)*m+j)
const int INF=0x3f3f3f3f;

queue <int> Q; int d[MAXN];
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
//	printf("%d\n",d[T]);
	return d[T];
}
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


const int px[4]={-1,-0,+0,+1};
const int py[4]={-0,-1,+1,+0};
void build(){
	FOR(i,1,n) FOR(j,1,m) {
		link(S,p(i,j,1),a[i][j][1]);
		FOR(l,2,k) link(p(i,j,l-1),p(i,j,l),a[i][j][l]);
		link(p(i,j,k),T,INF);
	}
	FOR(i,1,n) FOR(j,1,m) FOR(l,D+1,k) {
		FOR(t,0,3) {
			int nx=i+px[t]; int ny=j+py[t];
			if(1<=nx&&nx<=n&&1<=ny&&ny<=m){
				link(p(i,j,l),p(nx,ny,l-D),INF);
			}
		}
	}
}

int main()
{
	n=gi(),m=gi(),k=gi(),D=gi(); nm=n*m; S=n*m*k+1,T=S+1;
	FOR(l,1,k) FOR(i,1,n) FOR(j,1,m) a[i][j][l]=gi();
	build();
	int Ans=0; while(bfs()) Ans+=dinic(S,INF);
	printf("%d\n",Ans);
}
 
