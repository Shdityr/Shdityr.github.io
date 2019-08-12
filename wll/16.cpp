#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++) 
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while((c<'0'||'9'<c)&&c!='-')c=gc;int f(1);if(c=='-')f=-1,c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x*f;}
typedef long long ll;

const int N=500,M=100200;
int head[N],ver[M],nxt[M],tot=1; ll edge[M];
void link(int u,int v,ll w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot; edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot; edge[tot]=0;
}

int n,m,S,T; 
const ll INF=(1ll<<50);
ll a[60],b[60]; ll sum=0; bool e[60][60];

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
ll dinic(int x,ll Fl){
	if(x==T) return Fl;
	ll rem=Fl;
	for(int i=head[x];i;i=nxt[i]){
		int v=ver[i]; if(!edge[i]||d[v]!=d[x]+1) continue ;
		ll tmp=dinic(v,min(rem,edge[i])); if(!tmp){d[v]=0;continue ;}
		edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp; if(!rem) break ;
	}
	return Fl-rem;
}

bool check(ll mid)
{
	memset(head,0,sizeof(head)); tot=1;
	FOR(i,1,m) link(S,i,mid*b[i]);
	FOR(i,1,n) link(i+m,T,a[i]);
	FOR(i,1,m) FOR(j,1,n) {
		if(e[i][j]) link(i,j+m,INF);
	}
	ll flow=0; while(bfs()) flow+=dinic(S,INF);
	return flow==sum;
}

int main()
{
	n=gi(),m=gi(); S=n+m+1,T=S+1;
	FOR(i,1,n) a[i]=10000ll*gi(),sum+=a[i];
	FOR(i,1,m) b[i]=gi();
	FOR(i,1,m) FOR(j,1,n) e[i][j]=gi();
	ll l,r; l=0,r=1e11;
	while(l<r){
		ll mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%.6lf\n",(double)l/10000);
}

