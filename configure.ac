
dnl ----------------------------------------------------------------
dnl
dnl   Package Configurations.
dnl   パッケージ設定。
dnl

dnl
dnl   要求する autoconf のバージョンを指定する。
dnl

AC_PREREQ([2.68])

dnl
dnl   パッケージの情報を指定する。
dnl

AC_INIT(
    [NesDbg],
    [0.0.0],
    [BUG-REPORT-ADDRESS],
    [NesDbg])

dnl
dnl   ツールの出力ディレクトリを指定する。
dnl

AC_CONFIG_AUX_DIR([.Config])

dnl
dnl   ターゲットシステムを判定
dnl

m4_include([.M4/TargetSystem.m4])

dnl
dnl   適当なバージョンの automake を設定
dnl

m4_include([.M4/InitAutoMake.m4])


dnl ----------------------------------------------------------------
dnl
dnl   プロジェクトの基本設定。
dnl

AC_CONFIG_SRCDIR([Makefile.am])
AC_LANG([C++])

dnl
dnl   デフォルトのビルドオプション
dnl

m4_include([.M4/DefaultBuildOptions.m4])

dnl
dnl   Project Name Space.
dnl

NESDBG_CNF_NAMESPACE=NesDbg
AC_SUBST(NESDBG_CNF_NAMESPACE)


dnl ----------------------------------------------------------------
dnl
dnl   ディレクトリ名。
dnl

m4_include([.M4/ConfigDirectory.m4])

myac_customize_library_dir([Lib])
myac_customize_binary_dir([Bin])
myac_customize_include_dir(
    [Include], [NesDbg], [.Config], [Config.h])


dnl ----------------------------------------------------------------
dnl
dnl   ビルド環境の検査。
dnl

dnl
dnl   Check Programs.
dnl

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_RANLIB

dnl
dnl   Check Header Files.
dnl

dnl
dnl   Check Libraries.
dnl

dnl
dnl   Check Types.
dnl

dnl
dnl   Check Extra Compiler/Linker Options.
dnl

m4_include([.M4/Checks/CheckExtraFlags.m4])
m4_include([.M4/Checks/EnableCxx11.m4])

m4_include([.M4/Checks/ConstExpr.m4])
m4_include([.M4/Checks/NullPtr.m4])
m4_include([.M4/Checks/Override.m4])
m4_include([.M4/Checks/StaticAssert.m4])
m4_include([.M4/Checks/RightValueReference.m4])
m4_include([.M4/Checks/DefaultDeclarations.m4])


dnl ----------------------------------------------------------------
dnl
dnl   Additional Packages.
dnl   外部パッケージの追加
dnl

m4_include([.M4/Packages/WithExtPkgs.m4])
m4_include([.M4/Packages/CppUnit.m4])


dnl ----------------------------------------------------------------
dnl
dnl   Linker Scripts.
dnl   リンカスクリプトを生成する。
dnl

m4_include([Lib/.LinkerScript/LinkerScripts.m4])


dnl ----------------------------------------------------------------
dnl
dnl   Outputs.
dnl   出力ファイルを設定する。
dnl

dnl
dnl   Common Festures in Sub Repository.
dnl

m4_include([.CMake/GenConfigFiles.m4])
m4_include([.M4/GenConfigFiles.m4])
m4_include([Lib/Tests/GenConfigFiles.m4])

dnl
dnl   Basic Features.
dnl

AC_CONFIG_FILES([
    Makefile
    Bin/Makefile
    Lib/Makefile
    Lib/.Config/Makefile
    Lib/Common/Makefile
    Lib/Images/Makefile
    Lib/NesMan/Makefile
    Lib/pch/Makefile
])

AC_CONFIG_FILES([
    Include/NesDbg/.Config/ConfiguredNesDbg.h
])

dnl
dnl   Test Festures.
dnl

AC_CONFIG_FILES([
    Lib/Common/Tests/Makefile
    Lib/Images/Tests/Makefile
    Lib/NesMan/Tests/Makefile
    Lib/NesMan/Tests/TestConf.h
])

dnl
dnl   指定したファイルを生成する。
dnl

AC_OUTPUT

