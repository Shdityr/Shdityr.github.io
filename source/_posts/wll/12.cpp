#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

typedef long long ll;
int n,m; ll B,W,numb,numw;
ll v[50][50]; int S,T;

const int N=6000,M=100000;
int head[N],ver[M],nxt[M],tot=1; ll edge[M];
void link(int u,int v,ll w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
}

int d[N]; int cur[N];
queue <int> Q; 
bool bfs(){
	memset(d,0,sizeof(d));
	Q.push(S); d[S]=1;
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int v=ver[i]; if(!edge[i]||d[v]) continue ;
			d[v]=d[x]+1; Q.push(v);
		}
	}
//	FOR(i,1,T) printf("%d ",d[i]); printf("\n");
	if(d[T]) FOR(i,1,T) cur[i]=head[i];
	return d[T];
}

ll dinic(int x,ll Fl){
	if(x==T) return Fl;
	ll rem=Fl;
	for(int &i=cur[x];i;i=nxt[i]){
		int v=ver[i]; if(!edge[i]||d[v]!=d[x]+1) continue ;
		ll tmp=dinic(v,min(edge[i],rem)); if(!tmp){ d[v]=0; continue ; }
		edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp;
		if(!rem) break ;
	}
	return Fl-rem;
}

#define id(i,j) ((i-1)*m+j)
const int px[4]={-1,-0,+0,+1};
const int py[4]={-0,-1,+1,+0};
const ll INF=(1ll<<50);
bool ok(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}
bool check(ll mid){
	memset(head,0,sizeof(head)); tot=1; ll sum=0;
	FOR(i,1,n) FOR(j,1,m) { //printf("%d ",v[i][j]);
		if((i+j)&1){
			link(S,id(i,j),mid-v[i][j]),sum+=mid-v[i][j];
			FOR(k,0,3){
				int nx=i+px[k]; int ny=j+py[k];
				if(!ok(nx,ny)) continue ;
				link(id(i,j),id(nx,ny),INF);
			}
		}
		else{
			link(id(i,j),T,mid-v[i][j]);
		}
	}
	
//	int x=6; for(int i=head[x];i;i=nxt[i]) printf("%d %d|",ver[i],edge[i]); printf("\n");
//	printf("%lld\n",sum);
	ll flow=0; while(bfs()) flow+=dinic(S,INF);
	return flow==sum;
}

int main()
{
//	freopen("1.in","r",stdin);
	int Tsk=gi();
	while(Tsk--){
		n=gi(),m=gi(); S=n*m+1,T=S+1;
		ll l,r; l=0; r=INF;
		numb=numw=B=W=0;
		FOR(i,1,n) FOR(j,1,m) {
			v[i][j]=gi(); l=max(v[i][j],l);
			if((i+j)&1) B+=v[i][j],numb++; 
			else W+=v[i][j],numw++;
		}
//		printf("%d\n",l);
		if(numb!=numw){
			ll x=(B-W)/(numb-numw);
			if(x>=l&&check(x)) printf("%lld\n",x*numw-W);
			else printf("-1\n");
		}
		else{
			if(W!=B) printf("-1\n");
			else{
//				printf("%d!\n",check(3));
				while(l<r){
					ll mid=l+(r-l)/2;//printf("%d %d %d\n",l,r,mid);
					if(check(mid)) r=mid;
					else l=mid+1;
				}
				if(check(l)) printf("%lld\n",l*numw-W);
				else printf("-1\n");
			}
		}
	}	
}

