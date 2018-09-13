#include "headers/extensions.hpp"
#include "headers/graph.hpp"

person::person(int p_id,string p_name,string p_surname,bool gnd,int p_age):node(p_id){
	name=p_name;
	surname=p_surname;
	age=p_age;
	gender=gnd;
}



person::~person(){
	//cout<<surname<<" deleted"<<endl;
}

void person::print_properties(){

	cout<<"My name is "<<name<<" "<<surname<<", age:"<<age<<", id "<<get_id()<<endl;
}

string person::get_type(){
	return "person";
}

int person::get_gender(){
	if(gender){
		return 1;
	}
	else{
		return 0;
	}
}


int person::get_age(){
	return age;
}


int person::job(int** table){
	int i,tags,*temp;
	edge_list *current;
	current=neighbors;
	tags=0;
	if(neighbor_count==0){
		return 0;
	}
	temp=new int[neighbor_count];
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("works_at")){
			temp[tags]=current->get_single_data();
			tags++;
		}
		current=current->next;
	}
	if(tags>0){
		(*table)=new int[tags];
		for(i=0;i<tags;i++){
			(*table)[i]=temp[i];
		}
	}
	delete [] temp;
	return tags;
}

int person::university(){
	edge_list *current;
	current=neighbors;
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("studies_at")){
			return current->get_single_data();
		}
		current=current->next;
	}
	return -1;
}


int person::place(){
	edge_list *current;
	current=neighbors;
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("lives")){
			return current->get_single_data();
		}
		current=current->next;
	}
	return -1;
}




int person::interests(int** table){
	int i,tags,*temp;
	edge_list *current;
	current=neighbors;
	tags=0;
	if(neighbor_count==0){
		return 0;
	}
	temp=new int[neighbor_count];
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("has_interest")){
			temp[tags]=current->get_single_data();
			tags++;
		}
		current=current->next;
	}
	if(tags>0){
		(*table)=new int[tags];
		for(i=0;i<tags;i++){
			(*table)[i]=temp[i];
		}
	}
	delete [] temp;
	return tags;
}

int person::liked_posts(int** table){
	int i,likes,*temp;
	edge_list *current;
	current=neighbors;
	likes=0;
	if(neighbor_count==0){
		return 0;
	}
	temp=new int[neighbor_count];
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("likes")){
			temp[likes]=current->get_single_data();
			likes++;
		}
		current=current->next;
	}
	if(likes>0){
		(*table)=new int[likes];
		for(i=0;i<likes;i++){
			(*table)[i]=temp[i];
		}
	}
	delete [] temp;
	return likes;
}


int person::get_comments(int** table){
	int i,likes,*temp;
	edge_list *current;
	current=neighbors;
	likes=0;
	if(neighbor_count==0){
		return 0;
	}
	temp=new int[neighbor_count];
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("made_comment")){
			temp[likes]=current->get_single_data();
			likes++;
		}
		current=current->next;
	}
	if(likes>0){
		(*table)=new int[likes];
		for(i=0;i<likes;i++){
			(*table)[i]=temp[i];
		}
	}
	delete [] temp;
	return likes;
}


bool person::has_friend(int test){
	edge_list *current;
	current=neighbors;
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("knows")){
			if(current->get_single_data()==test){
				return true;
			}
		}
		current=current->next;
	}
	return false;
}




