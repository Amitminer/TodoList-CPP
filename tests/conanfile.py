from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps


class MyProjectConan(ConanFile):
    name = "todolist-benchmarks"
    version = "1.7.5"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    requires = ("sqlitecpp/3.3.1", "fmt/11.0.0", "benchmark/1.8.4")
    generators = "CMakeToolchain", "CMakeDeps"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
