#include <cmath>
#include "headers/graph.hpp"


using namespace std;

graph::graph(int initial_size,int bucket_size){
	int i;
	if(initial_size<1){
		cout<<"wrong input\ninitial hashtable size sets to 1 by default"<<endl;
	}
	if(bucket_size<1){
		cout<<"wrong input\ninitial bucket size sets to 1 by default"<<endl;
	}
	round=0;
	split_n=0;
	m=initial_size;
	current_size=m;
	next_round=m;
	c=bucket_size;
	hashindex=new bucket*[m];
	for(i=0;i<m;i++){
		hashindex[i]=new bucket(c);
	}
	deg_hash=0;
	deg_bp=0;
	nodes=0;
	edges=0;
}

graph::~graph(){
	int i;
	for(i=0;i<current_size;i++){
		delete hashindex[i];
	}
	delete [] hashindex;
}

void graph::insert_node(node * subject){
	int hash,ckey;
	bool causes_op;
	ckey=subject->get_id();
	hash=hash_function(ckey);
	causes_op=hashindex[hash]->add_element(subject);
	if(causes_op){
		expand();
		split();
	}
	nodes++;
}


int graph::edges_count(){
	return edges;
}

int graph::nodes_count(){
	return nodes;
}

int graph::hash_function(int key){
	int hash,round_factor;
	round_factor=pow(2.0,round);
	hash=key%(round_factor*m);
	if(hash<split_n){
		round_factor=round_factor*2;
		hash=key%(round_factor*m);
	}
	return hash;
}

int graph::rehash_function(int key){
	int hash,round_factor;
	round_factor=pow(2.0,(round+1));
	hash=key%(round_factor*m);
	return hash;
}

void graph::expand(){
	int i;
	bucket **new_t;
	new_t=new bucket*[current_size+1];
	for(i=0;i<current_size;i++){
		new_t[i]=hashindex[i];
	}
	new_t[current_size]=new bucket(c);
	current_size++;
	delete [] hashindex;
	hashindex=new_t;
}


void graph::split(){
	int count,hash,key;
	bucket *rehash_list;
	node *rehash_node;
	rehash_list=hashindex[split_n];
	hashindex[split_n]=new bucket(c);
	count=0;
	while((rehash_node=rehash_list->node_at(count))!=NULL){
		key=rehash_node->get_id();
		hash=rehash_function(key);
		hashindex[hash]->add_element(rehash_node);
		count++;
	}
	rehash_list->clear_bucket();
	delete rehash_list;
	split_n++;
	if(split_n==next_round){
		split_n=0;
		round++;
		next_round=next_round*2;
	}
}

void graph::show_state(){
	int i;
	for(i=0;i<current_size;i++){
		cout<<"hash #"<<i<<endl;
		hashindex[i]->show_contents();
	}
	cout<<"spliting stopped at "<<split_n<<", round "<<round<<endl;
}


node * graph::lookupnode(int key){
	int hash;
	hash=hash_function(key);
	return hashindex[hash]->return_node(key);
}

void graph::insert_edge(int tail,edge * some_edge){
	node *tail_node;	
	tail_node=lookupnode(tail);
	if(tail_node!=NULL){
		tail_node->add_neighbor(some_edge);
		edges++;
	}
	else{
		cout<<"tail node "<<tail<<" does not exist in graph"<<endl;
		delete some_edge;
	}
}


int graph::reach_single_node_classicBFS(int start, int end){
	int i,neighbors_count,*to_check,expansions,repeats;
	node *current_node;
	node_list *first_element,*last_element,*current_element;
	to_check=NULL;
	current_node=lookupnode(start);
	if(current_node==NULL){
		cout<<"starting node could not be found"<<endl;
		return 0;
	}
	if(start==end){
		return 0;
	}
	expansions=0;
	repeats=0;
	first_element=new node_list(0);
	first_element->hold(current_node);
	last_element=first_element;
	current_element=first_element;
	while(current_element!=NULL){
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			repeats++;
			if(first_element->contains(to_check[i])>=0){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				delete first_element;
				return 0;
			}
			else if(current_node->get_id()==end){
				i=current_element->get_depth()+1;
				delete[] to_check;
				delete first_element;
				cout<<"it took "<<expansions<<" expansions and "<<repeats<<" repeats"<<endl;
				return i;
			}
			last_element->next=new node_list(current_element->get_depth()+1);
			last_element=last_element->next;
			last_element->hold(current_node);
			expansions++;
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		current_element=current_element->next;
		if(current_element!=NULL){
			current_node=current_element->get_node();
		}
		else{
			cout<<"search failed - no path between nodes\n";
		}
	}
	if(to_check!=NULL){
		delete[] to_check;
		to_check=NULL;
	}
	delete first_element;
	return -1;
}


