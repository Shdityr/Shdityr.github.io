#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=60,MAXN=500,M=100000;
int head[MAXN],ver[M],nxt[M],edge[M],tot=1;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
}

int n,k,nn; char a[N][N]; int S,T;
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


void build(int mid){
	memset(head,0,sizeof(head)); tot=1; 
	FOR(i,1,n) link(S,i,mid),link(i,i+n,k);
	FOR(i,1,n) link(nn+i,T,mid),link(nn+i+n,nn+i,k);
	
	FOR(i,1,n) FOR(j,1,n) {
		if(a[i][j]=='Y') link(i,nn+j,1);
		else link(i+n,nn+j+n,1);
	}
}

bool check(int mid){
	build(mid);
	int sum=0; while(bfs()) sum+=dinic(S,INF);
	return sum==mid*n;
}

int main()
{
	n=gi(),k=gi(),nn=2*n; S=n*4+1,T=S+1;
	FOR(i,1,n) scanf("%s",a[i]+1);
	int l=0; int r=INF;
	while(l<r){
		int mid((l+r+1)>>1);
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
}
  
