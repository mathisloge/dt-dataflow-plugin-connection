cmake_minimum_required(VERSION 3.15)
project(MyPlugin LANGUAGES CXX)

find_package(imgui CONFIG REQUIRED)
find_package(Corrade REQUIRED PluginManager)
find_package(Magnum REQUIRED GL)
find_package(DtDataFlow CONFIG REQUIRED)

set(DTDF_PLUGIN_INSTALL_DBG_DIR ${CMAKE_INSTALL_PREFIX}/bin/dataflow/dbg)
set(DTDF_PLUGIN_INSTALL_REL_DIR ${CMAKE_INSTALL_PREFIX}/bin/dataflow/rel)


set(SOURCES         
    src/plugin.cpp
)
message(STATUS "Plugin DBG Install dir: ${DTDF_PLUGIN_INSTALL_DBG_DIR}")
message(STATUS "Plugin REL Install dir: ${DTDF_PLUGIN_INSTALL_REL_DIR}")
corrade_add_plugin(MyPlugin 
    "${DTDF_PLUGIN_INSTALL_DBG_DIR}"
    "${DTDF_PLUGIN_INSTALL_REL_DIR}"
    MyPlugin.conf 
    ${SOURCES}
)
set_property(TARGET MyPlugin PROPERTY CXX_STANDARD 20)

target_include_directories(
    MyPlugin PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(MyPlugin PRIVATE 
    Corrade::PluginManager
    Magnum::Magnum
    Magnum::GL
    imgui::imgui
    dt::imnodes
    dt::DtDataflowCore
    dt::DtDataflowPlugin
)
