#include<bits/stdc++.h>
#define il inline
#define ls t<<1
#define rs t<<1|1
using namespace std;
const int maxn=1e5+5;
struct Segment_tree
{
	int l;int r;bool lazy;
	long long cnt;
}tr[maxn<<2][22];
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
	for(int i=0;i<=20;i++) tr[t][i].cnt=tr[ls][i].cnt+tr[rs][i].cnt;
}
il void pushdown(int t)
{
	int l=tr[t][0].l,r=tr[t][0].r;
	int mid=l+r>>1;
	for(int i=0;i<=20;i++)
	{
		if(tr[t][i].lazy)
		{
			tr[ls][i].cnt=(mid-l+1)-tr[ls][i].cnt;
			tr[ls][i].lazy^=1;
			tr[rs][i].cnt=(r-mid)-tr[rs][i].cnt;
			tr[rs][i].lazy^=1;
			tr[t][i].lazy=0;
		}
	}
}
void build(int t,int l,int r)
{
	for(int i=0;i<=20;i++) tr[t][i].l=l,tr[t][i].r=r;
	if(l==r)
	{
		for(int i=0;i<=20;i++) tr[t][i].cnt=(a[l]>>i)&1;
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(t);
}
void Modify(int t,int ll,int rr,int x)
{
	if(ll<=tr[t][0].l&&tr[t][0].r<=rr)
	{
		for(int i=0;i<=20;i++)
			if((x>>i)&1)
			{
				tr[t][i].cnt=(tr[t][0].r-tr[t][0].l+1)-tr[t][i].cnt;
				tr[t][i].lazy^=1;
			}
		return;
	}
	int mid=tr[t][0].l+tr[t][0].r>>1;
	pushdown(t);
	if(ll<=mid) Modify(ls,ll,rr,x);
	if(rr>mid) Modify(rs,ll,rr,x);
	pushup(t);
}
long long Query(int t,int ll,int rr)
{
	if(ll<=tr[t][0].l&&tr[t][0].r<=rr)
	{
		long long res=0;
		for(int i=0;i<=20;i++) res+=tr[t][i].cnt<<i;
		return res;
	}
	pushdown(t);
	int mid=tr[t][0].l+tr[t][0].r>>1;
	long long res=0;
	if(ll<=mid) res+=Query(ls,ll,rr);
	if(rr>mid) res+=Query(rs,ll,rr);
	return res;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	m=read();
	int opt,ll,rr,x;
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
			Modify(1,ll,rr,x);
		}
	}
	return 0;
}
