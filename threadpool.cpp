#include "threadpool.hpp"

ThreadPool::ThreadPool(size_t thread_count): stop(false) {
    for(size_t i = 0; i<thread_count; i++){
        workers.emplace_back(&ThreadPool::worker_loop, this);
    }
}

ThreadPool::~ThreadPool(){
    stop.store(true);
    condition.notify_all();

    for(std::thread &worker: workers){
        if(worker.joinable()) worker.join();
    }
}

void ThreadPool::submit(std::function<void()> task){
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(std::move(task));
    }
    condition.notify_one();
}

void ThreadPool::wait_finish(){
    while(true){
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(tasks.empty()) break;
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

}

void ThreadPool::worker_loop(){
    while (!stop.load()) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this](){
                return stop.load() || !tasks.empty();
            });

            if(stop.load() && tasks.empty()) return;

            task = std::move(tasks.front());
            tasks.pop();    
        }
        task();
    }
}

