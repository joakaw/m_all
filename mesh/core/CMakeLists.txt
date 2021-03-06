set(MESH_CORE_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/internal_event.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nrf_mesh_configure.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/aes.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/msg_cache.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/transport.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/event.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/packet_buffer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/flash_manager_defrag.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/fifo.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nrf_flash.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/packet_mgr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/net_state.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mesh_flash.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nrf_mesh_utils.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nrf_mesh.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/queue.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/hal.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/aes_cmac.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/timer_scheduler.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/timer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ticker.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/rand.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nrf_mesh_opt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/timeslot.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bearer_event.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/enc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/network.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/msqueue.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nrf_mesh_keygen.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/cache.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/uri.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/flash_manager.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ccm_soft.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/toolchain.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/replay_cache.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/beacon.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/flash_manager_internal.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core_tx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/net_beacon.c" CACHE INTERNAL "")

add_library(mesh_core_${PLATFORM} STATIC ${MESH_CORE_SOURCE_FILES} ${MESH_BEARER_SOURCE_FILES})

target_include_directories(mesh_core_${PLATFORM} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/api
    ${${SOFTDEVICE}_INCLUDE_DIRS}
    ${${PLATFORM}_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/external/rtt/include

    # TODO: Better encapsulation/separation should keep headers under
    # include private.
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # TODO: Should not need to include DFU headers in CORE
    ${CMAKE_CURRENT_SOURCE_DIR}/../dfu/api
    ${CMAKE_CURRENT_SOURCE_DIR}/../dfu/include

    # TODO: Should not need to include PROV headers in CORE
    ${CMAKE_CURRENT_SOURCE_DIR}/../prov/api
    ${CMAKE_CURRENT_SOURCE_DIR}/../prov/include

    # TODO: Should not need to include BEARER headers in CORE
    ${CMAKE_CURRENT_SOURCE_DIR}/../bearer/api
    ${CMAKE_CURRENT_SOURCE_DIR}/../bearer/include
    )

target_compile_options(mesh_core_${PLATFORM} PUBLIC
    ${${ARCH}_DEFINES})

target_compile_definitions(mesh_core_${PLATFORM} PUBLIC
    ${USER_DEFINITIONS}
    ${${PLATFORM}_DEFINES}
    ${${SOFTDEVICE}_DEFINES})

get_property(core_include_dirs TARGET mesh_core_${PLATFORM} PROPERTY INCLUDE_DIRECTORIES)
add_pc_lint(mesh_core_${PLATFORM}
    "${MESH_CORE_SOURCE_FILES}"
    "${core_include_dirs}"
    "${${PLATFORM}_DEFINES};${${SOFTDEVICE}_DEFINES}")
