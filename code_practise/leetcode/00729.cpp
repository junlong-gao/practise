class MyCalendar {
  struct event {
    int s, e;
  };
  struct cmp {
    bool operator()(const event &l, const event &r) { return l.s < r.s; }
  };
  set<event, cmp> evs;

 public:
  MyCalendar() {}

  bool book(int start, int end) {
    if (start > end) return false;
    auto it = evs.lower_bound(event{end, end});
    if (it == evs.begin()) {
      evs.insert(event{start, end});
      return true;
    }

    --it;
    if (it->e > start) return false;
    evs.insert(event{start, end});
    return true;
  }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
