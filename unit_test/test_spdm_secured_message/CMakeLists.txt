cmake_minimum_required(VERSION 2.8.12)

INCLUDE_DIRECTORIES(${LIBSPDM_DIR}/unit_test/test_spdm_secured_message
                    ${LIBSPDM_DIR}/include
                    ${LIBSPDM_DIR}/include/library
                    ${LIBSPDM_DIR}/unit_test/include
                    ${LIBSPDM_DIR}/os_stub/include
                    ${LIBSPDM_DIR}/unit_test/cmockalib/cmocka/include
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if((TOOLCHAIN STREQUAL "VS2015") OR (TOOLCHAIN STREQUAL "VS2019") OR (TOOLCHAIN STREQUAL "VS2022"))
        ADD_COMPILE_OPTIONS(/wd4819)
    endif()
endif()

SET(src_test_spdm_secured_message
    test_spdm_secured_message.c
    encode_decode.c
)

SET(test_spdm_secured_message_LIBRARY
    memlib
    debuglib
    spdm_transport_mctp_lib
    spdm_common_lib
    ${CRYPTO_LIB_PATHS}
    rnglib
    cryptlib_${CRYPTO}
    malloclib
    spdm_crypt_lib
    spdm_secured_message_lib
    cmockalib
    spdm_device_secret_lib_null
)

if(TOOLCHAIN STREQUAL "ARM_DS2022")
    SET(test_spdm_secured_message_LIBRARY ${test_spdm_secured_message_LIBRARY} armbuild_lib)
endif()

if(NOT ((TOOLCHAIN STREQUAL "KLEE") OR (TOOLCHAIN STREQUAL "CBMC")))
    ADD_EXECUTABLE(test_spdm_secured_message ${src_test_spdm_secured_message})
    TARGET_LINK_LIBRARIES(test_spdm_secured_message ${test_spdm_secured_message_LIBRARY})
endif()
