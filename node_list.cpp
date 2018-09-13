#include "headers/graph.hpp"


node_list::node_list(int level){
	depth=level;
	next=NULL;
	marked=false;
}

node_list::~node_list(){
	held_node=NULL;
	if(next!=NULL){
		delete next;
	}
}

int node_list::contains(int key){
	if(held_node->get_id()==key){
		return depth;
	}
	else if(next==NULL){
		return -1;
	}
	else{
		return next->contains(key);
	}
}

int node_list::get_depth(){
	return depth;
}

void node_list::hold(node* some_node){
	held_node=some_node;
}

node* node_list::get_node(){
	return held_node;
}

void node_list::mark(){
	marked=true;
}

bool node_list::is_marked(){
	return marked;
}


double node_list::get_weight(){
	return weight;
}

void node_list::set_weight(double value){
	weight=value;
}




