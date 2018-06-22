  RandomListNode *copyRandomList(RandomListNode *head) {
    if (head == nullptr) return nullptr;
    RandomListNode *l, *r;
    for (l = head; l != nullptr; l = l->next->next) {
      r = new RandomListNode(l->label);
      r->next = l->next;
      l->next = r;
    }
    
    for (l = head; l != nullptr; l = l->next->next) {
      if (l->random) l->next->random = l->random->next;
    }
    
    RandomListNode *ret = head->next;
    for (l = head; l != nullptr; l = l->next) {
      r = l->next;
      l->next = r->next;
      if (r->next) r->next = r->next->next;
    }
    return ret;
  }