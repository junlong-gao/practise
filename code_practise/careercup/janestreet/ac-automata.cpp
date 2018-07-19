#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <deque>
#include <string>
#include <unordered_map>

using namespace std;
/*
 * Design a gamepad input controller <Jane Street>
 *
 */

using namespace std;

class ACAutomata {
   struct node {
      unordered_map<char, node*> children;
      node *suffix_link {nullptr},
           *output_link {nullptr};
      vector<string> actions;
      bool IsSeq() {
         return actions.size() > 0;
      }
   } rootNode_, *cur_{&rootNode_};

   void add_helper(
         node *root,
         const string &seq,
         const string &action,
         int soFar) {
      if (soFar == seq.size()) {
         root->actions.push_back(action);
         return;
      }
      if (root->children.count(seq[soFar]) == 0) {
         root->children[seq[soFar]] = new node;
      }
      add_helper(root->children[seq[soFar]], seq, action, soFar + 1);
   }

   void add(
         node *root,
         const string &seq,
         const string &action
         ) {
      add_helper(root, seq, action, 0);
   }

   void reconstruct(
         const vector<string> &seqs,
         const vector<string> &actions
         ) {
      for (int i = 0; i < seqs.size(); ++i) {
         add(&rootNode_, seqs[i], actions[i]);
      }

      deque<node *> q;
      for (auto pr : rootNode_.children) {
         pr.second->suffix_link = &rootNode_;
         q.emplace_back(pr.second);
      }

      while (q.size()) {
         auto top = q.front(); q.pop_front();
         for (auto pr : top->children) {
            node *w = pr.second;
            char c = pr.first;

            // reuse suffix
            node *x = top->suffix_link;
            while (x != &rootNode_ && x->children.count(c) == 0) {
               // keep tracking back using the suffix link as long
               // as we don't have a matching link c
               x = x->suffix_link;
            }

            if (x->children.count(c)) {
               // we have a longest prefix that is a suffix of node top
               w->suffix_link = x->children[c];

               if (w->suffix_link->IsSeq()) {
                  // this longest prefix suffix is a word, it is
                  // an output.
                  w->output_link = w->suffix_link;
               } else {
                  w->output_link = w->suffix_link->output_link;
               }
            } else {
               // x == root
               w->suffix_link = x;
            }

            // enqueue
            q.push_back(w);
         }
      }
   }

   public:
      ACAutomata(
            const vector<string> &seqs,
            const vector<string> &actions
            ) {
         reconstruct(seqs, actions);
      }

      ACAutomata() : ACAutomata({}, {}) {;}
      vector<string> activate(char c) {
         vector<string> ret;
         while (cur_ != &rootNode_ &&
                cur_->children.count(c) == 0) {
            cur_ = cur_->suffix_link;
         }

         if (cur_->children.count(c)) {
            cur_ = cur_->children[c];

            for (auto &s : cur_->actions) {
               ret.push_back(s);
            }

            node *out = cur_->output_link;
            while (out) {
               for (auto &s : out->actions) {
                  ret.push_back(s);
               }
               out = out->output_link;
            }
         }

         return ret;
      }

      void registerAction(const string &seq, const string &action) {
         reconstruct({seq}, {action});
      }
};


int main() {
   ACAutomata ac;
   ac.registerAction("abcd", "abcd");
   ac.registerAction("bc", "bc");

   auto in = [&](char in) {
      cout << "in:" << in << endl;
      cout << ">>>: ";
      for (auto s : ac.activate(in)) {
         cout << s << " ";
      }
      cout << endl;
   };

   in('a');
   in('b');
   in('c');
   in('d');
   ac.registerAction("abcdefghi", "abcdefghi");
   ac.registerAction("def", "def");
   ac.registerAction("fgh", "fgh");
   in('e');
   in('f');
   in('g');
   in('h');
   in('i');
   cout << "Passed" << endl;
   return 0;
}

