
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   DisCpu6502Test
    COMMAND  $<TARGET_FILE:DisCpu6502Test>
)

add_test(NAME   NesManagerTest
    COMMAND  $<TARGET_FILE:NesManagerTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(DisCpu6502Test       DisCpu6502Test.cpp)
add_executable(NesManagerTest       NesManagerTest.cpp)

