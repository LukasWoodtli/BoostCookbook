struct spinlock_t {
    bool try_lock();
};

struct port_t {
    bool block_ready();
};

template <class T> bool copy_to_buffer(T& /*value*/);
template <class T> void process(T& /*value*/);

#include <iostream>

#include <boost/coroutine2/coroutine.hpp>
typedef boost::coroutines2::asymmetric_coroutine<std::size_t> corout_t;

struct coroutine_task {
	std::string& result;

	coroutine_task(std::string& r)
		: result(r)
		{}

	void operator()(corout_t::pull_type& yield);

private:
	std::size_t ticks_to_work;
	void tick(corout_t::pull_type& yield);
};


void coroutine_task::operator()(corout_t::pull_type& yield) {
	ticks_to_work = yield.get();

	std::string buffer0;

	while (1) {
		const bool requires_1_more_copy = copy_to_buffer(buffer0);
		tick(yield);

		if (requires_1_more_copy) {
			std::string buffer1;

			copy_to_buffer(buffer1);
			tick(yield);

			process(buffer1);
			tick(yield);
		}

			process(buffer0);
			tick(yield);
	}
}

void coroutine_task::tick(corout_t::pull_type& yield) {
	result += 'o';

	if (ticks_to_work != 0) {
		--ticks_to_work;
	}

	if (ticks_to_work == 0) {
		// switching back to main
		yield();

		ticks_to_work = yield.get();
	}
}

int main() {
	std::string result;
	coroutine_task task(result);
	corout_t::push_type coroutine(task);

	spinlock_t spinlock;
	port_t port;

	while (!spinlock.try_lock()) {
		coroutine(10);
	}

	assert(result.size() == 10 * 100);
	result.clear();

	while (!port.block_ready()) {
		coroutine(300);
	}

	assert(result.size() == 10 * 300);
	std::cout << "Ok!\n";
}

// details:

template <class T> bool copy_to_buffer(T& /*value*/) {
    static std::size_t i = 0;
    ++ i;
     return i & 1;
}

template <class T> void process(T& /*value*/) {}

bool spinlock_t::try_lock() {
    static int i = 0;
    return i++ >= 100;
}

bool port_t::block_ready() {
    static int i = 0;
    return i++ >= 10;
}

