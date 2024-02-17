
#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

struct node *shift(struct node *list, int n);

struct node *readList(int size);
struct node *newNode(int value);
void printList(struct node *list);
void freeList(struct node *list);

int main(void) {
	printf("Enter list size: ");
	int size = 0;
	if (scanf("%d", &size) != 1) {
		fprintf(stderr, "error: failed to read list size\n");
		exit(EXIT_FAILURE);
	} else if (size < 0) {
		fprintf(stderr, "error: invalid list size\n");
		exit(EXIT_FAILURE);
	}

	if (size > 0) {
		printf("Enter list values: ");
	}

	struct node *list = readList(size);

	printf("List: ");
	printList(list);

	printf("Enter shift: ");
	int n = 0;
	if (scanf("%d", &n) != 1) {
		fprintf(stderr, "error: failed to read shift\n");
		exit(EXIT_FAILURE);
	} else if (n < 0) {
		fprintf(stderr, "error: invalid shift\n");
		exit(EXIT_FAILURE);
	}

	list = shift(list, n);
	printf("List after shifting %d time(s): ", n);
	printList(list);

	freeList(list);
	return EXIT_SUCCESS;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

struct node *shift(struct node *list, int n) {
	int size = 0;
	struct node *cur = list;
	while(cur != NULL) {
		cur = cur->next;
		size++;
	}
	// If n is > size, make it not so
	n = n % size;

	// No shifting to do
	if(size == 0 || n == 0) return list;

	// No Loops
	// New tail is (i == n), new head in (i == n + 1)

	cur = list;
	int i = 0;
	struct node *newTail;
	struct node *newHead;
	for(i = size - 1; i >= 0; i--) {
		// New tail
		if(i == n) {
			newTail = cur;
			newHead = cur->next;
		} else if(cur->next == NULL) {
			// New Head
			cur->next = list;
		}
		cur = cur->next;
		if(i == n) {
			newTail->next = NULL;
		}
	}

	return newHead;
}

////////////////////////////////////////////////////////////////////////
// !!! DO NOT MODIFY THE CODE BELOW !!!

struct node *readList(int size) {
	struct node *list = NULL;
	struct node *curr = NULL;
	for (int i = 0; i < size; i++) {
		int value = 0;
		if (scanf("%d", &value) != 1) {
			fprintf(stderr, "error: failed to read list value\n");
			exit(EXIT_FAILURE);
		}

		struct node *new = newNode(value);
		if (list == NULL) {
			list = new;
		} else {
			curr->next = new;
		}
		curr = new;
	}
	return list;
}

struct node *newNode(int value) {
	struct node *new = malloc(sizeof(struct node));
	if (new == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	new->value = value;
	new->next = NULL;
	return new;
}

void printList(struct node *list) {
	printf("[");
	for (struct node *curr = list; curr != NULL; curr = curr->next) {
		printf("%d", curr->value);
		if (curr->next != NULL) {
			printf(", ");
		}
	}
	printf("]\n");
}

void freeList(struct node *list) {
	struct node *curr = list;
	while (curr != NULL) {
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
}

