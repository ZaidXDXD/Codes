#include<bits/stdc++.h>
#define int long long int
using namespace std;

/*
-----------PROBLEM STATEMENT--------------

We have an array arr[0 . . . n-1]. We should be able to 
1 Find the maximum pair sum of elements from index l to r where 0 <= l <= r <= n-1
2 Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.

*/

class Node{
public:
	int MaxVal;
	int MaxSum;
	Node(){
		MaxVal = INT_MIN;
		MaxSum = INT_MIN;
	}
};

class Tree{
	int n, size;
	vector<int> arr;
	vector<Node> tree;
	
	int getMid(int s, int e){
		return s + (e - s)/2;
	}

	int getSize(int n){
		// Formula Used
		// 2*(2^(log2(n))) - 1;
		int m = (int)(ceil(log2(n)));
		int x = (int)(pow(2, m));
		return 2*x - 1; 
	}
	void Build(int, int, int);

	Node Compare(Node a, Node b){
		Node ans;
		ans.MaxSum = max(a.MaxVal+b.MaxVal, max(a.MaxSum, b.MaxSum));
		ans.MaxVal = max(a.MaxVal, b.MaxVal);
		return ans;
	}

	Node getMaxPairSumHelper(int, int, int, int, int);
	void Upgrade(int, int, int, int, int);
public:
	Tree(int n){
		this->n = n;
		size = getSize(n);
		tree.resize(size);
	}
	int pushInarr(int x){
		arr.push_back(x);
	}

	void Create();
	int getMaxPairSum(int, int);
	void Update(int, int);
	void PrintTree();
};

void Tree::PrintTree(){
	for(Node it: tree){
		if(it.MaxVal == INT_MIN && it.MaxSum == INT_MIN){
			cout << "NULL, ";
		}
		else{
			cout << "Val->" << it.MaxVal << " Sum->" << it.MaxSum << ", ";
		}
	}
	cout << endl;
}

void Tree::Upgrade(int s, int e, int idx, int val, int at){
	if(s == e){
		arr[s] = val;
		tree[at].MaxVal = val;
		tree[at].MaxSum = 0;
		return;
	}
	int mid = getMid(s, e);
	if(idx <= mid){
		Upgrade(s , mid, idx, val, 2*at+1);
	}
	else{
		Upgrade(mid+1, e, idx, val, 2*at+2);
	}
	tree[at] = Compare(tree[2*at+1], tree[2*at+2]);
}

void Tree::Update(int idx, int val){
	if(idx < 0 || idx >= n)
		return;
	Upgrade(0, n-1, idx, val, 0);
}

Node Tree::getMaxPairSumHelper(int s, int e, int l, int r, int at){
	if(l <= s && e <= r)
		return tree[at];
	Node Temp;
	if(s > e || s > r || e < l)
		return Temp;
	int mid = getMid(s, e);
	return Compare(getMaxPairSumHelper(s, mid, l, r, 2*at+1), getMaxPairSumHelper(mid+1, e, l, r, 2*at+2));
}

int Tree::getMaxPairSum(int l, int r){
	// General Rule
	// l <= s <= e <= r
	return getMaxPairSumHelper(0, n-1, l, r, 0).MaxSum;
}

void Tree::Build(int s, int e, int at){
	if(s == e){
		tree[at].MaxVal = arr[s];
		tree[at].MaxSum = 0;
		return;
	}
	int mid = getMid(s, e);
	Build(s, mid, 2*at+1);
	Build(mid+1, e, 2*at+2);
	tree[at] = Compare(tree[2*at+1], tree[2*at+2]);
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
	cout << "Max Pair Sum From " << l << " to " << r << " is " << ST.getMaxPairSum(l, r) << endl;
	int idx, val;
	cin >> idx >> val;
	ST.Update(idx, val);
	cout << "After Update :";
	ST.PrintTree();
}