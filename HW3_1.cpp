#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct node{
	int appear;
	long long level;
	long long parent;
	long long weight;
	node(void){
		parent=-1;
		appear=0;
		level=0;
		weight=0;
	}
};
struct path{
	int des;
	int w;
};
int nt,n,m,s,t;

vector<vector<path*> > store;
vector<node> status;
vector<node> status2;
queue<int> line;
void cinn(){
	cin>>n>>m>>s>>t;
	store.clear();
	status.clear();
	status.resize(n);
	status2.clear();
	status2.resize(n);
	store.resize(n);
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		path *p = new path;
		p->des=v;
		p->w=w;
		store[u].push_back(p);
	}
}
//§äcost>=iªº¸ô®| 
void bfs(){
	while(!line.empty()){	
		int jg=0,gog=0;	
		int now = line.front();
		int length = store[now].size();
		if(jg==1&&gog!=status[now].level){
			break;
		}
		for(int i=0;i<length;i++){
			int des = store[now][i]->des;
			if(store[now][i]->w>=status[now].level){

				if(status[des].appear==0){
					
					if(des==t&&jg==0){
						gog=status[now].level;
						jg=1;
					}
					
					line.push(des);
//					cout<<"push succes"<<endl;
					status[des].appear=1;
					status[des].parent=now;
					status[des].weight=status[now].weight+store[now][i]->w;
					status[des].level=status[now].level+1;
				}else{
					if(status[des].weight>status[now].weight+store[now][i]->w&&status[des].level==status[now].level+1){
						status[des].parent=now;
						status[des].weight=status[now].weight+store[now][i]->w;
					}	
				}
			}else{
//				cout<<"not enouth"<<endl;
			}
		}
		
		line.pop();
	}
	while(!line.empty()){
		line.pop();
	}
	return;
}
//§ä¤@¯ëBFS 
int bfs2(){
	int jg=0;
	while(!line.empty()){
		if(jg==1)break;		
		int now = line.front();
		int length = store[now].size();
		for(int i=0;i<length;i++){
			int des = store[now][i]->des;			
			if(status2[des].appear==0){					
				if(des==t&&jg==0){
					jg=1;
				}				
				line.push(des);
				status2[des].appear=1;
				status2[des].parent=now;
				status2[des].weight=store[now][i]->w;
				status2[des].level=status2[now].level+1;
			}			
		}		
		line.pop();
	}
	while(!line.empty()){
		line.pop();
	}
	return status2[t].level;
}
int main(){
	cin>>nt;
	for(int i=0;i<nt;i++){
		cinn();
		line.push(s);
		status[s].appear=1;
		status[s].level=1;
		status[s].parent=-1;
		status[s].weight=0;
		bfs();
		int n_p=status[t].parent;
		vector<int> ans;
		ans.push_back(t);		
		while(n_p!=-1){
//			cout<<n_p<<endl;
			ans.push_back(n_p);
			n_p=status[n_p].parent;
			if(n_p<0)break;
		}
		
		line.push(s);
		status2[s].appear=1;
		status2[s].level=1;
		status2[s].parent=-1;
		status2[s].weight=0;
		int num = bfs2();
//		cout<<num<<endl;	
		
		if(ans.size()==num){
			if(ans.back()!=s){
				cout<<-1<<endl;
			}else{
				for(int j=ans.size()-1;j>=0;j--){
					cout<<ans[j]<<" ";
				}
				cout<<endl;
			}
		}else{
			cout<<-1<<endl;
		}
		
		
	}
}
