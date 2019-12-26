#include<iostream>
#include<vector>
#include<cmath>

using namespace std;
int n,t,a,b;
struct node{
	int idx;
	int rank;
	int val;
	int end;
	vector<node*> son;
	node *father;
	node *top;
	node(){
		idx = 0;
		rank = 0;
		val = 0;
		end = 0;
		father = NULL;
		top = NULL;
		son.clear();
	}
};
struct ctrl_n{
	int dir;
	int chg;
	int zig;
	int idx;
};

node *root,*last_top;
vector<int> visited;
vector<int> parent;
vector<int> path;
vector<int> value;
vector<node*> store;
vector<vector<ctrl_n*> > control;

void print_tree(node *now){
	cout<<now->idx<<" ";
	for(int i=0;i<now->son.size();i++){
		print_tree(now->son[i]);
	}
}
void print_ctrl_n(int pos){
	for(int i=0;i<control[pos].size();i++){
		cout<<"zig:"<<control[pos][i]->zig<<endl;
		cout<<"dir:"<<control[pos][i]->dir<<endl;
		cout<<"chg:"<<control[pos][i]->chg<<endl;
	}
}
void print_top(int pos){
	cout<<store[pos]->top->idx<<endl;
}

void build_t(int now){	
	if(parent[now]!=0){
		visited[now]=1;
		store[now]->father = store[parent[now]];
		store[parent[now]]->son.push_back(store[now]);
		if(visited[parent[now]]==0){
			build_t(parent[now]) ;
		}			
	}else{
		root = store[now];
	}	
}
void store_data(node *now){
	control[now->idx].resize(path.size());
	control[now->idx][path.size()-1] = new ctrl_n;
	control[now->idx][path.size()-1]->dir = 2;
	control[now->idx][path.size()-1]->zig = 1;
	control[now->idx][path.size()-1]->chg = 0; 
	control[now->idx][path.size()-1]->idx = now->idx; 
	for(int i=path.size()-2;i>=0;i--){
		control[now->idx][i] = new ctrl_n;
		if(store[path[i]]->val>store[path[i+1]]->val){
			if(control[now->idx][i+1]->dir==2){
				control[now->idx][i]->dir = 1;
				control[now->idx][i]->zig = control[now->idx][i+1]->zig;
				control[now->idx][i]->chg = 0;
				control[now->idx][i]->idx = path[i];
			}else if(control[now->idx][i+1]->dir==1){
				control[now->idx][i]->dir = 1;
				control[now->idx][i]->zig = control[now->idx][i+1]->zig;
				control[now->idx][i]->chg = 0;
				control[now->idx][i]->idx = path[i];
			}else if(control[now->idx][i+1]->dir==0){
				control[now->idx][i]->dir = 1;
				control[now->idx][i]->zig = control[now->idx][i+1]->zig+1;
				control[now->idx][i]->chg = 0;
				control[now->idx][i+1]->chg = 1;
				control[now->idx][i]->idx = path[i];
			}			
		}else if(store[path[i]]->val<store[path[i+1]]->val){
			if(control[now->idx][i+1]->dir==2){
				control[now->idx][i]->dir = 0;
				control[now->idx][i]->zig = control[now->idx][i+1]->zig;
				control[now->idx][i]->chg = 0;
				control[now->idx][i]->idx = path[i];
			}else if(control[now->idx][i+1]->dir==1){
				control[now->idx][i]->dir = 0;
				control[now->idx][i]->zig = control[now->idx][i+1]->zig+1;
				control[now->idx][i]->chg = 0;
				control[now->idx][i+1]->chg = 1;
				control[now->idx][i]->idx = path[i];
			}else if(control[now->idx][i+1]->dir==0){
				control[now->idx][i]->dir = 0;
				control[now->idx][i]->zig = control[now->idx][i+1]->zig;
				control[now->idx][i]->chg = 0;	
				control[now->idx][i]->idx = path[i];			
			}
		}
	}	
}
void run_tree(node *now){
	path.push_back(now->idx);
	now->rank=path.size(); 
	for(int i=0;i<now->son.size();i++){
		run_tree(now->son[i]);
	}
	if(now->son.size()==0){
		last_top = now;
		now->end=1;
		store_data(now);
	}
	now->top=last_top;
	path.pop_back();
}
void cinn(){
	cin>>n>>t;
	parent.resize(n+1);
	visited.resize(n+1);
	value.resize(n+1);
	store.resize(n+1);
	control.resize(n+1);
	for(int i=1;i<=n;i++){
		int p;
		cin>>p;
		parent[i]=p;
	}
	for(int i=1;i<=n;i++){
		int p;
		cin>>p;
		value[i]=p;
		node *nd = new node;
		nd->val = p;
		nd->idx = i;
		store[i] = nd;
	}
	for(int i=1;i<=n;i++){
		if(visited[i]==0){
			build_t(i);
		}
	}
	run_tree(root);
}

