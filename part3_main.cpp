//file:part3_main

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "headers/graph.hpp"
#include "headers/extensions.hpp"
#include "headers/metrics.hpp"
#include "headers/extras.hpp"
#include "headers/queries.hpp"
#include <cfloat>

using namespace std;


communities * clique_percolation_method(int,graph *);
communities * communities_alg_one(int,graph*);
void create_edges(int,graph*);
bool match_cliques(int,int*,int*);
bool member(int *,int);


communities * girvan_newman(double,graph *);
communities * communities_alg_two(graph *);
bool modularity(int,double,graph *,double *);
bool knows(node *,int);



bool in(int id,int size,int * table){
	for(int i=0;i<size;i++){
		if(table[i]==id){
			return true;
		}
	}
	return false;
}

graph * forum_graph(int forum,int size_forum){

    ifstream datafile;
    string datastring,sub_a,sub_b;
	int va;
	int * persons;
	int p=0,p_id,pa,pb;
	node * n;
	edge * e;

	graph * person_graph=new graph(4,5);


	persons=new int[size_forum];

	datafile.open("dataset_part3/forum_hasMember_person.csv");
    getline(datafile,datastring);
	while(!datafile.eof()){
        getline(datafile,datastring);
        va=datastring.find("|");
        sub_a=datastring.substr(0,va);
        if(forum==(atoi(sub_a.c_str()))){
        //if(!sub_a.compare(forum)){
            datastring.erase(0,va+1);
            va=datastring.find("|");
			sub_b=datastring.substr(0,va);
			p_id=atoi(sub_b.c_str());
			persons[p]=p_id;
			n=new node(p_id);
			person_graph->insert_node(n);
			//cout<<"num:"<<p<<" "<<p_id<<endl;
			p++;
		}
	}
	datafile.close();
	datafile.clear();

	datafile.open("dataset_part3/person_knows_person.csv");
	getline(datafile,datastring);
	while(!datafile.eof()){
		getline(datafile,datastring);

		va=datastring.find("|");
		sub_a=datastring.substr(0,va);
		pa=atoi(sub_a.c_str());
		if(in(pa,size_forum,persons)){
			datastring.erase(0,va+1);
			va=datastring.find("|");
			sub_b=datastring.substr(0,va);
			pb=atoi(sub_b.c_str());
			if(in(pb,size_forum,persons)){
				e=new edge(pb);
				person_graph->insert_edge(pa,e);
				//cout<<"person a:"<<pa<<" knows person b:"<<pb<<endl;
			}
		}
	}

    return person_graph;
}

int forum_size(string forum){
	ifstream datafile;
	string datastring,sub_a;
	int va,num_persons=0;
	datafile.open("dataset_part3/forum_hasMember_person.csv");
    getline(datafile,datastring);
	while(!datafile.eof()){
        getline(datafile,datastring);

        va=datastring.find("|");
        sub_a=datastring.substr(0,va);
        if(!sub_a.compare(forum)){
			num_persons++;
		}
	}
	datafile.close();
	datafile.clear();
	return num_persons;
}

Pair * top_n_forums(int num){
	ifstream datafile;
	string datastring,sub_a;
	int va,a,p_id,size,temp_size,temp_id;
	graph * g;
	node *n;
	edge *e;
	Pair  *forum_pairs;

	g=new graph(4,5);

	forum_pairs=new Pair[num];
	for(int i=0;i<num;i++){
		forum_pairs[i].distance=-1;
	}

	datafile.open("dataset_part3/forum_hasMember_person.csv");
	getline(datafile,datastring);
	while(!datafile.eof()){
		getline(datafile,datastring);

		va=datastring.find("|");
		sub_a=datastring.substr(0,va);
		datastring.erase(0,va+1);
		a=atoi(sub_a.c_str());
		n=g->lookupnode(a);
		if(n==NULL){
			n=new node(a);
			g->insert_node(n);
		}
		va=datastring.find("|");
		sub_a=datastring.substr(0,va);
		p_id=atoi(sub_a.c_str());
		e=new edge(p_id);
		g->insert_edge(a,e);
	}

	g->deg_reset();
	while((p_id=g->next_node_id())>=0){
		n=g->lookupnode(p_id);
        size=n->edge_count();
        for(int i=0;i<num;i++){
			if(forum_pairs[i].distance<0){
                forum_pairs[i].ID=p_id;
                forum_pairs[i].distance=size;
				break;
			}
			else if(size>forum_pairs[i].distance){
				temp_size=size;
				temp_id=p_id;
				size=forum_pairs[i].distance;
				p_id=forum_pairs[i].ID;
				forum_pairs[i].distance=temp_size;
				forum_pairs[i].ID=temp_id;
			}
		}
	}

	/*for(int i=0;i<num;i++){
		cout<<"Forum me id:"<<forum_pairs[i].ID<<" has "<<forum_pairs[i].distance<<" members"<<endl;;
	}*/

	return forum_pairs;
}


