#include <cstdlib>
#include <fstream>
#include "headers/queries.hpp"
#include "headers/graph.hpp"
#include "headers/extras.hpp"
#include "headers/extensions.hpp"
#include "headers/metrics.hpp"


Matches* matchSuggestion(node* n, int k, int h, int x, int limit, graph* g){
	result_set *rset;
	Pair current,*result;
	int id,i,score,matches_found;
	node * current_node;
	string current_type;
	Matches *suggestions;
	id=n->get_id();
	rset=g->reach_all_nodes(id);
	result=new Pair[limit];
	for(i=0;i<limit;i++){
		result[i].ID=-1;
		result[i].distance=0;
	}
	matches_found=0;
	while(rset->next()){
		current=rset->get_result();
		current_node=g->lookupnode(current.ID);
		current_type=current_node->get_type();
		if(current_type.compare("person")){
			continue;
		}
		if(current.distance>=2 && current.distance<=h){
			score=match(n,current_node,k,x,current.distance,h);
			if(score>0){
				matches_found++;
				for(i=0;i<limit;i++){
					if(result[i].distance<score){
						id=current.ID;
						current=result[i];
						result[i].ID=id;
						result[i].distance=score;
						for(i=i+1;i<limit;i++){
							id=result[i].ID;
							score=result[i].distance;
							result[i]=current;
							current.ID=id;
							current.distance=score;
						}
					}
				}
			}
		}
	}
	if(matches_found>0){
		if(matches_found<limit){
			suggestions=new Matches(matches_found,result);
		}
		else{
			suggestions=new Matches(limit,result);
		}
		return suggestions;
	}
	else{
		return NULL;
	}
}


graph* getTopStalkers(int k, int x, int centralityMode, graph* g,graph *pkp,i_d_Pair **ss){
	int id,i;
	double cent;
	node *n;
	edge *edge_pnt;
	string sub_a,sub_b,datastring;
	person *p;
	i_d_Pair temp,*stalkers;
	graph *sgraph;
	ifstream datafile;
	g->deg_reset();
	if(k<1){
		return NULL;
	}
	sgraph=new graph(2,5);
	stalkers=new i_d_Pair[k];
	for(i=0;i<k;i++){
		stalkers[i].int_part=-1;
		stalkers[i].double_part=-1;
	}
	while((id=g->next_node_id())>=0){
		n=g->lookupnode(id);
        p=dynamic_cast<person*>(n);
        if(p==NULL){
			continue;
		}
		else if(is_stalker(p,x,g)){
			if(centralityMode==2){
				cent=betweennessCentrality(p,pkp);
			}
			else{
				cent=closenessCentrality(p,pkp);
			}
			for(i=0;i<k;i++){
				if(stalkers[i].double_part<0){
					stalkers[i].int_part=id;
					stalkers[i].double_part=cent;
					break;
				}
				else if(cent>stalkers[i].double_part){
					temp.int_part=id;
					temp.double_part=cent;
					id=stalkers[i].int_part;
					cent=stalkers[i].double_part;
					stalkers[i]=temp;
				}
			}
		}
	}
	for(i=0;i<k;i++){
		if(stalkers[i].int_part<0){
			break;
		}
		p=dynamic_cast<person*>(g->lookupnode(stalkers[i].int_part));
		n=new person(*p);
		sgraph->insert_node(n);
	}
	datafile.open("data/person_knows_person.csv");
	if(datafile.is_open()){
		getline(datafile,datastring);
		while(!datafile.eof()){
			getline(datafile,datastring);
			if(datastring.length()<3){
				continue;
			}
			i=datastring.find("|");
			sub_a=datastring.substr(0,i);
			sub_b=datastring.substr(i+1);
			id=atoi(sub_a.c_str());
			i=atoi(sub_b.c_str());
			if(sgraph->lookupnode(id)==NULL || sgraph->lookupnode(i)==NULL ){
				continue;
			}
			edge_pnt=new relation(id,i,"knows");
			sgraph->insert_edge(id,edge_pnt);
		}
	}
	else{
		cout<<"input error"<<endl;
	}

	datafile.close();
	(*ss)=stalkers;
	return sgraph;
}


