#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<algorithm>

using namespace std;

struct position{
	long long x;
	long long y;
};
struct path{
	long long a;
	long long b;
	long long cost;
	path(){
		a=0;
		b=0;
		cost=0;
	}
};
struct joint{
	long long parent;
	long long size;
	joint(){
		parent=-1;
		size=1;
	}
};

long long n,maxx;
long long total_c;
vector<long long> cost;
vector<position> pos;
vector<path*> dis;
vector<joint> group;

void cinn(){
	cin>>n;
	total_c=0;
	maxx=0; 
	cost.resize(n);
	pos.resize(n);
	group.resize(n);
	for(long long i=0;i<n;i++){
		long long c;
		cin>>c;
		total_c+=c;
		cost[i]=c;
		group[i].parent=i;
		group[i].size=1;
		maxx=maxx>c?maxx:c;
	}
	for(long long i=0;i<n;i++){
		long long x,y;
		cin>>x>>y;
		pos[i].x=x;
		pos[i].y=y;
	}
	for(long long i=0;i<n;i++){
		for(long long j=0;j<i;j++){
			long long distant = abs(pos[i].x-pos[j].x)+abs(pos[i].y-pos[j].y);
			if(distant<maxx){
				path *p = new path;
				p->a=i;
				p->b=j;
				p->cost=distant;
				dis.push_back(p);
			}			
		}
	}
}
long long find_root(long long b){
	vector<long long> fixed;
	long long now = b;
	while(group[now].parent!=now){
		fixed.push_back(now);
		now = group[now].parent;
	}
	for(long long i=0;i<fixed.size();i++){
		long long node = fixed[i];
		group[node].parent=now;
	}
	return now;
}
void solve(){
	//dis 代表每一條path的集合(sorted) 
	/*
		struct path{
			long long a;
			long long b;
			long long cost;
			path(){
				a=0;
				b=0;
				cost=0;
			}
		};		
	*/
	
	//cost[i] 代表第I個城市建立發電廠的成本 
	
	/* group[i]的結構 
		struct joint{
			long long parent;
			long long size;
			joint(){
				parent=-1;
				size=1;
			}
		};
	*/ 
	path *p;
	
	// 防止RE 
	if(!dis.empty()) p = dis.back();
	// 防止RE 
	
	while(!dis.empty()){
		//find_root(a)是指找a城市集合的root(或稱represent) 
		long long r1 = find_root(p->a);
		long long r2 = find_root(p->b);		
		long long del_n = cost[r1]>cost[r2]?r1:r2;
		if(r1==r2){		
			if(group[r1].size==n+1)break;	
		}else{
			if(cost[del_n]>=p->cost){
				total_c=total_c-cost[del_n]+(p->cost);
				if(group[r1].size>group[r2].size){					
					group[r2].parent=r1;
					group[r1].size=group[r2].size+group[r1].size;					
					cost[r1]=cost[r1]+cost[r2]-cost[del_n];
				}else{					
					group[r1].parent=r2;
					group[r2].size=group[r2].size+group[r1].size;					
					cost[r2]=cost[r1]+cost[r2]-cost[del_n];
				}				
			}			
		}		
		dis.pop_back();
		
		// 防止RE 
		if(!dis.empty()) p = dis.back();
		// 防止RE 
	}
}
bool mycom(path *p1,path *p2){
	if(p1->cost>p2->cost){
		return 1;
	}
	return 0;
}
int main(){
	cinn();
	sort(dis.begin(),dis.end(),mycom);
	solve();
	cout<<total_c<<endl;
}
