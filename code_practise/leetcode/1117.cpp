class H2O {
    mutex mu;
    condition_variable cv;
    int hNeeded{2}, oNeeded{1}, hLeaving{0}, oLeaving{0};
public:
    H2O() {
    }
    void leaveBarrier() {
        if (hLeaving == 2 && oLeaving == 1) {
            hLeaving = 0;
            oLeaving = 0;
            oNeeded = 1;
            hNeeded = 2;
            cv.notify_all();
        }
    }
    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock lk(mu);
        while (hNeeded == 0) {
            cv.wait(lk);
        }
        
        hNeeded--;
        cv.notify_all();
        
        while (hNeeded || oNeeded) {
            cv.wait(lk);
        }
        releaseHydrogen();
        
        hLeaving++;
        leaveBarrier();       
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock lk(mu);
        while (oNeeded == 0) {
            cv.wait(lk);
        }
        
        oNeeded--;
        cv.notify_all();
        
        while (hNeeded || oNeeded) {
            cv.wait(lk);
        }
        releaseOxygen();
        
        oLeaving++;
        leaveBarrier();       

    }
};
