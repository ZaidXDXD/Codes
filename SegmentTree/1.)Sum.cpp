#include<bits/stdc++.h>
#define int long long int
using namespace std;



/*
-----------PROBLEM STATEMENT--------------

We have an array arr[0 . . . n-1]. We should be able to 
1 Find the sum of elements from index l to r where 0 <= l <= r <= n-1
2 Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.

*/

class Tree{
	int n, size; 
	vector<int> arr;
	vector<int> tree;

	int getSize(int n){
		// Formula

		// 2*(2^(log2(n))) - 1;
		
		int m = (int)ceil(log2(n));
		int x = (int)pow(2, m);
		return 2*x - 1; 
	}

	int getMid(int s, int e){
		return s + (e - s)/2;
	}

	void Build(int, int, int);
	int getSumHelper(int, int, int, int, int);
	void Upgrade(int, int, int, int, int);
public:
	Tree(int n){
		this->n = n;
		size = getSize(n);
		tree.resize(size, -1);
	}
	void pushInarr(int x){
		arr.push_back(x);
	}
	void Create();
	int getSum(int, int);
	void Update(int, int);
	void PrintTree();
};

void Tree::PrintTree(){
	for(int at : tree){
		if(at == -1)
			cout << "NULL, ";
		else 
			cout << at << ", ";
	}
	cout << endl;
}

void Tree::Upgrade(int s, int e, int idx, int diff, int at){
	if(idx < s || idx > e || s > e)
		return;
	tree[at] += diff;
	int mid = getMid(s, e);
	if(s < e){
		Upgrade(s, mid, idx, diff, 2*at+1);
		Upgrade(mid+1, e, idx, diff, 2*at+2);	
	}
	
}

void Tree::Update(int idx, int val){
	if(idx < 0 || idx >= n)
		return;
	int diff = val - arr[idx];
	arr[idx] = val;
	Upgrade(0, n-1, idx, diff, 0);
}

int Tree::getSumHelper(int s, int e, int l, int r, int at){
	if(l <= s && e <= r){
		return tree[at];
	}
	if(s > r || e < l || s > e)
		return 0;
	int mid = getMid(s, e);
	return getSumHelper(s, mid, l, r, 2*at+1) + getSumHelper(mid+1, e, l, r, 2*at+2);
}

int Tree::getSum(int l, int r){

	// General Rule
	// l <= s <= e <= r

	return getSumHelper(0, n-1, l, r, 0);
}

void Tree::Build(int s, int e, int at){
	if(s == e){
		tree[at] = arr[s];
		return;
	}
	int mid = getMid(s, e);
	Build(s, mid, 2*at+1);
	Build(mid+1, e, 2*at+2);
	tree[at] = tree[2*at+1] + tree[2*at+2];
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
	cout << "Sum From " << l << " to " << r << " is " << ST.getSum(l, r) << endl;
	int idx, val;
	cin >> idx >> val;
	ST.Update(idx, val);
	cout << "After Update : ";
	ST.PrintTree();
}