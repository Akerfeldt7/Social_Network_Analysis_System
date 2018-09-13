#include <iostream>
#include <utility>
#include "headers/graph.hpp"

using namespace std;

result_set::result_set(node_list* data, graph* gdata){
	results=data;
	current_state=data;
	last_element=data;
	graph_pointer=gdata;
	current_result.ID=data->get_node()->get_id();
	current_result.distance=0;
}

result_set::~result_set(){
	delete results;
}

bool result_set::next(){
	if(current_state!=NULL){
		last_element=graph_pointer->bfs_step(results,current_state,last_element);
		current_state=current_state->next;
	}
	if(current_state==NULL){
		return false;
	}
	else{
		current_result.ID=current_state->get_node()->get_id();
		current_result.distance=current_state->get_depth();
		return true;
	}
}

void result_set::print(){
	node* temp;
	if(current_state!=NULL){
		temp=current_state->get_node();
		cout<<"node id: "<<temp->get_id()<<" path distance: "<<current_state->get_depth()<<endl;
	}
	else{
		cout<<"error - end of result set"<<endl;
	}
}


Pair result_set::get_result(){
	if(current_state!=NULL){
		return current_result;
	}
	else{
		cout<<"error - end of result set"<<endl;
		return current_result;
	}
}




