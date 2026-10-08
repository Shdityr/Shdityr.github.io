#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

int n,m,nm; const int N=55;
int a[N][N],b[N][N];

const int MAXN=10010,MAXM=200020; int S,T; int sum=0;
int head[MAXN],ver[MAXM],nxt[MAXM],edge[MAXM],tot=1;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
}

#define p1(i,j) ((i-1)*m+j)
#define p2(i,j) ((i-1)*m+j+nm)

const int INF=0x3f3f3f3f;
const int px[]={-1,+0,+0,+1};
const int py[]={-0,-1,+1,+0};
bool ok(int x,int y){ return 1<=x&&x<=n&&1<=y&&y<=m; }
void build(){
	FOR(i,1,n) FOR(j,1,m) {
		if((i+j)&1){
			link(p1(i,j),p2(i,j),b[i][j]);
			link(S,p1(i,j),a[i][j]);
			FOR(k,0,3){
				int nx=i+px[k]; int ny=j+py[k]; if(!ok(nx,ny)) continue ;
				link(p1(i,j),p2(nx,ny),INF),link(p2(i,j),p1(nx,ny),INF); 
			}
		}
		else{
			link(p2(i,j),p1(i,j),b[i][j]);
			link(p1(i,j),T,a[i][j]);
		}
	}
}

queue <int> Q; int d[MAXN];
bool bfs(){
	memset(d,0,sizeof(d));
	while(!Q.empty()) Q.pop();
	Q.push(S); d[S]=1;
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]||d[ver[i]]) continue ;
			int v=ver[i]; d[v]=d[x]+1;
			if(v==T) return 1;  Q.push(v);
		}
	}
	return 0;
}

int cur[MAXN]; int flow=0;
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

void upcur(){ FOR(i,1,T) cur[i]=head[i]; }

int main()
{
	n=gi(),m=gi(); nm=n*m; S=nm+nm+1,T=S+1;
	FOR(i,1,n) FOR(j,1,m) a[i][j]=gi();
	FOR(i,1,n) FOR(j,1,m) b[i][j]=gi(),sum+=b[i][j];
	
	build();
	
	while(bfs()) upcur(),flow+=dinic(S,INF);
	
	printf("%d\n",sum-flow);
}

