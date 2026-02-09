
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(module_title        "NesMan")

Include (${common_cmake_dir}/BuildCommon/ConfigModule.cmake)
Include (${common_cmake_dir}/BuildCommon/ConfigTarget.cmake)

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

set(library_source_files
        BaseCpuCore.cpp
        BaseDisCpu.cpp
        MemoryManager.cpp
        NesManager.cpp
        Cpu6502/Cpu6502.cpp
        Cpu6502/Dis6502.cpp
)

set(inclib_header_files
        ${inclib_source_dir}/BaseCpuCore.h
        ${inclib_source_dir}/BaseDisCpu.h
        ${inclib_source_dir}/CpuUtils.h
        ${inclib_source_dir}/MemoryManager.h
        ${inclib_source_dir}/NesManger.h
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${common_cmake_dir}/BuildCommon/BuildLib.cmake)
Include (${common_cmake_dir}/BuildCommon/Install.cmake)

##----------------------------------------------------------------
##
##    テストの設定。
##

Add_SubDirectory (Tests)
