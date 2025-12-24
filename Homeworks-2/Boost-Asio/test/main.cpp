#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <chrono>

int main() {
    std::cout << "=== Testing Strand (production version) ===" << std::endl;

    boost::asio::io_context ctx;
    std::mutex counter_mutex;
    // Удерживаем работу, чтобы ctx.run() не возвращался сразу
    auto work = boost::asio::make_work_guard(ctx);

    // Создаём strand через executor
    auto strand = boost::asio::make_strand(ctx.get_executor());
    auto strand2 = boost::asio::make_strand(ctx.get_executor());

    std::atomic<int> counter{0};

    // Запускаем 4 потока
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&ctx]{
            ctx.run();
        });
    }

    std::cout << "\n--- Test 1: post() ---" << std::endl;

    for (int i = 0; i < 50; ++i) {
        // Используем свободную функцию post — переносимо и работает для всех версий Boost
        boost::asio::post(strand, [&counter, i, &counter_mutex]() {
            // атомарно инкрементируем
            counter.fetch_add(1, std::memory_order_relaxed);

            std::this_thread::sleep_for(std::chrono::microseconds(5));

            {
                std::lock_guard<std::mutex> lock(counter_mutex);
                std::cout << "Task " << i << " (thread "
                          << std::this_thread::get_id() << ")" << std::endl;
            }
        });
        ++i;
        boost::asio::post(strand2, [&counter, i, &counter_mutex]() {
            counter.fetch_add(1, std::memory_order_relaxed);

            std::this_thread::sleep_for(std::chrono::microseconds(5));

            {
                std::lock_guard<std::mutex> lock(counter_mutex);
                std::cout << "Task " << i << " (thread "
                          << std::this_thread::get_id() << ")" << std::endl;
            }
        });
    }

    // Разрешаем ctx завершиться, когда все handlers выполнены
    work.reset();

    for (auto &t : threads) {
        if (t.joinable()) t.join();
    }

    std::cout << "Final counter = " << counter.load() << std::endl;
    return 0;
}
