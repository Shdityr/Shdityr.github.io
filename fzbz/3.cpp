#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

int n,m,numq;

const int N=20020,M=100010;
#define p(i,j) ((i-1)*m+j)
int head[N],ver[N*4],nxt[N*4],edge[N*4],tot=0;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot; edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot; edge[tot]=w;
}

struct node{ int x1,y1,x2,y2,id; }q[M],tmp[M];
int Ans[M]; int xx[N],yy[N];

struct qnode{
	int x,ds;
	bool operator < (const qnode b) const {
		return ds>b.ds;
	}
};
int dis[N]; priority_queue <qnode> Q;
void dijk(int S,int l1,int l2,int r1,int r2){
	memset(dis,0x3f,sizeof(dis)); 
	Q.push((qnode){S,0}); dis[S]=0;
	while(!Q.empty()){
		int x=Q.top().x,D=Q.top().ds; Q.pop();
		if(D>dis[x]) continue ;
		for(int i=head[x];i;i=nxt[i]){
			int v=ver[i]; if(!(l1<=xx[v]&&xx[v]<=l2&&r1<=yy[v]&&yy[v]<=r2)) continue ;
			if(dis[v]<=D+edge[i]) continue ;
			dis[v]=D+edge[i]; Q.push((qnode){v,dis[v]});
		}
	}
}

void solve(int l1,int l2,int r1,int r2,int ql,int qr){
	if(ql>qr) return ;
	
	if(l2-l1>r2-r1){
		int mi=(l1+l2>>1);
		FOR(i,r1,r2){
			dijk(p(mi,i),l1,l2,r1,r2);
			FOR(j,ql,qr)
				Ans[q[j].id]=min(Ans[q[j].id],dis[p(q[j].x1,q[j].y1)]+dis[p(q[j].x2,q[j].y2)]);
		}
		int l=ql,r=qr;
		FOR(i,ql,qr){
			if(q[i].x1<mi&&q[i].x2<mi) tmp[l++]=q[i];
			else if(q[i].x1>mi&&q[i].x2>mi) tmp[r--]=q[i];
		}
		l--,r++;
		FOR(i,ql,l) q[i]=tmp[i];
		FOR(i,r,qr) q[i]=tmp[i];
		
		solve(l1,mi-1,r1,r2,ql,l);
		solve(mi+1,l2,r1,r2,r,qr);
	}
	else{
		int mi=(r1+r2>>1);
		FOR(i,l1,l2){
			dijk(p(i,mi),l1,l2,r1,r2);
			FOR(j,ql,qr)
				Ans[q[j].id]=min(Ans[q[j].id],dis[p(q[j].x1,q[j].y1)]+dis[p(q[j].x2,q[j].y2)]);
		}
		int l=ql,r=qr;
		FOR(i,ql,qr){
			if(q[i].y1<mi&&q[i].y2<mi) tmp[l++]=q[i];
			else if(q[i].y1>mi&&q[i].y2>mi) tmp[r--]=q[i];
		}
		l--,r++;
		FOR(i,ql,l) q[i]=tmp[i];
		FOR(i,r,qr) q[i]=tmp[i];
		
		solve(l1,l2,r1,mi-1,ql,l);
		solve(l1,l2,mi+1,r2,r,qr);
	}
}

int main()
{
	n=gi(),m=gi(); 
	FOR(i,1,n) FOR(j,1,m-1)
		link(p(i,j),p(i,j+1),gi());
	FOR(i,1,n-1) FOR(j,1,m)
		link(p(i,j),p(i+1,j),gi());
	FOR(i,1,n) FOR(j,1,m) xx[p(i,j)]=i,yy[p(i,j)]=j;
	numq=gi(); memset(Ans,0x3f,sizeof(Ans));
	FOR(i,1,numq){
		q[i].x1=gi(),q[i].y1=gi(),q[i].x2=gi(),q[i].y2=gi();
		q[i].id=i;
	}
	solve(1,n,1,m,1,numq);
	FOR(i,1,numq) printf("%d\n",Ans[i]);
}

