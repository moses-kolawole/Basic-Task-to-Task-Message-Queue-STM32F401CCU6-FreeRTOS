# Basic Task-to-Task Message Queue — STM32F401CCU6 + FreeRTOS

## Overview

This project demonstrates basic **Inter-Task Communication (ITC)** using a FreeRTOS queue on the **STM32F401CCU6 Black Pill**.

The system consists of two independent tasks:

- **Producer Task** — generates an increasing message value and sends it to a queue every 1 second.
- **Consumer Task** — waits for messages from the queue, receives them, and toggles the built-in LED connected to PC13.

The communication follows the basic:

**Producer → Queue → Consumer**

model used in many FreeRTOS-based embedded systems.

## Project Code
[Click here to check out the project code](code)

## How It Works

A queue is created to hold up to 5 messages, with each message being a `uint32_t`:

```c
messageQueue = xQueueCreate(5, sizeof(uint32_t));
