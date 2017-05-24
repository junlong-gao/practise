#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct node{
    node *l, *r, *p;
    int v;
    node(node* _l = nullptr, 
            node* _r = nullptr,
            node* _p = nullptr,
            int _v = 0): l(_l),r(_r),p(_p),v(_v){;}
};

vector<list<node*>> levelOrder(node* root){
    vector<list<node*>> rst;
    if(root == nullptr) return rst;
    rst.emplace_back();
    rst.back().push_back(root);
    while(1){
        auto& cur = rst.back(); 
        list<node*> new_li;
        for(auto it = cur.cbegin(); it!=cur.cend(); ++it){
            if((*it)->l!=nullptr){
                new_li.push_back((*it)->l);
            }
            if((*it)->r!=nullptr){
                new_li.push_back((*it)->r);
            }
        }
        if(new_li.size() == 0) break;
        else rst.push_back(new_li);
    }
    return rst;
}

node* levelOrder(node* n1, node* n2){
    int l1, l2;
    l1 = l2 =0;
    node* w = n1;
    while(w){ w = w->p; l1++; }
    w = n2;
    while(w){ w = w->p; l2++; }
    if(l2 > l1){
        swap(l1, l2);
        swap(n1, n2);

    }
    while(l1!=l2 && n1){
        n1 = n1->p;
        l1--;
    }
    while(n1&&n2&&n1!=n2){
        n1 = n1->p;
        n2 = n2->p;
    }
    return n1;
}

void print(vector<int>& so_far, int end){
    for(int i = (int)so_far.size() - 1; i > end - 1; --i){
        cout << so_far[i] << " ";
    }
    cout << endl;
}

void bfs(const int sum, node* cur, vector<int> so_far){
    if(cur==nullptr) return;
    so_far.push_back(cur->v);
    int temp = 0;
    for(int i = so_far.size() - 1; i > -1; --i){
        temp += so_far[i];
        if(temp == sum) print(so_far, i);
    }
    bfs(sum, cur->l, so_far);
    bfs(sum, cur->r, so_far);
}

int main(){
    node r,a1,a2,a3,a4,a5;
    r.v = 0; r.l = &a1; a1.p = &r;
    a1.v = 1; a1.l = &a2; a2.p = &a1;
    a2.v = 2; a2.l=&a3; a2.r = &a4;
    a3.p = &a2; a4.p = &a2;
    a3.v = 3; 
    a4.v = 4; a4.l = &a5; a5.p = &a4;
    a5.v = 1;
    /*
    auto rst = levelOrder(&r);
    for(auto& li : rst){
        for(auto node : li){
            cout << node->v << " ";
        }
        cout << endl;
    }
    auto lca = levelOrder(&a3, &a4);
    cout << lca->v << endl;
    */
    vector<int> so_far;
    bfs(7, &r, so_far);

    return 0;
}
