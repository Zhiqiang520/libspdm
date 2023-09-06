/**
 *  Copyright Notice:
 *  Copyright 2021-2022 DMTF. All rights reserved.
 *  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
 **/

#include "spdm_secured_message_lib.h"
#include "spdm_transport_mctp_lib.h"

#include "test_spdm_secured_message.h"

#ifndef LIBSPDM_MAX_SPDM_MSG_SIZE
#define LIBSPDM_MAX_SPDM_MSG_SIZE 0x1200
#endif

void libspdm_test_encode_secured_message(void **State)
{
    libspdm_return_t status;
    size_t secured_message_size;
    uint8_t *secured_message;
    libspdm_secured_message_callbacks_t spdm_secured_message_callbacks;
    bool is_requester;
    uint32_t session_id;
    libspdm_secured_message_context_t *secured_message_context;
    uint8_t *app_message;
    size_t app_message_size;
    uint8_t *data_buffer;

    secured_message_context = *State;
    is_requester = false;
    spdm_secured_message_callbacks.version = LIBSPDM_SECURED_MESSAGE_CALLBACKS_VERSION;
    spdm_secured_message_callbacks.get_sequence_number = libspdm_mctp_get_sequence_number;
    spdm_secured_message_callbacks.get_max_random_number_count =
        libspdm_mctp_get_max_random_number_count;
    spdm_secured_message_callbacks.get_secured_spdm_version =
        libspdm_mctp_get_secured_spdm_version;
    session_id = 0xFFFFFFFF;
    secured_message_context->session_type = LIBSPDM_SESSION_TYPE_ENC_MAC;
    secured_message_context->session_state = LIBSPDM_SESSION_STATE_HANDSHAKING;
    secured_message_context->aead_key_size = LIBSPDM_MAX_AEAD_KEY_SIZE;
    secured_message_context->aead_iv_size = LIBSPDM_MAX_AEAD_IV_SIZE;

    data_buffer = (void *)malloc(LIBSPDM_MAX_SPDM_MSG_SIZE);
    libspdm_zero_mem(data_buffer, LIBSPDM_MAX_SPDM_MSG_SIZE);
    
    /* SessionId | SeqNum (O) | Length | ApplicationDataLength | AppData | */
    app_message = data_buffer +
                  sizeof(spdm_secured_message_a_data_header1_t) +
                  2 + /* MCTP_SEQUENCE_NUMBER_COUNT */
                  sizeof(spdm_secured_message_a_data_header2_t) +
                  sizeof(spdm_secured_message_cipher_header_t);

    uint8_t m_libspdm_gcm_pt[] = {
        0xf5, 0x6e, 0x87, 0x05, 0x5b, 0xc3, 0x2d, 0x0e,
        0xeb, 0x31, 0xb2, 0xea, 0xcc, 0x2b, 0xf2, 0xa5
    };
    app_message = m_libspdm_gcm_pt;
    libspdm_copy_mem(app_message, sizeof(m_libspdm_gcm_pt), m_libspdm_gcm_pt, sizeof(m_libspdm_gcm_pt));
    app_message_size = sizeof(m_libspdm_gcm_pt);
    secured_message = data_buffer;

    status = libspdm_encode_secured_message(secured_message_context, session_id, is_requester,
                                   app_message_size,
                                   app_message,
                                   &secured_message_size, secured_message,
                                   &spdm_secured_message_callbacks);
    free(data_buffer);
    assert_int_equal(status, LIBSPDM_STATUS_SUCCESS);
}

int libspdm_secmes_encode_decode_test_main(void)
{
    const struct CMUnitTest spdm_secmes_encode_decode_tests[] = {
        cmocka_unit_test(libspdm_test_encode_secured_message),
    };

    return cmocka_run_group_tests(spdm_secmes_encode_decode_tests,
                                  libspdm_secmes_unit_test_group_setup,
                                  libspdm_secmes_unit_test_group_teardown);
}
