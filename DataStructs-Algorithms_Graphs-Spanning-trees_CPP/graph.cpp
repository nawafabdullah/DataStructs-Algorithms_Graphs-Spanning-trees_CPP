/****************************************************************
/*            Noah Alharbi 
			  graph.cpp
/*            by Gara Pruesse
/*            Nov 16, 2017		  
/*            reads a graph in from a file
/*            builds graph, provides graph access routines
/*            and computes a Minimum Spanning Tree, using a function passed in
/*            
/*********************************************************************/

#include <queue>  // used in first prototype for minSpanningTree 
#include "graph.h"
#include "unionfind.h"

using namespace std;

// int NO_VERTEX=-1;

graph::graph()
{
	n=0;
}

graph::graph(int numverts)
{
   n=numverts;
   Adj = new vector<edge>[n];
}

// There are two ways to build a graph: one is to declare a graph using
// graph(n) and then using add_edge to add all the edges individually.
// The other is to intialize the graph without specifying n, and then 
// using the graph's method graph_read to read data from the file. 
// 5
// 0 1 100
// 3 2 450
// 5 5 5 
// The above is a sample of the contents of a file; in this case, the 
// graph will have five vertices 0, 1, 2, 3, 4, and edges (0,1) of weight 100
// and (2,3) of weight 450.  Any first integer of 5 or greater ends the graph data.
int graph::graph_read(char *fn)
{
   ifstream f;
   int u, v, w;
   

   f.open(fn);
   if (!f) { 
      cerr<<"File not openable. "<<endl; return 0;
      }
   f >> n;   
   cout << n<< endl; // n is the 
   Adj = new vector<edge>[n];

   f >> u;

   while (u<n && f)
   {
      // FOR YOU TO DO: read the vertex u is adjacent to, and the weight, and put in e
	  f >> v;
	  f >> w;
	  add_edge(u, v, w);
	  f >> u; // read the start of the next line
	
   }

   f.close();
   return 1;
}

graph::~graph()
{
   for (int v=0; v<n; v++)
   {
	   Adj[v].clear();
   }
} 
int graph::add_edge(int u, int v, int w)
// A stub
{    
	  edge e;
	  e.vertex1 = u;
	  e.vertex2 = v;
	  e.weight = w;
      // insert e into u's adjacency list
	  Adj[u].push_back(e);

	  e.vertex1 = v;
	  e.vertex2 = u;
      Adj[v].push_back(e);
	 
      return 1;
}


int graph::remove_edge(int u, int v)
// A stub
{   
  
	vector<edge>::iterator curr = Adj[u].begin(); 
	while(curr != Adj[u].end()){
		if((*curr).vertex2 == v){
			Adj[u].erase(curr);
	   	break;
		}
	curr++;
	}	
	
	return 1;
}

int graph::adjacent(int u, int v)
// A stub
{
	
 	return 1;		
}

// call print_vertex on each vertexin the graph
bool graph::print_graph()
{
   for (int v=0; v<n; v++)
   {
        print_vertex(v);
   }
   return true;
}

bool graph::print_vertex(int v)
{

   vector<edge>::iterator currneighb = Adj[v].begin();
   cout << v << ": ";
   while (currneighb != Adj[v].end()) 
   {
   	cout << (*currneighb).vertex2<< "  ";
   	currneighb ++;
   }
   cout << endl;
   return true;
}


/**********************************************************
 *             Minimum Spanning Tree 
 *
 **********************************************************/

graph graph::min_spanning_tree(int v)
// Returns a Minimum Spanning Tree; v is the start vertex.  
// For the first prototype of this subprogram, just 
// return a spanning tree -- it does not have to be minimum.
{
   graph T = graph(n);

// add some declarations here
   unionfind QU(n);
   int u, w;
 
   // NOT MINIMUN SPANNING TREE YET
   int num_edges = 0;
   int Tweight = 0;

   // consider each edge in turn: all those incident with v, v+1, etc. until n-1 
   // edges have been added or all the vertices have been considered (i.e., all 
   // edges considered.  Let Tweight be the total weight of the tree.
   int vert = v%n;
   vector<edge>::iterator e_ptr;

   
	
   for ( vert=v%n;  (vert != v-1) && num_edges < n-1; vert=(vert+1)%n) {
            // YOU PUT SOME INTERESTING CODE HERE.
			e_ptr = Adj[vert].begin(); 
		 	while(e_ptr != Adj[vert].end()){
				 	u = (*e_ptr).vertex2;
                    w = (*e_ptr).weight;
				if(QU.find(vert) != QU.find(u)){
					 
					QU.merge(vert, u);
					T.add_edge(vert, u, w);
					T.add_edge(u, vert, w);
					num_edges++;
					Tweight = (w + Tweight);
				}
				
				e_ptr++;
			}
			
		
            // ADD EDGES TO T ONLY IF THEY DO NOT FORM A CYCLE.
            // HOW WILL YOU BE ABLE TO TELL IF THE NEXT EDGE YOU
            // ARE CONSIDERING WILL FORM A CYCLE WITH WHAT HAS 
            // HAS ALREADY BEEN ADDED TO T?
		
      if (num_edges == n-1)  break;
	 
   }

   if (num_edges<n-1) 
      cout << "Graph was not connected. "<<n-num_edges<<" connected components.\n";
   cout << "Tree weight = "<<Tweight<< endl;
   return T;
}


            


         

