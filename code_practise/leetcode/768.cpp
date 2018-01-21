class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
      vector<int> tmp = arr;
      sort(tmp.begin(), tmp.end());
      unordered_map<int, deque<int>> inverse;
      for (int i = 0; i < tmp.size(); ++i) {
        inverse[tmp[i]].push_back(i);
      }
      int ma = -1;
      int count = 0;
      vector<bool> bitmap(arr.size() + 1, false);
      for (int i = 0; i < arr.size(); ++i) {
        int index = inverse[arr[i]].front();
        inverse[arr[i]].pop_front();
        if (ma < index) {
          ma = index;
        }
        bitmap[index] = true;
        bool canSplit = true;
        for (int rank = 0; rank <= ma; ++rank) {
          if (!bitmap[rank]) canSplit = false;
        }
        if (canSplit) {
          count ++;
        }
      }
      return count;
    }
};
