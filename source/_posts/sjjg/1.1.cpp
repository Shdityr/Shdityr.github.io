#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}

const int N=500050;
struct poi{ int d[2],v; }a[N];
int D; bool operator < (poi a,poi b){ return a.d[D]<b.d[D]; }
struct node{
	int mn[2],mx[2],ch[2]; int sum; poi a;
}t[N]; int rt=0,cnt=0;

int n;

#define ls t[o].ch[0]
#define rs t[o].ch[1]
void upd(int o,int ch){
	t[o].mn[0]=min(t[o].mn[0],t[ch].mn[0]);
	t[o].mn[1]=min(t[o].mn[1],t[ch].mn[1]);
	t[o].mx[0]=max(t[o].mx[0],t[ch].mx[0]);
	t[o].mx[1]=max(t[o].mx[1],t[ch].mx[1]);
}
void pushup(int o){
	t[o].mn[0]=t[o].mx[0]=t[o].a.d[0];
	t[o].mn[1]=t[o].mx[1]=t[o].a.d[1];
	t[o].sum=t[ls].sum+t[rs].sum+t[o].a.v;
	if(ls) upd(o,ls); if(rs) upd(o,rs);
}
int build(int l,int r,int ty){
	int o(l+r>>1); 
	D=ty; nth_element(&a[l],&a[o],&a[r+1]);
	t[o].a=a[o];
	if(l<o) ls=build(l,o-1,ty^1); else ls=0;
	if(r>o) rs=build(o+1,r,ty^1); else rs=0;
	pushup(o); return o;
}
void insert(int &o,int ty,poi a){
	if(!o) { o=cnt; t[o].a=a; return  pushup(o);}
	if(t[o].a.d[ty]<a.d[ty]) insert(rs,ty^1,a);
	else insert(ls,ty^1,a);
	pushup(o);
}

int check(node s,int l1,int l2,int r1,int r2){
	if(l1<=s.mn[0]&&s.mx[0]<=l2&&r1<=s.mn[1]&&s.mx[1]<=r2) return 1;
	if(l2<s.mn[0]||l1>s.mx[0]) return 0;
	if(r2<s.mn[1]||r1>s.mx[1]) return 0;
	return 2;
}

int query(int o,int l1,int l2,int r1,int r2){
	int ret(0);
	if(l1<=t[o].a.d[0]&&t[o].a.d[0]<=l2&&r1<=t[o].a.d[1]&&t[o].a.d[1]<=r2)
		ret+=t[o].a.v;
	if(ls){
		int d=check(t[ls],l1,l2,r1,r2);
		if(d==1)ret+=t[ls].sum;
		else if(d==2) ret+=query(ls,l1,l2,r1,r2);
	} 
	if(rs){
		int d=check(t[rs],l1,l2,r1,r2);
		if(d==1)ret+=t[rs].sum;
		else if(d==2) ret+=query(rs,l1,l2,r1,r2);
	} 
	return ret;
}

int lans=0;
int main()
{
//	freopen("1.in","r",stdin);
	n=gi(); int top=0;
	while(1){
		int opt=gi(); if(opt==3) break ;
		if(opt==1){
			int x=gi()^lans,y=gi()^lans,A=gi()^lans;
//			printf("%d %d %d\n",x,y,A);
			a[++cnt]=(poi){x,y,A};
			if(cnt%10000==0) rt=build(1,cnt,0);
			else insert(rt,0,a[cnt]);
		}
		else{
			int l1=gi()^lans,r1=gi()^lans,l2=gi()^lans,r2=gi()^lans;
//			printf("%d %d %d %d\n",l1,r1,l2,r2);
			lans=query(rt,l1,l2,r1,r2); printf("%d\n",lans);
		}
	} 
}

