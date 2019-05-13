cmake_minimum_required(VERSION 3.9)

project(cpp_indie_studio)

if (WIN32)
  SET(CMAKE_CXX_STANDARD 11)
endif(WIN32)


# Fichiers sources du projets
set(SRCS
 ../srcs/main.cpp
 ../srcs/core.cpp
 ../srcs/CEventReceiver.cpp
 ../srcs/CMenu.cpp
 ../srcs/CSound.cpp
 ../srcs/CCharacter.cpp
 ../srcs/CTimer.cpp
 ../srcs/CBox.cpp
 ../srcs/CMap.cpp
 ../srcs/CGame.cpp
 )

# headers du projets
include_directories(../include/)

#create executable
add_executable(bomberman ${SRCS})

set( EXECUTABLE_OUTPUT_PATH ../../)

# Génération de la liste des fichiers sources
if(UNIX)
 
 # Initialisation des flags de compilation g++
 set(CMAKE_CXX_FLAGS "-Wall")
 target_link_libraries(bomberman -lIrrlicht -lGL -lX11 -lXxf86vm -lIrrKlang)

 # recherche du package irrlicht
 
 
   # Recherche du package X11
 FIND_PACKAGE(X11)
 if (X11_FOUND)
   target_include_directories(bomberman PUBLIC ${X11_INCLUDE_DIR})
 else ()
   message(FATAL_ERROR "\nX11 not found")
   target_link_libraries(bomberman ${X11_LIBRARY})
 endif()

 # Recherche du package GLUT
 FIND_PACKAGE(GLUT)
 if (GLUT_FOUND)
   target_include_directories(bomberman PUBLIC ${GLUT_INCLUDE_DIR})
 else ()
   message(FATAL_ERROR "\nGLUT not found")
   target_link_libraries(bomberman ${GLUT_LIBRARY})
 endif()

 # Recherche du package ZLIB
 FIND_PACKAGE(ZLIB)

 if (ZLIB_FOUND)
   target_include_directories(bomberman PUBLIC ${ZLIB_INCLUDE_DIR})
 else ()
   message(FATAL_ERROR "\nZLIB not found")
   target_link_libraries(bomberman ${ZLIB_LIBRARY})
 endif()

endif(UNIX)

if (WIN32)
	add_executable(bomberman ${SRCS})

	include_directories(inc /usr/include/irrlicht)
	include_directories(inc include)
	include_directories(inc irrlicht)

	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

	target_link_libraries(bomberman "C:\\Program Files\\irrlicht.lib")
	target_link_libraries(bomberman "C:\\Program Files\\irrKlang.lib")
endif()
