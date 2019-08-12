#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++) 
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while((c<'0'||'9'<c)&&c!='-')c=gc;int f(1);if(c=='-')f=-1,c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x*f;}

const int N=10000,M=200200;
int head[N],ver[M],nxt[M],edge[M],tot=1;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot; edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot; edge[tot]=0;
}

int n,m,k; int S,T;
int p[20],num[20]; int s[20][20];

int fa[20];
int getf(int x){ return fa[x]==x?x:fa[x]=getf(fa[x]); }
void merge(int x,int y){ fa[getf(y)]=getf(x); }

const int INF=0x3f3f3f3f;

queue <int> Q; int d[N];
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
//	freopen("1.in","r",stdin);
	n=gi(),m=gi(),k=gi(); S=n+1,T=n+2;
	FOR(i,1,n+2) fa[i]=i;
	FOR(i,1,m){
		p[i]=gi(),num[i]=gi();
		FOR(j,0,num[i]-1){
			s[i][j]=gi();
			if(s[i][j]==0) s[i][j]=n+1;
			else if(s[i][j]==-1) s[i][j]=n+2; 
			if(j) merge(s[i][j],s[i][j-1]);
		}
	}
//	FOR(i,1,T) printf("%d ",getf(i)); 
	if(getf(S)!=getf(T)) { printf("0\n"); return 0; }
	
	T=N-2;
	for(int stp=1,mx=0;;stp++){
		FOR(i,1,m){
			int x=s[i][(stp-1)%num[i]]; int y=s[i][stp%num[i]];
			if(x==n+2) x=T;
			else x=(stp-1)*(n+1)+x;
			if(y==n+2) y=T;
			else y=stp*(n+1)+y;
//			printf("%d %d\n",x,y);
			link(x,y,p[i]);
		}
		while(bfs()) mx+=dinic(S,INF);
		if(mx>=k){ printf("%d\n",stp); return 0; }
		FOR(i,1,S) link((stp-1)*(n+1)+i,stp*(n+1)+i,INF);
	}
}
 
