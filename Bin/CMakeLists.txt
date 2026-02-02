
Include (${common_cmake_dir}/BuildCommon/ConfigTarget.cmake)

add_executable       (SampleApplication     SampleApplication.cpp)
target_link_libraries(SampleApplication     ${project_target_prefix}Common)

install(TARGETS         SampleApplication
        DESTINATION     ${bintop_dir_name}/
)
