#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;




// this is the class of the heap, it allocates size of the heap, BUFFER_SIZE

class heap::heap(int size){

	root = new heapnode[size];
	last = 0;
	size = BUFFER_SIZE;
	
}



// the function which executes the building construction

void heap::execute(int x){
	
	root[1].exec_time+=x;



	heapify();
}

  
 //function to swap buildings


void heap::swapbuilding( struct heapnode* a,struct heapnode* b){

	int bnum,exec_time,total_time;
	rbtnode *tmp1,*tmp2;
	

	// logic for swapping numbers of the building 
	bnum = a->bnum;
	a->bnum = b->bnum;
	b->bnum = bnum;

	//logic for swapping execution time
	exec_time = a->exec_time;
	a->exec_time = b->exec_time;
	b->exec_time = exec_time;

    //logic for swapping total construction times
	total_time = a->total_time;
	a->total_time = b->total_time;
	b->total_time = total_time;

    //logic for swapping respective Red black tree pointers
	tmp1 = a->twin;
	tmp2 = b->twin;

	tmp1->twin = b;
	tmp2->twin = a;

	tmp1 = a->twin;
	a->twin = b->twin;
	b->twin = tmp1;

	
}


// insertng new node into the heap
heapnode* heap::insert( int bnum,int exec_time,int total_time,rbtnode* p ){

	int ptr = ++last;

	if(last==size){
		size*=2;
		root = (struct heapnode*)realloc( root,sizeof(struct heapnode)*size );
	}

	root[last].bnum = bnum;
	root[last].exec_time = exec_time;
	root[last].total_time = total_time;
	root[last].twin = p;
	p->twin = &root[ptr];

	// balancing after insert
	while(ptr>1){
		if(root[ptr].exec_time < root[ptr/2].exec_time){
			swapbuilding(&root[ptr],&root[ptr/2]);
			ptr = ptr/2;
		}
		else
			break;
	}
	return &root[ptr];
}


void heap::updateMin( int exec_time ){
	root[1].exec_time = exec_time;
	heapify();
}


//recover heap properties after remove min
void heap::heapify(){
	int i=1,j;
	while(1){
		if(i*2>last )
			break;
		if(i*2+1>last)
			j=i*2;
		else
			j = root[i*2].exec_time < root[i*2+1].exec_time ? i*2:i*2+1;


		if(root[j].exec_time < root[i].exec_time){
			swapbuilding(&root[i],&root[j]);
			i = j;
		}
		else if(root[j].exec_time == root[i].exec_time){
            if(root[i].bnum<=root[j].bnum){
                break;
            }
            else{
                swapbuilding(&root[i],&root[j]);
                i = j;
            }
		}
		else
			break;

	}
}


//remove from top of the heap.
struct heapnode* heap::removeMin(){
	int i=1;

	struct heapnode *result = new heapnode;
	result->bnum = root[i].bnum;
	result->exec_time = root[i].exec_time;
	result->total_time = root[i].total_time;

	root[i].bnum = root[last].bnum;
	root[i].exec_time = root[last].exec_time;
	root[i].total_time = root[last].total_time;

	last--;
	heapify();
	return result;
}

