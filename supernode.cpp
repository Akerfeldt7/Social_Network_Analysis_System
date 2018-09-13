//supernode.cpp

#include "headers/extensions.hpp"
#include "headers/graph.hpp"


/*supernode::supernode(int n_id,int *table):node(n_id){
	ids=table;
}

supernode::~supernode(){
}

int * supernode::get_ids(){
	return ids;
}

string supernode::get_type(){
	return "supernode";
}*/


supernode::supernode(int sn_id,int *sub_ids):node(sn_id){
	clique=sub_ids;
}



supernode::~supernode(){
	delete [] clique;
}

int* supernode::clique_ids(){
	return clique;
}

string supernode::get_type(){
	return "supernode";
}
