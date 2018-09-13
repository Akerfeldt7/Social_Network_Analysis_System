#ifndef EXTRA_INC
#define EXTRA_INC

#include "graph.hpp"

class Matches{
	Pair *results;
	int count,current;
 public:
	Matches(int,Pair*);
	~Matches();
	int next_result(int*);
	int size();
	void reset();
	bool is_empty();
};

class communities{
	int cm_num;
	int **members;
 public:
	communities(int);
	~communities();
	void insert(int *);
	void show(int);
	int return_size_com();
	bool same_community(int,int);
};

#endif /* EXTRA_INC */
