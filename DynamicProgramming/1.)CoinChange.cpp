#include<bits/stdc++.h>
#define int long long int
using namespace std;


/*
----------Problem Statement-----------

Given a value N, if we want to make change for N cents, and we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins, how many ways can we make the change? The order of coins doesn’t matter.

*/

class Solution{
public:
	int CoinChange(vector<int> &, int &);
};

int Solution::CoinChange(vector<int> &coins, int &amount){
	vector<int> dp(amount+1);
	dp[0] = 1;
	for(int coin : coins){
		for(int i =1;i<=amount;i++){
			if(i >= coin){
				dp[i] += dp[i - coin];
			}
		}
	}
	return dp[amount];
}

signed main(){
	int n;
	cin >> n;
	vector<int> coins;
	for(int i=0;i<n;i++){
		int x;
		cin >> x;
		coins.push_back(x);
	}
	int amount;
	cin >> amount;
	Solution S;
	cout << "Number of Ways: " << S.CoinChange(coins, amount) << endl;
}