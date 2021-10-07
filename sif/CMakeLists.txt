set(
	sources
	main.cpp
)

find_library(SL libspot.so)
message("Lib1 is at: ${SL}")

add_executable(sif ${sources})
target_include_directories(sif PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(sif PRIVATE Sif Utils nlohmann_json::nlohmann_json cxxopts libspot.so)

include(GNUInstallDirs)
install(TARGETS sif DESTINATION "${CMAKE_INSTALL_BINDIR}")

