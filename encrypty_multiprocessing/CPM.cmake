include(cmake/CPM.cmake)

CPMAddPackage(
        NAME drogon
        VERSION 1.7.5
        GITHUB_REPOSITORY drogonframework/drogon
        GIT_TAG v1.7.5
)

target_link_libraries(${PROJECT_NAME} PRIVATE drogon)