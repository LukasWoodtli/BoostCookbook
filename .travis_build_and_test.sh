set -u
set -e
set -x

mkdir build
cd build
cmake -G 'Unix Makefiles' ..
make
./02_ConvertingData/ParsingInput
make test
