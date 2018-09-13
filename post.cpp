#include "headers/extensions.hpp"
#include "headers/graph.hpp"

post::post(int post_id,int person_id,int f_id):node(post_id){
	creator=person_id;
	conforum=f_id;
}

post::~post(){
    //cout<<name<<" deleted"<<endl;
}

void post::print_properties(){
    cout<<"post #"<<id<<" created by "<<creator<<endl;
}


string post::get_type(){
	return "post";
}

int post::get_creator(){
	return creator;
}

int post::get_forum(){
	return conforum;
}
