#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#define FOR(i,a,b) for(int i=a;i<=b;i++) 
using namespace std;

const int N=22,MAXN=N*N*4,M=200020;
int head[MAXN],ver[M],nxt[M],edge[M],cost[M],tot=1;
void link(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot; edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot; edge[tot]=0,cost[tot]=-c;
}

const int INF=0x3f3f3f3f;
int n,m,nm,S,T;
char s1[N][N],s2[N][N],up[N][N];

#define inn(i,j) (i-1)*m+j
#define mid(i,j) (i-1)*m+j+nm
#define out(i,j) (i-1)*m+j+nm+nm

const int px[8]={-1,-1,-1,+0,+0,+1,+1,+1}; 
const int py[8]={-1,-0,+1,-1,+1,-1,+0,+1};
bool ok(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}
void build(){
	S=nm*3+1,T=S+1;
	FOR(i,1,n){ FOR(j,1,m){
			int U=up[i][j]-'0';
			if(s1[i][j]==s2[i][j]||((U&1)==0)){
				link(inn(i,j),mid(i,j),U/2,0);
				link(mid(i,j),out(i,j),U/2,0);
			}
			else{
				if(s1[i][j]=='1'){ 
					link(inn(i,j),mid(i,j),U/2,0); 
					link(mid(i,j),out(i,j),U/2+1,0); 
				}
				else{ 
					link(inn(i,j),mid(i,j),U/2+1,0); 
					link(mid(i,j),out(i,j),U/2,0); 
				}
			}
		}
	}
	
	FOR(i,1,n){ FOR(j,1,m){
			if(s1[i][j]=='1') link(S,mid(i,j),1,0);
			if(s2[i][j]=='1') link(mid(i,j),T,1,0);
		}
	}
	
	FOR(i,1,n){ FOR(j,1,m){
			for(int l=0;l<8;l++){
				int nx=i+px[l]; int ny=j+py[l]; if(!ok(nx,ny)) continue ;
				link(out(i,j),inn(nx,ny),INF,1);
			}
		}
	}
	
}

queue <int> Q; int dis[MAXN]; bool In[MAXN]; int pre[MAXN],flow[MAXN];
bool spfa(){
	memset(dis,0x3f,sizeof(dis)); 
	dis[S]=0; Q.push(S); In[S]=1; flow[S]=INF;
	while(!Q.empty()){
		int x=Q.front(); Q.pop(); In[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]) continue ;
			int v=ver[i]; if(dis[x]+cost[i]>=dis[v]) continue ;
			dis[v]=dis[x]+cost[i]; flow[v]=min(flow[x],edge[i]);
			pre[v]=i; if(!In[v]) Q.push(v),In[v]=1;
		}
	}
//	printf("%d\n",dis[T]);
	return dis[T]<INF;
}
int Ans=0,tflow=0;
void update(){
	int x=T;
	while(x!=S){
		int i=pre[x];
		edge[i]-=flow[T];
		edge[i^1]+=flow[T];
		x=ver[i^1];
	}
	tflow+=flow[T];
	Ans+=flow[T]*dis[T];
}

int main()
{
	scanf("%d %d",&n,&m); nm=n*m;
	FOR(i,1,n) scanf("%s",s1[i]+1);
	FOR(i,1,n) scanf("%s",s2[i]+1);
	FOR(i,1,n) scanf("%s",up[i]+1); 

	int num1=0; FOR(i,1,n)FOR(j,1,m)if(s1[i][j]=='1')num1++;
	int num2=0; FOR(i,1,n)FOR(j,1,m)if(s2[i][j]=='1')num2++;
	if(num1!=num2){ printf("-1\n"); return 0;}
	
	build();
	while(spfa()) update();
	if(tflow!=num1) Ans=-1;
	
	printf("%d\n",Ans);
	return 0;
}
