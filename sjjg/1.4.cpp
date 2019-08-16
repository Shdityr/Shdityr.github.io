#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while((c<'0'||'9'<c)&&c!='-')c=gc;int f(1);if(c=='-')c=gc,f=-1;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x*f;}

const int N=100010;
int n,m,lt[N];
struct poi{int d[4];}a[N];  int b[N];
int D; bool operator < (poi a,poi b){return a.d[D]<b.d[D];}
struct node{int mn[4],mx[4],ch[2];poi a;}t[N]; int rt;
#define ls t[o].ch[0]
#define rs t[o].ch[1]
void upd(int o,int ch){
	FOR(i,0,3){
		 t[o].mn[i]=min(t[o].mn[i],t[ch].mn[i]);
		 t[o].mx[i]=max(t[o].mx[i],t[ch].mx[i]);
	}
}
void pushup(int o){
	FOR(i,0,3) t[o].mn[i]=t[o].mx[i]=t[o].a.d[i];
	if(ls) upd(o,ls);  if(rs) upd(o,rs);
}

int build(int l,int r,int ty){
	int o(l+r>>1);
	D=ty; nth_element(&a[l],&a[o],&a[r+1]); t[o].a=a[o];
	if(l<o) ls=build(l,o-1,(ty+1)%4);
	if(r>o) rs=build(o+1,r,(ty+1)%4);
	pushup(o); return o;
}

bool check(poi l,poi r,poi a){
	FOR(i,0,3)
		if(!(l.d[i]<=a.d[i]&&a.d[i]<=r.d[i]))
			return false;
	return true; 
}

poi L,R;
void query(int o){
	FOR(i,0,3) if(t[o].mn[i]>R.d[i]||t[o].mx[i]<L.d[i]) return ;
	if(check(L,R,t[o].a)) L.d[2]=max(L.d[2],t[o].a.d[2]);
	if(ls) query(ls);  if(rs) query(rs);
}

int lans=0;
int main()
{
	n=gi(),m=gi();
	FOR(i,1,n){
		b[i]=gi(); a[i]=(poi){lt[b[i]],i,b[i],0};
		lt[b[i]]=i;
	}
	FOR(i,1,n) lt[i]=n+1;
	for(int i=n;i>=1;i--) {
		a[i].d[3]=lt[b[i]];
		lt[b[i]]=i;
	}
//	FOR(i,1,n) printf("%d : %d %d %d %d\n",i,a[i].d[0],a[i].d[1],a[i].d[2],a[i].d[3]);
	rt=build(1,n,0);
	while(m--){
		int l=(gi()+lans)%n+1,r=(gi()+lans)%n+1;
		if(l>r) swap(l,r);
		L=(poi){0,l,0,r+1};
		R=(poi){l-1,r,N,n+1};
		query(rt); printf("%d\n",lans=L.d[2]);
	}
}

