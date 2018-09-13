#include "headers/extensions.hpp"
#include "headers/graph.hpp"

organization::organization(int o_id,string o_type,string o_name):node(o_id){
	type=o_type;
	name=o_name;
}

organization::~organization(){
	//cout<<"organization name: "<<name<<" deleted"<<endl;
}

void organization::print_properties(){
    cout<<name<<" ("<<type<<")"<<endl;
}

string organization::get_type(){
	return type;
}
