#pragma once

namespace example
{
    class ThreadPool
    {
      public:
        ThreadPool() : running(true)
        {
            uint32_t const numThreads = std::thread::hardware_concurrency() - 1;
            for (uint32_t i = 0; i < numThreads; ++i)
            {
                auto thread = std::unique_ptr<std::thread>(new std::thread([this]() -> void { this->loop(); }));
                threads.emplace_back(std::move(thread));
            }
        }

        ~ThreadPool()
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                running = false;
            }

            condition.notify_all();

            for (auto const& thread : threads)
            {
                thread->join();
            }
        }

        void loop()
        {
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    condition.wait(lock, [this]() { return !running || !tasks.empty(); });
                    if (!running)
                    {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        }

        template <typename Func>
        void push_task(Func&& function)
        {
            std::function<void()> task = [function]() -> void { function(); };

            {
                std::unique_lock<std::mutex> lock(mutex);

                if (!running)
                {
                    throw std::runtime_error("Tasks cannot be added to a stopped ThreadPool");
                }

                tasks.emplace(std::move(task));
            }

            condition.notify_one();
        }

      private:
        std::mutex mutex;
        std::condition_variable condition;
        std::vector<std::unique_ptr<std::thread>> threads;
        std::queue<std::function<void()>> tasks;
        bool running;
    };
} // namespace example