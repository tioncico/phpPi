/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_phpPi.h"
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


static int le_phpPi;

ZEND_BEGIN_ARG_INFO(arginfo_tioncico_test1, 0)//函数名,参数是否为引用类型,0代表不是
ZEND_END_ARG_INFO()//结束函数参数信息声明

ZEND_BEGIN_ARG_INFO(arginfo_tioncico_test2, 0)//函数名,参数是否为引用类型,0代表不是
        ZEND_ARG_INFO(0, str)//声明一个普通参数str
ZEND_END_ARG_INFO()//结束函数参数信息声明
PHP_FUNCTION (wiringPiSetup) {
    int status = wiringPiSetup();
    if (status == -1) {
        RETURN_BOOL(FALSE);
    } else {
        RETURN_BOOL(TRUE);
    }
}

PHP_FUNCTION (wiringPiSetupGpio) {
    int status = wiringPiSetupGpio();
    if (status == -1) {
        RETURN_BOOL(FALSE);
    } else {
        RETURN_BOOL(TRUE);
    }
}


PHP_FUNCTION (wiringPiSetupPhys) {
    wiringPiSetupPhys();
}


PHP_FUNCTION (wiringPiSetupSys) {
    wiringPiSetupSys();
}


PHP_FUNCTION (pinMode) {
    char *pin;
    int pinLength;
    char *model;
    int modelLength;

    if (zend_parse_parameters(2, "ss",&pin, &pinLength,&model, &modelLength) == FAILURE){
        RETURN_BOOL(FALSE);
    }

    php_printf("%s%s",pin,model);
//    pinMode(pin, model);
}
//
PHP_FUNCTION (digitalWrite) {
    int *pin;
    int *value;
    if (zend_parse_parameters(2, "s|s", &pin, &value) == FAILURE) {
        return;
    }
    pin = atoi(pin);
    value = atoi(value);
    digitalWrite(pin, value);
}

PHP_FUNCTION (digitalRead) {
    int *pin;
    if (zend_parse_parameters(1, "s", &pin) == FAILURE) {
        return;
    }
    pin = atoi(pin);
    int retVal = digitalRead(pin);
    RETURN_LONG(retVal);
}


PHP_FUNCTION (pwmWrite) {
    int *pin;
    int *value;

    if (zend_parse_parameters(2, "s|2", &pin, &value) == FAILURE) {
        return;
    }
    pin = atoi(pin);
    value = atoi(value);
    pwmWrite(pin, value);
}

PHP_FUNCTION (pullUpDnControl) {
    int *pin;
    int *pud;
    if (zend_parse_parameters(2, "s|2", &pin, &pud) == FAILURE) {
        return;
    }
    pin = atoi(pin);
    pud = atoi(pud);
    pullUpDnControl(pin, pud);
}

PHP_MINIT_FUNCTION (phpPi) {
    /* If you have INI entries, uncomment these lines
    REGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION (phpPi) {
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}

PHP_RINIT_FUNCTION (phpPi) {
#if defined(COMPILE_DL_PHPPI) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION (phpPi) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION (phpPi) {
    php_info_print_table_start();
    php_info_print_table_header(2, "phpPi support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}

const zend_function_entry phpPi_functions[] = {
        PHP_FE(wiringPiSetup, NULL)        /* For testing, remove later. */
        PHP_FE(wiringPiSetupGpio, NULL)        /* For testing, remove later. */
        PHP_FE(wiringPiSetupPhys, NULL)        /* For testing, remove later. */
        PHP_FE(wiringPiSetupSys, NULL)        /* For testing, remove later. */
        PHP_FE(pinMode, NULL)        /* For testing, remove later. */
//        PHP_FE(digitalWrite, NULL)        /* For testing, remove later. */
//        PHP_FE(digitalRead, NULL)        /* For testing, remove later. */
//        PHP_FE(pullUpDnControl, NULL)        /* For testing, remove later. */
        PHP_FE_END    /* Must be the last line in phpPi_functions[] */
};
zend_module_entry phpPi_module_entry = {
        STANDARD_MODULE_HEADER,
        "phpPi",
        phpPi_functions,
        PHP_MINIT(phpPi),
        PHP_MSHUTDOWN(phpPi),
        PHP_RINIT(phpPi),        /* Replace with NULL if there's nothing to do at request start */
        PHP_RSHUTDOWN(phpPi),    /* Replace with NULL if there's nothing to do at request end */
        PHP_MINFO(phpPi),
        PHP_PHPPI_VERSION,
        STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_PHPPI
#endif
