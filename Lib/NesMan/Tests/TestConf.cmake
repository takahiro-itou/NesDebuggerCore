
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   NesManagerTest
    COMMAND  $<TARGET_FILE:NesManagerTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(NesManagerTest       NesManagerTest.cpp)

