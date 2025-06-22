# 三种基本博弈
## [巴什博奕（Bash Game）](https://en.wikipedia.org/wiki/BASH!_(role-playing_game))
### &nbsp;&nbsp;&nbsp;&nbsp;简介：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;n个物品，双方每次取x个(1<=x<=k)，最后一个取得物品的人获胜。
### &nbsp;&nbsp;&nbsp;&nbsp;最优策略：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果n%(k+1)=0的时候先手必败
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;否则先手先取 n%(k+1) 随后与对手所取的物品量的和维持(k+1)就可获胜。
## [威佐夫博奕（Wythoff Game）](https://en.wikipedia.org/wiki/Wythoff%27s_game)
### &nbsp;&nbsp;&nbsp;&nbsp;简介：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;有两堆物品。两方轮流从一堆或两堆中拿走物品。在拿物品时有两种方法：其一是从两堆拿走相同量的物品；其二是从其中一堆拿走任意量的物品。<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;最后一个取得物品的人获胜。
### &nbsp;&nbsp;&nbsp;&nbsp;奇异局势：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;称必败状态为奇异局势，前几个奇异局势为：（0，0）,（1，2）,（3，5）,（4，7）,（6，10）,（8，13）,（9，15）,（11，18）,（12，20）。<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;判断奇异局势的公式为：a[k] = (1+√5)/2 * k, b[k] = a[k] + k &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这里（1+√5/2 为黄金分割数 1.61803398874989490253...）。
## [尼姆博奕（Nim Game）](https://en.wikipedia.org/wiki/Nim)
### &nbsp;&nbsp;&nbsp;&nbsp;简介：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;游戏者轮流从几堆石子（或者任何道具）中选择一堆，再从其中取走一个或多个。依规则不同，拿走最后一个的可能是输家，也有可能是赢家。当指定相应数量时，一堆这样的石子称作一个尼姆堆。
### &nbsp;&nbsp;&nbsp;&nbsp;必败判定：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;求出各堆石子数量（x1, x2, x3...）的尼姆和（Nim sum): x1 ^ x2 ^ x3... &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;尼姆和为0则先手必败。
