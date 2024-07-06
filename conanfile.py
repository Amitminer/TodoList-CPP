from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps


class MyProjectConan(ConanFile):
    name = "todo-list"
    version = "1.7"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    requires = ("sqlitecpp/3.3.1")
    generators = "CMakeToolchain", "CMakeDeps"

    def layout(self):
        self.folders.build = "build"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
