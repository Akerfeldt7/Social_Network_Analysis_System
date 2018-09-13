#include "headers/extensions.hpp"
#include "headers/graph.hpp"

forum::forum(int t_id,string t_name):node(t_id){
	title=t_name;
}

forum::~forum(){
    //cout<<name<<" deleted"<<endl;
}

void forum::print_properties(){
    cout<<title<<endl;
}


string forum::get_title(){
	return title;
}

string forum::get_type(){
	return "forum";
}


int forum::get_members(int** table){
	int i,tags,*temp;
	edge_list *current;
	current=neighbors;
	tags=0;
	if(neighbor_count==0){
		return 0;
	}
	temp=new int[neighbor_count];
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("has_member")){
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


int forum::get_posts(int** table){
	int i,tags,*temp;
	edge_list *current;
	current=neighbors;
	tags=0;
	if(neighbor_count==0){
		return 0;
	}
	temp=new int[neighbor_count];
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("has_post")){
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



bool forum::has_member(int test){
	edge_list *current;
	current=neighbors;
	while(current!=NULL){
		if(!(current->get_single_data_type()).compare("has_member")){
			if(current->get_single_data()==test){
				return true;
			}
		}
		current=current->next;
	}
	return false;
}
