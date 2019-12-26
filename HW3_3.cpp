#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<queue>
using namespace std;
int store[102][102];
int store2[102][102];
int des_p[51][26];
int n,m;
void cinn(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		store[0][i]=1;
		for(int j=1;j<=m;j++){
			string s;
			cin>>s;
			int des=0;
			int val;
			for(int k=0;k<s.size();k++){
				if(s[k]>='0'&&s[k]<='9'){
					des = des*10 + s[k]-'0';
				}else{
					val= s[k]-'A'; 
				}
			}			
			store[i][n+des]=1;
			store[n+des][2*n+1]=1;	
			des_p[des][val]=i;
		}		
	}
}
void printg(){
	for(int i=0;i<=2*n+1;i++){
    	for(int j=0;j<=2*n+1;j++){
    		cout<<store[i][j]<<" ";
		}
		cout<<endl;
	}

}
void print_des(){
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			cout<<des_p[i][j]<<" ";
		}
		cout<<endl;
	}
}
vector<int> pre;
vector<int> flow;
queue<int> line;

int bfs(int src,int des){
	while(!line.empty()){
        line.pop();
    }
    for(int i=0;i<=2*n+1;i++){
        pre[i]=-1;
    }
    pre[src]=0;
    flow[src]=10000;
    line.push(src);
    while(!line.empty()){
        int now = line.front();
//       cout<<"now:"<<now<<endl;
        line.pop();
        if(now == des)break;
        if(now==0){
        	for(int i=1;i<=n;i++){
                if(i!=src && store2[now][i]>0&&pre[i]==-1){
                    pre[i]=now;
                    flow[i] = min(store2[now][i],flow[now]);
                    line.push(i);
                }
            }
		}else if(now<=n){
            for(int i=n+1;i<=2*n;i++){
                if(i!=src && store2[now][i]>0&&pre[i]==-1){
                    pre[i]=now;
                    flow[i] = min(store2[now][i],flow[now]);
                    line.push(i);
                }
            }
        }else{
            for(int i=1;i<=n;i++){
                if(i!=src && store2[now][i]>0&&pre[i]==-1){
                    pre[i]=now;
                    flow[i] = min(store2[now][i],flow[now]);
                    line.push(i);
                }
            }
            if(store2[now][2*n+1]>0&&pre[2*n+1]==-1){
                pre[2*n+1]=now;
                flow[2*n+1] = min(store2[now][2*n+1],flow[now]);
                line.push(2*n+1);
            }
        }        
    }
    if(pre[des]==-1)return -1;
    return flow[des];
}
int maxflow(int src,int des){
	int change=0;
    int sum=0;
    while((change=bfs(src,des)!=-1)){
 //   	int stop;
 //   	cin>>stop;
        int fin = des;
        while(fin!=src){
            int pre_n = pre[fin];
            store2[pre_n][fin] = 0;
            store2[fin][pre_n] = 1;
            fin = pre_n; 
        }
        sum+=change;
    }
    return sum;
}
bool find_maxflow(int src,int num,int alpha){
	vector<int> mem;	
	int now = des_p[src][alpha];
//	cout<<src<<" "<<num<<" "<<alpha<<" "<<now<<endl;
	for(int i=n+1;i<=2*n;i++){
		if(i!=num&&store[now][i]==1){
			store[now][i]=0;
			mem.push_back(i);
		}
	}
	for(int i=0;i<=2*n+1;i++){
		for(int j=0;j<=2*n+1;j++){
			store2[i][j]=store[i][j];
		}
	}
	int check = maxflow(0,2*n+1);
	if(check==n){
		return 1;
	}else{
		for(int i=0;i<mem.size();i++){
			store[now][mem[i]]=1;
		}
//		printg();
//		int t;
//		cin>>t;
		return 0;
	}	
}
void solve(){
    pre.resize(2*n+2);
    flow.resize(2*n+2);
	int now = 1;
	while(now<=n){
		int alpha=0;
		while(!find_maxflow(now,now+n,alpha)){
			while(des_p[now][alpha]==des_p[now][alpha+1]){
				alpha++;
			}
			alpha++;
		}
        char c = 'A'+alpha;
        cout<<now<<c<<" ";
		now++;
	}
    cout<<endl;
}
int main(){
    cinn();
	solve();    
}
