#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=1010,M=100010,INF=0x3f3f3f3f;
int S,T; int cnt=0;
int head[N],ver[M],nxt[M],edge[M],cost[M],tot=1;
void link(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0,cost[tot]=-c;
}

int n,m;

int dis[N]; bool inq[N]; 
queue <int> Q; int frm[N],flow[N];
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

int Ans=0;
void modify(){
 	int x=T; int fl=flow[T];
	while(x!=S){ int i=frm[x];
		edge[i]-=fl,edge[i^1]+=fl;
		x=ver[i^1];
	}
	Ans+=fl*dis[T];
} 

int main()
{
	n=gi(),m=gi(); S=n+2,T=S+1;
	for(int i=1,a;i<=n;i++) a=gi(),link(i,i+1,INF-a,0); 
	link(S,1,INF,0),link(n+1,T,INF,0);//di i ge dian houmian de na tiao bian daibiao di i tian de suoxu liuliang 
	for(int i=1;i<=m;i++){ 
		int x,y,c; x=gi(),y=gi(),c=gi();
		link(x,y+1,INF,c);
	}
	
	while(spfa()) modify();
	
	printf("%d\n",Ans);
}

