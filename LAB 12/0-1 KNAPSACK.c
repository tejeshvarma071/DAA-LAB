#include <stdio.h>

int max(int a, int b) {
return (a &gt; b) ? a : b;
}

int main() {
int n, W;
printf(&quot;Enter number of items: &quot;);
scanf(&quot;%d&quot;, &amp;n);

int wt[n], val[n];
printf(&quot;Enter weights of items: &quot;);
for(int i = 0; i &lt; n; i++)
scanf(&quot;%d&quot;, &amp;wt[i]);

printf(&quot;Enter values of items: &quot;);
for(int i = 0; i &lt; n; i++)
scanf(&quot;%d&quot;, &amp;val[i]);

printf(&quot;Enter knapsack capacity: &quot;);
scanf(&quot;%d&quot;, &amp;W);

int dp[n+1][W+1];
for(int i = 0; i &lt;= n; i++) {
for(int w = 0; w &lt;= W; w++) {
if(i == 0 || w == 0)
dp[i][w] = 0;
else if(wt[i-1] &lt;= w)
dp[i][w] = max(val[i-1] + dp[i-1][w - wt[i-1]], dp[i-1][w]);
else
dp[i][w] = dp[i-1][w];
}
}
printf(&quot;Maximum value that can be obtained = %d\n&quot;, dp[n][W]);
return 0;
}
