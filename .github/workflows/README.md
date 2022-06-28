<h1>Reusable workflows</h1>

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Build LuaJIT](#build-luajit)
  - [lua_version](#lua_version)
  - [artifact_name](#artifact_name)
  - [upload_artifact](#upload_artifact)
- [Build Visual Studio project](#build-visual-studio-project)
  - [architecture](#architecture)
  - [configuration](#configuration)
  - [cpu_count](#cpu_count)
  - [output_file](#output_file)
  - [output_extension](#output_extension)
  - [artifact_name](#artifact_name-1)
  - [upload_pdb](#upload_pdb)
  - [pre_build_script](#pre_build_script)
  - [required_artifacts](#required_artifacts)
  - [required_artifacts_path](#required_artifacts_path)
- [Delete Artifacts](#delete-artifacts)
  - [name](#name)

## [Build LuaJIT](build_lua_jit.yml)

Builds [LuaJIT](https://luajit.org/) from source for *Windows, __x64__*.

### lua_version

- required: `true`
- type: `string`

### artifact_name

- required: `false`
- type: `string`
- default: `LuaJIT`

### upload_artifact

- required: `false`
- type: `bool`
- default: `true`

## [Build Visual Studio project](build_vs_project.yml)

### architecture

Must be either `x64` or `x86`.

- required: `true`
- type: `string`

### configuration

Visual Studio solution configuration (by default `Debug` or `Release`).

- required: `true`
- type: `string`

### cpu_count

- required: `false`
- type: `number`
- default: `16`

### output_file

Name of the compiled file __without__ extension.

- required: `true`
- type: `string`

### output_extension

Must be `dll`, `exe`, `lib` or `sys`.

- required: `true`
- type: `string`

### artifact_name

- required: `true`
- type: `string`
- default: empty string

### upload_pdb

- required: `false`
- type: `bool`
- default: `false`

### pre_build_script

- required: `false`
- type: `string`

### required_artifacts

- required: `false`
- type: `string`

### required_artifacts_path

- required: `false`
- type: `string`

## [Delete Artifacts](delete_artifacts.yml)

### name

- required: `true`
- type: `string`
