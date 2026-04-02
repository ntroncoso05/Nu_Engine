# !/bin/bash

# output directory
target="Targets/$1"

#active python env
source ~/nu/bin/activate

# install conan dependencies
conan install . --install-folder $target --build missing -s build_type=$1 -c tools.system.package_manager:sudo=True -c tools.system.package_manager:mode=install

# generate cmake build files
cmake -S . -B $target -DCMAKE_BUILD_TYPE=$1 -DCMAKE_TOOLCHAIN_FILE="conanbuildinfo.cmake"

# compile cmake build files
cmake --build $target --config $1