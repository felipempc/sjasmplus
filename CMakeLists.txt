cmake_minimum_required(VERSION 3.7)
project(sjasmplus)

SET(SJASMPLUS_VERSION 20170908+dev)

set(CMAKE_CXX_STANDARD 14)

configure_file(
        "${PROJECT_SOURCE_DIR}/sjasmplus_conf.h.in"
        "${PROJECT_BINARY_DIR}/sjasmplus_conf.h"
)
include_directories(${PROJECT_BINARY_DIR})

find_package (Boost REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES
        lua5.1/lapi.c
        lua5.1/lapi.h
        lua5.1/lauxlib.c
        lua5.1/lauxlib.h
        lua5.1/lbaselib.c
        lua5.1/lcode.c
        lua5.1/lcode.h
        lua5.1/ldblib.c
        lua5.1/ldebug.c
        lua5.1/ldebug.h
        lua5.1/ldo.c
        lua5.1/ldo.h
        lua5.1/ldump.c
        lua5.1/lfunc.c
        lua5.1/lfunc.h
        lua5.1/lgc.c
        lua5.1/lgc.h
        lua5.1/linit.c
        lua5.1/liolib.c
        lua5.1/llex.c
        lua5.1/llex.h
        lua5.1/llimits.h
        lua5.1/lmathlib.c
        lua5.1/lmem.c
        lua5.1/lmem.h
        lua5.1/loadlib.c
        lua5.1/lobject.c
        lua5.1/lobject.h
        lua5.1/lopcodes.c
        lua5.1/lopcodes.h
        lua5.1/loslib.c
        lua5.1/lparser.c
        lua5.1/lparser.h
        lua5.1/lstate.c
        lua5.1/lstate.h
        lua5.1/lstring.c
        lua5.1/lstring.h
        lua5.1/lstrlib.c
        lua5.1/ltable.c
        lua5.1/ltable.h
        lua5.1/ltablib.c
        lua5.1/ltm.c
        lua5.1/ltm.h
        lua5.1/lua.h
        lua5.1/lua.hpp
        lua5.1/luaconf.h
        lua5.1/lualib.h
        lua5.1/lundump.c
        lua5.1/lundump.h
        lua5.1/lvm.c
        lua5.1/lvm.h
        lua5.1/lzio.c
        lua5.1/lzio.h
#        resources/bin2c/bin2c.cpp
#        resources/SaveTAP_ZX_Spectrum_128K.bin.h
#        resources/SaveTAP_ZX_Spectrum_256K.bin.h
#        resources/SaveTAP_ZX_Spectrum_48K.bin.h
        sjasm/codeemitter.cpp
        sjasm/codeemitter.h
        sjasm/directives.cpp
        sjasm/directives.h
        sjasm/errors.cpp
        sjasm/errors.h
        sjasm/fs.h
        sjasm/fsutil.cpp
        sjasm/fsutil.h
        sjasm/global.cpp
        sjasm/global.h
        sjasm/io_snapshots.cpp
        sjasm/io_snapshots.h
        sjasm/io_tape.cpp
        sjasm/io_tape.h
        sjasm/io_trd.cpp
        sjasm/io_trd.h
        sjasm/labels.cpp
        sjasm/labels.h
        sjasm/listing.cpp
        sjasm/listing.h
        sjasm/lua_lpack.c
        sjasm/lua_lpack.h
        sjasm/lua_sjasm.cpp
        sjasm/lua_sjasm.h
        sjasm/lua_support.cpp
        sjasm/lua_support.h
        sjasm/memory.cpp
        sjasm/memory.h
        sjasm/modules.cpp
        sjasm/modules.h
        sjasm/options.cpp
        sjasm/options.h
        sjasm/parser.cpp
        sjasm/parser.h
        sjasm/reader.cpp
        sjasm/reader.h
        sjasm/sjasm.cpp
        sjasm/sjasm.h
        sjasm/sjio.cpp
        sjasm/sjio.h
        sjasm/support.cpp
        sjasm/support.h
        sjasm/tables.cpp
        sjasm/tables.h
        sjasm/util.cpp
        sjasm/util.h
        sjasm/z80.cpp
        sjasm/z80.h
        sjasm/zxspectrum.cpp
        sjasm/zxspectrum.h
#        sjasmwin32/sjasmwin32.cpp
#        sjasmwin32/sjasmwin32.h
        tolua++/tolua++.h
        tolua++/tolua_event.c
        tolua++/tolua_event.h
        tolua++/tolua_is.c
        tolua++/tolua_map.c
        tolua++/tolua_push.c
        tolua++/tolua_to.c)

if (WIN32)
  if (CMAKE_COMPILER_IS_GNUCC)
    set (CMAKE_RC_COMPILER_INIT windres)
    enable_language(RC)
    set (CMAKE_RC_COMPILE_OBJECT
      "<CMAKE_RC_COMPILER> -O coff <FLAGS> <DEFINES> <SOURCE> <OBJECT>")
  endif ()
  set (SOURCE_FILES ${SOURCE_FILES} "${PROJECT_SOURCE_DIR}/win32/sjasmplus.rc")
endif ()

include_directories(BEFORE sjasm lua5.1 tolua++)

add_executable(sjasmplus ${SOURCE_FILES})

target_link_libraries (sjasmplus ${Boost_LIBRARIES})

add_subdirectory(tests tests EXCLUDE_FROM_ALL)
