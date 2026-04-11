add_library(TgBotAPI MODULE Entry.cpp BotAPI.cpp Keyboard.cpp Message.cpp User.cpp)
target_link_libraries(TgBotAPI PRIVATE httplib TgBot)

generate_export_header(TgBotAPI
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/TgBotAPIExport.h"
    BASE_NAME TGBOTAPI
)