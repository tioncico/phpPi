dnl $Id$
dnl config.m4 for extension phpPi

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(phpPi, for phpPi support,
dnl Make sure that the comment is aligned:
[  --with-phpPi          Include phpPi support])
PHP_ADD_LIBRARY_WITH_PATH(wiringPi, /usr/lib/, SAY_SHARED_LIBADD)
PHP_SUBST(SAY_SHARED_LIBADD)

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(phpPi, whether to enable phpPi support,
dnl Make sure that the comment is aligned:
dnl [  --enable-phpPi           Enable phpPi support])

if test "$PHP_PHPPI" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-phpPi -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/phpPi.h"  # you most likely want to change this
  dnl if test -r $PHP_PHPPI/$SEARCH_FOR; then # path given as parameter
  dnl   PHPPI_DIR=$PHP_PHPPI
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for phpPi files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHPPI_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHPPI_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the phpPi distribution])
  dnl fi

  dnl # --with-phpPi -> add include path
  dnl PHP_ADD_INCLUDE($PHPPI_DIR/include)

  dnl # --with-phpPi -> check for lib and symbol presence
  dnl LIBNAME=phpPi # you may want to change this
  dnl LIBSYMBOL=phpPi # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHPPI_DIR/$PHP_LIBDIR, PHPPI_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHPPILIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong phpPi lib version or lib not found])
  dnl ],[
  dnl   -L$PHPPI_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHPPI_SHARED_LIBADD)

  PHP_NEW_EXTENSION(phpPi, phpPi.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
