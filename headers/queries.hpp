#include "graph.hpp"
#include "extras.hpp"
#include "extensions.hpp"


Matches* matchSuggestion(node*,int,int,int,int,graph*);

graph* getTopStalkers(int,int,int,graph*,graph*,i_d_Pair**);

void findTrends(int,graph*,string**,string**);

graph* buildTrustGraph(int,graph*);

double estimateTrust(node*,node*,graph*);

double trust_calc(person*,int,int,graph*);

bool is_stalker(person*,int,graph*);

int comp(int*,int,int,int);

int match(node*, node*,int,int,int,int);

int add_interests(Pair**,int,int*,int);