int main(){

////////////////////////grafos network//////////////////////////////////////////
	int m=2,c=3;
	graph * network=new graph(m,c);

	//nodes//
	node * n1=new node(1);
	node * n2=new node(2);
	node * n3=new node(3);
	node * n4=new node(4);
	node * n5=new node(5);
	node * n6=new node(6);
	node * n7=new node(7);
	node * n8=new node(8);
	node * n9=new node(9);

	network->insert_node(n1);
	network->insert_node(n2);
	network->insert_node(n3);
	network->insert_node(n4);
	network->insert_node(n5);
	network->insert_node(n6);
	network->insert_node(n7);
	network->insert_node(n8);
	network->insert_node(n9);

	//edges//
	edge * e1=new edge(3); //
	edge * e2=new edge(1); //
	edge * e3=new edge(4);//
	edge * e4=new edge(1);//
	edge * e5=new edge(2);//
	edge * e6=new edge(1);//
	edge * e7=new edge(2);//
	edge * e8=new edge(3);//
	edge * e9=new edge(4);//
	edge * e10=new edge(3);//
	edge * e11=new edge(5);//
	edge * e12=new edge(4);//
	edge * e13=new edge(6);//
	edge * e14=new edge(4);//
	edge * e15=new edge(7);//
	edge * e16=new edge(5);//
	edge * e17=new edge(6);//
	edge * e18=new edge(5);//
	edge * e19=new edge(8);//
	edge * e20=new edge(5);//
	edge * e21=new edge(7);
	edge * e22=new edge(6);
	edge * e23=new edge(8);
	edge * e24=new edge(6);
	edge * e25=new edge(7);
	edge * e26=new edge(8);
	edge * e27=new edge(9);
	edge * e28=new edge(7);

	network->insert_edge(1,e1);
	network->insert_edge(3,e2);
	network->insert_edge(1,e3);
	network->insert_edge(4,e4);
	network->insert_edge(1,e5);
	network->insert_edge(2,e6);
	network->insert_edge(3,e7);
	network->insert_edge(2,e8);
	network->insert_edge(3,e9);
	network->insert_edge(4,e10);
	network->insert_edge(4,e11);
	network->insert_edge(5,e12);
	network->insert_edge(4,e13);
	network->insert_edge(6,e14);
	network->insert_edge(5,e15);
	network->insert_edge(7,e16);
	network->insert_edge(5,e17);
	network->insert_edge(6,e18);
	network->insert_edge(5,e19);
	network->insert_edge(8,e20);
	network->insert_edge(6,e21);
	network->insert_edge(7,e22);
	network->insert_edge(6,e23);
	network->insert_edge(8,e24);
	network->insert_edge(8,e25);
	network->insert_edge(7,e26);
	network->insert_edge(7,e27);
	network->insert_edge(9,e28);

	cout<<"ALGORITHMOS 1 for network"<<endl;
	int k=3;
	communities *com_one;
	com_one=clique_percolation_method(k,network);
	cout<<"Found "<<com_one->return_size_com()<<" communities"<<endl;
	for(int i=0;i<com_one->return_size_com();i++){
		com_one->show(i);
	}
	delete com_one;
	
	cout<<endl<<"ALGORITHMOS 2 for network"<<endl;
	communities *com_two;
    com_two=girvan_newman(1,network);
	cout<<"Found "<<com_two->return_size_com()<<" communities"<<endl;
	for(int i=0;i<com_two->return_size_com();i++){
		com_two->show(i);
	}
	delete com_two;



////////////////////////////////////////////////////////////////////////////////


///////////////FORUMS/////////////////////////////////////////////////////////
	cout<<endl<<endl;

	communities *com_one_f, *com_two_f;
	int i,j,n=6;
    graph *forum_g;     //*test;
    Pair  *forum_pairs;
    forum_pairs=top_n_forums(n);
    
    for(i=0;i<n;i++){
		cout<<"Forum_id:"<<forum_pairs[i].ID<<endl;
	}
	//////////////////////////////////////////////////////////////////////////
	cout<<endl<<"ALGORITHMOS 1 for forum_graphs"<<endl<<endl;
	for(i=0;i<n;i++){
        forum_g=forum_graph(forum_pairs[i].ID,forum_pairs[i].distance);
		com_one_f=clique_percolation_method(3,forum_g);   //gia k=3 kai apo kato gia k=4
		//com_one_f=clique_percolation_method(4,forum_g);
        cout<<"Forum_id:"<<forum_pairs[i].ID<<endl;
		cout<<"Found "<<com_one_f->return_size_com()<<" communities"<<endl;
		for(j=0;j<com_one_f->return_size_com();j++){
			com_one_f->show(j);
		}
		delete com_one_f;
		delete forum_g;
		cout<<endl;
	}
	////////////////////////////////////////////////////////////////////
	cout<<endl<<"ALGORITHMOS 2 for forum_graphs"<<endl<<endl;
	for(i=0;i<n;i++){
        forum_g=forum_graph(forum_pairs[i].ID,forum_pairs[i].distance);
        if(forum_pairs[i].ID==34680){  //troei segn epeidi prospathoun na mpoun duplicates nodes kai ginetai kapoio lathos
			delete forum_g;
			continue;
		}
		else if(forum_pairs[i].ID==228460){  //megalo forum,trexei para polu ora
            delete forum_g;
			continue;
		}
		else if(forum_pairs[i].ID==228280){ //megalos forum,trexei para polu ora
            delete forum_g;
			continue;
		}
		com_two_f=girvan_newman(1,forum_g);
	    cout<<"Forum_id:"<<forum_pairs[i].ID<<endl;
		cout<<"Found "<<com_two_f->return_size_com()<<" communities"<<endl;
		for(j=0;j<com_two_f->return_size_com();j++){
			com_two_f->show(j);
		}
		delete com_two_f;
		delete forum_g;
		cout<<endl;
	}
	

}




