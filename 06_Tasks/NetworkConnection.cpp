#include <functional>
#include <iostream>
#include <memory>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>  // io_context in newer boost versions
#include <boost/thread/thread.hpp>

#include <boost/asio/ip/tcp.hpp>

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>

typedef boost::asio::deadline_timer::time_type time_type;

class tcp_connection_ptr {
  std::shared_ptr<boost::asio::ip::tcp::socket> socket_;

 public:
  explicit tcp_connection_ptr(
      std::shared_ptr<boost::asio::ip::tcp::socket> socket)
      : socket_(socket) {}

  tcp_connection_ptr(boost::asio::io_service& ios,
                     boost::asio::ip::tcp::endpoint endpoint)
      : socket_(std::make_shared<boost::asio::ip::tcp::socket>(std::ref(ios))) {
    socket_->connect(endpoint);
  }

  template <class Functor>
  void async_read(const boost::asio::mutable_buffers_1& buf, const Functor& f,
                  std::size_t at_least_bytes) const {
    boost::asio::async_read(*socket_, buf,
                            boost::asio::transfer_at_least(at_least_bytes), f);
  }

  template <class Functor>
  void async_write(const boost::asio::const_buffers_1& buf,
                   const Functor& f) const {
    boost::asio::async_write(*socket_, buf, f);
  }

  template <class Functor>
  void async_write(const boost::asio::mutable_buffers_1& buf,
                   const Functor& f) const {
    boost::asio::async_write(*socket_, buf, f);
  }

  void shutdown() const {
    socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_->close();
  }
};

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
  explicit timer_task(boost::asio::io_service& ios,
                      const Time& duration_or_time,
                      const Functor& task_unwrapped)
      : base_t(task_unwrapped),
        timer_(std::make_shared<boost::asio::deadline_timer>(
            std::ref(ios), duration_or_time)) {}

  void push_task() const { timer_->async_wait(*this); }

  void operator()(const boost::system::error_code& error) const {
    if (!error) {
      base_t::operator()();
    } else {
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

  tcp_connection_ptr create_connection(const char* addr,
                                       unsigned short port_num) {
    return tcp_connection_ptr(
        ios_, boost::asio::ip::tcp::endpoint(
                  boost::asio::ip::address_v4::from_string(addr), port_num));
  }
};

// TEST

const unsigned short g_port_num = 65001;

bool g_authed = false;

void finish_socket_auth_task(const boost::system::error_code& err,
                             std::size_t bytes_transferred,
                             const tcp_connection_ptr& soc,
                             const std::shared_ptr<std::string>& data) {
  if (err && err != boost::asio::error::eof) {
    std::cerr << "finish_socket_auth_task: Client error: " << err.message()
              << '\n';
    assert(false);
  }

  if (bytes_transferred != 2) {
    std::cerr << "finish_socket_auth_task: wrong bytes count\n";
    assert(false);
  }

  data->resize(bytes_transferred);
  if (*data != "OK") {
    std::cerr << "finish_socket_auth_task: wrong response " << *data << "\n";
    assert(false);
  }

  g_authed = true;
  soc.shutdown();
  tasks_processor::get().stop();
}

void receive_auth_task(const boost::system::error_code& err,
                       const tcp_connection_ptr& soc,
                       const std::shared_ptr<std::string>& data) {
  if (err) {
    std::cerr << "receive_auth_task: Client error on recieve: " << err.message()
              << '\n';
    assert(false);
  }

  soc.async_read(boost::asio::buffer(&(*data)[0], data->size()),
                 std::bind(&finish_socket_auth_task, std::placeholders::_1,
                           std::placeholders::_2, soc, data),
                 1);
}

void send_auth_task() {
  tcp_connection_ptr soc =
      tasks_processor::get().create_connection("127.0.0.1", g_port_num);

  std::shared_ptr<std::string> data =
      std::make_shared<std::string>("auth_name");

  soc.async_write(
      boost::asio::buffer(*data),
      std::bind(&receive_auth_task, std::placeholders::_1, soc, data));
}

int main() {
	//task_processor::get().run_at(boost::posix_time::seconds(1) &send_auth_task);
	//task_processor::get().add_listener(g_port_num, &authorizer::on_connection_accpet);

	//assert(!g_authed);

	//tasks_processor::get().start();
	//assert(g_authed);
}
