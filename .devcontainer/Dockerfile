#FROM i386/ubuntu:18.04
FROM ubuntu:18.04

# Base stuff

RUN apt-get update 
# Setup what's needed to get the latest release of cmake (>3.10)
RUN apt-get install -y apt-transport-https ca-certificates gnupg software-properties-common wget

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null


RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN apt-get install -y --no-install-recommends cmake

RUN apt-get install -y --no-install-recommends \
    libssl-dev \
    openssl \
    libtool \
    autoconf \
    automake \
    build-essential \
    uuid-dev 

RUN apt-get install -y --no-install-recommends \
    tofrodos \
    curl \
    tree \
    silversearcher-ag \
    valgrind \
    git 

RUN apt-get install -y --no-install-recommends \
    libcairo2-dev \
    libgraphicsmagick1-dev \
    libpng-dev 

RUN apt-get install -y --no-install-recommends \
    libxi-dev \
    libopenal-dev \
    libgl1-mesa-dev \
    libglw1-mesa-dev \
    freeglut3-dev 

RUN apt-get install -y --no-install-recommends libboost-dev
 
# because, why not?
RUN apt-get install -y --no-install-recommends sudo vim

#RUN apt-get install -y --no-install-recommends clang-10
RUN curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
 | tar -xJC . && \
 mv clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04 clang_10 && \
 echo "export PATH=/clang_10/bin:$PATH" >> ~/.bashrc && \
 echo "export LD_LIBRARY_PATH=/clang_10/lib:$LD_LIBRARY_PATH" >> ~/.bashrc

#RUN echo ‘export PATH=/clang_10/bin:$PATH’ >> ~/.bashrc && echo ‘export LD_LIBRARY_PATH=/clang_10/lib:$LD_LIBRARY_PATH’ >> ~/.bashrc
RUN git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
RUN cd P0267_RefImpl && mkdir build && cd build && pwd && cmake .. && make install


RUN apt-get autoremove


#RUN rm -rf /var/lib/apt/lists/*