int graph::reach_node_through(int start,int mid, int end, int *all_paths){
	int i,neighbors_count,*to_check,paths,marked,con;
	node *current_node;
	node_list *first_element,*last_element,*current_element;
	to_check=NULL;
	current_node=lookupnode(start);
	if(current_node==NULL){
		cout<<"starting node could not be found"<<endl;
		return 0;
	}
	if(start==end){
		return 0;
	}
	first_element=new node_list(0);
	first_element->hold(current_node);
	last_element=first_element;
	current_element=first_element;
	paths=0;
	marked=0;
	while(current_element!=NULL){
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			con=first_element->contains(to_check[i]);
			if((con>=0)&&(con<=current_element->get_depth())){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				delete first_element;
				return 0;
			}
			last_element->next=new node_list(current_element->get_depth()+1);
			last_element=last_element->next;
			last_element->hold(current_node);
			if(current_element->is_marked()){
				last_element->mark();
			}
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		while(current_element!=NULL){
			current_element=current_element->next;
			if(current_element==NULL){
				break;
			}
			else{
				current_node=current_element->get_node();
				if(current_node->get_id()==end){
					paths++;
					if(current_element->is_marked()){
						marked++;
					}
					continue;
				}
				else if(current_node->get_id()==mid){
					current_element->mark();
				}
				break;
			}
		}
	}
	if(to_check!=NULL){
		delete[] to_check;
		to_check=NULL;
	}
	delete first_element;
	(*all_paths)=paths;
	return marked;
}

int graph::reach_single_node(int start, int end){
	int i,neighbors_count,*to_check,dpth,repeats,expansions;
	node *current_node;
	node_list *first_element,*last_element,*current_element;
	node_list *first_element_sec,*last_element_sec,*current_element_sec;
	to_check=NULL;
	repeats=0;
	expansions=0;
	if(start==end){
		return 0;
	}
	current_node=lookupnode(start);
	if(current_node==NULL){
		cout<<"starting node could not be found"<<endl;
		return -1;
	}
	first_element=new node_list(0);
	first_element->hold(current_node);
	last_element=first_element;
	current_element=first_element;
	current_node=lookupnode(end);
	if(current_node==NULL){
		cout<<"ending node could not be found"<<endl;
		delete first_element;
		return -1;
	}
	first_element_sec=new node_list(0);
	first_element_sec->hold(current_node);
	last_element_sec=first_element_sec;
	current_element_sec=first_element_sec;
	while(current_element!=NULL && current_element_sec!=NULL){
		current_node=current_element->get_node();
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			repeats++;
			if(first_element->contains(to_check[i])>=0){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				delete first_element;
				delete first_element_sec;
				return -1;
			}
			else if((dpth=first_element_sec->contains(current_node->get_id()))>=0){
				i=current_element->get_depth()+dpth+1;
				delete[] to_check;
				delete first_element;
				delete first_element_sec;
				//cout<<"it took "<<expansions<<" expansions and "<<repeats<<" repeats"<<endl;
				return i;
			}
			last_element->next=new node_list(current_element->get_depth()+1);
			last_element=last_element->next;
			last_element->hold(current_node);
			expansions++;
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		current_node=current_element_sec->get_node();
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			repeats++;
			if(first_element_sec->contains(to_check[i])>=0){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				delete first_element;
				delete first_element_sec;
				return -1;
			}
			else if((dpth=first_element->contains(current_node->get_id()))>=0){
				i=current_element_sec->get_depth()+1+dpth;
				delete[] to_check;
				delete first_element;
				delete first_element_sec;
				//cout<<"it took "<<expansions<<" expansions and "<<repeats<<" repeats"<<endl;
				return i;
			}
			last_element_sec->next=new node_list(current_element_sec->get_depth()+1);
			last_element_sec=last_element_sec->next;
			last_element_sec->hold(current_node);
			expansions++;
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		current_element=current_element->next;
		current_element_sec=current_element_sec->next;
	}
	cout<<"search failed - no path between nodes"<<endl;
	if(to_check!=NULL){
		delete[] to_check;
		to_check=NULL;
	}
	delete first_element;
	delete first_element_sec;
	return -1;
}

