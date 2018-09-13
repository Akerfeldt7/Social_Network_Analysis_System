#include "headers/extensions.hpp"
#include "headers/graph.hpp"

comment::comment(int comm_id,int post_id,int creator_id):node(comm_id){
	creator=creator_id;
	compost=post_id;
}

comment::~comment(){
    //cout<<name<<" deleted"<<endl;
}

void comment::print_properties(){
    cout<<"comment #"<<id<<" created by "<<creator<<" in reply of "<<compost<<endl;
}


string comment::get_type(){
	return "comment";
}

int comment::get_creator(){
	return creator;
}

int comment::reply_of(){
	return compost;
}
