
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.size()<=1) {
			return 0;
		}
		vector<vector<int>> f(2,vector<int>(prices.size(),0));
		
		for (int k = 0; k < 2; k++) {
			int j = 0;
			for (int i = 1; i < (int)prices.size(); i ++) {
				int temp = f[(k+1)%2][j]-prices[j];
				
				if (f[(k+1)%2][j]-prices[j] < f[(k+1)%2][i] - prices[i]) {
					j = i;
				}
				f[k%2][i] = max(f[(k)%2][i-1], prices[i] + temp);
			}
		}
		
		return f[1][prices.size()-1];
	}
	inline int max(int x, int y){
		return x>y?x:y;
	}
	
};

int main(int argc, const char * argv[]) {
	//vector<int> prices = {2,1,2,0,1};
	//vector<int> prices = {1,2};
	//vector<int> prices = {6,1,3,2,4,7};
	//vector<int> prices = {3,3,5,0,0,3,1,4};
	vector<int> prices = {3,2,6,5,0,3};
	Solution mysolutions;
	mysolutions.maxProfit(prices);
    return 0;
}
