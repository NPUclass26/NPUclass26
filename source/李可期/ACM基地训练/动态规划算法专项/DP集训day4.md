# day4 数位DP

没有什么数位DP的基础，写过的题也少，基本属于是我的知识盲区了。



### 大致思路

基本上就是按位划分阶段考虑DP，看具体题目决定具体怎么转移。

### T1 火柴棒等式

题意就是用火柴棒摆一个加号等式，问能摆出不同等式的方案数

设$dp[i][sum][ex][o1][o2]$ 为考虑了从低到高的$i$位，一共用了$sum$根火柴，当前是否有进位，以及上下两位是否截止

```cpp
void DP()
{
	dp[0][0][0][0][0]=1;
	for(int i=0;i<=n/4;i++)	
		for(int sum=0;sum<=n;sum++)
			for(int ex=0;ex<=1;ex++)
				for(int o1=0;o1<=1;o1++)
					for(int o2=0;o2<=1;o2++)
					{
						if(dp[i][sum][ex][o1][o2])
						{
							int now=dp[i][sum][ex][o1][o2];
							if(ex==0 && o1==1 && o2==1) continue;
							for(int shang=0;shang<=9;shang++)
								if(o1==0 || shang==0)
									for(int xia=0;xia<=9;xia++)
									{
										if(o2==0||xia==0)
										{
											int ni,nex,no1,no2,nsum;
											ni=i+1;nex=(shang+xia+ex)/10;
											nsum=sum+s[shang]*(1-o1)+s[xia]*(1-o2)+s[(shang+xia+ex)%10];
											//两个数同时截止 
											if((o1 || shang)&&(o2||xia)) dp[ni][nsum][nex][1][1]+=now;
                                            //上面截止，下面不截止
											if((o1||shang)&&o2==0) dp[ni][nsum][nex][1][0]+=now;
                                            //下面截止，上面不截止
                                            if((o1==0)&&(o2||xia) dp[ni][nsum][nex][0][1]+=now;
                                            //都不截止
                                            if((o1==0)&&(o2==0)) dp[ni][nsum][nex][0][0]+=now;
										}
									}
						}
					}
}
```

将每个状态对应的新状态都开一个变量保存，更不容易出错

### T2

你有一组非零数字（不一定唯一），你可以在其中插入任意个 0，这样就可以产生无限个数。比如说给定 {1,2}{1,2}，那么可以生成数字 12，21，102，120，201，210，1002，1020 等等。

现在给定一个数，问在这个数之前有多少个数（注意这个数不会有前导 0）。

乍一看觉得是一个~~我不会~~的可重复元素的康拓展开

额，用数位DP的看法的话，我们需要从高位到低位去填数，直到填出了给定的数为止，写成代码也很简单，只需要开一个数组记录某个数字还有多少次没填即可

代码如下

```
void dfs(int wei)
{
	if(!wei) return;//递归边界,将每一位都枚举完了
	for(int j=0;j<=s[wei];j++)
	if(num[j]>0)
	{
		num[j]--;
		add(ans,cal());//如果算出的数小于给定的数答案++
		num[j]++;//回溯
	}
	//开始填下一位的数
	num[s[wei]]--;
	dfs(wei-1);
}
```

### T3

windy数

设$dp[i][j]$为考虑了从高到低的前$i$位，且结尾数字是$j$的$windy$数的个数

先预处理这些，然后把对应的加起来就可以，渐渐理解了老师一开始说的，与其说是DP，不如说是一类计数问题

```cpp
void init()
{
    memset(dp,0,sizeof(dp));
    for(int i=0;i<10;i++) dp[1][i]=1;
    for(int i=2;i<=10;i++)
        for(int j=0;j<10;j++)
        	for(int k=0;k<10;k++)
            	if(abs(j-k)>=2) dp[i][j]+=dp[i-1][k];
} 
int slove(int x)
{
    int len=0;
    while (x)
    {
        w[++len]=x%10;
        x/=10;
    }
    w[len+1]=0;
    int ans=0;
    for(int i=1;i<len;i++)
     	for(int j=1;j<10;j++) 
		 	ans+=dp[i][j];
    for(int i=1;i<w[len];i++) ans+=dp[len][i];
    for(int i=len-1;i;i--)
    {
        for(int j=0;j<w[i];j++)
            if(abs(w[i+1]-j)>=2) ans+=dp[i][j];
        if(abs(w[i+1]-w[i])<2) break;
     }
     return ans;
}
```



### T4

给出两个数a,b，求出[a,b][a,b]中各位数字之和能整除原数的数的个数。

题目问的是各位数字之和，最大的longlong也才18位，最多也就有180种数字之和

可以考虑这个数位的和对给定的数的取模

于是设$dp[i][s][m]$为考虑前$i$位，各位的和为$s$，对c取模的值为m的方案数

逆推的话,枚举$k$，就有

$dp[i+1][s+k][(m*10+k)modsum]=\sum dp[i][s][m]$

实际枚举每一位的时候要注意有没有超过上界，要增加一维判断

### T5

Volodya 认为一个数字 x 是美丽的，当且仅当 x∈Z+ 并且对于 x 的每一个非零位上的数 y，都有 y∣x。

你需要帮助他算出在区间 $[l,r]$ 中有多少个数是美丽的。

以前别人给我讲过这道题，当时没听懂，写了一些数位DP之后发现这是一道挺套路的题

记录$dp[i][yu][lcm][0/1]$表示当前第$i$位，yu表示当前状态的%2520的余数,lcm表示当前$0-9$各个数字的选取情况

但是我DP写挂了。。。看题解调了半天也不懂哪里错了，代码就不放了



以前没有怎么系统地接触过数位DP，现在也就是个打板子高手。。。