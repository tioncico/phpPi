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

/* If you declare any globals in php_phpPi.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(phpPi)
*/

/* True global resources - no need for thread safety here */
static int le_phpPi;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("phpPi.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_phpPi_globals, phpPi_globals)
    STD_PHP_INI_ENTRY("phpPi.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_phpPi_globals, phpPi_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_phpPi_compiled(string arg)
   Return a string to confirm that the module is compiled in */

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
    char *pin, *model = NULL;
    size_t
    pin_len, model_len;

    if (zend_parse_parameters(2, "ss", &pin, &pin_len, &model, &model_len) == FAILURE) {
        return;
    }
    pinMode(atoi(pin), atoi(model));
}


PHP_FUNCTION (digitalWrite) {
    char *pin, *value = NULL;
    size_t
    pin_len, value_len;

    if (zend_parse_parameters(2, "ss", &pin, &pin_len, &value, &value_len) == FAILURE) {
        return;
    }
    digitalWrite(atoi(pin), atoi(value));
}

PHP_FUNCTION (digitalRead) {
    char *pin;
    size_t
    pin_len;
    if (zend_parse_parameters(1, "s", &pin, &pin_len) == FAILURE) {
        return;
    }
    int retVal = digitalRead(atoi(pin));
    RETURN_LONG(retVal);
}


PHP_FUNCTION (pwmWrite) {
    char *pin, *value = NULL;
    size_t
    pin_len, value_len;
    if (zend_parse_parameters(2, "ss", &pin, &pin_len, &value, &value_len) == FAILURE) {
        return;
    }
    pwmWrite(atoi(pin), atoi(value));
}

PHP_FUNCTION (pullUpDnControl) {
    char *pin, *pud = NULL;
    size_t
    pin_len, pud_len;
    if (zend_parse_parameters(2, "ss", &pin, &pin_len, &pud, &pud_len) == FAILURE) {
        return;
    }
    pullUpDnControl(atoi(pin), atoi(pud));
}


PHP_FUNCTION (piMillis) {
    int retVal = millis();
    RETURN_LONG(retVal);
}

PHP_FUNCTION (piMicros) {
    int retVal = micros();
    RETURN_LONG(retVal);
}

PHP_FUNCTION (piDelay) {
    char *howLong;
    size_t len;
    if (zend_parse_parameters(1, "s", &howLong, &len) == FAILURE) {
        return;
    }
    delay(atoi(howLong));
}
PHP_FUNCTION (piDelayMicroseconds) {
    char *howLong;
    size_t len;
    if (zend_parse_parameters(1, "s", &howLong, &len) == FAILURE) {
        return;
    }
    delayMicroseconds(atoi(howLong));
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_phpPi_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_phpPi_init_globals(zend_phpPi_globals *phpPi_globals)
{
	phpPi_globals->global_value = 0;
	phpPi_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION (phpPi) {
    /* If you have INI entries, uncomment these lines
    REGISTER_INI_ENTRIES();
    */
    REGISTER_LONG_CONSTANT("PI_INPUT", 0, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PI_OUTPUT", 1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PI_PWM_OUTPUT", 2, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PI_GPIO_CLOCK", 3, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("PI_LOW", 0, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PI_HIGH", 1, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("PI_PUD_OFF", 0, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PI_PUD_DOWN", 1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PI_PUD_UP", 2, CONST_CS | CONST_PERSISTENT);
    return SUCCESS;
}


/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION (phpPi) {
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION (phpPi) {
#if defined(COMPILE_DL_PHPPI) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION (phpPi) {
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION (phpPi) {
    php_info_print_table_start();
    php_info_print_table_header(2, "phpPi support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

/* {{{ phpPi_functions[]
 *
 * Every user visible function must have an entry in phpPi_functions[].
 */
const zend_function_entry phpPi_functions[] = {
        PHP_FE(wiringPiSetup, NULL)        /* For testing, remove later. */
        PHP_FE(wiringPiSetupGpio, NULL)        /* For testing, remove later. */
        PHP_FE(wiringPiSetupPhys, NULL)        /* For testing, remove later. */
        PHP_FE(wiringPiSetupSys, NULL)        /* For testing, remove later. */
        PHP_FE(pinMode, NULL)        /* For testing, remove later. */
        PHP_FE(digitalWrite, NULL)        /* For testing, remove later. */
        PHP_FE(digitalRead, NULL)        /* For testing, remove later. */
        PHP_FE(pwmWrite, NULL)        /* For testing, remove later. */
        PHP_FE(pullUpDnControl, NULL)        /* For testing, remove later. */
        PHP_FE(piMillis, NULL)        /* For testing, remove later. */
        PHP_FE(piMicros, NULL)        /* For testing, remove later. */
        PHP_FE(piDelay, NULL)        /* For testing, remove later. */
        PHP_FE(piDelayMicroseconds, NULL)        /* For testing, remove later. */
        PHP_FE_END    /* Must be the last line in phpPi_functions[] */
};
/* }}} */

/* {{{ phpPi_module_entry
 */
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
/* }}} */

#ifdef COMPILE_DL_PHPPI
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(phpPi)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
