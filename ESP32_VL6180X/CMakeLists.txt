set(COMPONENT_SRCS
    api/core/src/vl6180x_api.c
    api/platform/src/vl6180x_i2c.c
    api/platform/src/vl6180x_platform.c
)

set(COMPONENT_ADD_INCLUDEDIRS
    inc
    api/config
    api/core/inc
    api/platform/inc
)

register_component()
