#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;} 
typedef long long ll;

const int N=100010,D=24;
int rt[N],ls[N*D],rs[N*D],sum[N*D];
int n,a[N],b[N],num=0; int cnt=0;

void build(int &o,int l,int r){
	o=++cnt; if(l==r) return ;
	int mid(l+r>>1); build(ls[o],l,mid),build(rs[o],mid+1,r);
}

void modify(int X,int p,int &o,int l,int r){
	o=++cnt;
	ls[o]=ls[p],rs[o]=rs[p],sum[o]=sum[p]+1;
	if(l==r) return ;  int mid(l+r>>1);
	if(X<=mid) modify(X,ls[p],ls[o],l,mid);
	else modify(X,rs[p],rs[o],mid+1,r); 
}

int query(int o1,int o2,int l,int r,int val){
	if(l==r) return sum[o2]-sum[o1];  int mid(l+r>>1);
	if(val<=mid) return query(ls[o1],ls[o2],l,mid,val);
	else return sum[ls[o2]]-sum[ls[o1]]+query(rs[o1],rs[o2],mid+1,r,val);
}


int mx[N][D],g[N][D]; int lg[N];
void get_st(){
	for(int i=1;(1<<i)<=n;i++) lg[1<<i]=i;
	FOR(i,1,n) if(!lg[i]) lg[i]=lg[i-1];
	
	FOR(i,1,n) mx[i][0]=a[i],g[i][0]=i;
	for(int l=1;(1<<l)<=n;l++){
		for(int i=1;i+(1<<l)-1<=n;i++){
			int rx=i+(1<<(l-1));
			if(mx[i][l-1]>mx[rx][l-1])  mx[i][l]=mx[i][l-1],g[i][l]=g[i][l-1];
			else  mx[i][l]=mx[rx][l-1],g[i][l]=g[rx][l-1];
		}
	}
}

int gmx(int l,int r){
	int t=lg[r-l+1]; int rx=r-(1<<t)+1;
	return mx[l][t]>mx[rx][t]?g[l][t]:g[rx][t]; 
} 

ll Ans=0;
void solve(int l,int r){
	if(l>r) return ;
	int p=gmx(l,r);
	int mid(l+r>>1);
	if(p<=mid){
		FOR(i,l,p){
			int k=upper_bound(b+1,b+num+1,a[p]/a[i])-b-1;
			if(k>0) Ans+=query(rt[p-1],rt[r],1,num,k);
		}
	}
	else{
		FOR(i,p,r){
			int k=upper_bound(b+1,b+num+1,a[p]/a[i])-b-1;
			if(k>0) Ans+=query(rt[l-1],rt[p],1,num,k);
		}
	}
	solve(l,p-1),solve(p+1,r);
}

int main()
{
	n=gi(); FOR(i,1,n) a[i]=gi(),b[i]=a[i];
	sort(b+1,b+n+1); num=unique(b+1,b+1+n)-b-1;
	build(rt[0],1,num); 
	FOR(i,1,n){
		int t=lower_bound(b+1,b+num+1,a[i])-b;
		modify(t,rt[i-1],rt[i],1,num);
	}
	get_st();
	solve(1,n);
	printf("%lld\n",Ans);
}
