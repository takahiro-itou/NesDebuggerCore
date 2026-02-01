
##
##    List of Tests.
##

extra_tests             =
TESTS                   =  \
        FooTest            \
        ${extra_tests}
##
##    Test Configurations.
##

target_testee_library       +=  -lsampleFoo

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

FooTest_SOURCES     =  FooTest.cpp