void findTrends(int k, graph* g, string** wt, string** mt){
	int id,i,*tags,fs,ms;
	node *n;
	person *p;
	tag *t;
	Pair *list_m,*list_f;
	string *womenTrends, *menTrends;
	fs=k;
	ms=k;
	list_m=new Pair[k];
	list_f=new Pair[k];
	for(i=0;i<k;i++){
		list_m[i].ID=-1;
		list_m[i].distance=0;
		list_f[i].ID=-1;
		list_f[i].distance=0;
	}
    g->deg_reset();
	while((id=g->next_node_id())>=0){
		n=g->lookupnode(id);
		p=dynamic_cast<person*>(n);
		if(p==NULL){
			continue;
		}
		i=p->interests(&tags);
		if(!i){
			continue;
		}
		if(p->get_gender()){
			fs=add_interests(&list_f,fs,tags,i);
		}
		else{
			ms=add_interests(&list_m,ms,tags,i);
		}
		delete [] tags;
	}
	menTrends=new string[k];
	womenTrends=new string[k];
	for(i=0;i<k;i++){
		//cout<<list_m[i].ID<<" man "<<list_m[i].distance<<endl;
		//cout<<list_f[i].ID<<" woman "<<list_f[i].distance<<endl;
		id=list_m[i].ID;
		n=g->lookupnode(id);
        t=dynamic_cast<tag*>(n);
		if(t!=NULL){
        	menTrends[i]=t->get_tag();
		}
		else{
			cout<<"error "<<id<<endl;
			menTrends[i]="null";
		}
		id=list_f[i].ID;
        n=g->lookupnode(id);
        t=dynamic_cast<tag*>(n);
		if(t!=NULL){
        	womenTrends[i]=t->get_tag();
		}
		else{
			cout<<"error "<<id<<endl;
			womenTrends[i]="null";
		}
	}
	(*wt)=womenTrends;
	(*mt)=menTrends;
	delete [] list_f;
	delete [] list_m;
}



graph* buildTrustGraph(int id_forum, graph* g){
	int size,i,j;
	int m=3;  //initial size of hash_table
	int c=5; //inital size of bucket
	double calc;
	node* n;
	forum * f;
	person *p,*tp;
	edge *edge_pnt;
	graph * trust_graph;
	int *table;
	trust_graph=new graph(m,c);
	n=g->lookupnode(id_forum);
	f=dynamic_cast<forum*>(n);
	size=f->get_members(&table);
	for(i=0;i<size;i++){
        n=g->lookupnode(table[i]);
 		p=dynamic_cast<person*>(n);
		tp=new person(*p);
 		trust_graph->insert_node(tp);
		for(j=0;j<size;j++){
			if(i==j){
				continue;
			}
 			else if(p->has_friend(table[j])){
				calc=trust_calc(p,table[j],id_forum,g);
                edge_pnt=new relation(table[i],table[j],"trust",calc);
				trust_graph->insert_edge(table[i],edge_pnt);
			}
			else{
				continue;
			}
		}
	}
	delete [] table;
	return trust_graph;
}



double estimateTrust(node* a, node* b, graph* trustGraph){
	int i,neighbors_count,con,terminal_depth;
	double terminal_trust,test;
	node *current_node;
	node_list *first_element,*last_element,*current_element,*temp_element;
	i_d_Pair *to_check;
	to_check=NULL;
	current_node=a;
	if(a==b || a==NULL || b==NULL){
		return 0;
	}
	first_element=new node_list(0);
	first_element->hold(current_node);
	first_element->set_weight(1);
	last_element=first_element;
	current_element=first_element;
	terminal_trust=0;
	terminal_depth=0;
	while(current_element!=NULL){
		neighbors_count=current_node->get_neighbors(&to_check);
		for(i=0;i<neighbors_count;i++){
			con=first_element->contains(to_check[i].int_part);
			if((con>=0)&&(con<=current_element->get_depth())){
				continue;
			}
			else if(con<0){
				current_node=trustGraph->lookupnode(to_check[i].int_part);
				if(current_node==NULL){
					cout<<"error: failed to locate node with id "<<to_check[i].int_part<<endl;
					delete[] to_check;
					delete first_element;
					return 0;
				}
				if(current_node==b){
					terminal_depth=current_element->get_depth()+1;
					terminal_trust=to_check[i].double_part*current_element->get_weight();
				}
				last_element->next=new node_list(current_element->get_depth()+1);
				last_element=last_element->next;
				last_element->hold(current_node);
				last_element->set_weight(to_check[i].double_part*current_element->get_weight());
				continue;
			}
			else{
				current_node=trustGraph->lookupnode(to_check[i].int_part);
				temp_element=current_element;
				while(current_node!=temp_element->get_node()){
					temp_element=temp_element->next;
				}
				test=to_check[i].double_part*current_element->get_weight();
				if(test>temp_element->get_weight()){
					temp_element->set_weight(test);
					if(current_node==b){
						terminal_trust=test;
					}
				}
			}
		}
		if(neighbors_count>0){
			delete[] to_check;
			to_check=NULL;
		}
		current_element=current_element->next;
		if(current_element!=NULL){
			current_node=current_element->get_node();
			if(current_element->get_depth()==terminal_depth){
				return terminal_trust;
			}
		}
	}
	if(to_check!=NULL){
		delete[] to_check;
		to_check=NULL;
	}
	delete first_element;
	return terminal_trust;
}




