cmake_minimum_required(VERSION 3.15)
project(ConnectionPlugin LANGUAGES CXX)

find_package(Boost REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Corrade REQUIRED PluginManager)
find_package(Magnum REQUIRED GL)
find_package(DtDataFlow CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(DTDF_PLUGIN_INSTALL_DBG_DIR ${CMAKE_INSTALL_PREFIX}/bin/dataflow/dbg)
set(DTDF_PLUGIN_INSTALL_REL_DIR ${CMAKE_INSTALL_PREFIX}/bin/dataflow/rel)


set(CON_SRCS
    src/connections/serial_connection.cpp
    src/connections/udp_connection.cpp
    src/connections/tcp_connection.cpp
)
set(SLOTS_SRCS
    src/slots/io_context_slot.cpp
)
set(NODE_SRCS
    src/nodes/io_context_node.cpp
    src/nodes/connection_node.cpp
    src/nodes/tcp_client_node.cpp
    src/nodes/udp_node.cpp
    src/nodes/serial_node.cpp
)
set(SOURCES         
    src/plugin.cpp
    ${CON_SRCS}
    ${NODE_SRCS}
    ${SLOTS_SRCS}
)

set(COMPILE_DEFS BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)
if(WIN32)
    # fix to win 10 yet
    list(APPEND COMPILE_DEFS _WIN32_WINNT=0x0A00)
endif()

message(STATUS "Plugin DBG Install dir: ${DTDF_PLUGIN_INSTALL_DBG_DIR}")
message(STATUS "Plugin REL Install dir: ${DTDF_PLUGIN_INSTALL_REL_DIR}")
corrade_add_plugin(ConnectionPlugin 
    "${DTDF_PLUGIN_INSTALL_DBG_DIR}"
    "${DTDF_PLUGIN_INSTALL_REL_DIR}"
    ConnectionPlugin.conf 
    ${SOURCES}
)
set_property(TARGET ConnectionPlugin PROPERTY CXX_STANDARD 20)

target_include_directories(
    ConnectionPlugin PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(ConnectionPlugin PRIVATE 
    Boost::headers
    spdlog::spdlog
    Corrade::PluginManager
    Magnum::Magnum
    Magnum::GL
    imgui::imgui
    dt::imnodes
    dt::DtDataflowCore
    dt::DtDataflowPlugin
)
target_compile_definitions(ConnectionPlugin PUBLIC ${COMPILE_DEFS})
