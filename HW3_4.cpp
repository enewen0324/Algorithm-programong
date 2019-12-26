#include<vector>
#include<iostream>
#include<map>
#include<set>
#include<cmath>
using namespace std;
struct mode{	
    int distant;
    int visit_mon;
    int position;    
};
struct pos{
    int x;
    int y;
};
int n;
vector<pos> node_pos;
vector<vector<int> > node_dis;
vector<int> pokemon;
map<string,int> pokemon_apr;
int pokemon_num;
void stop(){
    int stop;
    cin>>stop;
}
void printg(){
	for(int i=0;i<node_dis.size();i++){
		for(int j=0;j<node_dis[i].size();j++){
			cout<<node_dis[i][j]<<" ";
		}
		cout<<endl;
	}
}
bool operator<(mode m1,mode m2){
    if(m1.distant==m2.distant){
        if(m1.visit_mon==m2.visit_mon){
            return m1.position<m2.position;
        }
        return m1.visit_mon<m2.visit_mon;
    }
    return m1.distant<m2.distant;
}
void cinn(){
    cin>>n;
    pokemon.resize(n+1);
    node_pos.resize(n+1);
    pokemon_num =1 ;
    for(int i=0;i<n;i++){
        int x,y;
        string p;
        cin>>x>>y>>p;
        node_pos[i].x=x;
        node_pos[i].y=y;
        if(pokemon_apr.count(p)==0){
            pokemon_apr.insert(pair<string,int>(p,pokemon_num));//每一位元代表一種寶可夢
            pokemon_num*=2;
//            cout<<pokemon_num<<endl;
        }
        pokemon[i]=pokemon_apr.find(p)->second;
//        cout<<"pokemon[i]:"<<pokemon[i]<<endl;
    }
    node_pos[n].x=0;
    node_pos[n].y=0;
    pokemon[n]=0;//訓練家
}
void cal_dis(){
    node_dis.resize(n+1);
    for(int i=0;i<n+1;i++){
        node_dis[i].resize(n+1);
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            node_dis[i][j]=abs(node_pos[i].x-node_pos[j].x)+abs(node_pos[i].y-node_pos[j].y);
        }
    }
//    printg();
}
void find_path(){
    vector<vector<int> > dp;
    dp.resize(pokemon_num);
    for(int i=0;i<dp.size();i++){
        dp[i].resize(n+1);
        for(int j=0;j<=n;j++){
            dp[i][j]=2000000000;
        }
    }
    dp[0][n]=0;//從沒有寶可夢、訓練家位置開始dp
    set<mode> priority_queue;
    priority_queue.insert({0,0,n});
    while(!priority_queue.empty()){
        int now_node = priority_queue.begin()->position;
        int now_catch = priority_queue.begin()->visit_mon;
        priority_queue.erase(priority_queue.begin());
//        cout<<"now node:"<<now_node<<endl;
//        cout<<"now subset:"<<now_catch<<endl;
        for(int i=0;i<n+1;i++){
            int next_node = i;
            int going_to_catch = now_catch | pokemon[i];//若抓過則維持原樣、沒有則新增
            int path = node_dis[now_node][next_node];
//            cout<<"pokemon[i]:"<<pokemon[i]<<endl;
//            cout<<"next node:"<<next_node<<endl;
//            cout<<"next subset:"<<going_to_catch<<endl;
            if(dp[going_to_catch][next_node]>dp[now_catch][now_node]+path){
                priority_queue.erase( {dp[going_to_catch][next_node],going_to_catch,next_node});
                dp[going_to_catch][next_node]=dp[now_catch][now_node]+path;
                priority_queue.insert({dp[going_to_catch][next_node],going_to_catch,next_node});
            }
 //           cout<<"dist[nexts][nextn]:"<<dp[going_to_catch][next_node]<<endl;
// 			  stop();
        }        
    }
    cout<<dp[pokemon_num-1][n];
}
int main(){
    cinn();
    cal_dis();
    find_path();
}
