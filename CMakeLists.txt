project(ServerMonitor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(ServerMonitor_SRCS ThreadPing.cpp ConfigReader.cpp ServerMonitor.cpp main.cpp)
qt4_automoc(${ServerMonitor_SRCS})
add_executable(ServerMonitor ${ServerMonitor_SRCS})
target_link_libraries(ServerMonitor ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} )

install(TARGETS ServerMonitor RUNTIME DESTINATION bin)
