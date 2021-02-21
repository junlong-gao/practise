class FizzBuzz {
private:
    int n;
    int c {1};
    mutex mu;
    condition_variable cv;
public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
    
        while (true) {
            std::unique_lock lk(mu);
            while (c<=n && ! (c%3==0 && c%5!=0)) {
                cv.wait(lk);
            }
            if (c > n) {
                return;
            }

            printFizz();
            c++;
            cv.notify_all();
        }

    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (true) {
            std::unique_lock lk(mu);
            while (c<=n && ! (c%3!=0 && c%5==0)) {
                cv.wait(lk);
            }
            if (c > n) {
                return;
            }
            printBuzz();
            c++;
            cv.notify_all(); 
        }
   
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            std::unique_lock lk(mu);
            while (c<=n && ! (c%3==0 && c%5==0)) {
                cv.wait(lk);
            }
            if (c > n) {
                return;
            }

            printFizzBuzz();
            c++;
            cv.notify_all();  
        }
     
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (true) {
            std::unique_lock lk(mu);
            while (c<=n && ! (c%3!=0 && c%5!=0)) {
                cv.wait(lk);
            }
            if (c > n) {
                return;
            }
            printNumber(c);
            c++;
            cv.notify_all(); 
        }
   
    }
};
