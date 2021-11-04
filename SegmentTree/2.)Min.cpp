#include<bits/stdc++.h>
#define int long long int
using namespace std;

/*
-----------PROBLEM STATEMENT--------------

We have an array arr[0 . . . n-1]. We should be able to 
1 Find the minimum of elements from index l to r where 0 <= l <= r <= n-1
2 Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.

*/

class Tree{
	int n, size;
	vector<int> arr;
	vector<int> tree;

	int getSize(int n){

		// Formula Used
		// 2*(2^(log2(n))) - 1
		int m = (int)(ceil(log2(n)));
		int x = (int)(pow(2, m));
		return 2*x - 1;
	}

	int getMid(int s, int e){
		return s + (e - s)/2;
	}

	void Build(int , int , int );
	int getMinHelper(int, int, int, int, int);
	void Upgrade(int, int, int, int, int);
public:
	Tree(int n){
		this->n = n;
		size = getSize(n);
		tree.resize(size, INT_MAX);
	}
 	void pushInarr(int x){
 		arr.push_back(x);
 	}

 	void Create();
 	int getMin(int, int);
 	void Update(int, int);
 	void PrintTree();
};

void Tree::PrintTree(){
	for(int i=0;i<size;i++){
		if(tree[i] == INT_MAX)
			cout << "NULL, ";
		else 
			cout << tree[i] << ", ";
	}
	cout << endl;
}

void Tree::Upgrade(int s, int e, int idx, int val, int at){
	if(s == e){
		arr[idx] = val;
		tree[at] = val;
		return;
	}
	int mid = getMid(s, e);
	if(idx <= mid){
		Upgrade(s, mid, idx, val, 2*at+1);
	}
	else{
		Upgrade(mid+1, e, idx, val, 2*at+2);
	}

	tree[at] = min(tree[2*at+1] , tree[2*at+2]);
}

void Tree::Update(int idx, int val){
	if(idx < 0 || idx >= n)
		return;
	Upgrade(0, n-1, idx, val, 0);
}

int Tree::getMinHelper(int s, int e, int l, int r, int at){
	if(l <= s && e <= r)
		return tree[at];
	if(e < l || r < s || s > e)
		return INT_MAX;
	int mid = getMid(s,e);
	return min(getMinHelper(s, mid, l, r, 2*at+1), getMinHelper(mid+1, e, l, r, 2*at+2));
}

int Tree::getMin(int l, int r){
	// General Idea
	// l <= s <= e <= r
	return getMinHelper(0, n-1, l, r, 0);
}

void Tree::Build(int s, int e, int at){
	// cout << s << " " << e << endl;
	if(s == e){
		tree[at] = arr[s];
		return;
	}
	int mid = getMid(s, e);
	Build(s, mid, 2*at+1);
	Build(mid+1, e, 2*at+2);
	tree[at] = min(tree[2*at+1], tree[2*at+2]);
}

void Tree::Create(){
	Build(0, n-1, 0);
}

signed main(){
	int n; 
	cin >> n;
	Tree ST(n);
	for(int i=0;i<n;i++){
		int x;
		cin >> x;
		ST.pushInarr(x);
	}
	ST.Create();
	ST.PrintTree();
	int l, r;
	cin >> l >> r;
	cout << "Smallest in range from " << l << " to " << r << " is " << ST.getMin(l, r) << endl;
	int idx, val;
	cin >> idx >> val;
	ST.Update(idx, val);
	ST.PrintTree();
}