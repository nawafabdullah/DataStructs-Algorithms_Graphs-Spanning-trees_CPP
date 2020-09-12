//
// unionfindQU.cpp
// Stubs provided by: Gara Pruesse
// Implementation provided by: Noah Alharbi
// Date: November 2017
//
// This unionfind class implements disjoint sets as an array of integers 
//  The implmentation is the classic "Quick-Find" implementation,
//  wherein the name of the set containing each element is stored 
//  in the "parent" array indexed by element name -- thus 
//  to find the set containing element 5, look up parent[5]
//  
//  Merge (union) involves renaming the parent of all the elements of 
//  one set to have the name of the other set (always the one with the smaller
//  element-name).
//
#include "unionfind.h"


unionfind::unionfind(int k)
{
//set array size 
  n = k;
//allocate new memory space for the parent array  
  parent = new int[k];
  for(int i = 0; i < n; i++){
    parent[i] = i;
  }
//allocate memory space for the rank array 
  rank = new int[k];
  for(int i = 0; i < n; i++){
    rank[i] = 0;
  }
}

//destructor intilization to delete both parent and rank array
unionfind::~unionfind(void)
{
  delete [] parent;
  delete [] rank;
}


int unionfind::find(int p )
//finding the set represintitive 
{
  if(parent[p] == p){
    return p;
  }
  parent[p] = find(parent[p]);
  return parent[p];
}


void unionfind::merge(int p, int q)
// merge the 2 sets  
{
  
  int pp= find(p);
  int qq =find(q);

  	if(rank[pp] == rank[qq]){
		rank[pp]++;
		parent[qq] = pp;

  	}else if(rank[pp] > rank[qq]){

		parent[qq] = pp;
 
  	}else if(rank[qq] > rank[pp]){

		parent[pp] = qq;
	}
	
 
}
void unionfind::debugprint()
// display the contents and structure of parent array
{
	for (int i = 0; i < n; i++){
			find(i);
	}
	
  	for(int i = 0; i<n; i++){
    if(parent[i] == i){
      cout <<"[" << i << "]:";
      for (int j = 0; j<n; j++){
			if(parent[j] == i){
	  		 cout << " " << j;
			}
  		}
      cout <<endl;
    }
  }

  

 
}
