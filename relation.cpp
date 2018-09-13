#include "headers/extensions.hpp"



relation::relation(int ignore,int des_id,string status):edge(des_id){
	type=status;
}

relation::relation(int ignore,int des_id,string status,double edge_weight):edge(des_id,edge_weight){
	type=status;
}

relation::~relation(){
	//cout<<"to "<<get_id()<<" as "<<type<<" deleted"<<endl;
}


string relation::get_type(){
	return type;
}
