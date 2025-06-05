add_executable(Testbed main.cpp)
target_link_libraries(Testbed PRIVATE HiveCore)

if(WIN32)
    find_path(VULKAN_SDK_INCLUDE_DIR
        NAMES vulkan/vulkan.h
        PATHS "C:/VulkanSDK/*/Include"
        # YOUR/CUSTOM/PATH/TO/VulkanSDK/Include
        DOC "Path to Vulkan SDK include directory")

    if(VULKAN_SDK_INCLUDE_DIR)
        message(STATUS "Found Vulkan SDK include directory: ${VULKAN_SDK_INCLUDE_DIR}")
        target_include_directories(Testbed PRIVATE ${VULKAN_SDK_INCLUDE_DIR})
    else()
        message(FATAL_ERROR "Vulkan SDK include directory not found. Please set VULKAN_SDK_INCLUDE_DIR.")
    endif()
endif()