#include<bits/stdc++.h>
#define int long long int 
using namespace std;

/* 
------ Problem Statement ---------

Kosaraju Algorithm 

Find Strongly Connected Components

----------Key Idea--------------

1.) SCC remains the same even in a transpose graph.

True Graph:
	
	SCC1 ---> SCC2 ---> SCC3

Transpose Graph 
	
	SCC1 <--- SCC2 <--- SCC3

*/ 

class Graph{
	int nodes, edges;
	vector<vector<int>> graph;
	void DFS(int, vector<bool>&, stack<int>&);
	vector<vector<int>> Transpose();
	void SCCHelper(int, vector<bool> &, vector<int> &, vector<vector<int>> Tgraph);
public:
	Graph(int nodes, int edges){
		this->nodes = nodes;
		this->edges = edges;
		graph.resize(nodes);
	}

	void addEdge(int u, int v){
		graph[u].push_back(v);
	}

	vector<vector<int>> SCC();
};

vector<vector<int>> Graph::Transpose(){
	vector<vector<int>> Tgraph(nodes);
	for(int at=0;at<nodes;at++){
		for(int to: graph [at]){
			Tgraph[to].push_back(at);
		}
	}
	return Tgraph;
}

void Graph::DFS(int at, vector<bool> &visited, stack<int> &S){
	visited[at]=true;
	for(int to: graph[at]){
		if(!visited[to]){
			DFS(to, visited, S);
		}
	}
	S.push(at);
}

void Graph::SCCHelper(int at, vector<bool> &visited, vector<int>& Component, vector<vector<int>> Tgraph){
	visited[at] = true;
	Component.push_back(at);
	for(int to: Tgraph[at]){
		if(!visited[to])
			SCCHelper(to, visited, Component, Tgraph);
	}
}

vector<vector<int>> Graph::SCC(){
	vector<bool> visited(nodes);
	stack<int> S;
	DFS(0, visited, S);
	visited.clear();
	visited.resize(nodes, false);
	vector<vector<int>> Tgraph = Transpose();
	vector<vector<int>> StrongComponents;
	while(!S.empty()){
		int node = S.top();
		S.pop();
		if(visited[node])
			continue;
		vector<int> Component;
		SCCHelper(node, visited, Component, Tgraph);
		StrongComponents.push_back(Component);
	}
	return StrongComponents;
}

signed main(){
	int nodes, edges;
	cin >> nodes >> edges;
	Graph G(nodes, edges);
	int u, v;
	for(int i=0;i<edges;i++){
		cin >> u >> v;
		G.addEdge(u, v);
	}
	vector<vector<int>> sc = G.SCC();
	for(int i =0;i<(int)sc.size(); i++){
		for(int node: sc[i]){
			cout << node << ", ";
		}
		cout << endl;
	}
}