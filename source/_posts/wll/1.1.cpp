//https://loj.ac/problem/115 
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std; 
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

int n,m;
const int N=220,M=10222,MAXM=(N+N+M)*2;
int head[N],ver[MAXM],nxt[MAXM],edge[MAXM],tot=1; int S,T;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
}

int a[N],inn[M],bh[M]; 
int flow0,flow;
const int INF=0x3f3f3f3f;

queue <int> Q; int d[N];
bool bfs(){
	memset(d,0,sizeof(d));
	d[S]=1; Q.push(S);
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]||d[ver[i]]) continue ;
			int v=ver[i]; d[v]=d[x]+1; Q.push(v);
		}
	}
	return d[T];
} 

int dinic(int x,int Fl){
	if(x==T) return Fl;
	int rem=Fl;
	for(int i=head[x];i;i=nxt[i]){
		if(!edge[i]||d[ver[i]]!=d[x]+1) continue ;
		int v=ver[i]; int k=dinic(v,min(rem,edge[i]));
		if(!k){ d[v]=0; continue ; }
		edge[i]-=k,edge[i^1]+=k; rem-=k;
		if(!rem) break ;
	}
	return Fl-rem;
}

int main()
{
	n=gi(),m=gi(); S=n+1,T=S+1; 
	for(int i=1;i<=m;i++){
		int u,v,z1,z2; u=gi(),v=gi(),z1=gi(),z2=gi();
		inn[i]=z1; a[u]-=z1,a[v]+=z1; link(u,v,z2-z1);
		bh[i]=tot;
	}
	for(int i=1;i<=n;i++){
		if(a[i]>0) link(S,i,a[i]),flow0+=a[i];
		if(a[i]<0) link(i,T,-a[i]);
	}
	
	while(bfs()) flow+=dinic(S,INF);

	if(flow!=flow0) printf("NO\n");
	else{
		printf("YES\n");
		for(int i=1;i<=m;i++)
			printf("%d\n",inn[i]+edge[bh[i]]);
	}
	return 0;
}

