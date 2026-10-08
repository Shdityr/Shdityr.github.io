#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
#include <algorithm>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int N=1010,M=100010;
int head[N],ver[M],nxt[M],tot=1; int edge[M],cost[M]; int S,T,ss,tt;
void link(int u,int v,int w,int c){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w,cost[tot]=c;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0,cost[tot]=-c;
}

int n,m;
char s[20][20]; int a[N];
#define id(i,j) ((i-1)*m+j)
const int px[4]={-1,+0,+0,+1};
const int py[4]={-0,-1,+1,+0};
inline bool ok(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}

int flow,flow0,A_cost;
const int INF=0x3f3f3f3f;

void build()
{
	S=n*m+1,T=S+1,ss=T+1,tt=ss+1;
	FOR(i,1,n) FOR(j,1,m){
		if(s[i][j]=='#') continue ;
		if((i+j)&1){
			if(i==1||j==1||i==n||j==m) link(id(i,j),T,1,1);//huafei 1 de daijia jianshao 1 de ru liuliang
			a[S]-=2; a[id(i,j)]+=2; //link(S,id(i,j),0,0) 
			for(int k=0;k<4;k++){
				int nx=i+px[k]; int ny=j+py[k]; 
				if(!ok(nx,ny)||s[nx][ny]=='#') continue ;
				link(id(i,j),id(nx,ny),1,0);
			}
		}
		else{
			if(i==1||j==1||i==n||j==m) link(S,id(i,j),1,1);//huafei 1 de daijia jianshao 1 de chu liuliang
			a[id(i,j)]-=2; a[T]+=2; //link(id(i,j),tt,0,0);
		}		
	}
	FOR(i,1,T){
		if(a[i]>0) link(ss,i,a[i],0);
		if(a[i]<0) link(i,tt,-a[i],0);
	}
}

queue <int> Q; int dis[N]; bool inq[N];
bool spfa(int s,int t){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0; Q.push(s); inq[s]=1;
	while(!Q.empty()){
		int x=Q.front(); Q.pop(); inq[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]) continue ;
			int v=ver[i]; if(dis[x]+cost[i]>=dis[v]) continue ;
			dis[v]=dis[x]+cost[i]; if(!inq[v]) Q.push(v),inq[v]=1; 
		}
	} 
//	printf("%d ",dis[s]);
	return dis[t]<INF;
}

int mark[N];
int dfs(int x,int t,int Fl){
	mark[x]=1;
	if(x==t) return Fl;
	int rem=Fl;
	for(int i=head[x];i;i=nxt[i]){
		if(!mark[ver[i]]&&dis[x]+cost[i]==dis[ver[i]]&&edge[i]){
			int v=ver[i]; int tmp=dfs(v,t,min(edge[i],rem));
			if(!tmp){ dis[v]=INF; continue ; }
			edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp; A_cost+=cost[i]*tmp;
			if(!rem) break ;
		}
	}
	return Fl-rem;
}

void wll(int x,int y){
	while(spfa(x,y)){
		memset(mark,0,sizeof(mark));
		do mark[y]=0,flow+=dfs(x,y,INF); while(mark[y]);
	}
}

bool check(){
	for(int i=head[ss];i;i=nxt[i])
		if(edge[i]) return false;
	return true;
}

int main()
{
//	freopen("3.in","r",stdin);
//	freopen("my.out","w",stdout);
	while(scanf("%s",s[++n]+1)!=EOF); n--; 
	m=strlen(s[1]+1); build(); link(T,S,INF,0);
	wll(ss,tt);
	if(check()) printf("%d\n",A_cost/2);
	else printf("-1\n"); 
}
 
