set -u
set -e

mkdir build
cd build
cmake -G 'Unix Makefiles' ..
make
./02_ConvertingData/ParsingInput
make test
