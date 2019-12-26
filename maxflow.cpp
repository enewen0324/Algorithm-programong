#include <iostream>
#include <queue>
#include<string.h>
using namespace std;
#define arraysize 201
int maxData = 0x7fffffff;
int capacity[arraysize][arraysize]; //???留网?的容量
int flow[arraysize];                //???源?到?前?????剩多少流量可用
int pre[arraysize];                 //??在??路?上?前??的前?,同??????是否在?列中
int n,m;
queue<int> myqueue;
int BFS(int src,int des)
{
    int i,j;
    while(!myqueue.empty())       //?列清空
        myqueue.pop();
    for(i=1;i<m+1;++i)
    {
        pre[i]=-1;
    }
    pre[src]=0;
    flow[src]= maxData;
    myqueue.push(src);
    while(!myqueue.empty())
    {
        int index = myqueue.front();
        myqueue.pop();
        if(index == des)            //找到了增?路?
            break;
        for(i=1;i<m+1;++i)
        {
            if(i!=src && capacity[index][i]>0 && pre[i]==-1)
            {
                 pre[i] = index; //??前?
                 flow[i] = min(capacity[index][i],flow[index]);   //??：迭代的找到增量
                 myqueue.push(i);
            }
        }
    }
    if(pre[des]==-1)      //?留?中不再存在增?路?
        return -1;
    else
        return flow[des];
}
int maxFlow(int src,int des)
{
    int increasement= 0;
    int sumflow = 0;
    while((increasement=BFS(src,des))!=-1)
    {
         int k = des;          //利用前??找路?
         while(k!=src)
         {
              int last = pre[k];
              capacity[last][k] -= increasement; //改?正向?的容量
              capacity[k][last] += increasement; //改?反向?的容量
              k = last;
         }
         sumflow += increasement;
    }
    return sumflow;
}
int main()
{
    int i,j;
    int start,end,ci;
    while(cin>>n>>m)
    {
        memset(capacity,0,sizeof(capacity));
        memset(flow,0,sizeof(flow));
        for(i=0;i<n;++i)
        {
            cin>>start>>end>>ci;
            if(start == end)               //考?起???相同的情?
               continue;
            capacity[start][end] +=ci;     //此?注意可能出?多?同一起???的情?
        }
        cout<<maxFlow(1,m)<<endl;
    }
    return 0;
}
