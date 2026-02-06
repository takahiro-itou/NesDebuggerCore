dnl----------------------------------------------------------------
dnl
dnl   Linker Scripts.
dnl   リンカスクリプトを生成する。
dnl

AC_CONFIG_FILES([Lib/libsampleCommon.a:Lib/.LinkerScript/Common.in])
AC_CONFIG_FILES([Lib/libsampleImages.a:Lib/.LinkerScript/Images.in])
AC_CONFIG_FILES([Lib/libnesdbgNesMan.a:Lib/.LinkerScript/NesMan.in])

