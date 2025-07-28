//
// Created by wstap on 2025-07-27.
//

#include "JobSystem.h"

namespace hive {
	JobSystem::JobSystem() {
		// Leaves two threads, one for the main program and one for the operating system
		const unsigned int num_threads = std::max(1U, std::thread::hardware_concurrency() -2U);
		HIVE_LOG_INFO("Creating %i worker threads", num_threads);

		m_threads.reserve(num_threads);
		for (unsigned int i = 0; i < num_threads; ++i) {
			m_threads.emplace_back(&JobSystem::worker, this);
		}
	}

	JobSystem::~JobSystem() {
		HIVE_LOG_INFO("Shutting down job system and joining threads.");
		std::unique_lock lock(m_queueMutex);
		m_shouldStop = true;
		m_condition.notify_all();

		for (auto& thread : m_threads) {
			if (thread.joinable()) {
				thread.join();
			}
		}
	}

	void JobSystem::schedule(std::function<void()> job)
	{
		auto job_wrapper = std::make_unique<LambdaJob>(std::move(job));
		schedule(std::move(job_wrapper));
	}

	void JobSystem::schedule(std::unique_ptr<IJob> job)
	{
		{
			std::unique_lock lock(m_queueMutex);
			m_jobQueue.push_back(std::move(job));
		}
		m_condition.notify_one();
	}

	void JobSystem::worker()
	{
		while(true) {
			std::unique_ptr<IJob> job;
			{
				std::unique_lock lock(m_queueMutex);

				m_condition.wait(lock, [this]
				{
					return m_shouldStop || !m_jobQueue.empty();
				});

				if (m_shouldStop) return;

				job = std::move(m_jobQueue.front());
				m_jobQueue.pop_front();
			}

			if (job) {
				(*job)();
			}

		}
	}
} // hive