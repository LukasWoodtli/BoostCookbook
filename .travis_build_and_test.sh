set -u
set -e

mkdir build
cd build
cmake -G 'Unix Makefiles' ..
make
./03_ManagingResources/FunctionalObjectsInVariable
make test
