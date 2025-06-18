# ThreadPool + USB Device Detection (Windows, C++17)

This project demonstrates a modular ThreadPool framework that integrates real USB device detection using Windows SetupAPI.

Each detected USB device is submitted as a task into the thread pool, simulating concurrent testing for future automated diagnostic tools.

---

##  Features

- C++17 ThreadPool with `std::thread`, `mutex`, and `condition_variable`
- Windows USB device detection via `SetupDiEnumDeviceInfo`
- Each USB device is simulated as a test task
- Console output demonstrates asynchronous execution
- Modular structure for future extension (e.g. real testing, log storage, protocol analysis)

---

##  Build (MSYS2 / MinGW / Windows)

```bash
g++ -std=c++17 -o usb_demo main.cpp threadpool.cpp usb_task.cpp -lsetupapi


```
 
##  Sample Output

```
偵測到 USB 裝置數量：14
[USB] 測試開始：泛型 SuperSpeed USB 集線器
[USB] 測試開始：USB xHCI 相容的主機控制器
[USB] 測試開始：USB 根集線器 (USB 3.0)
[USB] 測試開始：Generic USB Hub
[USB] 測試完成：泛型 SuperSpeed USB 集線器
[USB] 測試開始：USB xHCI 相容的主機控制器
[USB] 測試完成：USB xHCI 相容的主機控制器
[USB] 測試開始：USB Composite Device
[USB] 測試完成：USB 根集線器 (USB 3.0)
[USB] 測試開始：USB Composite Device
...
[USB] 測試完成：USB Composite Device
所有 USB 測試完成！
```