/*
Max: K - 1 + W
Min: K
For the final draw:
Pr{ E = K - 1 + W }      = 1 / W * Pr { E = K - 1 }
Pr{ E = K - 1 + W - 1}  = 1 / W * Pr { E = K - 2 } + 1 / W * Pr{ E = K - 1 } 
 		            = Pr { E = K - 1 + W } + 1 / W * Pr { E = K - 2 }
Pr{ E = K - 1 + W - 2}  = 1 / W * Pr { E = K - 3 }  + 1 / W * Pr { E = K - 2 } + 1 / W * Pr{ E = K - 1 }
		            = Pr { E = K - 1 + W - 1}  + 1 / W * Pr { E = K - 3 }
…
Pr { E = K } = 1 / W * \sum{Pr { E = K - j } } where j \in [1, W]

Before final draw:
Pr { E = e } = 1/ W \sum { Pr {E = e - j} } where j \in [1, W] 
Pr { E = e - 1 } = 1/ W \sum { Pr {E = e - 1 - j} } where j \in [1, W]
		= 1/ W \sum { Pr {E = e - k} } where j \in [2, W + 1]
		= 1/ W \sum { Pr {E = e - j} } where j \in [2, W + 1]
Pr { E = e } = 	1/ W \sum { Pr {E = e - j} } where j \in [1, W] 
	       =   1/ W * Pr {E = e - 1} + 1/ W \sum { Pr {E = e - j} } where j \in [2, W] 
	       =  1/ W * Pr {E = e - 1} - 1/W * Pr {E = e - W - 1} + 1/ W \sum { Pr {E = e - j} } where j \in [2, W + 1]
       =  Pr { E = e - 1 } + 1/ W * Pr {E = e - 1} - 1/ W * Pr {E = e - W - 1}
        = ( 1 + 1/ W ) Pr {E = e - 1} - 1/ W * Pr {E = e - W - 1}

Pr { E = 1 } = 1
Pr { E = 2 } = 1 / W + 1 / W * Pr { E = 1}
Pr { E = 3 } = 1 / W + 1 / W * Pr { E = 2 } + 1 / W * 1 / W
	       = 1 / W + 1 / W * (1 / W + 1 / W^2) + 1 / W^2
 	        = 1 / W + 2 / W^2 + 1 / W^3
(1 + 1/ W) * (1 / W + 1 / W^2) = 1 / W + 1 / W ^ 2 + 1 / W ^2 + 1 / W^3


              
*/
class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0|| N == 0) return 1;

vector<double> pr(K + W + 2, 0);
double w = 1 / static_cast<double>(W);
double ret = 0;
        pr[0] = 1;
        pr[1] = w;
         for (int i = 2; i <= K - 1; ++i) {
		double last = 0;
		int prev = i - W - 1;
		if (prev >= 0) {
			last = pr[prev];
		}
		pr[i] = pr[i - 1] * (1 + w) - w * last;
        //cout << pr[i] << endl;
         }
	for (int j = W; j >= 1; --j) {
		int e = K - 1 + j;
		if (e >= 0) {
			pr[e] = w * (e - W >= 0? pr[e - W] : 0) + pr[e + 1];
		}
		if (e <= N) {
			ret += pr[e];
		}
	}
	return ret;
    }
};



