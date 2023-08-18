#include<bits/stdc++.h>
#define il inline
#define ls t<<1
#define rs t<<1|1
using namespace std;
const int maxn=1e5+5;
struct Segment_tree
{
	int l;int r;
	int mx;long long sum;
}tr[maxn<<2];
int a[maxn],n,m;
il int read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		num=num*10+ch-'0';
		ch=getchar();
	}
	return num*f;
}
il void pushup(int t)
{
	tr[t].sum=tr[ls].sum+tr[rs].sum;
	tr[t].mx=max(tr[ls].mx,tr[rs].mx);
}
/*il void pushdown(int t)
{
	if(!tr[t].lazy) return;
	tr[ls].sum%=tr[t].lazy;
	tr[ls].lazy=tr[t].lazy;
	tr[rs].sum%=tr[t].lazy;
	tr[rs].lazy=tr[t].lazy;
	tr[t].lazy=0;
}*/
void build(int t,int l,int r)
{
	tr[t].l=l;tr[t].r=r;
	if(l==r)
	{
		tr[t].sum=a[l];
		tr[t].mx=a[l];
		return;
	}
	int mid=tr[t].l+tr[t].r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(t);
}
void Modify_mod(int t,int ll,int rr,int x)
{
	if(tr[t].mx<x) return;
	if(tr[t].l==tr[t].r)
	{
		tr[t].sum%=x;
		tr[t].mx=tr[t].sum;
		return;
	}
	int mid=tr[t].l+tr[t].r>>1;
	if(ll<=mid) Modify_mod(ls,ll,rr,x);
	if(rr>mid) Modify_mod(rs,ll,rr,x);
	pushup(t);
}
void Modify(int t,int k,int x)
{
	if(tr[t].l==tr[t].r) 
	{
		tr[t].sum=x;
		tr[t].mx=x;
		return;
	}
	int mid=tr[t].l+tr[t].r>>1;
	if(k<=mid) Modify(ls,k,x);
	else Modify(rs,k,x);
	pushup(t);
}
long long Query(int t,int ll,int rr)
{
	if(ll<=tr[t].l&&tr[t].r<=rr) return tr[t].sum;
	int mid=tr[t].l+tr[t].r>>1;
	long long res=0;
	if(ll<=mid) res+=Query(ls,ll,rr);
	if(rr>mid) res+=Query(rs,ll,rr);
	return res;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	int opt,ll,rr,k,x;
	while(m--)
	{
		opt=read();
		if(opt==1)
		{
			ll=read();rr=read();
			printf("%lld\n",Query(1,ll,rr));
		}
		if(opt==2)
		{
			ll=read();rr=read();x=read();
			Modify_mod(1,ll,rr,x);
		}
		if(opt==3)
		{
			k=read();x=read();
			Modify(1,k,x);
		}
	}
	return 0;
}
