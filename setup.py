import json
import os
import subprocess
import sys
from pathlib import Path

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext


# A CMakeExtension needs a sourcedir instead of a file list.
# The name must be the _single_ output extension from the CMake build.
# If you need multiple extensions, see scikit-build.
class CMakeExtension(Extension):
    def __init__(self, name: str, source_dir: str = '') -> None:
        super().__init__(name, sources=[])
        self.source_dir = os.fspath(Path(source_dir).resolve())


with open('vcpkg.json', 'r') as vcpkg_file:
    vcpkg_json = json.load(vcpkg_file)
    version = vcpkg_json['version-string']
    commit = vcpkg_json['builtin-baseline']


def update_submodule(path, url, commit_or_tag):
    if not os.path.exists(path) or len(os.listdir(path)) == 0:
        print(f'{path} path does not exist or empty')

    if not os.path.exists(path):
        print(f'creating {path} path')
        os.mkdir(path)

    print(f'cloning {url}...')

    subprocess.run(['git', 'init'], cwd=path, check=True)
    subprocess.run(['git', 'remote', 'add', 'origin', url], cwd=path, check=True)
    subprocess.run(['git', 'fetch', '--depth', '1', 'origin', commit_or_tag], cwd=path, check=True)
    subprocess.run(['git', 'checkout', 'FETCH_HEAD'], cwd=path, check=True)
    subprocess.run(['git', 'submodule', 'update', '--init', '--recursive', '--depth', '1'], cwd=path, check=True)


class CMakeBuild(build_ext):
    def build_extension(self, ext: CMakeExtension) -> None:
        # Must be in this form due to bug in .resolve() only fixed in Python 3.10+
        ext_fullpath = Path.cwd() / self.get_ext_fullpath(ext.name)
        ext_dir = ext_fullpath.parent.resolve()

        cfg = 'Debug'

        # Set Python_EXECUTABLE instead if you use PYBIND11_FINDPYTHON
        # EXAMPLE_VERSION_INFO shows you how to pass a value into the C++ code
        # from Python.
        cmake_args = [
            f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={ext_dir}{os.sep}',
            f'-DPYTHON_EXECUTABLE={sys.executable}',
            f'-DCMAKE_BUILD_TYPE={cfg}',  # not used on MSVC, but no harm
            f'-DPy=ON'
        ]
        build_args = []

        build_temp = Path(self.build_temp) / ext.name
        if not build_temp.exists():
            build_temp.mkdir(parents=True)

        vcpkg_path = os.path.join(ext.source_dir, 'vcpkg')
        update_submodule(path=vcpkg_path, url='https://github.com/microsoft/vcpkg', commit_or_tag=commit)

        pybind11_path = os.path.join(ext.source_dir, 'src', 'py', 'pybind11')
        update_submodule(path=pybind11_path, url='https://github.com/pybind/pybind11', commit_or_tag='v2.11.1')

        subprocess.run(
            ['cmake', ext.source_dir, *cmake_args], cwd=build_temp, check=True
        )
        subprocess.run(
            ['cmake', '--build', '.', *build_args], cwd=build_temp, check=True
        )


setup(
    name='dinapy',
    version=version,
    author='Igor Kozlov',
    author_email='igorkozlov1992@gmail.com',
    description='A test project using pybind11 and CMake',
    long_description='',
    ext_modules=[CMakeExtension('dinapy')],
    cmdclass={'build_ext': CMakeBuild},
    zip_safe=False,
    python_requires='>=3.7',
)
