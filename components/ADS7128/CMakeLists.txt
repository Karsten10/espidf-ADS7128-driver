# Register the component (ESP-IDF treats each library as a "component")
idf_component_register(
    SRCS "src/ADS7128.c"  # Source files for this component
    INCLUDE_DIRS "include"  # Directories with header files
    REQUIRES driver
)
