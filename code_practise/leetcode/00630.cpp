class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        struct course {
            int t, idx;
        };
        struct comp {
            bool operator()(const course &l, const course &r) {
                return (l.t != r.t) ? (l.t < r.t) : (l.idx < r.idx);
            }
        };

        set<course, comp> current;
        sort(courses.begin(), courses.end(),
        [&](const vector<int> &l, const vector<int> &r) {
           return l[1] < r[1];
        });
        int time = 0;
        for (int i = 0; i < courses.size(); ++i) {
            current.insert({courses[i][0], i});
            time += courses[i][0];
            if (time > courses[i][1]) {
                time -= current.rbegin()->t;
                current.erase(*current.rbegin());
            }
        }
        return current.size();
    }
};

/*
Digestion:
let dp[i][t] = opt of S[i ... n], given time t has been spent
Then original problem is dp[0][0].

First sort by deadline, and ith element is the ith earliest deadline course.
At position i, we either take it (greedy argument: if we can take a course,
we can take the course of the earliest deadline)
If we cannot take it, we *should replace it with the longest course scheduled so far*.

Proof:
Let S = {(t_i, d_i)}, i \in {0, 1, ... N - 1} be the ordered sequence of the
task to be scheduled, ordered by deadline d_i.

Let S^k be the first k tasks of S

Let opt(S^i) be the set of optimial solution having the earliest finish time,
that is,
\forall alpha \in schedule seq of S^i,
\forall beta \in opt(S^i):
    |alpha| > |opt(S^i)| or F(alpha) >= F(opt(S^i)).

The above algorithm maintains the invariant current \in opt(S^i)
Proof.
1. Base:
   time is 0 and set is empty,
   - if t_0 <= d_0 then the invariant is true trivially
   - if t_0 > d_0, no possible job to be scheduled, and line 24 will remove the
     inserted job.

2. Induction:
   assume we have current \in opt(S^i)
   -  if task i+1 is compatitble with current, we append it to the end, giving us
      current'.
      We argue current' is now optimal because |current'| = |current| + 1, and the
      optimal size can only grow at most by 1 when you have one more task to schedule.
      (details why?)
      We further argue this current' has earliest finishing time, because if you have
      a better finish time schedule alpha for S^{i + 1}
      - if alpha does not have task i + 1, contradiction.
      - if alpha has task i + 1, remove it, you obtain a schedule for S^i has better
      finish time than current. contradiction.
   -  if taks i + 1 is not compatitble with current, we argue that we cannot have
      an optimial of size |current| + 1 for S^{i+1}.
      this is because, if we do, say, alpha
      - if alpha does not have task i + 1, contradiction.
      - if alpha has task i + 1, remove it, you obtain a schedule beta for S^i,
         whose finish time F(beta) + t_{i+1} <= d_{i+1}.
         however, as task i + 1 is not compatitble:
         F(current) + t_{i + 1} > d_{i + 1}
         ==> F(beta) <= d_{i+1} - t_{i + 1} < F(current)
         contradiction to the fact that current has the earliest finish time.
      Now, as the optimal cannot have size m + 1 for S^{i + 1}, the best we
      can do is size m. To get the earliest finishing time optimal schedule
      for S^{i + 1}, we simply remove the longest task in current \union
      {task_{i + 1}}. We argue this is the earliest, because if we have a better
      earliest schedule alpha
      - if alpha does not have task i + 1,
        - if the longest is task_{i + 1}, then current' = current, and
          F(alpha) < F(current') = F(current)
          contradiction
        - if the longest is not task_{i + 1}, then some longest task in current
          must be removed:
          F(current') = F(current) - t_{longest} + t_{i + 1}
                      < F(current)
          and F(alpha) < F(current') < F(current)
          but alpha does not have task i + 1, so alpha is an optimal for S^i,
          having finish time earlier than F(current), contradiction.
      - if alpha have task i + 1
        - if the longest is not task_{i + 1}, then some longest task in current
          must be removed:
          F(current') = F(current) - t_{longest} + t_{i + 1}
                      < F(current)
        - if the longest is task_{i + 1}
        // TODO

*/