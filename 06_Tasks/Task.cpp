#include <iostream>
#include <functional>

#include <boost/thread/thread.hpp>
#include <boost/asio/io_service.hpp> // io_context in newer boost versions

namespace detail {
    template <class T>
    struct task_wrapped {
    private:
        T task_unwrapped_;
        
    public:
        explicit task_wrapped(const T& task_unwrapped)
          : task_unwrapped_(task_unwrapped)
        {}
        
        void operator()() const {
            // resetting interruption
            try {
                boost::this_thread::interruption_point();
            }
                catch (const boost::thread_interrupted&) {}
            
            try {
                // Executing task
                task_unwrapped_();
            }
            catch (const std::exception& e) {
                std::cerr << "Exception: " << e.what() << '\n';
            }
            catch (const boost::thread_interrupted& e) {
                std::cerr << "Exception: Thread interrupted\n";
            }
            catch (...) {
                std::cerr << "Unknown Exception\n";
            }
        }
    };


    template <class T>
    task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
        return task_wrapped<T>(task_unwrapped);
    }
}


class tasks_processor : private boost::noncopyable {
    boost::asio::io_service         ios_;
    boost::asio::io_service::work   work_;  

    tasks_processor()
     :  ios_(),
        work_(ios_)
    {}

public:
    static tasks_processor& get() {
        static tasks_processor proc;
        return proc;
    }

    
    template <class T>
    inline void push_task(const T& task_unwrapped) {
        ios_.post(detail::make_task_wrapped(task_unwrapped));
    }

    void start() {
        ios_.run();
    }
    
    void stop() {
        ios_.stop();
    }
};



// TEST

int g_val = 0;
void func_test() {
    ++g_val;
    if (g_val == 3) {
        throw std::logic_error("Just checking");
    }
    
    boost::this_thread::interruption_point();
    if (g_val == 10) {
        // emulation of thread interruption (will be caught and not stop execution)
        throw boost::thread_interrupted();
    }
    
    if (g_val == 90) {
        tasks_processor::get().stop();
    }
}

int main() {
    static const std::size_t tasks_count = 100;

    // stop is called at 90
    static_assert(tasks_count > 90, "");
    
    for (std::size_t i = 0; i < tasks_count; ++i) {
        tasks_processor::get().push_task(&func_test);
    }
    
    // use boost::bind
    tasks_processor::get().push_task(std::bind(std::plus<int>(), 2, 2));

    // processing not started yet
    assert(g_val == 0);

    // will not throw but blocks until one of the tasks calls stop)
    tasks_processor::get().start();
    assert(g_val == 90);

}
