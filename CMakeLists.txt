
##----------------------------------------------------------------
##
##    Package Configurations.
##    パッケージ設定。
##

##
##    要求するツールのバージョンを指定する。
##

cmake_minimum_required(VERSION  3.0.2)

##
##    パッケージの情報を指定する。
##

set(project_name        Sample)
set(serial              "0.0.0")

project(${project_name}     VERSION  1.0.0)


##
##    共通の .cmake ファイルの置いてある場所。
##

set(common_cmake_dir        "${PROJECT_SOURCE_DIR}/.CMake")

##
##    ターゲットシステムを判定
##

Include (${common_cmake_dir}/TargetSystem.cmake)


##----------------------------------------------------------------
##
##    プロジェクトの基本設定。
##

##
##    デフォルトのビルドオプション。
##

Include (${common_cmake_dir}/DefaultBuildOptions.cmake)

##
##    Project Name Space.
##

set(SAMPLE_CNF_NAMESPACE    Sample)


##----------------------------------------------------------------
##
##    ディレクトリ名。
##

set(inctop_dir_name         "Include")
set(bintop_dir_name         "Bin")
set(libtop_dir_name         "Lib")

Include (${common_cmake_dir}/ConfigDirectory.cmake)


##----------------------------------------------------------------
##
##    ビルド環境の検査。
##

##
##    Check Programs.
##

##
##    Check Header Files.
##

##
##    Check Libraries.
##

##
##    Check Types.
##

##
##    Check Extra Compiler/Linker Options.
##

Include (${common_cmake_dir}/Checks/EnableCxx11.cmake)

Include (${common_cmake_dir}/Checks/ConstExpr.cmake)
Include (${common_cmake_dir}/Checks/NullPtr.cmake)
Include (${common_cmake_dir}/Checks/Override.cmake)
Include (${common_cmake_dir}/Checks/StaticAssert.cmake)
Include (${common_cmake_dir}/Checks/RightValueReference.cmake)
Include (${common_cmake_dir}/Checks/DefaultDeclarations.cmake)


##----------------------------------------------------------------
##
##    Additional Packages.
##    外部ライブラリ。
##

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}  ${common_cmake_dir}/Packages
)

Find_Package (CppUnit)

##----------------------------------------------------------------
##
##    設定を書き込んだファイルを生成。
##

configure_file(
    "${incpkg_source_dir}/.Config/ConfiguredSample.h.in"
    "${incpkg_binary_dir}/.Config/ConfiguredSample.h"
)

configure_file(
    "${incpkg_source_dir}/.Config/Config.h.cmake.in"
    "${incpkg_binary_dir}/.Config/.${project_name}.Config.h"
)

##----------------------------------------------------------------
##
##    パッケージコンフィグレーション。
##

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${project_name}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${project_name}Config.cmake"
    @ONLY
)

install(FILES   "${CMAKE_CURRENT_BINARY_DIR}/${project_name}Config.cmake"
        DESTINATION  .
)

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

Add_SubDirectory (Lib)
Add_SubDirectory (Bin)
