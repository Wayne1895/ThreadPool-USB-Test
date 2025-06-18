#include "usb_task.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include <initguid.h> 
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>

#pragma comment(lib, "setupapi.lib")  // MSVC 專用，MSYS2 請用 -lsetupapi

std::vector<std::string> list_usb_devices() {
    std::vector<std::string> devices;

    HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_USB, nullptr, nullptr, DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        return devices;
    }

    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); ++i) {
        char name[1024];
        if (SetupDiGetDeviceRegistryPropertyA(
                hDevInfo, &devInfoData, SPDRP_DEVICEDESC,
                nullptr, (PBYTE)name, sizeof(name), nullptr)) {
            devices.emplace_back(name);
        }
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
    return devices;
}

std::function<void()> create_usb_task(const std::string& device_name) {
    return [device_name]() {
        std::cout << "[USB] 測試開始：" << device_name << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "[USB] 測試完成：" << device_name << std::endl;
    };
}