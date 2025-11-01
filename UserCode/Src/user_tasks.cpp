//
// Created by cycsjtuer on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"

uint32_t send = 0;
uint32_t recv = 0;
uint32_t count = 0;
constexpr auto flag_1 = 1u << 0;
constexpr auto flag_2 = 1u << 1;

osSemaphoreId_t semaphore_handle;
constexpr osSemaphoreAttr_t semaphore_attr = {
        .name = "semaphore"
};



osThreadid_t test1_task_handle;
constexpr osThreadAttr_t test_task1_attributes = {
        .name = "test1Task",
        .stack_size = 256 * 4,
        .priority = osPriorityNormal
};
[[noreturn]] void test1_task(void *) {
    while (true) {
        const auto tick = osKernelGetSysTimerCount();
        ++count;
        osDelayUntil(tick + 1);
    }
}

void user_tasks_init() {
    test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes);
    test1_task_handle = osThreadNew(test1_task, nullptr, &test_task1_attributes);

    semaphore_handle = osSemaphoreNew(1, 0, nullptr);


}