communities * clique_percolation_method(int k,graph *network){
	int i,j=0,test_id=10;
	int *table,*klikes;
	graph * supergraph=new graph(2,3);
	node * super;
	int count=network->find_k_cliques(k,&klikes);
	while(j<k*count){
        table=new int[k];
		for(i=0;i<k;i++){
			table[i]=klikes[j];
			j++;
		}
		super=new supernode(test_id,table);
		supergraph->insert_node(super);
		test_id++;
	}

	create_edges(k,supergraph);
	communities *com;
	com=communities_alg_one(k,supergraph);
	return com;
}


void create_edges(int k,graph* g){
	int i,start,end,checked,nodes;
    int *sup_s_table,*sup_c_table;
    supernode * sup_s, *sup_c;
    edge *e;
	checked=0;
	nodes=g->nodes_count()-1;
	while(checked<nodes){
		g->deg_reset();
		for(i=0;i<=checked;i++){
			start=g->next_node_id();
		}
		sup_s=dynamic_cast<supernode*>(g->lookupnode(start));
		sup_s_table=sup_s->clique_ids();
		checked++;
		while((end=g->next_node_id())>=0){
			sup_c=dynamic_cast<supernode*>(g->lookupnode(end));
			sup_c_table=sup_c->clique_ids();
			if(match_cliques(k,sup_s_table,sup_c_table)){
				e=new edge(sup_s->get_id());
				g->insert_edge(sup_c->get_id(),e);
				e=new edge(sup_c->get_id());
				g->insert_edge(sup_s->get_id(),e);
			}
		}
	}
}

bool match_cliques(int k,int *array_a,int *array_b){
	int i,j,matches=0;
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			if(array_a[i]==array_b[j]){
				matches++;
			}
		}
	}
	if(matches==(k-1)){
		return true;
	}
	else{
		return false;
	}
}

