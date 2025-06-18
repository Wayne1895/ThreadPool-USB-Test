#pragma once
#include <string>
#include <vector>
#include <functional>

// 列出目前 USB 裝置名稱
std::vector<std::string> list_usb_devices();

// 建立任務
std::function<void()> create_usb_task(const std::string& device_name);