#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define N 500050
#define gc getchar()
inline int gi(){register int x(0);register char c(gc);while(c<'0'||'9'<c)c=gc;while('0'<=c&&c<='9')x=x*10+c-'0',c=gc;return x;}
const int P=1e9;

int a[N]; int n;
int mns[N],mxs[N],mnj[N],mxj[N],mms[N],mmj[N];

int Ans=0;
void ins(int x){ Ans=(Ans+x)%P; }

int eql(int l,int r){ return (l+r)*(r-l+1)/2%P; }

void solve(int l,int r){
	if(l==r){ ins(a[l]*a[l]); return ; }
	int mid((l+r)/2); solve(l,mid),solve(mid+1,r);
	int mn,mx; mn=P,mx=0;
	mns[mid]=mxs[mid]=mnj[mid]=mxj[mid]=mms[mid]=mmj[mid]=0;
	FOR(j,mid+1,r){
		mn=min(mn,a[j]),mx=max(mx,a[j]);
		mns[j]=(mns[j-1]+mn)%P;
		mxs[j]=(mxs[j-1]+mx)%P;
		mnj[j]=(mnj[j-1]+mn*j)%P;
		mxj[j]=(mxj[j-1]+mx*j)%P;
		mms[j]=(mms[j-1]+mn*mx)%P;
		mmj[j]=(mmj[j-1]+mn*mx%P*j)%P;
	}
	mn=P,mx=0; int p,q; p=q=mid+1;
	for(int i=mid;i>=l;i--){
		mn=min(mn,a[i]),mx=max(mx,a[i]);
		while(p<=r&&a[p]>=mn) p++;
		while(q<=r&&a[q]<=mx) q++;
		if(p<q){
			ins(mn*mx%P*eql(mid-i+2,p-i));
			ins(mx*(mnj[q-1]-mnj[p-1]+P)+(1-i+P)*mx%P*(mns[q-1]-mns[p-1]+P));
			ins(mmj[r]-mmj[q-1]+P+(1-i+P)*(mms[r]-mms[q-1]+P));
		}
		else{
			ins(mx*mn%P*eql(mid-i+2,q-i));
			ins(mn*(mxj[p-1]-mxj[q-1]+P)+(1-i+P)*mn%P*(mxs[p-1]-mxs[q-1]+P));
			ins(mmj[r]-mmj[p-1]+P+(1-i+P)*(mms[r]-mms[p-1]+P));
		}
	}
}

signed main()
{
	n=gi(); FOR(i,1,n) a[i]=gi();
	solve(1,n); printf("%lld\n",Ans);
}

