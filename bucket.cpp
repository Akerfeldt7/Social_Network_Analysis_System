#include <iostream>
#include "headers/graph.hpp"


using namespace std;

bucket::bucket(int c){
	int i;
	bucket_size=c;
	current_elements=0;
	ovpg=0;
	cell=new node*[c];
	for(i=0;i<c;i++){
		cell[i]=NULL;
	}
}

bucket::~bucket(){
	int i;
	for(i=0;i<current_elements;i++){
		//cout<<"delete "<<cell[i]->get_id()<<endl;
		delete cell[i];
	}
	delete[] cell;
}

void bucket::clear_bucket(){
	int i;
	for(i=0;i<current_elements;i++){
		cell[i]=NULL;
	}
	current_elements=0;
}

bool bucket::add_element(node * to_add){
	int i,position,cells;
	cells=bucket_size*(ovpg+1);
	for(i=0;i<cells;i++){
		if(cell[i]==NULL){
			cell[i]=to_add;
			current_elements++;
			return false;
		}
		else if(cell[i]->get_id()>to_add->get_id()){
			position=i;
			if(current_elements<cells){
				for(i=current_elements;i>position;i--){
					cell[i]=cell[i-1];
				}
				cell[position]=to_add;
				current_elements++;
				return false;
			}
			else{
				overflow_bucket(position,to_add);
				current_elements++;
				return true;
			}
		}
		else if(cell[i]->get_id()==to_add->get_id()){
			cout<<"no duplicates allowed ("<<to_add->get_id()<<")"<<endl;
			return false;
		}
	}
	overflow_bucket(i,to_add);
	current_elements++;
	return true;
}

void bucket::overflow_bucket(int position,node *element){
	int i,old_size,new_size;
	node **new_bucket;
	ovpg++;
	old_size=bucket_size*ovpg;
	new_size=old_size+bucket_size;
	new_bucket=new node*[new_size];
	for(i=0;i<position;i++){
		new_bucket[i]=cell[i];
	}
	new_bucket[position]=element;
	for(i=position;i<old_size;i++){
		new_bucket[i+1]=cell[i];
	}
	for(i=(old_size+1);i<new_size;i++){
		new_bucket[i]=NULL;
	}
	delete [] cell;
	cell=new_bucket;
}

node* bucket::node_at(int index){
	if(index<current_elements){
		return cell[index];
	}
	else{
		return NULL;
	}
}

void bucket::show_contents(){
	int i;
	for(i=0;i<current_elements;i++){
		cout<<"cell #"<<i<<": node id: "<<cell[i]->get_id()<<endl;
	}
}


node * bucket::return_node(int id_key){
	int left,right,mid,euros;
	bool found;
	euros=current_elements;
	left=0;
	right=euros-1;
	found=false;
	while((!found) && (left<=right)){
		mid=(left+right)/2;
		if(cell[mid]->get_id()==id_key){
			found=true;
		}
		else if(cell[mid]->get_id()>id_key){
			right=mid-1;
		}
		else{
			left=mid+1;
		}
	}
	if(found){
		return cell[mid];
	}
	else{
		return NULL;
	}
}


int bucket::degree_at(int position){
	if(position<current_elements){
		return cell[position]->edge_count();
	}
	else{
		return -1;
	}
}


int bucket::id_at(int position){
	if(position<current_elements){
		return cell[position]->get_id();
	}
	else{
		return -1;
	}
}




