
#include <deque>

#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>


class work_queue {
public:
	typedef boost::function<void()> task_type;

private:
	std::deque<task_type>				tasks_;
	boost::mutex								mutex_;
	boost::condition_variable		cond_;

public:
	void push_task(const task_type& task) {
		boost::unique_lock<boost::mutex> lock(mutex_);
		tasks_.push_back(task);
		lock.unlock(); // not needed, but makes code faster than to rely on unlockint in `notify_one`
		cond_.notify_one();
	}

	task_type try_pop_task() {
		task_type ret;
		boost::lock_guard<boost::mutex> lock(mutex_);
		if (!tasks_.empty()) {
			ret = tasks_.front();
			tasks_.pop_front();
		}

		return ret;
	}

	task_type pop_task() {
		boost::unique_lock<boost::mutex> lock(mutex_);
		while (tasks_.empty()) {
			cond_.wait(lock);
		}

		task_type ret = tasks_.front();
		tasks_.pop_front();

		return ret;
	}
	
	
};


// TESTS //
work_queue g_queue;

void do_nothing() {}

const std::size_t test_tasks_count = 3000;

void pusher() {
	for (std::size_t i = 0; i < test_tasks_count; ++i) {
		// Adding task
		g_queue.push_task(&do_nothing);
	}
}

void popper_sync() {
	for (std::size_t i = 0; i < test_tasks_count; ++i) {
		// get task and execute
		g_queue.pop_task()();
	}
}


int main() {
	boost::thread pop_sync1(&popper_sync);
	boost::thread pop_sync2(&popper_sync);
	boost::thread pop_sync3(&popper_sync);

	boost::thread push1(&pusher);
	boost::thread push2(&pusher);
	boost::thread push3(&pusher);

	pop_sync1.join();
	pop_sync2.join();
	pop_sync3.join();

	push1.join();
	push2.join();
	push3.join();

	// assert that no tasks remain
	assert(!g_queue.try_pop_task());

	g_queue.push_task(&do_nothing);
	assert(g_queue.try_pop_task());
}
