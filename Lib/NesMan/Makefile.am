
##
##    ライブラリのビルドとインストール。
##

AUTOMAKE_OPTIONS    =  subdir-objects

##
##    List of Directories.
##

module_dir_name     =  NesMan
SUBDIRS             =  .  Tests

include  $(top_srcdir)/.M4/BuildCommon/DirList.inc
include  $(top_srcdir)/.M4/BuildCommon/DefVars.inc

##
##    List of Source and Header Files.
##

extra_library_source_files  =
extra_library_header_files  =
extra_noinst_data_files     =
extra_noinst_header_files   =

library_source_files        +=  \
        BaseCpuCore.cpp                 \
        BaseDisCpu.cpp                  \
        MemoryManager.cpp               \
        NesManager.cpp                  \
        Cpu6502/Cpu6502.cpp             \
        Cpu6502/Dis6502.cpp             \
        ${extra_library_source_files}

library_instantiations      +=
library_inline_files        +=

dist_noinst_data_files      +=  \
        ${extra_noinst_data_files}

dist_noinst_header_files    +=  \
        Cpu6502/AddressingMode.h        \
        Cpu6502/Cpu6502.h               \
        Cpu6502/Dis6502.h               \
        Cpu6502/Instructions.inl        \
        Cpu6502/InstTable.h             \
        ${extra_noinst_header_files}

inclib_header_files         +=  \
        ${inclib_source_dir}/BaseCpuCore.h      \
        ${inclib_source_dir}/BaseDisCpu.h       \
        ${inclib_source_dir}/CpuUtils.h         \
        ${inclib_source_dir}/MemoryManager.h    \
        ${inclib_source_dir}/NesManager.h       \
        ${extra_library_header_files}

inclib_nodist_header_files  +=

library_install_srcfiles    +=  \
        ${library_inline_files}

library_compile_srcfiles    +=  \
        ${library_source_files}    \
        ${library_instantiations}

##
##    List of Libraries.
##

static_libraries_list   +=  libnesdbgNesMan.static.a
shared_libraries_list   +=

##
##    Internal Libraries.
##

##
##    Include Common Install Settings.
##

include  $(top_srcdir)/.M4/BuildCommon/Install.inc

##
##    Build Libraries.
##

libnesdbgNesMan_static_a_SOURCES    =  ${library_source_files}

