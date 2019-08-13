#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#include <map>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while((c<'0'||'9'<c)&&c!='-')c=gc;int f(1);if(c=='-')c=gc,f=-1;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x*f;}

const int MAXN=200000,M=MAXN*16;
int head[MAXN],ver[M],nxt[M],edge[M],tot=1;
void link(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=head[u],head[u]=tot,edge[tot]=w;
	ver[++tot]=u,nxt[tot]=head[v],head[v]=tot,edge[tot]=0;
}

int n,cnt=0; int S,T;
const int INF=0x3f3f3f3f;

struct poi{
	int x,y;
	poi(int a=0,int b=0) { x=a,y=b; }
	bool operator < (const poi a) const { return x==a.x?y<a.y:x<a.x; }
	poi operator + (const poi a) const {
		return poi(x+a.x,y+a.y);
	}
};

poi p[MAXN];
map <poi,int> id,val,f;
map <poi,bool> bk;

queue <int> Q; int d[MAXN];
bool bfs(){
	memset(d,0,sizeof(d));
	d[S]=1; Q.push(S);
	while(!Q.empty()){
		int x=Q.front(); Q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if(!edge[i]||d[ver[i]]) continue ;
			int v=ver[i]; d[v]=d[x]+1,Q.push(v);
		}
	}
	return d[T];
}
int dinic(int x,int Fl){
	if(x==T) return Fl;
	int rem=Fl;
	for(int i=head[x];i;i=nxt[i]){
		int v=ver[i]; if(!edge[i]||d[v]!=d[x]+1) continue ;
		int tmp=dinic(v,min(rem,edge[i])); if(!tmp){d[v]=0;continue ;}
		edge[i]-=tmp,edge[i^1]+=tmp; rem-=tmp; if(!rem) break ;
	}
	return Fl-rem;
}

void linka(int a,int p,int b){
	if(!bk[poi(S,a)]) link(S,a,INF),bk[poi(S,a)]=1;
	if(!bk[poi(a,p)]) link(a+cnt,p,INF),bk[poi(a,p)]=1;
	if(!bk[poi(p,b)]) link(p+cnt,b,INF),bk[poi(p,b)]=1;
	if(!bk[poi(b,T)]) link(b+cnt,T,INF),bk[poi(b,T)]=1;
}

int sum=0;
void build(){
	FOR(i,1,n) if(f[p[i]]<2) {
		int pt=id[p[i]],ene=val[p[i]]*(10+f[p[i]]); sum+=ene;
		link(pt,pt+cnt,ene); if(!f[p[i]]){ f[p[i]]=2; continue ; }
		int a[4],b[4]; int na=0,nb=0; f[p[i]]=2;
		
		if(!(a[++na]=id[p[i]+poi(1,0)])) na--;
		if(!(a[++na]=id[p[i]+poi(0,1)])) na--;
		if(!(a[++na]=id[p[i]+poi(-1,-1)])) na--;
		
		if(!(b[++nb]=id[p[i]+poi(1,1)])) nb--;
		if(!(b[++nb]=id[p[i]+poi(-1,0)])) nb--;
		if(!(b[++nb]=id[p[i]+poi(0,-1)])) nb--;
		
		FOR(x,1,na) FOR(y,1,nb) linka(a[x],pt,b[y]);
	}
}


int main()
{
	freopen("1.in","r",stdin);
	n=gi();
	FOR(i,1,n) {
		int x=gi(),y=gi(),z=gi(),c=gi();
		p[i]=poi(x-z,y-z);  if(!id[p[i]]) id[p[i]]=++cnt;
		val[p[i]]+=c; f[p[i]]=((x+y+z)%3==0);
	}
	S=cnt*2+1,T=S+1;
	build();
	int Ans=0; while(bfs()) Ans+=dinic(S,INF);
	printf("%.1lf\n",(double)(sum-Ans)/10);
}
  