int graph::longest_path(int start){
	int i,neighbors_count,*to_check,current_depth;
	node *current_node;
	node_list *first_element,*last_element,*current_element;
	to_check=NULL;
	current_node=lookupnode(start);
	current_depth=0;
	if(current_node==NULL){
		cout<<"starting node could not be found"<<endl;
		return -1;
	}
	first_element=new node_list(0);
	first_element->hold(current_node);
	last_element=first_element;
	current_element=first_element;
	while(current_element!=NULL){
		current_node=current_element->get_node();
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			if(first_element->contains(to_check[i])>=0){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				delete first_element;
				return -1;
			}
			last_element->next=new node_list(current_element->get_depth()+1);
			last_element=last_element->next;
			last_element->hold(current_node);
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		current_depth=current_element->get_depth();
		current_element=current_element->next;
	}
	if(to_check!=NULL){
		delete[] to_check;
		to_check=NULL;
	}
	return current_depth;
}

node_list* graph::reach_all_nodes(int start,int *size,node_list *tail){
	int i,neighbors_count,*to_check;
	node *current_node;
	node_list *first_element,*last_element,*current_element;
	to_check=NULL;
	*size=0;
	current_node=lookupnode(start);
	if(current_node==NULL){
		cout<<"starting node could not be found"<<endl;
		return NULL;
	}
	first_element=new node_list(0);
	first_element->hold(current_node);
	last_element=first_element;
	current_element=first_element;
	while(current_element!=NULL){	
		(*size)++;
		current_node=current_element->get_node();
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			if(first_element->contains(to_check[i])>=0){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				delete first_element;
				return NULL;
			}
			last_element->next=new node_list(current_element->get_depth()+1);
			last_element=last_element->next;
			last_element->hold(current_node);
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		current_element=current_element->next;
	}
	if(to_check!=NULL){
		delete[] to_check;
		to_check=NULL;
	}
	last_element->next=tail;
	return first_element;
}

result_set* graph::reach_all_nodes(int start){
	node_list *expansion_list;
	result_set* result;
	node *current_node;
	current_node=lookupnode(start);
	if(current_node==NULL){
		cout<<"starting node could not be found"<<endl;
		return NULL;
	}
	expansion_list=new node_list(0);
	expansion_list->hold(current_node);
	result=new result_set(expansion_list,this);
	return result;
}


node_list* graph::bfs_step(node_list* list,node_list* current_element,node_list* last_element){
	int i,neighbors_count,*to_check;
	node* current_node;
	to_check=NULL;
	if(current_element!=NULL){
		current_node=current_element->get_node();
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			if(list->contains(to_check[i])>=0){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				return NULL;
			}
			last_element->next=new node_list(current_element->get_depth()+1);
			last_element=last_element->next;
			last_element->hold(current_node);
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		current_element=current_element->next;
	}
	return last_element;
}

void graph::deg_reset(){
	deg_hash=0;
	deg_bp=0;
}

int graph::next_node_degree(){
	int degree;
	degree=hashindex[deg_hash]->degree_at(deg_bp);
	if(degree>=0){
		deg_bp++;
		return degree;
	}
	else{
		deg_bp=0;
		deg_hash++;
		if(deg_hash<current_size){
			return next_node_degree();
		}
		else{
			return -1;
		}
	}
}




int graph::next_node_id(){
	int id;
	id=hashindex[deg_hash]->id_at(deg_bp);
	if(id>=0){
		deg_bp++;
		return id;
	}
	else{
		deg_bp=0;
		deg_hash++;
		if(deg_hash<current_size){
			return next_node_id();
		}
		else{
			deg_hash--;
			return -1;
		}
	}
}

int graph::next_node_id(int* bck,int* cll){
	int id;
	id=hashindex[(*bck)]->id_at((*cll));
	if(id>=0){
		(*cll)++;
		return id;
	}
	else{
		(*cll)=0;
		(*bck)++;
		if((*bck)<current_size){
			return next_node_id(bck,cll);
		}
		else{
			(*bck)--;
			return -1;
		}
	}
}

//////////////////////meros 3///////////////

/*int graph::find_k_cliques(int k,int** cliques){
    int i,array[]={1,2,3,1,3,4,4,5,6,5,6,7,5,6,8,5,7,8,6,7,8};
	(*cliques)=new int[21];
	for(i=0;i<21;i++){
		(*cliques)[i]=array[i];
	}
	return 7;
}*/


