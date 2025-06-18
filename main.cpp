#include "threadpool.hpp"
#include "usb_task.hpp"
#include <iostream>

int main() {
    ThreadPool pool(4);

    auto usb_list = list_usb_devices();
    std::cout << "偵測到 USB 裝置數量：" << usb_list.size() << std::endl;

    for (const auto& name : usb_list) {
        pool.submit(create_usb_task(name));
    }

    pool.wait_finish();
    std::cout << "所有 USB 測試完成！" << std::endl;
    return 0;
}
