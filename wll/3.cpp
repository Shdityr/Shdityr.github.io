#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
using namespace std;
const int N=1010,M=100010,INF=0x3f3f3f3f;
int ty[11][66];

int S,T; int cnt=0;
int head[N],ver[M],nxt[M],edge[M],cost[M],tot=1;
void add(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0,cost[tot]=-c;
}

int n,m;

int top;
void csh(){
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			ty[i][j]=++cnt;
			add(cnt,T,1,0);
		}
	}
}

int dis[N]; bool In[N]; queue <int> Q; int frm[N],flow[N];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	Q.push(S); In[S]=1; dis[S]=0; flow[S]=INF;	
	while(!Q.empty()){
		int x=Q.front(); int D=dis[x]; Q.pop(); In[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]) continue ;
			int v=ver[i]; if(D+cost[i]>=dis[v]) continue ;
			dis[v]=D+cost[i]; frm[v]=i; flow[v]=min(flow[x],edge[i]);
			if(!In[v]) In[v]=1,Q.push(v);
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
	S=++cnt,T=++cnt;
	scanf("%d %d",&m,&n); csh(); top=cnt;
	for(int i=1;i<=n;i++) add(S,top+i,1,0); 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int vl; scanf("%d",&vl);
			for(int k=1;k<=n;k++){
				add(top+i,ty[j][k],1,vl*k);
			}
		}
	}
	
	while(spfa()) modify();
	
	printf("%.2lf\n",(double)Ans/n);
}

