add_library(TgBotAPI MODULE Entry.cpp BotAPI.cpp Handler.cpp)
target_link_libraries(TgBotAPI PRIVATE httplib)

generate_export_header(TgBotAPI
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/TgBotAPIExport.h"
    BASE_NAME TGBOTAPI
)