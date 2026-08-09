#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t messageQueue;


/* Producer Task */
void ProducerTask(void *argument)
{
    uint32_t message = 0;

    while(1)
    {
        message++;
        xQueueSend(messageQueue, &message, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


/* Consumer Task */
void ConsumerTask(void *argument)
{
    uint32_t receivedMessage;

    while(1)
    {
        xQueueReceive(messageQueue, &receivedMessage, portMAX_DELAY);

        GPIOC->ODR ^= (1 << 13);
    }
}


int main(void)
{
    // Enable the clock pin
    RCC->AHB1ENR |= (1 << 2);

    // Enable the output LED pin
    GPIOC->MODER &= ~(3 << (13 * 2));
    GPIOC->MODER |= (1 << (13 * 2));


    // Create the queue
    messageQueue = xQueueCreate(5, sizeof(uint32_t));


    // Create Producer Task
    xTaskCreate(ProducerTask,
                "Producer",
                128,
                NULL,
                1,
                NULL);


    // Create Consumer Task
    xTaskCreate(ConsumerTask,
                "Consumer",
                128,
                NULL,
                1,
                NULL);


    // Start FreeRTOS
    vTaskStartScheduler();


    while(1)
    {

    }
}
