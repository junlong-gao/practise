class ProductOfNumbers {
    vector<int> pfx;
public:
    ProductOfNumbers() {
    }
    
    void add(int num) {
        if (pfx.empty()) {
            pfx.push_back(num);
        } else {
           pfx.push_back(pfx.back() * num);
        }
        
        if (pfx.back() == 0) {
            pfx.clear();
        }
    }
    
    int getProduct(int k) {
        int target  = pfx.size() - 1 - k;
        if (target == -1) {
            return pfx.back();
        }
        if (target < -1) {
            return 0;
        }
        return pfx.back() / pfx[target];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */