#include <map>
#include <string>
#include <thread>
#include <shared_mutex>
#include <mutex>

#include <boost/thread/thread.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

/* General notes:
 * - shared locking: access resource from multiple threads (readers)
 * - When we try to unique lock a resource that is shared locked, operations will be blocked until there are no read (shared) locks 
 *   remaining and only after that resource is unique locked, forcing new shared locks to wait until the unique lock is released.
*/




struct user_info {
	std::string address;
	unsigned short age;

	// other stuff
};


/////////////////////
// Boost ////////////
/////////////////////

class users_online {
	typedef boost::shared_mutex 				mutex_t;
	mutable mutex_t											users_mutex_; // mutable: can be modified in const member functions
	std::map<std::string, user_info>		users_;

public:
	bool is_online(const std::string& username) const {
		boost::shared_lock<mutex_t> lock(users_mutex_);
		return users_.find(username) != users_.end();
	}

	unsigned short get_age(const std::string& username) const {
		boost::shared_lock<mutex_t> lock(users_mutex_);
		return users_.at(username).age;
	}
	
	void set_online(const std::string& username, const user_info& data) {
		boost::lock_guard<mutex_t> lock(users_mutex_);
		users_.insert(std::make_pair(username, data));
	}

	// ...

};

static users_online users;


static void worker() {
	for (int i = 0; i < 300; ++i) {
		users.set_online("Lukas", user_info{"Zürich", 37});
		(void)users.get_age("Lukas");
		(void)users.is_online("Lukas");
	}
}




/////////////////////
// C++17 ////////////
/////////////////////

class users_online_std {
	typedef std::shared_mutex 				mutex_t; // C++17 at least needed
	mutable mutex_t											users_mutex_;
	std::map<std::string, user_info>		users_;

public:
	bool is_online(const std::string& username) const {
		std::shared_lock<mutex_t> lock(users_mutex_);
		return users_.find(username) != users_.end();
	}

	unsigned short get_age(const std::string& username) const {
		std::shared_lock<mutex_t> lock(users_mutex_);
		return users_.at(username).age;
	}
	
	void set_online(const std::string& username, const user_info& data) {
		std::lock_guard<mutex_t> lock(users_mutex_);
		users_.insert(std::make_pair(username, data));
	}

	// ...

};

static users_online_std users_std;


static void worker_std() {
	for (int i = 0; i < 300; ++i) {
		users_std.set_online("Lukas", user_info{"Zürich", 37});
		(void)users_std.get_age("Lukas");
		(void)users_std.is_online("Lukas");
	}
}



/////////////////////
// Tests ////////////
/////////////////////

int main() {
	// Boost //////////////////
	boost::thread t1(&worker);
	boost::thread t2(&worker);
	boost::thread t3(&worker);

	t1.join();
	t2.join();
	t3.join();


	// C++17 //////////////////
	std::thread t4(&worker_std);
	std::thread t5(&worker_std);
	std::thread t6(&worker_std);

	t4.join();
	t5.join();
	t6.join();

}
