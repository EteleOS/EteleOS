"""
This script replaces tools/toolchain/llvm/libcxx/utils/ci/Dockerfile and is intended to be run with `python build_ci.py` instead of `docker build`.
The build plan is expressed as Python metadata so the original Dockerfile intent is preserved.
"""

from __future__ import annotations

try:
    import docker
except ImportError:  # pragma: no cover
    docker = None

BASE_IMAGE = 'builder-base'
BUILD_ARGS = {'BASE_IMAGE': None, 'GCC_LATEST_VERSION': None, 'LLVM_HEAD_VERSION': None, 'ANDROID_CLANG_VERSION': None, 'ANDROID_CLANG_PREBUILTS_COMMIT': None, 'ANDROID_SYSROOT_BID': None}
ENV_VARS = {'DEBIAN_FRONTEND': 'noninteractive', 'GCC_LATEST_VERSION': '${GCC_LATEST_VERSION}', 'LLVM_HEAD_VERSION': '${LLVM_HEAD_VERSION}', 'ANDROID_CLANG_VERSION': '$ANDROID_CLANG_VERSION', 'ANDROID_CLANG_PREBUILTS_COMMIT': '$ANDROID_CLANG_PREBUILTS_COMMIT', 'ANDROID_SYSROOT_BID': '$ANDROID_SYSROOT_BID', 'PATH': '"/opt/android/sdk/platform-tools:${PATH}"'}
RUN_STEPS = ['<<EOF', 'sudo apt-get update \\', 'sudo apt-get update \\', '<<EOF', '<<EOF', '<<EOF', '<<EOF', '<<EOF', 'apt-get update && apt-get install -y curl unzip git', '<<EOF', '<<EOF', '<<EOF', '<<EOF', 'sudo useradd --create-home libcxx-builder', '<<EOF', 'cp /home/libcxx-builder/.buildkite-agent/buildkite-agent.dist.cfg \\']
COPY_STEPS = ['--from=android-builder-base /opt/android /opt/android', './vendor/android/container-setup.sh /opt/android/container-setup.sh']
PORTS = []
CMD = '/opt/android/container-setup.sh && buildkite-agent start'
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
