/**
 *  Copyright Notice:
 *  Copyright 2021-2023 DMTF. All rights reserved.
 *  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
 **/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "internal/libspdm_secured_message_lib.h"

int libspdm_secmes_unit_test_group_setup(void **state);
int libspdm_secmes_unit_test_group_teardown(void **state);