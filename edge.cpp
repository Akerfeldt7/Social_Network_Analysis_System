#include "headers/graph.hpp"






edge::edge(int target){
	head_id=target;
	weight=1;
}

edge::edge(int target,double edge_w){
	head_id=target;
	weight=edge_w;
}

double edge::get_weight(){
	return weight;
}

edge::~edge(){
	//cout<<"edge to "<<head_id<<" deleted"<<endl;
}

int edge::get_id(){
	return head_id;
}
