//
// Created by Junlong Gao on 11/27/16.
//

#ifndef C_11_LAB_CONCURRENCY_H
#define C_11_LAB_CONCURRENCY_H
namespace concurrency{
    void demo();
    void test_rwlock();

    /*
     * a read write lock is a high level sync obj
     * that allow for concurrent read but single write.
     */
    class RWlock{
        struct impl;
        impl* rw_impl;
    public:
        RWlock();
        ~RWlock();

        void read_lock();
        void write_lock();

        void read_unlock();
        void write_unlock();

        /* delete funny business */
        RWlock(RWlock&&) = delete;
        RWlock(const RWlock&) = delete;
        RWlock& operator=(RWlock&&) = delete;
        RWlock& operator=(const RWlock&) = delete;
    };

    template <typename T>
    class BoundedBuffer{
        struct impl;
        impl* bb_impl;
    public:
        BoundedBuffer(unsigned);
        ~BoundedBuffer();

        /*
         * move into the bounded
         * queue end
         */
        void put(T&&);


        /*
         * get one out from the
         * front of the
         * queue
         */
        T get();

        BoundedBuffer(BoundedBuffer&&) = delete;
        BoundedBuffer(const BoundedBuffer&) = delete;
        BoundedBuffer&operator=(BoundedBuffer&&) = delete;
        BoundedBuffer&operator=(const BoundedBuffer&) = delete;

    };
    void test_bb();
    class MemoryBarrier{

    };
}
#endif //C_11_LAB_CONCURRENCY_H
