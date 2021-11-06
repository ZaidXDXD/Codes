#include<bits/stdc++.h> 
#define int long long int
using namespace std;


/*
-----------PROBLEM STATEMENT--------------

We have an array arr[0 . . . n-1]. We should be able to 
1 Find the count of odd and even number of elements from index l to r where 0 <= l <= r <= n-1
2 Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.

*/


class Node{
public:
	int odd, even;
	Node(){
		odd = 0;
		even = 0;
	}
	Node operator + (Node const &a){
		Node result;
		result.odd = odd + a.odd;
		result.even = even + a.even;
		return result;
 	}
};


class Tree{
	int n, size;
	vector<int> arr;
	vector<Node> tree;
	
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
	void Build(int, int, int);
	Node getCountHelper(int, int, int, int, int);
	void Upgrade(int, int, int, int, int);
public:
	Tree(int n){
		this->n = n;
		size = getSize(n);
		tree.resize(size);
	}
	void pushInarr(int x){
		arr.push_back(x);
	}
	void Create();
	Node getCount(int, int);
	void PrintTree();
	void Update(int, int);
};

void Tree::Upgrade(int s, int e, int idx, int val, int at){
	if(s == e){
		arr[s] = val;
		if(val%2){
			tree[at].odd = 1;
			tree[at].even = 0;
		}
		else{
			tree[at].odd = 0;
			tree[at].even = 1;
		}
		return;
	}
	int mid = getMid(s, e);
	if(idx <= mid){
		Upgrade(s, mid, idx, val, 2*at+1);
	}
	else{
		Upgrade(mid+1, e, idx, val, 2*at+2);
	}
	tree[at] = tree[2*at+2] + tree[2*at+1];
}

void Tree::Update(int idx, int val){
	if(idx < 0 || idx >= n)
		return;
	Upgrade(0, n-1, idx, val, 0);
}

void Tree::PrintTree(){
	for(Node at : tree){
		if(at.odd == 0 && at.even == 0)
			cout << "NULL, ";
		else
			cout << "odd: " << at.odd << " even: " << at.even << ", ";
	}
	cout << endl;
}

Node Tree::getCountHelper(int s, int e, int l, int r, int at){
	if(l <= s && e <= r)
		return tree[at];

	Node temp;
	if(s > e || s > r || l > e)
		return temp;
	
	int mid = getMid(s, e);
	return getCountHelper(s, mid, l, r, 2*at+1)+getCountHelper(mid+1, e, l, r, 2*at+2);
}

Node Tree::getCount(int l, int r){
	return getCountHelper(0, n-1, l, r, 0);
}
void Tree::Build(int s, int e, int at){
	if(s == e){
		if(arr[s]%2){
			tree[at].odd = 1;
		}
		else{
			tree[at].even = 1;
		}
		return;
	}
	int mid = getMid(s, e);
	Build(s, mid, 2*at+1);
	Build(mid+1, e, 2*at+2);
	tree[at] = tree[2*at+1] + tree[2*at+2];
}

void Tree::Create(){
	// General Rule
	// l <= s <= e <= r
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
	cout << "Number of Odd numbers from " << l << " to " << r << " is " << ST.getCount(l, r).odd << endl;
	cout << "Number of Even numbers from " << l << " to " << r << " is " << ST.getCount(l, r).even << endl;
	int idx, val;
	cin >> idx >> val;
	ST.Update(idx, val);
	cout << "After Update: ";
	ST.PrintTree();
}