int graph::reach_edges_through(int start,int left,int right, int end, int *all_paths){
	int i,neighbors_count,*to_check,paths,marked,con;
	node *current_node;
	node_list *first_element,*last_element,*current_element;
	to_check=NULL;
	current_node=lookupnode(start);
	if(current_node==NULL){
		cout<<"starting node could not be found"<<endl;
		return 0;
	}
	if(start==end){
		return 0;
	}
	first_element=new node_list(0);
	first_element->hold(current_node);
	last_element=first_element;
	current_element=first_element;
	paths=0;
	marked=0;
	while(current_element!=NULL){
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			con=first_element->contains(to_check[i]);
			if((con>=0)&&(con<=current_element->get_depth())){
				continue;
			}
			current_node=lookupnode(to_check[i]);
			if(current_node==NULL){
				cout<<"error: failed to locate node with id "<<to_check[i]<<endl;
				delete[] to_check;
				delete first_element;
				return 0;
			}
			last_element->next=new node_list(current_element->get_depth()+1);
			last_element=last_element->next;
			last_element->hold(current_node);
			if(current_element->is_marked()){
				last_element->mark();
			}
			else if(current_node->get_id()==left  &&  current_element->get_node()->get_id()==right ){
				last_element->mark();
			}
			else if(current_node->get_id()==right  &&  current_element->get_node()->get_id()==left ){
				last_element->mark();
			}
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		while(current_element!=NULL){
			current_element=current_element->next;
			if(current_element==NULL){
				break;
			}
			else{
				current_node=current_element->get_node();
				if(current_node->get_id()==end){
					paths++;
					if(current_element->is_marked()){
						marked++;
					}
					continue;
				}
				break;
			}
		}
	}
	if(to_check!=NULL){
		delete[] to_check;
		to_check=NULL;
	}
	delete first_element;
	(*all_paths)=paths;
	return marked;
}



struct clique_sck{  //lista
	int * held_clique;
	clique_sck * next;
};

int graph::find_k_cliques(int k,int **k_cliques){
	int *k_set;
	int a,b,i,rc,cliques_found;
	bool next_k_set;
	clique_sck *clique_list,*f_clique;
	k_set=new int[k*3];
	a=0;
	b=0;
	cliques_found=0;
	clique_list=NULL;
	for(i=0;i<(k*3);i+=3){
		k_set[i]=next_node_id(&a,&b);
		if(k_set[i]==-1){
			cout<<"k can't be larger than the graph"<<endl;
			delete [] k_set;
			return 0;
		}
		k_set[i+1]=a;
		k_set[i+2]=b;
	}
	rc=1;
	while(rc<=k){
		if(is_k_clique(k,k_set)){
			cliques_found++;
			f_clique=new clique_sck;
			f_clique->held_clique=new int[k];
			for(i=0;i<k;i++){
				f_clique->held_clique[i]=k_set[i*3];
			}
			f_clique->next=clique_list;
			clique_list=f_clique;
		}
		rc=1;
		next_k_set=false;
		while(!next_k_set){
			if(rc>k){
				break;
			}
			next_k_set=true;
			i=(k-rc)*3;
			k_set[i]=next_node_id(k_set+(i+1),k_set+(i+2));
			if(k_set[i]==-1){
				rc++;
				next_k_set=false;
				continue;
			}
			a=k_set[i+1];
			b=k_set[i+2];
			i+=3;
			while(i<k*3){
				k_set[i]=next_node_id(&a,&b);
				if(k_set[i]==-1){
					rc++;
					next_k_set=false;
					break;
				}
				k_set[i+1]=a;
				k_set[i+2]=b;
				i+=3;
			}
		}
	}
	delete [] k_set;
	f_clique=clique_list;
	k_set=new int[cliques_found*k];
	for(i=0;i<cliques_found;i++){
		for(a=0;a<k;a++){
			k_set[i*k+a]=f_clique->held_clique[a];
		}
		f_clique=f_clique->next;
		delete [] clique_list->held_clique;
		delete clique_list;
		clique_list=f_clique;
	}
	(*k_cliques)=k_set;
	return cliques_found;
}

bool graph::is_k_clique(int k, int* sub){
	int i,j;
	node *node_a;
	for(i=0;i<(k-1)*3;i+=3){
		node_a=lookupnode(sub[i]);
		if(node_a->edge_count()<k-1){
			return false;
		}
		for(j=i+3;j<k*3;j+=3){
			if(!node_a->is_connected(sub[j])){
				return false;
			}
		}
	}
	return true;
}
























