class MyCircularQueue {
    int cap;
    vector<int> data;
    int h, t;
public:
    MyCircularQueue(int k) {
       h = 0; t = 0;
       cap = k + 1;
       data.resize(cap); 
    }
    
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
       data[h % cap] = value;
       h++; 
        return true;
    }
    
    bool deQueue() {
       if (isEmpty()) {
           return false;
       } 
       t++;
        return true;
    }
    
    int Front() {
        if (isEmpty()) {
            return -1;
        }
       return data[t % cap]; 
    }
    
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
       return data[(h - 1 + cap) % cap]; 
    }
    
    bool isEmpty() {
       return h == t; 
    }
    
    bool isFull() {
       return (h + 1) % cap == t; 
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */