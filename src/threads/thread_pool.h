#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

#include <spdlog/spdlog.h>
#include "../utils/logger.h"

namespace thread_management
{
  /**
   * @class ThreadPool
   * @brief A thread pool for executing tasks in parallel on a set of threads
   *
   */
  class ThreadPool
  {
  public:
    /**
     * @brief Construct a new ThreadPool object
     *
     * @param[in] num_threads Number of threads to use
     */
    explicit ThreadPool(std::size_t num_threads)
        : m_logger(logger::Logger::get_logger()), m_stop(false)
    {
      for (std::size_t iterator; iterator < num_threads; ++iterator)
      {
        m_threads.emplace_back([this]
                               {
            while (true)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->m_queue_mutex);
                    this->m_condition.wait(lock, [this]
                                           { return this->m_stop || !this->m_tasks.empty(); });

                    if (this->m_stop && this->m_tasks.empty())
                        return;

                    task = std::move(this->m_tasks.front());
                    this->m_tasks.pop();
                }

                task();
            } });
      }
    }

    /**
     * @brief Destroy the ThreadPool object
     *
     */
    ~ThreadPool()
    {
      {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        m_stop = true;
      }

      m_condition.notify_all();

      for (std::thread &thread : m_threads)
        thread.join();
    }

    /**
     * @brief Adds a new task to the pool
     *
     * @tparam Function Function type
     * @tparam Args Argument types
     *
     * @param[in] function Function to execute
     * @param[in] args Arguments to pass to the function
     *
     * @return std::future<typename std::result_of<Function(Args...)>::type>
     *         Future object holding the result of the function
     *
     * @throw std::runtime_error If the pool is stopped
     */
    template <class Function, class... Args>
    auto enqueue(Function &&function, Args &&...args)
        -> std::future<typename std::result_of<Function(Args...)>::type>
    {
      try
      {
        using ReturnType = typename std::result_of<Function(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<Function>(function),
                      std::forward<Args>(args)...));

        std::future<ReturnType> result = task->get_future();

        {
          std::unique_lock<std::mutex> lock(m_queue_mutex);

          if (m_stop)
            throw std::runtime_error("ThreadPool: enqueue on stopped pool");

          m_tasks.emplace([task]()
                          { (*task)(); });
        }

        m_condition.notify_one();
        return result;
      }
      catch (const std::exception &e)
      {
        m_logger->error("ThreadPool: Error: {}", e.what());
        throw;
      }
      catch (...)
      {
        m_logger->error("ThreadPool: Unknown error");
        throw;
      }
    }

  private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_queue_mutex;
    std::condition_variable m_condition;
    std::shared_ptr<spdlog::logger> m_logger;

    bool m_stop;
  };
} // namespace thread_management