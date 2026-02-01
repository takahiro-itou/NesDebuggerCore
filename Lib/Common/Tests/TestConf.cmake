
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   SampleDocumentTest
    COMMAND  $<TARGET_FILE:SampleDocumentTest>
)

add_test(NAME   SampleSettingsTest
    COMMAND  $<TARGET_FILE:SampleSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(SampleDocumentTest       SampleDocumentTest.cpp)
add_executable(SampleSettingsTest       SampleSettingsTest.cpp)
