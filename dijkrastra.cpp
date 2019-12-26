const int  MAXINT = 32767;
const int MAXNUM = 10;
int dist[MAXNUM];
int prev[MAXNUM];

int A[MAXUNM][MAXNUM];

void Dijkstra(int v0)
{
  　　bool S[MAXNUM];                                  // 判?是否已存入??到S集合中
      int n=MAXNUM;
  　　for(int i=1; i<=n; ++i)
 　　 {
      　　dist[i] = A[v0][i];
      　　S[i] = false;                                // 初始都未用???
      　　if(dist[i] == MAXINT)    
            　　prev[i] = -1;
 　　     else 
            　　prev[i] = v0;
   　　}
   　 dist[v0] = 0;
   　 S[v0] = true; 　　
 　　 for(int i=2; i<=n; i++)
 　　 {
       　　int mindist = MAXINT;
       　　int u = v0; 　　                            // 找出?前未使用的?j的dist[j]最小值
      　　 for(int j=1; j<=n; ++j)
      　　    if((!S[j]) && dist[j]<mindist)
      　　    {
         　　       u = j;                             // u保存?前?接?中距离最小的?的?? 
         　 　      mindist = dist[j];
       　　   }
       　　S[u] = true; 
       　　for(int j=1; j<=n; j++)
       　　    if((!S[j]) && A[u][j]<MAXINT)
       　　    {
           　    　if(dist[u] + A[u][j] < dist[j])     //在通?新加入的u?路?找到离v0?更短的路?  
           　    　{
                   　　dist[j] = dist[u] + A[u][j];    //更新dist 
                   　　prev[j] = u;                    //??前??? 
            　　    }
        　    　}
   　　}
}
