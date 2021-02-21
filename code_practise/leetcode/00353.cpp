class SnakeGame {
	pair<int, int> head;
	int w, h;
	int serialize(int x, int y) {
		return x + y * w;
	}
	list<int> body;
	unordered_set<int> table;
	vector<pair<int, int>> foods;
	int curFood = 0;
public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food) {
        	h = width;
	w = height;
	head = {0, 0};
	body.push_back(serialize(0, 0));
	table.insert(serialize(0, 0));
	swap(food, foods);
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body. 
case 1: empty:
	push new position, deque the end of the snake, return current cap
case 2: food:
 	push new position, don't deque, return cap
case 3: self, out
	die -> -1
*/
    int move(string direction) {
	static const unordered_map<string, pair<int, int>> d {
		{"U", {-1, 0}},
{"L", {0, -1}},
{"R", {0, 1}},
{"D", {1, 0}}		
	};
       	head.first = head.first + d.at(direction).first;
	head.second = head.second + d.at(direction).second;
	int s = serialize(head.first, head.second);
	if (curFood < foods.size() &&
    foods[curFood].first == head.first &&
    foods[curFood].second == head.second) {
		body.push_back(s);
		table.insert(s);
		curFood++;
		return body.size() - 1;
	}

// XXX when move, pop first then check collision
	table.erase(body.front());
	body.pop_front();

if (table.count(s) != 0 ||
  head.first < 0 || 
  head.first >= w || 
  head.second < 0 ||
  head.second >= h) {
		return -1;
	} else {
		body.push_back(s);
		table.insert(s);
		return body.size() - 1;
	}
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */

