#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <future>
#include <functional>
#include <stdexcept>

using namespace std;

class ThreadPool {
    vector <thread> workers;
    queue <function<void()>> tasks;

    mutex m;
    condition_variable condition;
    bool stop;
public:

    explicit ThreadPool(size_t poolSize)
            : stop(false) {
        for (size_t i = 0; i < poolSize; ++i)
            workers.emplace_back(
                    [this] {
                        while (true) {
                            function<void()> task;
                            {
                                unique_lock <mutex> lock(m);
                                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                                if (stop && tasks.empty())
                                    return;
                                task = move(tasks.front());
                                tasks.pop();
                            }
                            task();
                        }
                    }
            );
    }


    template<class Func, class... Args>
    auto exec(Func &&f, Args &&... args) -> future<decltype(f(args...))> {
        auto task = make_shared < packaged_task < typename result_of<Func(Args...)>::type() >> (
                bind(forward<Func>(f), forward<Args>(args)...)
        );
        auto res = task->get_future();
        {
            unique_lock<mutex> lock(m);
            if (stop)
                throw runtime_error("The pool has already stopped");

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_all();
        return res;
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(m);
            stop = true;
        }
        condition.notify_all();
        for (thread &worker: workers)
            worker.join();
    }
};


#endif