int find_top(){
	int a_top=store[a]->top->idx;
	int b_top=store[b]->top->idx;
	int up = store[a]->rank>store[b]->rank?store[b]->rank-1:store[a]->rank-1;
	int bound = 0;
	while(up!=bound){
		int n_i = (up+bound)/2;
		if(control[a_top][n_i]->idx==control[b_top][n_i]->idx){
			bound = n_i+1;
		}else{
			up = n_i;
		}
	}
	if(control[a_top][up]->idx!=control[b_top][up]->idx)return up-1;
//	cout<<control[a_top][up]->idx<<endl;
	return up;
}
int find_s(){
	int a_top=store[a]->top->idx;
	int b_top=store[b]->top->idx;
	if(store[a]->rank==1){
		int rk1 = store[b]->rank-1;
		if(control[b_top][rk1]->chg==0){
			return control[b_top][0]->zig-control[b_top][rk1]->zig+1;
		}else{
			return control[b_top][0]->zig-control[b_top][rk1]->zig;
		}
	}else if(store[b]->rank==1){
		int rk1 = store[a]->rank-1;
		if(control[a_top][rk1]->chg==0){
			return control[a_top][0]->zig-control[a_top][rk1]->zig+1;
		}else{
			return control[a_top][0]->zig-control[a_top][rk1]->zig;
		}
	}else if(a_top==b_top){
		int pos_top = store[a]->rank>store[b]->rank?a:b;
		int another = store[a]->rank<store[b]->rank?a:b;
		int rk1 = store[pos_top]->rank-1;
		int rk2 = store[another]->rank-1;
		if(control[a_top][rk1]->chg==0){
			return control[a_top][rk2]->zig-control[a_top][rk1]->zig+1;
		}else{
			return control[a_top][rk2]->zig-control[a_top][rk1]->zig;
		}
	}else{
		int p1,p2,jg1,jg2;
		int new_top = find_top();
		if(control[a_top][new_top]->idx==a){
			int rk1 = store[b]->rank-1;
			int rk2 = store[a]->rank-1;
			if(control[b_top][rk1]->chg==0){
				return control[b_top][rk2]->zig-control[b_top][rk1]->zig+1;
			}else{
				return control[b_top][rk2]->zig-control[b_top][rk1]->zig;
			}
		}else if(control[a_top][new_top]->idx==b){
			int rk2 = store[b]->rank-1;
			int rk1 = store[a]->rank-1;
			if(control[a_top][rk1]->chg==0){
				return control[a_top][rk2]->zig-control[a_top][rk1]->zig+1;
			}else{
				return control[a_top][rk2]->zig-control[a_top][rk1]->zig;
			}
		}else{		
			int rk1 = store[a]->rank-1;
			int rk2 = store[b]->rank-1;
			if(control[a_top][rk1]->chg==0){
				p1 = control[a_top][new_top]->zig-control[a_top][rk1]->zig+1;
			}else{
				p1 = control[a_top][new_top]->zig-control[a_top][rk1]->zig;
			}		
			jg1 = control[a_top][new_top]->dir;
			
			if(control[b_top][rk2]->chg==0){
				p2 = control[b_top][new_top]->zig-control[b_top][rk2]->zig+1;
			}else{
				p2 = control[b_top][new_top]->zig-control[b_top][rk2]->zig;
			}		
			jg2 = control[b_top][new_top]->dir;		
			if(jg1==jg2){
				return p1+p2;
			}else{
				return p1+p2-1;
			}
		}
	}
}
void data_in(){
	for(int i=0;i<t;i++){
		cin>>a>>b;
		int ans = find_s();
		cout<<ans<<endl;
	}
}
int main(){
	cinn();
//	cout<<path.size();
//	return 1;
//	print_top(8);
//	print_top(5);
	data_in();
//	print_tree(root);
//	cout<<endl;
//	print_ctrl_n(8);
//	cout<<"-----------------"<<endl;
//	print_ctrl_n(1);
	//data_in();
}
