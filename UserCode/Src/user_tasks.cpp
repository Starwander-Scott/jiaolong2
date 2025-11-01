//
// Created by cycsjtuer on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"


uint32_t count = 0;
uint32_t send = 0;
uint32_t recv = 0;

osMessageQueueAttr_t queue_attributes = {.name = "test_queue"};
osMessageQueueId_t test_queue_handle;


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
    while (true) {
        const auto tick = osKernelGetTickCount();
        send += 1;
        osMessageQueuePut(test_queue_handle, &send, 0, 0);
        osDelayUntil(tick + 1);
    }
}

[[noreturn]] void test2_task(void *) {
    while (true) {
        osMessageQueueGet(test_queue_handle, &recv, nullptr,osWaitForever);
    }
}


void user_tasks_init() {
    // test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes); // 创建任务
    test_queue_handle = osMessageQueueNew(10, 4, &queue_attributes);
    test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes);
    test2_task_handle = osThreadNew(test2_task, nullptr, &test2_task_attributes);
}
