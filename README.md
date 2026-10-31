# Warehouse AMR Stack

A C++17 / ROS 2 stack for an autonomous mobile robot in a warehouse, written from scratch by hand to review robotics fundamentals on a concrete application.

**Status:** early stage (project skeleton). Kinematics, localization and navigation are planned.

## Build and run

Requires Ubuntu 22.04, CMake ≥ 3.16 and GCC 11+.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/amr_robot
```

Add `-DAMR_ENABLE_SANITIZERS=ON` (with a Debug build) to run with AddressSanitizer and UndefinedBehaviorSanitizer.
