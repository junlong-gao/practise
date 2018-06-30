#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/*
 * partition by arr[r - 1] and return its placement index when l < r.
 * in particular idx - l + 1 gives a lower bound on how many elements in
 * arr[l...r) is <=- A[r - 1]
 */
int partition(vector<int> &arr, int l, int r) {
   if (l == r) assert(0);
   if (l == r - 1) return l;
   int i = l - 1;
   int p = arr[r - 1];
   for (int j = l; j < r - 1; ++j) {
      if (arr[j] <= p) {
         i++;
         swap(arr[i], arr[j]);
      }
   }
   swap(arr[i + 1], arr[r - 1]);
   return i + 1;
}

int selection(vector<int> &arr, int l, int r, int rank) {
   if (l == r) assert(0);
   if (l == r - 1) {
      assert(rank == 1);
      return arr[l];
   }

   int idx = partition(arr, l, r);
   int count = idx - l + 1;
   if (count == rank) {
      return arr[idx];
   } else if (count < rank) {
      return selection(arr, idx + 1, r, rank - count);
   } else {
      return selection(arr, l, idx, rank);
   }
   assert(0);
}

int sel(vector<int> &arr, int rank) {
   return selection(arr, 0, arr.size(), rank);
}

int main() {
   {
      vector<int> t{1, 3, 2}, e{1, 2, 3};
      int ret = partition(t, 0, t.size());
      assert(t == e);
      assert(ret == 1);
   }
   {
      vector<int> t{1, 2, 1}, e{1, 1, 2};
      int ret = partition(t, 0, t.size());
      assert(t == e);
      assert(ret == 1);
   }
   {
      vector<int> t{3, 1, 2}, e{1, 2, 3};
      int ret = partition(t, 0, t.size());
      assert(t == e);
      assert(ret == 1);
   }
   {
      vector<int> t{5,4,3,3,2, 1};
      assert(sel(t, 1) == 1);
      assert(sel(t, 2) == 2);
      assert(sel(t, 3) == 3);
      assert(sel(t, 4) == 3);
      assert(sel(t, 5) == 4);
      assert(sel(t, 6) == 5);
   }
   cout << "Passed..." << endl;
   return 0;
}
