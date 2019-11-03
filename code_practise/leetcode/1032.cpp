class ACAutoma {
  /*
   * cf.  http://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/02/Small02.pdf
   *
   * A trie is a link-based representation of a group of (non empty) words by
   * prefix.
   *
   * A suffix link in each trie node points to the longest proper suffix of the
   * current node (a node is a prefix). If there is no such node, pointing to root
   * as root is the empty prefix.
   *
   * An output link in each trie node points to longest word node that is a proper
   * suffix of the current node. If there is no such node, pointing to null
   * (assuming no empty words). Following the output link repeatedly will output
   * all matched patterns being a proper suffix of the current node.
   *
   * Construction of suffix link follows the following key observation: if w is a
   * prefix and a is the next char after w, then the suffix link of wa is related
   * to the suffix link of w.
   *
   * Construction of output link follows the following key observation: if the
   * suffix link of node w is a word, it is the longest one word being a proper
   * suffix. Otherwise, just use the output link of the suffix link.
   *
   * Both of them arises from the fact that if x is a suffix of y, y is a suffix
   * of z, then x is a suffix of z.
   *
   * Matching is done by maintaining the following invariant: if m[i] is the next
   * char to match in text m, node* cursor is the longest matching prefix (node)
   * up to m[i-1] in the trie of patterns. When i = 0, cursor points at root node
   * (empty string).
   */

   struct node {
     bool isWord_ {false};
     const string *word_;
     unordered_map<char, unique_ptr<node>> children_;

     node* suffix_link_;
     node* output_link_ {nullptr};

     void add_node(
       int curIdx, const string& input
     ) {
       if (curIdx == input.size()) {
         isWord_ = true;
         word_ = &input;
         return;
       }

       char c = input[curIdx];
       if (children_.count(c) == 0) {
         children_[c] = make_unique<node>();
       }

       children_[c]->add_node(curIdx + 1, input);
     }
   } root_, *cursor = &root_;

public:
   ACAutoma(const vector<string>& pattern) {
     for (const string & p : pattern) {
       assert(p.length());
       root_.add_node(0, p);
     }

     deque<node*> q;
     for (auto &pr : root_.children_) {
       q.push_back(pr.second.get());
       pr.second->suffix_link_ = &root_;
     }

     while (!q.empty()) {
       auto top = q.front(); q.pop_front();

       for (auto &pr : top->children_) {
         char a = pr.first;
         node *w = pr.second.get();

         node* suffix = top->suffix_link_;
         while (suffix != &root_ &&
                   suffix->children_.count(a) == 0) {
          suffix = suffix->suffix_link_;
         }

         if (suffix->children_.count(a) == 0) {
           w->suffix_link_ = &root_;
         } else {
           w->suffix_link_ = suffix->children_[a].get();

           if (w->suffix_link_->isWord_) {
             w->output_link_ = w->suffix_link_;
           } else {
             w->output_link_ = w->suffix_link_->output_link_;
           }
         }

         q.push_back(w);
       }
     }
  }

   bool match(char c) {
      while (cursor != &root_ &&
               cursor->children_.count(c) == 0) {
         cursor = cursor->suffix_link_;
      }

      if (cursor->children_.count(c) == 0) {
         return false;
      }

      cursor = cursor->children_[c].get();
      if (cursor->isWord_ || cursor->output_link_) {
          return true;
      }
      return false;
   }
};


class StreamChecker {
    ACAutoma *ac;

public:
    ~StreamChecker() {
        delete ac;
    }
    StreamChecker(vector<string>& words) {
       ac = new ACAutoma(words);
    }

    bool query(char letter) {
       return ac->match(letter);
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */