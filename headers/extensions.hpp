#ifndef EXTEN_INC
#define EXTEN_INC


#include <iostream>
#include "graph.hpp"

using namespace std;


class person : public node{
 private:
	string name;
	string surname;
	bool gender;
	int age;
 public:
	person(int,string,string,bool,int);
	~person();
	void print_properties();
	string get_type();
	int get_gender();
	int get_age();
	int job(int**);
	int university();
	int place();
	int interests(int**);
	int liked_posts(int**);
	int get_comments(int**);
	bool has_friend(int);
	
};

class organization : public node{
 private:
	string type;
	string name;
 public:
	organization(int,string,string);
	~organization();
	void print_properties();
	string get_type();
};

class place : public node{
 private:
	string name;
	string type;
 public:
	place(int,string,string);
	~place();
	void print_properties();
	string get_type();
};

class tag : public node{
 private:
	string name;
 public:
	tag(int,string);
	~tag();
	void print_properties();
	string get_type();
	string get_tag();
};


class post : public node{
 private:
	int creator;
	int conforum;
 public:
	post(int,int,int);
	~post();
	void print_properties();
	string get_type();
	int get_creator();
	int get_forum();
};


class comment : public node{
 private:
	int creator;
	int compost;
 public:
	comment(int,int,int);
	~comment();
	void print_properties();
	string get_type();
	int get_creator();
	int reply_of();
};

class forum : public node{
 private:
	string title;
 public:
	forum(int,string);
	~forum();
	void print_properties();
	string get_title();
	string get_type();
	bool has_member(int);
	int get_members(int**);
	int get_posts(int**);
};



class supernode : public node{
 private:
	int *clique;
 public:
	supernode(int,int*);
	~supernode();
	int *clique_ids();
	string get_type();
};

////////////////////////////////

class relation : public edge{
 private:
	string type;
 public:
	relation(int,int,string);
	relation(int,int,string,double);
	~relation();
	string get_type();
};



#endif /* EXTE_INC */
