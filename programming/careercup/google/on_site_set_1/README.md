Problem 1 . given many pairs , output all the conflict pairs
```cpp
struct Interval {
	int index; //event number
	int start;
     int end;
};

bool compare(Interval& a, Interval& b) {
	return a.start == b.start ? a.index < b.index : a.start < b.start;
}

void ConflictPair(vector<Interval>& event, int n) {
	sort(event.begin(), event.end(), compare);
    for (int i = 0; i < len; i++) {
    	int s = i + 1, e = len - 1;
  		int cur = i; 
    	while (s < = e) {
 			int mid = (s + e) / 2;
 			/** check overlap event index **/
 			if (event[mid] .start > event[i].end) {
				end = mid - 1;
 			}
 			else {
				cur = mid;
				s = mid + 1;
 			}
  		}
  		for(int j = i + 1; j <= cur; j++) {
			/***** output the event[i] conflict with the event[j]   ***/
  		}
	}
}
```
Problem 2

UTF-8 Validation

Uses 1-4 bytes to represent a character, subjected to the following rules:

For 1-byte character, the first bit is a 0, followed by its unicode code.
For n bytes character, the first n-bits are all one's, the n+1 bit is 0, followed by n-1 bytes with most significant 2 bits being 10.
Please see this for more details about UTF-8 variable width encoding rules here:
http://stackoverflow.com/a/6339292/490463
```cpp
bool valid_utf8(vector<unsigned char>& data) {
	int count = 0;
	for(auto c : data) {
		if(count == 0) {
	  		/** set the remained the utf-8 char count **/
	  		if((c >> 5) == 0b110)  count = 1;  
	  		else if((c >> 4) == 0b1110)   count = 2;
	  		else if((c >> 3) == 0b11110)  count = 3;
	  		else if((c >> 7))   return false;
	  	} else {
	        if((c >> 6) != 0b10)   return false;
	   		count--;
	  	}
	}
    return count == 0;
}
```
Problem 3 Given a 2d array, find the submatrix which has the largest sum.
```cpp
int max_sub_rect(const vector<vector<int>>& matrix) {
	if(matrix.empty() || matrix[0].empty())  return 0;
	int row = matrix.size(),  col = matrix[0].size();
	vector<vector<int>>  col_sum = matrix;
	   /*** calculate the accumulated sum of the col elements ***/
	for(int i = 1; i < row; i++) {
		for(int j = 0; j < col; j++) {
			col_sum[i][j] += col_sum[i-1][j];
		}
	}
   
    int result = 0;
 	for(int i = 0; i < row; i++) {
		for(int j = 0; j <=i; j++) {
  		int sum = 0;  
			for(int k = 0; k < col; k++) {
	   		/** get the col-sum at col k **/
				int temp = j == 0 ? col_sum[i][k] : col_sum[i][k] - col_sum[j-1][k]; 
				sum += temp;
				result = max(result, sum);
				sum = max(sum , 0);
			}
		}
 	}
 	return result;
}
```
Problem 4 Pacific Atlantic problem
```cpp
void   dfs(Point pt, uunordered_map<Point, bool>& visited, vector<vector<int>>& matrix) {
	vector<Point> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	for(auto dir : dirs) {
		Point new_p = { dir.x + pt.x,  dir.y + pt.y };
		if(new_p.x < 0 || new_p.x >= matrix.size() || 
	                       new_p.y < 0 || new_p.y >= matrix[0].size()){
			continue;
		}
		if(matrix[new_p.x][new_p.y] < matrix[pt.x][pt.y] || visited.count(new_p) {
			continue;
		}
		visited[new_p] = true;
		dfs(new_p, visited, matrix);
	 }
}

vector<Point> flowing_water(vector<vector<int>>& matrix) {
	int n = matrix.size();
	unordered_map<Point, bool> visited_1;
	/*** up ***/
	for(int i = 0; i < n; i++) {
		visited_1[{0, i}] = true;
		search({0, i}, visited_1, matrix);
	}
	/*** left ***/
	for(int i = 0; i < n; i++) {
		visited_1[{i, 0}] = true;
		search({i, 0}, visited_1, matrix);
	}

	unordered_map<Point, bool> visited_2;
	/*** down ***/
	for(int i = 0; i < n; i++) {
		visited_2[{n - 1, i}] = true;
		search({n - 1, i}, visited_2, matrix);
	}
	/*** right ***/
	for(int i = 0; i < n; i++) {
		visited_2[{i, n - 1}] = true;
		search({i, n - 1}, visited_2, matrix);
	}

	vector<Point>  result;
	for(auto p : visited_1) {
		if(visited_2.count(p.first)) 
			result.push_back(p.first);
	}
	return result;
}
```
