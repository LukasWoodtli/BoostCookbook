#include <boost/scope_exit.hpp>
#include <cstdio>


#define ASSERT(p) do{if(!p) exit(EXIT_FAILURE);}while(0)


static bool testFileClosed = false;

void file_handling(bool simlateThrow) {
    std::FILE* f = std::fopen("example_file.txt", "w");
    ASSERT(f);
    
    BOOST_SCOPE_EXIT(f) {
        std::fclose(f);
        testFileClosed = true;
    } BOOST_SCOPE_EXIT_END
    
    // some code that could throw
    if (simlateThrow)
        throw int();
}
    


int main() {
    testFileClosed = false;
    file_handling(false);
    ASSERT(testFileClosed);
    
    try {
        testFileClosed = false;
        file_handling(true);
    }
    catch(...) {}
    ASSERT(testFileClosed);
}
