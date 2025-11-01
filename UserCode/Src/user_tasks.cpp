//
// Created by cycsjtuer on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"


uint32_t count = 0;
uint32_t send1 = 0;
uint32_t send2 = 0;
uint32_t recv = 0;
constexpr auto flag_1 = 1u << 0;
constexpr auto flag_2 = 1u << 1;


osSemaphoreAttr_t test_semaphore_attributes = {.name = "test_semaphore"};
osSemaphoreId_t test_semaphore_handle;
osEventFlagsAttr_t test_event_flags_attributes = {.name = "test_event_flags"};
osEventFlagsId_t test_event_flags_handle;


osThreadId_t test_task_handle; // 任务句柄，用于引用任务
constexpr osThreadAttr_t test_task_attributes = {
    .name = "test_task", // 任务名称，便于调试
    .stack_size = 128 * 4, // 栈大小=512字节（128字*4字节/字）
    .priority = osPriorityNormal, // 优先级设为普通
};


osThreadId_t test2_task_handle; // 任务句柄，用于引用任务
constexpr osThreadAttr_t test2_task_attributes = {
    .name = "test2_task", // 任务名称，便于调试
    .stack_size = 128 * 4, // 栈大小=512字节（128字*4字节/字）
    .priority = osPriorityNormal, // 优先级设为普通
};

osThreadId_t test3_task_handle; // 任务句柄，用于引用任务
constexpr osThreadAttr_t test3_task_attributes = {
    .name = "test3_task", // 任务名称，便于调试
    .stack_size = 128 * 4, // 栈大小=512字节（128字*4字节/字）
    .priority = osPriorityNormal, // 优先级设为普通
};

//
// [[noreturn]] void test_task(void *) {
//     while (true) {
//         const auto tick = osKernelGetTickCount(); // 获取当前系统tick计数
//         ++count; // 递增全局计数器
//         osDelayUntil(tick + 1); // 延迟直到下一个tick周期
//     }
// }
//
//

[[noreturn]] void test_task(void *) {
    // while (true) {
    //     const auto tick = osKernelGetTickCount();
    //     if (send++ % 5 == 0) {
    //         osSemaphoreRelease(test_semaphore_handle);
    //     }
    //     osDelayUntil(tick + 1);
    // }
    while (true) {
        const auto tick = osKernelGetTickCount();
        send1++;
        if (send1 % 7 == 0) {
            osEventFlagsSet(test_event_flags_handle, flag_1);
        } else if (send1 % 7 == 1) {
            osEventFlagsClear(test_event_flags_handle, flag_1);
        }
        osDelayUntil(tick + 100);
    }
    //
    // osEventFlagsWait(test_event_flags_handle, flag_1 | flag_2,osFlagsWaitAll,osWaitForever);
    // osEventFlagsClear(test_event_flags_handle, flag_1 | flag_2);
    // osEventFlagsSet(test_event_flags_handle, flag_1 | flag_2);
}

[[noreturn]] void test2_task(void *) {
    while (true) {
        const auto tick = osKernelGetTickCount();
        send2++;
        osEventFlagsSet(test_event_flags_handle, flag_2);
        osDelayUntil(tick + 100);
    }
}

[[noreturn]] void test3_task(void *) {
    while (true) {
        osEventFlagsWait(test_event_flags_handle, flag_1 | flag_2,osFlagsWaitAll,osWaitForever);
        recv++;
        osEventFlagsClear(test_event_flags_handle, flag_1 | flag_2);
    }
}

// [[noreturn]] void test2_task(void *) {
//     while (true) {
//         osSemaphoreAcquire(test_semaphore_handle,osWaitForever);
//         recv++;
//     }
// }


void user_tasks_init() {
    // test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes); // 创建任务
    // test_semaphore_handle = osSemaphoreNew(1, 0, &test_semaphore_attributes);
    test_event_flags_handle = osEventFlagsNew(&test_event_flags_attributes);
    test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes);
    test2_task_handle = osThreadNew(test2_task, nullptr, &test2_task_attributes);
    test3_task_handle = osThreadNew(test3_task, nullptr, &test3_task_attributes);
    // test2_task_handle = osThreadNew(test2_task, nullptr, &test2_task_attributes);
}
