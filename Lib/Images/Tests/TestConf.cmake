
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   FullColorImageTest
    COMMAND  $<TARGET_FILE:FullColorImageTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(FullColorImageTest       FullColorImageTest.cpp)

