#include<bits/stdc++.h>
#define il inline
#define ls t<<1
#define rs t<<1|1
#define lowbit(x) (x&(-x))
using namespace std;
const int maxn=3e5+5;
struct Segment_tree
{
	int l;int r;
	long long kinds;long long lazy;
}tr[maxn<<2];
struct Edge
{
	int next;int to;
}edge[maxn];
int head[maxn],tim,n,m,col[maxn],pos[maxn],in[maxn],out[maxn],tot;
il void addedge(int from,int to)
{
	edge[++tot].next=head[from];
	edge[tot].to=to;
	head[from]=tot;
}
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
void dfs(int u,int fa)
{
	in[u]=++tim;
	pos[tim]=u;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
	out[u]=tim;
}
il void pushup(int t)
{
	tr[t].kinds=tr[ls].kinds|tr[rs].kinds;
}
il void pushdown(int t)
{
	int mid=tr[t].l+tr[t].r>>1;
	if(tr[t].lazy)
	{
		tr[ls].kinds=tr[t].lazy;
		tr[ls].lazy=tr[t].lazy;
		tr[rs].kinds=tr[t].lazy;
		tr[rs].lazy=tr[t].lazy;
		tr[t].lazy=0;
	}
}
void build(int t,int l,int r)
{
	tr[t].l=l;tr[t].r=r;
	if(l==r)
	{
		tr[t].kinds=1ll<<col[pos[l]];
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(t);
}
void Modify(int t,int ll,int rr,int c)
{
	if(ll<=tr[t].l&&tr[t].r<=rr)
	{
		tr[t].kinds=1ll<<c;
		tr[t].lazy=1ll<<c;
		return;
	}
	pushdown(t);
	int mid=tr[t].l+tr[t].r>>1;
	if(ll<=mid) Modify(ls,ll,rr,c);
	if(rr>mid) Modify(rs,ll,rr,c);
	pushup(t);
}
long long Query(int t,int ll,int rr)
{
	if(ll<=tr[t].l&&tr[t].r<=rr) return tr[t].kinds;
	pushdown(t);
	int mid=tr[t].l+tr[t].r>>1;
	long long res=0;
	if(ll<=mid) res|=Query(ls,ll,rr);
	if(rr>mid) res|=Query(rs,ll,rr);
	return res;
}
int main()
{
	int x,y,opt;
	n=read();m=read();
	for(int i=1;i<=n;i++) col[i]=read();
	for(int i=1;i<=n-1;i++)
	{
		x=read();y=read();
		addedge(x,y);
		addedge(y,x);
	}
	dfs(1,0);
	build(1,1,n);
	while(m--)
	{
		long long ans=0;
		opt=read();
		if(opt==1)
		{
			x=read();y=read();
			Modify(1,in[x],out[x],y);
		}
		if(opt==2)
		{
			x=read();
			long long tmp=Query(1,in[x],out[x]);
			while(tmp)
			{
				ans++;
				tmp-=lowbit(tmp);
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
