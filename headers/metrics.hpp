#include "graph.hpp"

void degreeDistribution(graph*);

int diameter(graph*);

double average_path(graph*);

double density(graph*);

int numberOfCCs(graph*);

int maxCC(graph*);

double closenessCentrality(node* n, graph* g);

double betweennessCentrality(node*, graph*);

double edgebetweennessCentrality(node *l,node *r, graph *g); //meros 3
