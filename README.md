<h1 align="center">Haze-Dumper Plugin SDK</h1>
<p align="center">A software development kit (SDK) to develop C++ plugins for the haze-dumper or to extend the Lua API.</p>
<p align="center">
  <a target="_blank"><img src="https://img.shields.io/badge/CMake-3.15-blue" alt="CMake Version" /></a>
  <a target="_blank"><img src="https://img.shields.io/badge/Clang-13-41B883" alt="Clang Version" /></a>
  <a target="_blank"><img src="https://img.shields.io/badge/LuaJIT-5.1.0--beta3-4e67d9" alt="LuaJIT Version" /></a>
  <a target="_blank"><img src="https://img.shields.io/badge/Visual Studio-2022-purple" alt="Visual Studio Version" /></a>
</p>

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Local Development](#local-development)
  - [Windows](#windows)
  - [MacOS](#macos)
  - [Linux](#linux)
- [3rd party libraries](#3rd-party-libraries)

## Local Development

1. Install `git`
   1. Arch: `sudo pacman -S git`
   2. Ubuntu/Debian: `sudo apt install -y git`
   3. Fedora: `sudo dnf install git-all`
   4. Windows: [git for windows](https://git-scm.com/download/win)
2. Clone the repository recursively: `git clone --recursive https://github.com/hazedumper/hazedumper`

### Windows

1. Install [Visual Studio 2022](https://visualstudio.microsoft.com/vs/)
2. Open the `Developer PowerShell for VS 2022`
3. Navigate into the repository
4. Enter the code below to build [LuaJIT]((https://luajit.org/)) from source

```Powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; .\build_lua_jit.ps1
```

5. Open the `hazedumper.sln` in Visual Studio 2022

### MacOS

### Linux

1. Install [LuaJIT]((https://luajit.org/)) using your systems package manager or follow their official [installation instruction](https://luajit.org/install.html):
   1. Arch: `sudo pacman -S luajit`
   2. Ubuntu/Debian: `sudo apt install -y libluajit-5.1-dev`
   3. Fedora: `sudo yum install luajit`

## 3rd party libraries

- [@Mike Pall](https://github.com/MikePall) - [The LuaJIT Project](https://luajit.org/)
- [@jarro2783](https://github.com/jarro2783) - [Lightweight C++ command line option parser](https://github.com/jarro2783/cxxopts)