communities * communities_alg_one(int k,graph *g){
	int id,i,size,*prnt,z=0,l;
	int *community, *dif;
	node_list *tested,*cm,*stop_point;
	communities  *com;
	tested=NULL;
	stop_point=NULL;
	bool test;
	prnt=new int[k];
	int num_of_com=numberOfCCs(g);
	com=new communities(num_of_com);
	g->deg_reset();
	while((id=g->next_node_id())>=0){
		if((tested!=NULL)&&(tested->contains(id)>=0)){
			continue;
		}
		else{
			tested=g->reach_all_nodes(id,&size,tested);
			dif=new int[k*size];
			for(int j=0;j<k*size;j++){
				dif[j]=-1;
			}
			cm=tested;
			while(cm->next!=stop_point){
				prnt=dynamic_cast<supernode*>(cm->get_node())->clique_ids();
				for(i=0;i<k;i++){
					test=member(dif,prnt[i]);
					if(!test){
						dif[z]=prnt[i];
						z++;
					}
				}
				cm=cm->next;
			}
			prnt=dynamic_cast<supernode*>(cm->get_node())->clique_ids();
			for(i=0;i<k;i++){
				test=member(dif,prnt[i]);
				if(!test){
					dif[z]=prnt[i];
					z++;
				}
			}
			stop_point=tested;
			community=new int[z+1];
			for(l=0;l<z;l++){
				community[l]=dif[l];
			}
			community[l]=-1;
			delete []dif;
			com->insert(community);
		}
		z=0;
	}
	delete tested;
	return com;
}

bool member(int * dif,int id){
	int i=0;
	while(dif[i]!=-1){
		if(dif[i]==id){
			return true;
		}
		i++;
	}
	return false;
}

/////////////////////////////////////////////////////
//sunartiseis algorithmou_2

struct remove_ids{
	int left;
	int right;
	struct remove_ids *next;
};

communities *girvan_newman(double fin,graph *network){  //kainourgio parallagi
	communities *com=NULL;
	node * a, *b;
	int ne,nodes,checked=0;
	int l,r;
	int bck_f=0,cll_f=0,bck_s=0,cll_s=0;
	double max_edgebet=0.0,edgebet;
	double max_q=-2.0,q=0.0;
	remove_ids *list,*remove_list;
	remove_list=NULL;
	int removes=0;


	ne=network->edges_count();
	//cout<<"edges:"<<ne<<endl;
	if(ne==0){
		//cout<<"graph has no edges so all nodes are different communities"<<endl;
        com=communities_alg_two(network);
		return com;
	}
	nodes=network->nodes_count();
	//cout<<"nodes:"<<nodes<<endl;
	bck_f=0;
	cll_f=0;
	while(checked<nodes){   //upologismos tou edgebettwennes centrallity gia oles tis akmes tou grafou
	    l=network->next_node_id(&bck_f,&cll_f);
		bck_s=bck_f;
		cll_s=cll_f;
		checked++;
    	while((r=network->next_node_id(&bck_s,&cll_s))>=0){
            edgebet=edgebetweennessCentrality(network->lookupnode(l),network->lookupnode(r),network);
			if(edgebet!=-1){
				if(edgebet>max_edgebet){
					max_edgebet=edgebet;
					if(remove_list==NULL){
						remove_list=new remove_ids;
						remove_list->left=l;
						remove_list->right=r;
						remove_list->next=NULL;
					}
					else{
                        while(remove_list->next!=NULL){
							list=remove_list;
							remove_list=remove_list->next;
							delete list;
						}
						remove_list->left=l;
						remove_list->right=r;
					}
				}
				else if(edgebet==max_edgebet){
                    list=new remove_ids;
					list->left=l;
					list->right=r;
					list->next=remove_list;
					remove_list=list;
				}
			}
		}
	}
	list=remove_list;
	while(list!=NULL){
		removes++;
    	//cout<<"("<<list->left<<","<<list->right<<")"<<"has max edgebettweness:"<<max_edgebet<<endl;
    	a=network->lookupnode(list->left);
		b=network->lookupnode(list->right);
		a->remove_edge(list->right);
		b->remove_edge(list->left);
    	list=list->next;
	}
	ne=ne-2*removes;
	if(ne<=0){
        com=communities_alg_two(network);
        return com;
	}
	while(!modularity(ne,fin,network,&q)){
		if(q>max_q){
			max_q=q;
			//cout<<"MAX_Q:"<<max_q<<endl;
			if(com!=NULL){
				delete com;
			}
			com=communities_alg_two(network);
			/*cout<<"Found "<<com->return_size_com()<<" communities"<<endl;  //gia ektuposi kalhterou community (na to bgalo)
			for(int i=0;i<com->return_size_com();i++){
				com->show(i);
			}*/
		}
		max_edgebet=0;
		checked=0;
		while(remove_list!=NULL){  
			list=remove_list;
			remove_list=remove_list->next;
			delete list;
		}
		remove_list=NULL;
		bck_f=0;
		cll_f=0;
		while(checked<nodes){   //upologismos tou edgebettwennes centrallity gia oles tis akmes tou grafou
		    l=network->next_node_id(&bck_f,&cll_f);
			bck_s=bck_f;
			cll_s=cll_f;
			checked++;
			while((r=network->next_node_id(&bck_s,&cll_s))>=0){
            	edgebet=edgebetweennessCentrality(network->lookupnode(l),network->lookupnode(r),network);
				if(edgebet!=-1){
					if(edgebet>max_edgebet){
						max_edgebet=edgebet;
						if(remove_list==NULL){
							remove_list=new remove_ids;
							remove_list->left=l;
							remove_list->right=r;
							remove_list->next=NULL;
						}
						else{
                            while(remove_list->next!=NULL){
								list=remove_list;
								remove_list=remove_list->next;
								delete list;
							}
							remove_list->left=l;
							remove_list->right=r;
						}
					}
					else if(edgebet==max_edgebet){
                    	list=new remove_ids;
						list->left=l;
						list->right=r;
						list->next=remove_list;
						remove_list=list;
					}
				}
			}
		}
		removes=0;
		list=remove_list;  
		while(list!=NULL){
			removes++;
    		//cout<<"("<<list->left<<","<<list->right<<")"<<"has max edgebettweness:"<<max_edgebet<<endl;
    		a=network->lookupnode(list->left);
			b=network->lookupnode(list->right);
			a->remove_edge(list->right);
			b->remove_edge(list->left);
    		list=list->next;
		}
		ne=ne-2*removes;
		if(ne<=0){  //kainourgia
			while(remove_list!=NULL){  
				list=remove_list;
				remove_list=remove_list->next;
				delete list;
			}
			//cout<<"MAX_Q:"<<max_q<<endl;
			return com;
		}
	}
	if(com==NULL){
        while(remove_list!=NULL){  
			list=remove_list;
			remove_list=remove_list->next;
			delete list;
		}
		com=communities_alg_two(network);
		return com;
	}
	else{
        //cout<<"MAX_Q:"<<max_q<<endl;
		return com;
	}
}

