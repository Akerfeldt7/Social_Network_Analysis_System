#ifndef GRAPH_INC
#define GRAPH_INC


#include <iostream>

using namespace std;

class graph;

class edge{
	int head_id;
	double weight;
 public:
	edge(int);
	edge(int,double);
	virtual ~edge();
	int get_id();
	double get_weight();
};

struct i_d_Pair{
	int int_part;
	double double_part;
};


class edge_list{
	edge* held_element;
 public:
	~edge_list();
	edge_list* next;
	void hold(edge*);
	int get_data(int**,int);
	int get_data(i_d_Pair**,int);
	int get_single_data();
	string get_single_data_type();
	bool remove(int,edge_list **);
};

class node{
 protected:
	int id,neighbor_count;
	edge_list* neighbors;
 public:
	node(int);
	node(node &obj);
	virtual ~node();
	int get_id();
	void add_neighbor(edge*);
	int get_neighbors(int**);
	int get_neighbors(i_d_Pair**);
	int edge_count();
	virtual void print_properties();
	virtual string get_type();
	void remove_edge(int);
	bool is_connected(int);
};


class node_list{
	int depth;
	node* held_node;
	bool marked;
	double weight;
 public:
	node_list(int);
	~node_list();
	node_list* next;
	node* get_node();
	void hold(node*);
	int contains(int);
	int get_depth();
	void mark();
	bool is_marked();
	double get_weight();
	void set_weight(double);
};

struct Pair{
	int ID;
	int distance;
};




class result_set{
	node_list *results,*current_state,*last_element;
	graph* graph_pointer;
	Pair current_result;
 public:
	result_set(node_list*,graph*);
	~result_set();
	bool next();
	void print();
	Pair get_result();
};



class bucket{
	node **cell;
	int bucket_size,ovpg,current_elements;
 public:
	bucket(int);
	~bucket();
	void clear_bucket();
	bool add_element(node*);
	void show_contents();
	void overflow_bucket(int,node*);
	node* node_at(int);
	node* return_node(int);
	int degree_at(int);
	int id_at(int);
};

class graph{
	bucket **hashindex;
	int m,c,current_size,round,split_n,next_round,deg_hash,deg_bp,nodes,edges;
 public:
	graph(int,int);
	~graph();
	void insert_node(node*);
	int hash_function(int);
	int rehash_function(int);
	void expand();
	void split();
	void show_state();
	node *lookupnode(int);
	void insert_edge(int,edge*);
	int reach_single_node(int,int);
	int reach_single_node_classicBFS(int,int);  //ignore
	int reach_node_through(int,int,int,int*);
	result_set* reach_all_nodes(int);
	node_list* reach_all_nodes(int,int*,node_list*);
	int longest_path(int);
	node_list* bfs_step(node_list*,node_list*,node_list*);
	int next_node_degree();
	int next_node_id();
	int next_node_id(int* bck,int* cll); //meros 3
	void deg_reset();
	int nodes_count();
	int edges_count();
	int find_k_cliques(int k,int** cliques); //meros 3
	bool is_k_clique(int k, int* sub); //meros 3
	int reach_edges_through(int,int,int,int,int *); //meros 3
	
};

#endif /* GRAPH_INC */

