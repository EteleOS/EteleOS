"""
This script replaces tools/toolchain/llvm/clang/utils/analyzer/Dockerfile and is intended to be run with `python build_analyzer.py` instead of `docker build`.
The build plan is expressed as Python metadata so the original Dockerfile intent is preserved.
"""

from __future__ import annotations

try:
    import docker
except ImportError:  # pragma: no cover
    docker = None

BASE_IMAGE = 'ubuntu:bionic'
BUILD_ARGS = {}
ENV_VARS = {'PATH': '"/analyzer/bin:${PATH}"'}
RUN_STEPS = ['apt-get update && apt-get install -y \\', 'wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null', "apt-add-repository -y 'deb https://apt.kitware.com/ubuntu/ bionic main'", 'apt-get update && apt-get install -y \\', 'apt-get install -y \\', 'apt-get install -y \\', 'apt-get install -y \\', 'apt-get install -y \\', 'apt-get install -y \\', 'apt-get install -y \\', 'update-alternatives --install /usr/bin/python python /usr/bin/python3 1', 'pip3 install -r /requirements.txt']
COPY_STEPS = ['entrypoint.py /entrypoint.py', 'requirements.txt /requirements.txt']
PORTS = []
CMD = None
ENTRYPOINT = '["python", "/entrypoint.py"]'

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
