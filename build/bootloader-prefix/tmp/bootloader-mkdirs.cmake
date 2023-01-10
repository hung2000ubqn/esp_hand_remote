# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Esp/Espressif/frameworks/esp-idf-v5.0/components/bootloader/subproject"
  "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader"
  "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader-prefix"
  "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader-prefix/tmp"
  "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader-prefix/src/bootloader-stamp"
  "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader-prefix/src"
  "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/doantotnghiep/esp_code/esp32_hand_remote/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
