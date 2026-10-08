#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=300000,M=1500100;
int head[N],ver[M],nxt[M],edge[M],tot=0; 
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
//	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=w;
}

int n,S,T;
#define id(i,j) ((i-1)*n+j)



int dis[N]; 
struct qnode{
	int x,dis;
	bool operator < (const qnode &rhs) const {
		return dis>rhs.dis;
	}
};
priority_queue <qnode> Q;
bool vis[N];
int dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	dis[S]=0; Q.push((qnode){S,0});
	while(!Q.empty()){
		int x=Q.top().x; int D=Q.top().dis; Q.pop();
		if(vis[x]) continue ; vis[x]=1;
		for(int i=head[x];i;i=nxt[i]){
			int v=ver[i]; if(vis[v]||D+edge[i]>=dis[v]) continue ;
			dis[v]=D+edge[i]; Q.push((qnode){v,dis[v]});
		} 
	}
	return dis[T];
}

int main()
{
//	freopen("10.in","r",stdin);
	n=gi(); S=n*n+1,T=S+1;
	
	FOR(i,0,n) FOR(j,1,n) {
		if(!i) link(id(i+1,j),T,gi());
		else if(i==n) link(S,id(i,j),gi());
		else link(id(i+1,j),id(i,j),gi()); 
	}
	
	FOR(i,1,n) FOR(j,0,n) {
		if(!j) link(S,id(i,j+1),gi());
		else if(j==n) link(id(i,j),T,gi());
		else link(id(i,j),id(i,j+1),gi());
		
	}
	
	FOR(i,0,n) FOR(j,1,n){
		if(!i) link(T,id(i+1,j),gi());
		else if(i==n) link(id(i,j),S,gi());
		else link(id(i,j),id(i+1,j),gi()); 
	}
	
	FOR(i,1,n) FOR(j,0,n) {
		if(!j) link(id(i,j+1),S,gi());
		else if(j==n) link(T,id(i,j),gi());
		else link(id(i,j+1),id(i,j),gi());
		
	}
	
	printf("%d\n",dijkstra());
}