communities * communities_alg_two(graph *g){
	int j=0,z=0;
	int size;
	int id_a;
	int num_of_com;
	node_list *tested,*cm,*stop_point=NULL;
	int * community;
	num_of_com=numberOfCCs(g);
	tested=NULL;
	g->deg_reset();
	communities *com=new communities(num_of_com); 
	while((id_a=g->next_node_id())>=0){
	    if(tested!=NULL && (tested->contains(id_a))>=0){
			continue;
		}
		else{       
			tested=g->reach_all_nodes(id_a,&size,tested);
			community=new int[size+1]; //to +1 gia na xoraei kai to -1 oste na blepoume pou teleionei o pinakas
			community[j]=id_a;
			j++;
			cm=tested;
			while(cm->next!=stop_point){
				community[j]=cm->next->get_node()->get_id();
				j++;
				cm=cm->next;
			}
			community[j]=-1; //deixnei oti to proigoumeno itan to teleutaio id tou community
			com->insert(community);
			stop_point=tested;
			z=0;
			j=0;
		}
	}
	delete tested;
	return com; 
}

bool modularity(int m,double x,graph * g,double * max_q){
	double q,sum=0.0,grade;
	bool flag;
	int gradef,gradesec;
	int f,nodes;
	node * first,*second;
	result_set * rs;
	Pair pa;
	nodes=g->nodes_count();
	g->deg_reset();
	for(int i=0;i<nodes;i++){
        f=g->next_node_id();
        first=g->lookupnode(f);
        gradef=first->edge_count();
		rs=g->reach_all_nodes(f);
		while(rs->next()!=false){
			pa=rs->get_result();
			second=g->lookupnode(pa.ID);
			gradesec=second->edge_count();
			flag=knows(first,pa.ID);
			grade=double(gradef)*double(gradesec)/double(m);
			if(flag){
				sum=1.0-grade+sum;
			}
			else{
				sum=sum-grade;
			}
		}
	}
	q=(sum/2)*(1.0/double(m));  
	*max_q=q;
	//cout<<"Q:"<<q<<endl;
	if(q>=x){
		return true;
	}
	else{
		return false;
	}
}



bool knows(node * a,int id){
	int * neighbors,count;
	count=a->get_neighbors(&neighbors);
	for(int i=0;i<count;i++){
		if(neighbors[i]==id){
			return true;
		}
	}
	return false;
}











