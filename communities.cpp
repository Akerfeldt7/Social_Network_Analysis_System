#include "headers/graph.hpp"
#include "headers/extras.hpp"

communities::communities(int size){
	cm_num=size;
	members=NULL;
	if(size>0){
		members=new int *[size];
		for(int i=0;i<size;i++){
			members[i]=NULL;
		}
	}
}

communities::~communities(){
	//cout<<"delete communities"<<endl;
	if(members!=NULL){
		delete [] members;
	}
}

void communities::insert(int * table){
	if(members!=NULL){
		for(int i=0;i<cm_num;i++){
			if(members[i]==NULL){
				members[i]=table;
				//cout<<"ebala stin thesi "<<i<<" to community"<<endl;
				break;
			}
		}
	}
}

/*void communities::show(int point){
	int i=0;
	if(point>=cm_num || point<0){
		cout<<"Wrong input"<<endl;
	}
	else{
		while(members[point][i]!=-1){
                cout<<"community "<<point<<" has node:"<<members[point][i]<<endl;
                i++;
		}
	}
}*/

void communities::show(int point){
	int i=0;
	if(point>=cm_num || point<0){
		cout<<"Wrong input"<<endl;
	}
	else{
        cout<<"community "<<point<<" has node:";
		while(members[point][i]!=-1){
                cout<<members[point][i]<<" ";
                i++;
		}
		cout<<endl;
	}
}


int communities::return_size_com(){
	return cm_num;
}

bool communities::same_community(int a,int b){
	int j,com_a=-1,com_b=-1;
	for(int i=0;i<cm_num;i++){
		j=0;
		while(members[i][j]!=-1){
			if((members[i][j]==a)){
				com_a=i;
			}
			else if(members[i][j]==b){
               com_b=i;
			}
			j++;
		}
		if(com_a!=-1 && com_b!=-1){
			return true;
		}
		else if( (com_a!=-1 && com_b==-1) || (com_b!=-1 && com_a==-1) ){
			return false;
		}
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
