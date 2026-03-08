cmake_minimum_required(VERSION 3.26)

project(AppWatcher LANGUAGES Swift)

add_executable(appwatch
    main.swift
)

target_link_libraries(appwatch
    "-framework AppKit"
)