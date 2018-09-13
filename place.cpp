#include "headers/extensions.hpp"
#include "headers/graph.hpp"

place::place(int pl_id,string pl_name,string pl_type):node(pl_id){
	name=pl_name;
	type=pl_type;
}

place::~place(){
    //cout<<name<<" deleted"<<endl;
}

void place::print_properties(){
    cout<<name<<" ("<<type<<")"<<endl;
}


string place::get_type(){
	return type;
}