double trust_calc(person *p1 ,int id2,int id_forum,graph *g){
	int likes,i,id1_likes=0,bet_likes=0,id1_comments=0,bet_comments=0,comments;
	double calc_likes=0.0,calc_comments=0.0;
	node *n;
	post * pos;
	int *table,*comment_table;
	likes=p1->liked_posts(&table);
	for(i=0;i<likes;i++){
		n=g->lookupnode(table[i]);
        pos=dynamic_cast<post*>(n);
		if(id_forum==(pos->get_forum())){
			id1_likes++;
			if(id2==(pos->get_creator())){
				bet_likes++;
			}
		}
	}
	comments=p1->get_comments(&comment_table);
	for(i=0;i<comments;i++){
        n=g->lookupnode(comment_table[i]);
        pos=dynamic_cast<post*>(n);
		if(id_forum==(pos->get_forum())){
			id1_comments++;
			if(id2==(pos->get_creator())){
				bet_comments++;
			}
		}
	}
	if(id1_likes!=0){
		calc_likes=(0.3*bet_likes)/id1_likes;
	}
	if(id1_comments!=0){
		calc_comments=(0.7*bet_comments)/id1_comments;
	}
	delete []table;
	delete []comment_table;
	return calc_likes+calc_comments;
}


int add_interests(Pair** itable,int psize,int* ttable,int tsize){
	int i,j,id,count;
	bool found;
	Pair *temp,*ptable;
	ptable=(*itable);
	for(i=0;i<tsize;i++){
		found=false;
		for(j=0;j<psize;j++){
			if(ptable[j].ID==ttable[i]){
				found=true;
				ptable[j].distance=ptable[j].distance+1;
				while( (j>0) && (ptable[j].distance>ptable[j-1].distance)){
					id=ptable[j].ID;
					count=ptable[j].distance;
					ptable[j]=ptable[j-1];
					ptable[j-1].ID=id;
					ptable[j-1].distance=count;
					j--;
				}
				break;
			}
			else if(ptable[j].ID<0){
				found=true;
				ptable[j].ID=ttable[i];
				ptable[j].distance=1;
				break;
			}
		}
		if(!found){
			temp=new Pair[psize+1];
			for(j=0;j<psize;j++){
				temp[j]=ptable[j];
			}
			temp[j].ID=ttable[i];
			temp[j].distance=1;
			psize++;
			delete [] ptable;
			ptable=temp;
			temp=NULL;
		}
	}
	(*itable)=ptable;
	return psize;
}


bool is_stalker(person * p,int x,graph *g){
	int size,i,j,id_creator,creators=0;
	int *table;
	Pair *result;
	post *tpost;
	size=p->liked_posts(&table);
	if(!size){
		return false;
	}
	result=new Pair[size];
	for(i=0;i<size;i++){
		result[i].ID=-1;
		result[i].distance=0;
	}
	for(i=0;i<size;i++){
		tpost=dynamic_cast<post*>(g->lookupnode(table[i]));
		id_creator=tpost->get_creator();
		for(j=0;j<creators;j++){
			if(result[j].ID==id_creator){
				result[j].distance++;
				break;
			}
		}
		if(j==creators){
			result[creators].ID=id_creator;
			result[creators].distance++;
			creators++;
		}
	}
	for(i=0;i<creators;i++){
		if( (result[i].distance>x) && (p->get_id()!=result[i].ID)){
            if(!p->has_friend(result[i].ID)){
				delete [] table;
				delete [] result;
				return true;
			}
		}
	}
	delete [] table;
	delete [] result;
	return false;
}



int comp(int* table_a, int size_a, int* table_b, int size_b){
	int i,j,counter;
	counter=0;
	for(i=0;i<size_a;i++){
		for(j=0;j<size_b;j++){
			if(table_a[i]==table_b[j]){
				counter++;
				break;
			}
		}
	}
	return counter;
}

int match(node *node_a,node *node_b,int min,int max_ad,int distance,int max_dis){
	int i,j,score,*t1,*t2;
	person *p1,*p2;
	p1=dynamic_cast<person*>(node_a);
	p2=dynamic_cast<person*>(node_b);
	if(p1->get_gender()==p2->get_gender()){
		return 0;
	}
	score=0;
	i=p1->job(&t1);
	if(i<min){
		if(i){
			delete [] t1;
		}
		return 0;
	}
	j=p2->job(&t2);
	if(j<min){
		if(i){
			delete [] t1;
		}
		if(j){
			delete [] t2;
		}
		return 0;
	}
	i=comp(t1,i,t2,j);
	if(i){
		delete [] t1;
	}
	if(j){
		delete [] t2;
	}
	if(i==0){
		return 0;
	}
	else{
		score++;
	}
	i=p1->university();
	if((i>=0)&&(i==p2->university())){
		score++;
	}
	i=p1->place();
	if((i>=0)&&(i==p2->place())){
		score++;
	}
	if(!score){
		return 0;
	}
	j=p1->get_age()-p2->get_age();
	if(j<0){
		j=j*(-1);
	}
	if(j>max_ad){
		return 0;
	}
	score=score+max_ad-j;
	i=p1->interests(&t1);
	if(i<min){
		if(i){
			delete [] t1;
		}
		return 0;
	}
	j=p2->interests(&t2);
	if(j<min){
		if(i){
			delete [] t1;
		}
		if(j){
			delete [] t2;
		}
		return 0;
	}
	i=comp(t1,i,t2,j);
	if(i){
		delete [] t1;
	}
	if(j){
		delete [] t2;
	}
	if(i<min){
		return 0;
	}
	score=score+i+(max_dis-distance)/2;
	return score;
}
