#pragma once
#include <thread>
#include <utility>
#include <mutex>
#include <condition_variable>

namespace hive {
    class HIVE_API IJob {
    public:
        IJob() = default;
        virtual ~IJob() = default;

        IJob(const IJob&) = delete;
        IJob& operator=(const IJob&) = delete;

        virtual void operator()() const = 0;
    };

    class HIVE_API JobSystem {
    public:
        JobSystem();
        ~JobSystem();

        void schedule(std::function<void()> job);
        void schedule(std::unique_ptr<IJob> job);

    private:
        void worker();

        std::vector<std::thread> m_threads;

        std::deque<std::unique_ptr<IJob>> m_jobQueue;
        std::mutex m_queueMutex;
        std::condition_variable m_condition;
        bool m_shouldStop = false;

        class LambdaJob : public IJob
        {
        public:
            LambdaJob(std::function<void()> lambda): m_lambda(std::move(lambda)) {}
            void operator()() const override { m_lambda(); }
        private:
            std::function<void()> m_lambda;
        };
    };

} // hive
