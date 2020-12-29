cmake_minimum_required(VERSION 3.16.3)

project(HelloGDBProject VERSION 1.0.0)

set(Source_Files
"src/main.c"
)

set(ALL_FILES ${Source_Files})

add_executable(${PROJECT_NAME} ${ALL_FILES})
set(TARGET_BINARY HelloGDBProject)

add_custom_target(build ALL)

add_custom_target(build_and_debug ALL DEPENDS ${TARGET_BINARY})

# Note: Replace 192.168.1.128 with your Raspberry Pi 4's IP address
set(BOARD_IP 192.168.1.128)
set(PORT_NO 10000) 

add_custom_command(TARGET build_and_debug POST_BUILD
COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_BINARY} root@${BOARD_IP}:.
COMMAND ssh root@${BOARD_IP} 'gdbserver :${PORT_NO} ./${TARGET_BINARY}'
)
