#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while((c<'0'||'9'<c)&&c!='-')c=gc;int f(1);if(c=='-')c=gc,f=-1;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x*f;}

const int N=1000050;
struct poi{int d[2];}a[N]; int Num=0;
int D; bool operator < (poi a,poi b){return a.d[D]<b.d[D];}
struct node{
	int mn[2],mx[2],ch[2]; poi a; int siz;
}t[N]; int rt=0,cnt=0,tot=0;

int m; int stk[N]; int top=0;

#define ls t[o].ch[0]
#define rs t[o].ch[1]

const float alpha=0.75;
int Newnode(){
	if(!top) return ++tot;
	return stk[top--];
}

void update(int o,int ch){
	t[o].mn[0]=min(t[o].mn[0],t[ch].mn[0]); 
	t[o].mn[1]=min(t[o].mn[1],t[ch].mn[1]);
	t[o].mx[0]=max(t[o].mx[0],t[ch].mx[0]); 
	t[o].mx[1]=max(t[o].mx[1],t[ch].mx[1]);
	
}
void pushup(int o){
	t[o].mn[0]=t[o].mx[0]=t[o].a.d[0]; t[o].mn[1]=t[o].mx[1]=t[o].a.d[1];
	t[o].siz=t[ls].siz+t[rs].siz+1;
	if(ls) update(o,ls); if(rs) update(o,rs);
}

int build(int l,int r,int ty){
	int mid(l+r>>1); 
	D=ty; nth_element(&a[l],&a[mid],&a[r+1]);
	int o=Newnode(); t[o].a=a[mid];
	if(l<mid) ls=build(l,mid-1,ty^1); else ls=0;
	if(r>mid) rs=build(mid+1,r,ty^1); else rs=0;
	pushup(o); return o;
}

void del(int o){
	if(ls) del(ls);
	a[++Num]=(poi){t[o].a.d[0],t[o].a.d[1]}; stk[++top]=o;
	if(rs) del(rs);
}
void check(int &o,int ty){
	if(t[o].siz*alpha<t[ls].siz||t[o].siz*alpha<t[rs].siz)
		Num=0,del(o),o=build(1,Num,ty);
}
void insert(int &o,int ty,poi a){
	if(!o){ o=Newnode(); t[o].a=a; return pushup(o); }
	if(a.d[ty]>t[o].a.d[ty]) insert(rs,ty^1,a);
	else insert(ls,ty^1,a);
	pushup(o); check(o,ty);
}

int Ans=0;
int dist(int o,int x,int y){
	return max(t[o].mn[0]-x,0)+max(x-t[o].mx[0],0)+max(t[o].mn[1]-y,0)+max(y-t[o].mx[1],0);
}
void query(int o,int x,int y){
	int tmp=abs(t[o].a.d[0]-x)+abs(t[o].a.d[1]-y),d[2];
	d[0]=ls?dist(ls,x,y):2e9;
	d[1]=rs?dist(rs,x,y):2e9;
	
	Ans=min(Ans,tmp); int k=d[0]>d[1];
	if(d[k]<Ans) query(t[o].ch[k],x,y);
	if(d[k^1]<Ans) query(t[o].ch[k^1],x,y);
}

int main()
{
	Num=gi(),m=gi();
	FOR(i,1,Num) a[i].d[0]=gi(),a[i].d[1]=gi();
	rt=build(1,Num,0); tot=Num,Num=0;
	while(m--){
		int opt=gi(),x=gi(),y=gi();
		if(opt==1){
			insert(rt,0,(poi){x,y});
		}
		else{
			Ans=2e9; query(rt,x,y);
			printf("%d\n",Ans);
		}
	}
}

