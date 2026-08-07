"""
This script replaces tools/toolchain/llvm/llvm/utils/docker/nvidia-cuda/Dockerfile and is intended to be run with `python build_nvidia_cuda.py` instead of `docker build`.
The build plan is expressed as Python metadata so the original Dockerfile intent is preserved.
"""

from __future__ import annotations

try:
    import docker
except ImportError:  # pragma: no cover
    docker = None

BASE_IMAGE = 'nvidia/cuda:8.0-devel'
BUILD_ARGS = {'checkout_args': None, 'buildscript_args': None}
ENV_VARS = {}
RUN_STEPS = ['apt-get update && \\', '/tmp/scripts/checkout.sh ${checkout_args}', '/tmp/scripts/build_install_llvm.sh --to /tmp/clang-install ${buildscript_args}']
COPY_STEPS = ['checksums /tmp/checksums', 'scripts /tmp/scripts', '--from=builder /tmp/clang-install/ /usr/local/']
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
