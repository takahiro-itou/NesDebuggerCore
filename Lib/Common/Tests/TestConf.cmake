
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   NesDbgProjectTest
    COMMAND  $<TARGET_FILE:NesDbgProjectTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(NesDbgProjectTest        NesDbgProjectTest.cpp)
