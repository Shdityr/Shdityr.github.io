#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#define sqr(x) ((x)*(x))
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

typedef long long ll;
int n,k;

const int N=100010;
struct poi{ll d[2];}a[N];
int D; bool operator < (poi a,poi b){ return a.d[D]<b.d[D]; }
struct node{ ll mn[2],mx[2],ch[2]; poi a; }t[N]; int rt=0;
#define ls t[o].ch[0]
#define rs t[o].ch[1]
priority_queue <ll,vector<ll>,greater<ll> > Q;
void upd(int o,int ch){
	t[o].mn[0]=min(t[o].mn[0],t[ch].mn[0]);
	t[o].mn[1]=min(t[o].mn[1],t[ch].mn[1]);
	t[o].mx[0]=max(t[o].mx[0],t[ch].mx[0]);
	t[o].mx[1]=max(t[o].mx[1],t[ch].mx[1]);
}
void pushup(int o){
	t[o].mn[0]=t[o].mx[0]=t[o].a.d[0];
	t[o].mn[1]=t[o].mx[1]=t[o].a.d[1];
	if(ls) upd(o,ls); if(rs) upd(o,rs);
}

int build(int l,int r,int ty){
	int o(l+r>>1);
	D=ty; nth_element(&a[l],&a[o],&a[r+1]);
	t[o].a=a[o];
	if(l<o) ls=build(l,o-1,ty^1);
	if(r>o) rs=build(o+1,r,ty^1);
	pushup(o); return o;
}

//ll sqr(ll x){ return x*x; }
ll dist(poi a,poi b){
	return sqr(a.d[0]-b.d[0])+sqr(a.d[1]-b.d[1]);
}

ll Dist(poi a,node b){
	ll ret(0);
	ret=max(ret,dist(a,(poi){b.mn[0],b.mn[1]}));
	ret=max(ret,dist(a,(poi){b.mn[0],b.mx[1]}));
	ret=max(ret,dist(a,(poi){b.mx[0],b.mn[1]}));
	ret=max(ret,dist(a,(poi){b.mx[0],b.mx[1]}));
	return ret;
}

void query(int o,poi a){
	ll dis=dist(t[o].a,a);
	if(dis>Q.top()) Q.pop(),Q.push(dis);
	if(ls&&Dist(a,t[ls])>Q.top()) query(ls,a);
	if(rs&&Dist(a,t[rs])>Q.top()) query(rs,a);
}

int main()
{
	n=gi(),k=gi();
	for(int i=1;i<=n;i++) a[i].d[0]=gi(),a[i].d[1]=gi();
	rt=build(1,n,0);
	for(int i=1;i<=k+k;i++) Q.push(0);
	for(int i=1;i<=n;i++) query(rt,a[i]);
	printf("%lld\n",Q.top());
}

