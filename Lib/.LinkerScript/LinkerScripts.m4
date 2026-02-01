dnl----------------------------------------------------------------
dnl
dnl   Linker Scripts.
dnl   リンカスクリプトを生成する。
dnl

AC_CONFIG_FILES([Lib/libsampleBar.a:Lib/.LinkerScript/Bar.in])
AC_CONFIG_FILES([Lib/libsampleCommon.a:Lib/.LinkerScript/Common.in])
AC_CONFIG_FILES([Lib/libsampleFoo.a:Lib/.LinkerScript/Foo.in])
AC_CONFIG_FILES([Lib/libsampleImages.a:Lib/.LinkerScript/Images.in])

