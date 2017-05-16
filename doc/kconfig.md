The MCU C++ library can be customized with the same tool that the Linux kernel use; kconfig.

The CMake function `mcucpp_configure_target(TARGET foo)` want to create a target called `foo-kconfig` that launches the
configuration tool for you. However, if the `kconfig` program can't be found in your system's PATH you will get a 
warning when configuring your build.

There are no good binary builds of `kconfig` but for Linux and Cygwin on Windows there are a Git repository that can be
used: `http://ymorin.is-a-geek.org/git/kconfig-frontends`. Building it is fairly easy:

    git clone http://ymorin.is-a-geek.org/git/kconfig-frontends
    cd kconfig-frontends
    autoreconf -fi
    ./configure --prefix=$(pwd)/kconfig-frontends
    make install -j

Note that if you first run CMake, get the error message, fix the problem and then run CMake again you will still get the
problem because CMake cached the search. The easiest way to just nuke the current build directory and re-run CMake. If
you don't want to do that, you can run `ccmake $src_dir` and remove the `KCONFIG_PROGRAM` cache entry.
