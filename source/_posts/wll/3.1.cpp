#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=100010,M=10000020;
int head[N],ver[M],nxt[M],edge[M],cost[M],tot=1;
void link(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0,cost[tot]=-c;
}

int n,m,p,np; 
int a[44]; int tim[110][40];
#define id(i,j) ((i-1)*p+j)

const int INF=0x3f3f3f3f; int S,T; int now[N];
queue <int> Q; bool inq[N]; 
int dis[N]; int frm[N],flow[N];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	Q.push(S); inq[S]=1; dis[S]=0; flow[S]=INF;
	while(!Q.empty()){
		int x=Q.front(); Q.pop(); inq[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]||dis[ver[i]]<=dis[x]+cost[i]) continue ;
			int v=ver[i]; dis[v]=dis[x]+cost[i];
			frm[v]=i; flow[v]=min(flow[x],edge[i]);
			if(!inq[v]) Q.push(v),inq[v]=1;
		}
	}
//	printf("%d\n",dis[T]);
	return dis[T]<INF; 
}
int Ans=0;
void update(){
	int x=T;
	while(x!=S){
		int i=frm[x];
		edge[i]-=flow[T],edge[i^1]+=flow[T];
		x=ver[i^1];
	}
	Ans+=dis[T]*flow[T];
}

int main()
{
//	freopen("2.in","r",stdin);
	n=gi(),m=gi();
	FOR(i,1,n) a[i]=gi(),p+=a[i];
	np=m*p; S=np+n+1,T=S+1;
	FOR(i,1,n) link(S,np+i,a[i],0);
	FOR(i,1,n) FOR(j,1,m) tim[j][i]=gi();
	FOR(x,1,np) link(x,T,1,0); 
	FOR(i,1,n){
		FOR(j,1,m) link(np+i,id(j,1),1,tim[j][i]*1);
	}
	FOR(i,1,m) now[i]=1;
	while(spfa()){
		update();
		int t=(ver[frm[T]^1]-1)/p+1; now[t]++;
		FOR(i,1,n) link(np+i,id(t,now[t]),1,tim[t][i]*now[t]);
	}
	printf("%d\n",Ans);
}
 
