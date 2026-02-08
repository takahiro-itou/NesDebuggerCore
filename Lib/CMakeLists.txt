
##----------------------------------------------------------------
##
##    プロジェクトの基本設定。
##

set(libraries_target_prefix)

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

add_subdirectory(Tests)
add_subdirectory(.Config)

add_subdirectory(Common)
add_subdirectory(Images)
add_subdirectory(NesMan)

