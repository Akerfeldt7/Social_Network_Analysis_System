#include "headers/extensions.hpp"
#include "headers/graph.hpp"

tag::tag(int t_id,string t_name):node(t_id){
	name=t_name;
}

tag::~tag(){
    //cout<<name<<" deleted"<<endl;
}

void tag::print_properties(){
    cout<<name<<endl;
}


string tag::get_tag(){
	return name;
}

string tag::get_type(){
	return "tag";
}
