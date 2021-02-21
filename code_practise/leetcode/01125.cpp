class Solution {
    unordered_map<string, int> pos;
    int target = 0;
    vector<int> p;
    int infty = INT_MAX / 2;
    
    void normalizeTarget(vector<string>& req_skills,
                        vector<vector<string>>& people) {
        for (int i = 0; i < req_skills.size(); ++i) {
            pos[req_skills[i]] = i;
            target |= (1 << i);
        }
        p.resize(people.size(), 0);
        for (int i = 0; i < people.size(); ++i) {
            for (int j = 0; j < people[i].size(); ++j) {
                if (pos.count(people[i][j]) == 0) continue;
                p[i] |= (1 << pos[people[i][j]]);
            }
        }
    }
    
    unordered_map<int, unordered_map<int, int>> dp;
    unordered_map<int, unordered_map<int, bool>> c;
    int exclude(int from, int s) {
        return from & (~s);
    }
    
    int sol(int i, int req) {
        if (dp.count(i) && dp[i].count(req)) {
            return dp[i][req];
        }
        
        int &ans = dp[i][req];
        
        if (req == 0)  {
            return ans = 0;
        }
        
        if (i == 0) {
            if (exclude(req, p[i]) == 0) {
                c[i][req] = true;
                return ans = 1;
            } else {
                c[i][req] = false;
                return ans = infty;
            }
        }
        int l = sol(i - 1, exclude(req, p[i])) + 1;
        int r = sol(i - 1, req);
        if (l <= r) {
            c[i][req] = true;
        } else {
            c[i][req] = false;
        }
        return ans = min(l, r);
    }
    
    vector<int> team;
    void constructSol(int n, int req) {
        if (n < 0) return;
        if (c[n][req]) {
            team.push_back(n);
            constructSol(n - 1, exclude(req, p[n]));
        } else {
            constructSol(n - 1, req);
        }
    }
public:
    vector<int> smallestSufficientTeam(
        vector<string>& req_skills, 
        vector<vector<string>>& people) {
        
        normalizeTarget(req_skills, people);
        int s = sol(p.size() - 1, target);
        constructSol(p.size() - 1, target);
        sort(team.begin(), team.end());
        return team;
    }
};
