#include <functional>
#include <iostream>
#include <memory>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>  // io_context in newer boost versions
#include <boost/thread/thread.hpp>

typedef boost::asio::deadline_timer::time_type time_type;

namespace detail {
template <class T>
struct task_wrapped {
 private:
  T task_unwrapped_;

 public:
  explicit task_wrapped(const T& task_unwrapped)
      : task_unwrapped_(task_unwrapped) {}

  void operator()() const {
    // resetting interruption
    try {
      boost::this_thread::interruption_point();
    } catch (const boost::thread_interrupted&) {
    }

    try {
      // Executing task
      task_unwrapped_();
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << '\n';
    } catch (const boost::thread_interrupted& e) {
      std::cerr << "Exception: Thread interrupted\n";
    } catch (...) {
      std::cerr << "Unknown Exception\n";
    }
  }
};


template <class Functor>
struct timer_task : public task_wrapped<Functor> {
private:
	typedef task_wrapped<Functor> base_t;
	std::shared_ptr<boost::asio::deadline_timer> timer_;

public:
	template <class Time>
	explicit timer_task(
		boost::asio::io_service& ios,
		const Time&duration_or_time,
		const Functor& task_unwrapped)
			: base_t(task_unwrapped),
			  timer_(std::make_shared<boost::asio::deadline_timer>(std::ref(ios), duration_or_time))
		{}

		void push_task() const {
			timer_->async_wait(*this);
		}
		
		void operator()(const boost::system::error_code& error) const {
			if (!error) {
				base_t::operator()();
			}
			else {
				std::cerr << error << "\n";
			}
		}
 };

template <class T>
task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
  return task_wrapped<T>(task_unwrapped);
}

template <class Time, class Functor>
inline timer_task<Functor> make_timer_task(boost::asio::io_service& ios,
                                           const Time& duration_or_time,
                                           const Functor& task_unwrapped) {
  return timer_task<Functor>(ios, duration_or_time, task_unwrapped);
}
}  // namespace detail

class tasks_processor : private boost::noncopyable {
  boost::asio::io_service ios_;
  boost::asio::io_service::work work_;

  tasks_processor() : ios_(), work_(ios_) {}

 public:
  static tasks_processor& get() {
    static tasks_processor proc;
    return proc;
  }

  template <class T>
  inline void push_task(const T& task_unwrapped) {
    ios_.post(detail::make_task_wrapped(task_unwrapped));
  }

  template <class Functor>
  void run_at(time_type time, const Functor& f) {
    detail::make_timer_task(ios_, time, f).push_task();
  }

  void start() { ios_.run(); }

  void stop() { ios_.stop(); }
};

// TEST

void func_test() {
	std::cout << "Hello\n";
}

int main() {
  static const std::size_t tasks_count = 3;


  for (std::size_t i = 0; i < tasks_count; ++i) {
    tasks_processor::get().run_at(boost::posix_time::from_time_t(time(NULL) + 3*i), &func_test);
  }

  // will not throw but blocks until one of the tasks calls stop)
  tasks_processor::get().start();
}
