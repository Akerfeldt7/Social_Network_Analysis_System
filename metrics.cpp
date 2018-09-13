#include <iostream>
#include <cstring>
#include <fstream>
#include "headers/metrics.hpp"

using namespace std;

void degreeDistribution(graph *network){
	int *degrees,*old;
	int curr_degree,max_degree=0,i;
	degrees=new int[max_degree+1];
	for(i=0;i<=max_degree;i++){
		degrees[i]=0;
	}
	network->deg_reset();
	while((curr_degree=network->next_node_degree())>=0){
		if(curr_degree>max_degree){
			old=degrees;
			degrees=new int[curr_degree+1];
			memcpy(degrees,old,(max_degree+1)*sizeof(int));
			delete [] old;
			old=NULL;
			for(i=max_degree+1;i<curr_degree;i++){
				degrees[i]=0;
			}
			degrees[i]=1;
			max_degree=curr_degree;
		}
		else{
			degrees[curr_degree]++;
		}
	}
	ofstream outfile;
	double p;
	int n;
	n=network->nodes_count();
	outfile.open("plot.dat");
	for(i=0;i<=max_degree;i++){
		p=(1.0)*degrees[i]/n;
		cout<<"degree "<<i<<": "<<degrees[i];
		outfile<<i<<" "<<p<<endl;
		if(degrees[i]==1){
			cout<<" node"<<endl;
		}
		else{
			cout<<" nodes"<<endl;
		}
	}
	outfile.close();
	delete [] degrees;
}



int diameter(graph *network){
	int node_id,path,longest_path;
	network->deg_reset();
	longest_path=0;
	while((node_id=network->next_node_id())>=0){
		path=network->longest_path(node_id);
		if(path>longest_path){
			longest_path=path;
		}
	}
	return longest_path;
}


double average_path(graph *network){
	int id;
	long psum,paths;
	double result;
	result_set *res;
	Pair current;
	psum=0;
	paths=0;
	network->deg_reset();
	while((id=network->next_node_id())>=0){
		res=network->reach_all_nodes(id);
		while(res->next()){
			current=res->get_result();
			psum=psum+current.distance;
			paths++;
		}
		delete res;
	}
	result=((double)psum)/paths;
	return result;
}



int numberOfCCs(graph *g){
	int id,size,CCs;
	node_list *tested;
	node *nd;
	tested=NULL;
	CCs=0;
	g->deg_reset();
	while((id=g->next_node_id())>=0){
		if((tested!=NULL)&&(tested->contains(id)>=0)){
			continue;
		}
		else{
			nd=g->lookupnode(id);
			if(!nd->get_type().compare("person") || !nd->get_type().compare("supernode")||!nd->get_type().compare("node")){
				tested=g->reach_all_nodes(id,&size,tested);
				CCs++;
			}
		}
	}
	delete tested;
	return CCs;
}

int maxCC(graph *g){
	int id,size,max_size;
	node_list *tested;
	node *nd;
	tested=NULL;
	max_size=0;
	g->deg_reset();
	while((id=g->next_node_id())>=0){
		if((tested!=NULL)&&(tested->contains(id)>=0)){
			continue;
		}
		else{
			nd=g->lookupnode(id);
			if(!nd->get_type().compare("person") ||!nd->get_type().compare("supernode") ||!nd->get_type().compare("node")){
				tested=g->reach_all_nodes(id,&size,tested);
				if(size>max_size){
					max_size=size;
				}
			}
		}
	}
	delete tested;
	return max_size;
}

double density(graph *network){
	int n_edges,n_nodes;
	int ar,par;
	double dens;
	n_nodes=network->nodes_count();
	n_edges=network->edges_count();
	ar=n_edges;
	par=n_nodes*(n_nodes-1);
	dens=(2.0*ar)/(1.0*par);
	return dens;
}

double closenessCentrality(node* n, graph* g){
	int n_id,id;
	double cc;
	result_set *rset;
	Pair current;
	n_id=n->get_id();
	cc=0.0;
	rset=g->reach_all_nodes(n_id);
	while(rset->next()){
		current=rset->get_result();
		cc=cc+1.0/current.distance;
	}
	cc=cc/(g->nodes_count()-1);
	delete rset;
	return cc;
}


double betweennessCentrality(node *c, graph *g){
	int st_n,st,start,mid,end,i,checked,nodes;
	double cc;
	mid=c->get_id();
	cc=0.0;
	checked=0;
	nodes=g->nodes_count()-1;
	while(checked<nodes){
		g->deg_reset();
		for(i=0;i<=checked;i++){
			start=g->next_node_id();
		}
		checked++;
		if(start==mid){
			start=g->next_node_id();
			checked++;
		}
		while((end=g->next_node_id())>=0){
			if(end==mid){
				continue;
			}
			st_n=g->reach_node_through(start,mid,end,&st);
			//cout<<mid<<" contained in "<<st_n<<" out of "<<st<<" paths from "<<start<<" to "<<end<<endl;
			if(st_n>0){
				cc=((double)st_n)/st+cc;
			}
		}
	}
	cc=cc/((nodes*(nodes-1))/2);
	return cc;
}

////////////////////////////////////////////////////////////
////////////meros 3///////////////////////////

double edgebetweennessCentrality(node *l,node *r, graph *g){
	int st_n,st,start,left,right,end,i,checked,nodes;
	int count_neighbors;
	int flag=0;
	int *neighbors;
	double cc;
	left=l->get_id();
	right=r->get_id();
	count_neighbors=l->get_neighbors(&neighbors);
	for(int z=0;z<count_neighbors;z++){
		if(right==neighbors[z]){
			flag=1;
		}
	}
	if(flag==0){
		return -1;
	}
	cc=0.0;
	checked=0;
	nodes=g->nodes_count()-1;
	while(checked<nodes){
		g->deg_reset();
		for(i=0;i<=checked;i++){
			start=g->next_node_id();
		}
		checked++;
		while((end=g->next_node_id())>=0){
			st_n=g->reach_edges_through(start,left,right,end,&st);
			//cout<<"("<<left<<","<<right<<")"<<" contained in "<<st_n<<" out of "<<st<<" paths from "<<start<<" to "<<end<<endl;
			if(st_n>0){
				cc=((double)st_n)/st+cc;
			}
		}
	}
	return cc;
}

