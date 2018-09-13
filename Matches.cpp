#include "headers/graph.hpp"
#include "headers/extras.hpp"


Matches::Matches(int sz,Pair* input){
	int i;
	current=0;
	count=sz;
	results=NULL;
	if(sz>0){
		results=new Pair[sz];
		for(i=0;i<sz;i++){
			results[i]=input[i];
		}
	}
}


Matches::~Matches(){
	if(results!=NULL){
		delete [] results;
	}
}

bool Matches::is_empty(){
	if(!count){
		return true;
	}
	else{
		return false;
	}
}

int Matches::size(){
	return count;
}

void Matches::reset(){
	current=0;
}

int Matches::next_result(int* id){
	int score;
	if(current<count){
		(*id)=results[current].ID;
		score=results[current].distance;
		current++;
		return score;
	}
	else{
		(*id)=-1;
		return 0;
	}
}
	
