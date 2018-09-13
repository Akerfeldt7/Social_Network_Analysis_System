#include "headers/graph.hpp"



node::node(int rid){
	id=rid;
	neighbor_count=0;
	neighbors=NULL;
}


node::node(node &obj){
	id=obj.get_id();
	neighbor_count=0;
	neighbors=NULL;
}


node::~node(){
	delete neighbors;
}

int node::get_id(){
	return id;
}


void node::add_neighbor(edge* neighbor){
	edge_list* new_element=new edge_list();
	new_element->hold(neighbor);
	new_element->next=neighbors;
	neighbors=new_element;
	neighbor_count++;
}

int node::get_neighbors(int** edges){
	if(neighbors!=NULL){
		return neighbors->get_data(edges,0);
	}
	else{
		return 0;
	}
}


int node::get_neighbors(i_d_Pair** edges){
	if(neighbors!=NULL){
		return neighbors->get_data(edges,0);
	}
	else{
		return 0;
	}
}

int node::edge_count(){
	//cout<<id<<" "<<neighbor_count<<endl;
	return neighbor_count;
}

void node::print_properties(){
}


string node::get_type(){
	return "node";
}

void node::remove_edge(int ed){
	if(neighbors->remove(ed,&neighbors)){
		neighbor_count--;
	}
}

bool node::is_connected(int i){
	edge_list *current;
	current=neighbors;
	while(current!=NULL){
		if(current->get_single_data()==i){
			return true;
		}
		current=current->next;
	}
	return false;
}

