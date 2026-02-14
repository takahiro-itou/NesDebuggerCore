
##
##    List of Tests.
##

extra_tests             =
TESTS                   =  \
        DisCpu6502Test          \
        NesManagerTest          \
        ${extra_tests}

##
##    Test Configurations.
##

target_testee_library       +=  -lnesdbgNesMan

dist_noinst_data_files      +=  hello.nes

dist_noinst_data_files      +=
dist_noinst_header_files    +=
extra_test_drivers          +=
library_test_drivers        +=
source_test_drivers         +=

##
##    Compile and Link Options.
##

test_cppflags_common        +=
test_ldflags_common         +=

##
##    Test Programs.
##

DisCpu6502Test_SOURCES      =  DisCpu6502Test.cpp
NesManagerTest_SOURCES      =  NesManagerTest.cpp

