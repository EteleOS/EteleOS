"""
This script replaces tools/toolchain/llvm/libcxx/utils/ci/vendor/android/Dockerfile.emulator and is intended to be run with `python build_android.py` instead of `docker build`.
The build plan is expressed as Python metadata so the original Dockerfile intent is preserved.
"""

from __future__ import annotations

try:
    import docker
except ImportError:  # pragma: no cover
    docker = None

BASE_IMAGE = 'ubuntu:jammy'
BUILD_ARGS = {'API  # e.g. 21': None, 'TYPE  # one of: default, google_apis, or google_apis_playstore': None, 'ABI   # e.g. armeabi-v7a, x86': None}
ENV_VARS = {'ANDROID_HOME': '/opt/android/sdk', 'PATH': '"${ANDROID_HOME}/platform-tools:${PATH}"', 'EMU_PACKAGE_NAME': '"system-images;android-${API};${TYPE};${ABI}"', 'EMU_PARTITION_SIZE': '8192'}
RUN_STEPS = ['apt-get update && apt-get install -y \\', 'curl -sL https://dl.google.com/android/repository/commandlinetools-linux-9477386_latest.zip -o cmdline-tools.zip && \\', 'yes | sdkmanager --licenses', 'sdkmanager --install emulator', 'sdkmanager --install "platforms;android-${API}"', 'sdkmanager --install "${EMU_PACKAGE_NAME}"', 'echo "ALL ALL = (ALL) NOPASSWD: ALL" >> /etc/sudoers', 'useradd --create-home emulator']
COPY_STEPS = ['./emulator-entrypoint.sh /opt/emulator/bin/emulator-entrypoint.sh', './emulator-wait-for-ready.sh /opt/emulator/bin/emulator-wait-for-ready.sh']
PORTS = ['5037']
CMD = None
ENTRYPOINT = '["emulator-entrypoint.sh"]'

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
