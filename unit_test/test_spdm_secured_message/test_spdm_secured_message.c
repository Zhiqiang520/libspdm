/**
 *  Copyright Notice:
 *  Copyright 2021-2023 DMTF. All rights reserved.
 *  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
 **/


#include "test_spdm_secured_message.h"

static void *m_test_secured_message_context;

int libspdm_secmes_unit_test_group_setup(void **state)
{
    m_test_secured_message_context = (void *)malloc(sizeof(libspdm_secured_message_context_t));
    libspdm_secured_message_init_context (m_test_secured_message_context);
    *state = m_test_secured_message_context;
    return 0;
}

int libspdm_secmes_unit_test_group_teardown(void **state)
{
    libspdm_secured_message_context_t *secured_message_context;
    secured_message_context = *state;
    free(secured_message_context);
    return 0;
}

void libspdm_setup_test_secmes_context(libspdm_secured_message_context_t *secured_message_context)
{
    m_test_secured_message_context = secured_message_context;
}

extern int libspdm_secmes_encode_decode_test_main(void);

int main(void)
{
    int return_value = 0;

    if (libspdm_secmes_encode_decode_test_main() != 0) {
        return_value = 1;
    }

    return return_value;
}
