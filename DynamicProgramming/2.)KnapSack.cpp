#include<bits/stdc++.h>
#define int long long int
using namespace std;

/*
----------Problem Statement-----------

Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items respectively. Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item or don’t pick it (0-1 property).

*/

class Solution{
public:
	int KnapSack(vector<int> &weights, vector<int> &values, int size);
};

int Solution::KnapSack(vector<int> &weights, vector<int> &values, int size){
	vector<int> dp(size + 1);
	int n = weights.size();
	for(int i=0;i<n;i++){
		for(int wt = size; wt >= 0; wt--){
			if(weights[i] <= wt){
				dp[wt] = max(dp[wt], dp[wt-weights[i]] + values[i]);
			}
		}
	}
	return dp[size];
}

signed main(){
	int n, x;
	cin >> n;
	vector<int> weights, values;
	for(int i =0;i<n;i++){
		cin >> x;
		weights.push_back(x);
	}
	for(int i=0;i<n;i++){
		cin >> x;
		values.push_back(x);
	}
	int size;
	cin >> size;
	Solution S;
	cout << "Maximum Value: " << S.KnapSack(weights, values, size) << endl;
}