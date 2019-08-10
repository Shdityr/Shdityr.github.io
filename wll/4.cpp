#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=1010,M=100010; int S,T; 
int head[N],ver[M],nxt[M],edge[M],cost[M],tot=1;
void link(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0,cost[tot]=-c;
}

int n,m;

int dis[N]; bool inq[N]; 
queue <int> Q; int frm[N],flow[N];
const int INF=0x3f3f3f3f;
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	Q.push(S); inq[S]=1; dis[S]=0; flow[S]=INF;	
	while(!Q.empty()){
		int x=Q.front(); int D=dis[x]; Q.pop(); inq[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]) continue ;
			int v=ver[i]; if(D+cost[i]>=dis[v]) continue ;
			dis[v]=D+cost[i]; frm[v]=i; flow[v]=min(flow[x],edge[i]);
			if(!inq[v]) inq[v]=1,Q.push(v);
		} 
	}
	return dis[T]<INF;
}

int flow_=0;
void modify(){
 	int x=T; int fl=flow[T];
	while(x!=S){ int i=frm[x];
		edge[i]-=fl,edge[i^1]+=fl;
		x=ver[i^1];
	}
	flow_+=fl*dis[T];
} 

int main()
{
	n=gi(),m=gi(); S=n+1,T=n;
	for(int i=1,u,v,w;i<=m;i++){
		u=gi(),v=gi(),w=gi();  link(u+n,v,1,w);
	}
	for(int i=1;i<=n;i++){
		if(i!=1&&i!=n) link(i,i+n,1,0); 
	}
	while(spfa()) modify();
	
	int num=0; for(int i=head[S];i;i=nxt[i]) if(!edge[i]) num++;
	
	printf("%d %d\n",num,flow_);
}

