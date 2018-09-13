#include "headers/graph.hpp"
#include "headers/extensions.hpp"



edge_list::~edge_list(){
	if(next!=NULL){
		delete next;
	}
	delete held_element;
}

void edge_list::hold(edge* new_element){
	held_element=new_element;
}

int edge_list::get_data(int** datatable,int count){
	int size;
	if(next!=NULL){
		size=next->get_data(datatable,count+1);
		(*datatable)[count]=held_element->get_id();
		return size;
	}
	else{
		*datatable=new int[count+1];
		(*datatable)[count]=held_element->get_id();
		return (count+1);
	}
}

int edge_list::get_data(i_d_Pair** datatable,int count){
	int size;
	if(next!=NULL){
		size=next->get_data(datatable,count+1);
		(*datatable)[count].int_part=held_element->get_id();
		(*datatable)[count].double_part=held_element->get_weight();
		return size;
	}
	else{
		*datatable=new i_d_Pair[count+1];
		(*datatable)[count].int_part=held_element->get_id();
		(*datatable)[count].double_part=held_element->get_weight();
		return (count+1);
	}
}

int edge_list::get_single_data(){
	return held_element->get_id();
}

string edge_list::get_single_data_type(){
	relation *pnt;
	pnt=dynamic_cast<relation*>(held_element);
	if(pnt!=NULL){
		return pnt->get_type();
	}
	else{
		return "connects";
	}
}

bool edge_list::remove(int edge_id,edge_list** start){
	edge_list *temp;
	if(held_element->get_id()==edge_id){
		(*start)=next;
		next=NULL;
		delete this;
		return true;
	}
	else if(next==NULL){
		return false;
	}
	else if(next->get_single_data()==edge_id){
		temp=next;
		next=next->next;
		temp->next=NULL;
		delete temp;
		return true;
	}
	else{
		return next->remove(edge_id,NULL);
	}
}
