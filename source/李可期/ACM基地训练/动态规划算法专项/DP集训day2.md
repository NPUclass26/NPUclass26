## DAY2 区间DP

### 合并石子以及四边形不等式优化
石子合并是很经典的区间DP了

经典方程：设$dp[l][r]$为合并区间$l$到$r$的最小代价，那么枚举断点$i$，则有

$dp[l][r]=min(dp[l][i]+dp[i+1][r])+cost[l][r]$

然后，考虑枚举断点时的优化。

设$p[i][j]$表示当区间$[i, j]$取最优决策时所选择的断点，这时可以证明有$p[i][j - 1] <= p[i][j] <= p[i + 1][j]$

每次决策时只需要枚举$[p[i][j - 1],p[i + 1][j]]$之间的断点即可，理论复杂度变为了$o(n^2)$

```cpp
for(int len=2;len<=n;len++)
	for(int l=1,r=len;r<=n;l++,r++) 
	{
    	f[l][r]=inf;
    	for(int k=p[l][r-1];k<=p[l+1][r];k++)
    	if(f[l][r]>f[l][k]+f[k+1][r]+w(l,r)) 
		{
        	f[l][r]=f[l][k]+f[k+1][r]+w(l,r);
        	p[l][r]=k; //更新最优决策点
    	}
	}

```

### 例题1

这道题相当的难

有n个人参加选秀，每个人有一个Di值，Di值*（出场时间-1）决定他们的悲惨度，这i个人按顺序出场，但是在出场前可以通过一个栈略微调整出场顺序，输出调整后的总悲惨度最小值

没有想到出栈顺序是可以和二叉树的后序遍历有关系的，所以我连区间DP的影子都没看出来。

**一个比较重要且难以想到的点：在每段区间$[l,r]$中，最后一个出场的人$i$，就相当于是一个根节点，$[l,i]$相当于它的左子树，$[i+1,r]$相当于它的右子树**

于是我们有了一个区间DP的想法，设$dp[l][r]$表示区间$[l,r]$的最小悲惨程度，考虑枚举中间点$i$，也就是最后一个出场的人，那么就有

$dp[l][r]=min(dp[l][i-1]+dp[i+1][r]+cost(i,l,r))$

其中$cost(i,l,r)$表示的是$i$是区间$[l,r]$最后一个出场时的代价，但是这个$cost$并不好求,因为我们并不清楚这段区间到底是全局第几个出场的

于是增加一维设$dp[l][r][k]$表示区间$[l,r]$出场的第一个人是全局第$k$个人时的最小悲惨程度

枚举$i,k$就有$dp[l][r][k]=min(dp[l][i-1][k]+dp[i+1][r][k+(i-l+1)]+D[i]*(k+(r-l)))$

但是枚举四个量$l,r,i,k$的时间复杂度变成了$O(n^4)$，显然会超时。

**这里就又要考虑一下哪个量是可以提前算出来的了，显然是$k$**

**老师这里是又转化了一下，每个人多等一秒钟，就相当于悲惨程度加D**

**于是考虑每段区间要等待的人数，右边的人要等左边的人，第$i$个人等了其他所有人，**那么依然枚举断点$i$

就有$dp[l][r]=min(dp[l][i-1]+dp[i+1][r]+(i-l)*sum[i+1][r]+D[i]*(r-l))$

**我的想法：若$l$是第$k$个上场,那么$[l+1,k]$肯定是在$l$之前上场的,$[k+1,r]$肯定是在**
**$l$之后上场的。因为$l$在$[l,r]$中是第$k-l+1$个，所以花费为$D[l]*(k-l)$，然后$[k+1,r]$要等$[l,k]$上场，所以花费为$(sum[r]-sum[k])*(k-l+1)$**

那么就有：$dp[l][r]=min(dp[l+1][k]+dp[k+1][r]+d[l]*(k-l)+(sum[r]-sum[k])*(k-l+1)$

也能降到$o(n^3)$耶

该死的HDOJ上不去了，本来想测一下这个题的

讲完这道题之后其实差不多熟悉了区间DP的套路，就是看看能不能从区间中间枚举断点，将区间划分成两个子区间，之后又上OI wiki了解了下四边形不等式

就是形如这种$dp[l][r]=min(dp[l][i]+dp[i+1][r])+cost[l][r]$方程

如果$cost[l][r]$满足四边形不等式的话，那么咱就可以优化咯

之后的题目都还简单，知道是区间DP后基本一眼出

### 例题2

HDU5115(又是HDU上的qwq)

​	一群狼排成一排，每只狼有一个固定攻击值a[i]，还有他左右与它相邻的狼给它的附加值，因此它对人的攻击总值是固定攻击值+附加值，一个人消灭第i只狼的同时会受到它的总攻击值的伤害，问一个人要按什么顺序消灭全部狼，能使获得受到的攻击值最低。$n<=500$

知道是区间DP了真的很好想，要消灭$[l,r]$，那么最后消灭的狼的左右一定是$l-1$和$r+1$

于是设$dp[l][r]$为消灭区间$[l+1,r-1]$的所有狼所收到的最低攻击值。枚举最后一个消灭的狼则有

$dp[l][r]=min(dp[l][k]+dp[k][r]+a[k]+a[l]+a[r])$

### 例题3

一排按钮，每个按钮按下去之后会在Ti秒后弹起来，从1号点出发，问：最少需要多少时间，能让所有按钮都按下去？输出路径。N<=1000

这也是一道我没有看出区间DP影子的题目。~~课堂上问了老师之后才发现是自己题目意思理解错了~~

发现几个非常明显的结论：

1、如果要将一段区间的按钮全部按下，那么必不可能从中间的按钮开始，因为会反复经过一段重复的区间，之前按下的白费。

2、每个按钮只有最后一次被按下才是有用的，操作序列应该是一个个逐渐变小的区间，证明同1，不然会有一段白费的按钮

从上面的推断可以相处于是设$dp[l][r][0/1]$为当前在区间$[l,r]$的左/右端点，将整个区间的按钮全部按下所需的最小时间，由于不可能从中间断开，所以直接得出方程

$dp[l][r][0]=min(dp[l+1][r][0]+dis[l+1]-dis[l],dp[l+1][r][1]+dis[r]-dis[l])$

$dp[l][r][1]=min(dp[l][r-1][1]+dis[r]-dis[r-1],dp[l][r-1][0]+dis[r]-dis[l])$

今天老师讲的还是挺慢的，能跟的上了
