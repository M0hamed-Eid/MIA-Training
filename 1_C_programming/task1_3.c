#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to represent a task
struct Task {
    int id;
    char description[100];
    int completed;
};

// func to add a task
void addTask(struct Task tasks[], int *taskCount);


// func to view tasks
void viewTasks(struct Task tasks[], int taskCount);

// func to remove a task
void removeTask(struct Task tasks[], int *taskCount, int taskId);

int main() {
    struct Task tasks[100];
    int taskCount = 0;
    int choice, taskId;

    printf("Minions Task Manager\n");

    while (1) {
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Remove Task\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                printf("Enter task ID to remove: ");
                scanf("%d", &taskId);
                removeTask(tasks, &taskCount, taskId);
                break;
            case 4:
                printf("Exiting Minions Task Manager. Have a great day!\n");
                exit(0);
            default:
                printf("Invalid option. Please select again.\n");
        }
    }

    return 0;
}

void addTask(struct Task tasks[], int *taskCount) {
    struct Task newTask;
    printf("Enter task description: ");
    scanf(" %[^\n]", newTask.description);

    newTask.id = (*taskCount) + 1;

    printf("Is the task completed? (1 for completed, 0 for incomplete): ");
    scanf("%d", &newTask.completed);

    tasks[*taskCount] = newTask;
    (*taskCount)++;

    printf("Task added successfully!\n");
}


void viewTasks(struct Task tasks[], int taskCount) {
    printf("Current Tasks:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("Task ID: %d\n", tasks[i].id);
        printf("Description: %s\n", tasks[i].description);
        printf("Status: %s\n", tasks[i].completed ? "Completed" : "Incomplete");
    }
}

void removeTask(struct Task tasks[], int *taskCount, int taskId) {
    int foundIndex = -1;

    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].id == taskId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < (*taskCount - 1); i++) {
            tasks[i] = tasks[i + 1];
        }

        (*taskCount)--;
        printf("Task removed successfully!\n");
    } else {
        printf("Task not found!\n");
    }
}