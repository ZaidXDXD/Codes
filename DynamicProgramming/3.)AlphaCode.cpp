#include<bits/stdc++.h>
#define int long long int
using namespace std;

class Solution{
	int MOD = 1e9+7;
public:
	int AlphCode(string);
};

int Solution::AlphCode(string num){
	int n = num.size();
	vector<int> dp(n);
	dp[0]=1; 
	for(int i = 1;i<n;i++){
		int alphabet = (num[i-1]-'0')*10+(num[i]-'0');
		if(num[i] != '0')
			dp[i] = dp[i-1];
		if(alphabet>=10 && alphabet <= 26 && i>1)
			dp[i] += dp[i-2];
		else if(alphabet>=10 && alphabet <=26)
			dp[i] += 1;
		dp[i] = dp[i]%MOD;
	}
	return dp[n-1];
}

signed main(){
	string s;
	cin >> s;
	Solution S;
	cout << "Number of Different Codes: " << S.AlphCode(s) << endl;
}