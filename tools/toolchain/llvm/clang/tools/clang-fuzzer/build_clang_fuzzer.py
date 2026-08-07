"""
This script replaces tools/toolchain/llvm/clang/tools/clang-fuzzer/Dockerfile and is intended to be run with `python build_clang_fuzzer.py` instead of `docker build`.
The build plan is expressed as Python metadata so the original Dockerfile intent is preserved.
"""

from __future__ import annotations

try:
    import docker
except ImportError:  # pragma: no cover
    docker = None

BASE_IMAGE = 'ubuntu:16.04'
BUILD_ARGS = {}
ENV_VARS = {}
RUN_STEPS = ['apt-get update -y', 'apt-get install -y autoconf automake libtool curl make g++ unzip wget git \\', 'wget -qO- https://github.com/google/protobuf/releases/download/v3.3.0/protobuf-cpp-3.3.0.tar.gz | tar zxf -', 'cd protobuf-3.3.0 && ./autogen.sh && ./configure && make -j $(nproc) && make check -j $(nproc) && make install && ldconfig', 'svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm', "cd llvm/tools && svn co http://llvm.org/svn/llvm-project/cfe/trunk clang -r $(cd ../ && svn info | grep Revision | awk '{print $2}')", "cd llvm/projects && svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt -r $(cd ../ && svn info | grep Revision | awk '{print $2}')", 'mkdir build0 && cd build0 && cmake -GNinja -DCMAKE_BUILD_TYPE=Release ../llvm && ninja', 'mkdir build1 && cd build1 && cmake -GNinja -DCMAKE_BUILD_TYPE=Release ../llvm \\', 'cd build1 && ninja clang-fuzzer', 'cd build1 && ninja clang-objc-fuzzer', 'cd build1 && ninja clang-proto-fuzzer', 'cd build1 && ninja clang-proto-to-cxx', 'cd build1 && ninja clang-loop-proto-to-cxx', 'cd build1 && ninja clang-loop-proto-to-llvm', 'cd build1 && ninja clang-loop-proto-fuzzer', 'cd build1 && ninja clang-llvm-proto-fuzzer']
COPY_STEPS = []
PORTS = []
CMD = None
ENTRYPOINT = None

def build_plan():
    return {
        'base_image': BASE_IMAGE,
        'build_args': BUILD_ARGS,
        'environment': ENV_VARS,
        'run_steps': RUN_STEPS,
        'copy_steps': COPY_STEPS,
        'ports': PORTS,
        'cmd': CMD,
        'entrypoint': ENTRYPOINT,
    }

def build_image(path=".", tag="local-image") -> object:
    if docker is None:
        raise RuntimeError("docker package is required to build the image")
    client = docker.from_env()
    return client.images.build(path=path, tag=tag, buildargs=BUILD_ARGS, pull=True)

if __name__ == "__main__":
    print(build_plan())
