cmake_minimum_required(VERSION 3.15)
project(TowerDefenseGame VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 设置第三方库路径
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty)

# 添加 cJSON 库
add_library(cJSON STATIC ${THIRDPARTY_DIR}/cJSON/cJSON.c)
target_include_directories(cJSON PUBLIC 
    ${THIRDPARTY_DIR}/cJSON/include
)
# 设置cJSON输出位置
set_target_properties(cJSON PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# src/main.cc
set(SRC_MAIN 
    ${PROJECT_SOURCE_DIR}/src/main.cc
)

# src/bullet
set(SRC_BULLET 
    ${PROJECT_SOURCE_DIR}/src/bullet/ArrowBullet.cc
    ${PROJECT_SOURCE_DIR}/src/bullet/AxeBullet.cc
    ${PROJECT_SOURCE_DIR}/src/bullet/Bullet.cc
    ${PROJECT_SOURCE_DIR}/src/bullet/ShellBullet.cc
)

# src/common
set(SRC_COMMON 
    ${PROJECT_SOURCE_DIR}/src/common/Animation.cc
    ${PROJECT_SOURCE_DIR}/src/common/CoinProp.cc
    ${PROJECT_SOURCE_DIR}/src/common/Map.cc
    ${PROJECT_SOURCE_DIR}/src/common/Route.cc
    ${PROJECT_SOURCE_DIR}/src/common/Timer.cc
    ${PROJECT_SOURCE_DIR}/src/common/TwoVector.cc
)

# src/enemy
set(SRC_ENEMY 
    ${PROJECT_SOURCE_DIR}/src/enemy/Enemy.cc
    ${PROJECT_SOURCE_DIR}/src/enemy/GoblinEnemy.cc
    ${PROJECT_SOURCE_DIR}/src/enemy/GoblinPriestEnemy.cc
    ${PROJECT_SOURCE_DIR}/src/enemy/KingSlimEnemy.cc
    ${PROJECT_SOURCE_DIR}/src/enemy/SkeletonEnemy.cc
    ${PROJECT_SOURCE_DIR}/src/enemy/SlimEnemy.cc
)

# src/manager
set(SRC_MANAGER 
    ${PROJECT_SOURCE_DIR}/src/manager/BulletManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/CoinManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/ConfigManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/EnemyManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/GameManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/HomeManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/PlayerManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/ResourcesManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/TowerManager.cc
    ${PROJECT_SOURCE_DIR}/src/manager/WaveManager.cc
)

# src/tower
set(SRC_TOWER 
    ${PROJECT_SOURCE_DIR}/src/tower/ArcherTower.cc
    ${PROJECT_SOURCE_DIR}/src/tower/AxemanTower.cc
    ${PROJECT_SOURCE_DIR}/src/tower/GunnerTower.cc
    ${PROJECT_SOURCE_DIR}/src/tower/Tower.cc
)

# src/ui/panel
set(SRC_UI_PANEL 
    ${PROJECT_SOURCE_DIR}/src/ui/panel/Panel.cc
    ${PROJECT_SOURCE_DIR}/src/ui/panel/PlacePanel.cc
    ${PROJECT_SOURCE_DIR}/src/ui/panel/UpgradePanel.cc
)

# src/ui
set(SRC_UI 
    ${SRC_UI_PANEL}
    ${PROJECT_SOURCE_DIR}/src/ui/Banner.cc
    ${PROJECT_SOURCE_DIR}/src/ui/StatusBar.cc
)

# 可执行文件
add_executable(TowerDefenseGame 
    ${SRC_MAIN}
    ${SRC_BULLET}
    ${SRC_COMMON}
    ${SRC_ENEMY}
    ${SRC_MANAGER}
    ${SRC_TOWER}
    ${SRC_UI}
)

# 包含头文件
target_include_directories(TowerDefenseGame PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/bullet
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/enemy
    ${PROJECT_SOURCE_DIR}/src/manager
    ${PROJECT_SOURCE_DIR}/src/tower
    ${PROJECT_SOURCE_DIR}/src/ui
    ${PROJECT_SOURCE_DIR}/src/ui/panel

    ${THIRDPARTY_DIR}/SDL2/include
    ${THIRDPARTY_DIR}/SDL2_gfx/include
    ${THIRDPARTY_DIR}/SDL2_image/include
    ${THIRDPARTY_DIR}/SDL2_mixer/include
    ${THIRDPARTY_DIR}/SDL2_ttf/include
)

# 链接库目录
target_link_directories(TowerDefenseGame PRIVATE
    ${THIRDPARTY_DIR}/SDL2/lib/x64
    ${THIRDPARTY_DIR}/SDL2_gfx/lib/x64
    ${THIRDPARTY_DIR}/SDL2_image/lib/x64
    ${THIRDPARTY_DIR}/SDL2_mixer/lib/x64
    ${THIRDPARTY_DIR}/SDL2_ttf/lib/x64
)

# 链接库
target_link_libraries(TowerDefenseGame PRIVATE
    cJSON
    SDL2
    SDL2main
    SDL2_gfx
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)

# 设置可执行文件输出名称和位置
set_target_properties(TowerDefenseGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    OUTPUT_NAME "TowerDefenseGame"
)

# 安装规则
install(TARGETS TowerDefenseGame
    RUNTIME DESTINATION bin
    CONFIGURATIONS Release
)

# 复制必要的DLL文件和资源文件夹（Windows平台）
if(WIN32)
    add_custom_command(TARGET TowerDefenseGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${THIRDPARTY_DIR}/SDL2/lib/x64/SDL2.dll"
            "$<TARGET_FILE_DIR:TowerDefenseGame>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${THIRDPARTY_DIR}/SDL2_image/lib/x64/SDL2_image.dll"
            "$<TARGET_FILE_DIR:TowerDefenseGame>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${THIRDPARTY_DIR}/SDL2_mixer/lib/x64/SDL2_mixer.dll"
            "$<TARGET_FILE_DIR:TowerDefenseGame>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${THIRDPARTY_DIR}/SDL2_ttf/lib/x64/SDL2_ttf.dll"
            "$<TARGET_FILE_DIR:TowerDefenseGame>"
        # 复制config文件夹（递归复制整个目录）
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/config"
            "$<TARGET_FILE_DIR:TowerDefenseGame>/config"
        # 复制resources文件夹（递归复制整个目录）
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:TowerDefenseGame>/resources"
    )
else()
    # 非Windows平台，只复制资源文件夹
    add_custom_command(TARGET TowerDefenseGame POST_BUILD
        # 复制config文件夹（递归复制整个目录）
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/config"
            "$<TARGET_FILE_DIR:TowerDefenseGame>/config"
        # 复制resources文件夹（递归复制整个目录）
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:TowerDefenseGame>/resources"
    )
endif()
