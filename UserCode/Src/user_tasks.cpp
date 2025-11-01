//
// Created by cycsjtuer on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"

uint32_t count = 0;


osThreadId_t test_task_handle; // 任务句柄，用于引用任务
constexpr osThreadAttr_t test_task_attributes = {
    .name = "test_task", // 任务名称，便于调试
    .stack_size = 128 * 4, // 栈大小=512字节（128字*4字节/字）
    .priority = osPriorityNormal, // 优先级设为普通
};

[[noreturn]] void test_task(void *) {
    while (true) {
        const auto tick = osKernelGetTickCount(); // 获取当前系统tick计数
        ++count; // 递增全局计数器
        osDelayUntil(tick + 1); // 延迟直到下一个tick周期
    }
}


void user_tasks_init() {
    test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes); // 创建任务
}
