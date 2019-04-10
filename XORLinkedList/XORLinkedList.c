#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "XORLinkedList.h"

//////////////////////////////////////////////////
XLL_t *createXLList() {
    XLL_t *list = malloc(sizeof(XLL_t));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->tail = NULL;
    
    return list;
}

bool destroyXLList(XLL_t *list, XLL_OPTION_e option) {
    // Block illegal parameters.
    if (list == NULL) return false;
    
    clearXLList(list, option);
    free(list);
    return true;
}

bool clearXLList(XLL_t *list, XLL_OPTION_e option) {
    // Block illegal parameters.
    if (list == NULL) return false;
    if (list->head == NULL) return true;
    
    while (!isEmptyXLList(list)) {
        void *element = pullXLList(list);
        if ((option == XLL_OPTION_WITH_ELEMENT) &&
            (element != NULL)) {
            free(element);
        }
    }
    
    return true;
}

bool insertXLList(XLL_t *list, void *element) {
    return insertAtTailOnXLList(list, element);
}

bool insertAtHeadOnXLList(XLL_t *list, void *element) {
    // Block illegal parameters.
    if (list == NULL) return false;
    if (element == NULL) return false;
    
    XLLC_t *cell = createCellOnXLList(element);
    if (list->head == NULL) {
        cell->xorp = NULL;
        list->head = cell;
        list->tail = cell;
    }
    else {
        XLLC_t *prev = NULL;
        XLLC_t *next1 = list->head;
        XLLC_t *next2 = (XLLC_t *)xor(prev, next1->xorp);
        cell->xorp = (XLLC_t *)xor(prev, next1);
        next1->xorp = (XLLC_t *)xor(cell, next2);
        list->head = cell;
    }
    
    return true;
}

bool insertAtTailOnXLList(XLL_t *list, void *elemet) {
    // Block illegal parameters.
    if (list == NULL) return false;
    if (elemet == NULL) return false;
    
    XLLC_t *cell = createCellOnXLList(elemet);
    if (list->tail == NULL) {
        cell->xorp = NULL;
        list->head = cell;
        list->tail = cell;
    }
    else {
        XLLC_t *next = NULL;
        XLLC_t *prev1 = list->tail;
        XLLC_t *prev2 = (XLLC_t *)xor(next, prev1->xorp);
        cell->xorp = (XLLC_t *)xor(prev1, next);
        prev1->xorp = (XLLC_t *)xor(prev2, cell);
        list->tail = cell;
    }
    
    return true;
}

void *pullXLList(XLL_t *list) {
    return pullHeadOnXLList(list);
}

void *pullHeadOnXLList(XLL_t *list) {
    if (isEmptyXLList(list)) return NULL;
    
    const XLLC_t *prev = NULL;
    XLLC_t *cell = list->head;
    XLLC_t *next1 = (XLLC_t *)xor(prev, cell->xorp);
    list->head = next1;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    else {
        XLLC_t *next2 = (XLLC_t *)xor(cell, next1->xorp);
        next1->xorp = (XLLC_t *)xor(prev, next2);
    }
    
    void *element = cell->element;
    free(cell);
    return element;
}

void *pullTailOnXLList(XLL_t *list) {
    if (isEmptyXLList(list)) return NULL;
    
    const XLLC_t *next = NULL;
    XLLC_t *cell = list->tail;
    XLLC_t *prev1 = (XLLC_t *)xor(cell->xorp, next);
    list->tail = prev1;
    if (list->tail == NULL) {
        list->head = NULL;
    }
    else {
        XLLC_t *prev2 = (XLLC_t *)xor(prev1->xorp, cell);
        prev1->xorp = (XLLC_t *)xor(prev2, next);
    }
    
    void *element = cell->element;
    free(cell);
    return element;
}

void *findElementOnXLList(XLL_t *list, int (*comp)(void*, void*), void *element) {
    // Block illegal parameters.
    if (isEmptyXLList(list)) return NULL;
    
    XLL_TRACKER_t *tracker = getTrackerAtHeadOnXLList(list);
    while (tracker != NULL) {
        XLLC_t *cell = tracker->current;
        int check = (*comp)(cell->element, element);
        if (check == 0) {
            destroyTrackerOnXLList(tracker);
            return cell->element;
        }
        tracker = getNextTrackerOnXLList(tracker);
    }
    destroyTrackerOnXLList(tracker);
    return NULL;
}

void *findMinOnXLList(XLL_t *list, int (*comp)(void*, void*)) {
    // Block illegal parameters.
    if (isEmptyXLList(list)) return NULL;
    
    XLL_TRACKER_t *tracker = getTrackerAtHeadOnXLList(list);
    XLLC_t *min = tracker->current;
    while (tracker != NULL) {
        XLLC_t *cell = tracker->current;
        int check = (*comp)(min->element, cell->element);
        if (check > 0) {
            min = cell;
        }
        tracker = getNextTrackerOnXLList(tracker);
    }
    destroyTrackerOnXLList(tracker);
    return min->element;
}

void *findMaxOnXLList(XLL_t *list, int (*comp)(void*, void*)) {
    // Block illegal parameters.
    if (isEmptyXLList(list)) return NULL;
    
    XLL_TRACKER_t *tracker = getTrackerAtHeadOnXLList(list);
    XLLC_t *max = tracker->current;
    while (tracker != NULL) {
        XLLC_t *cell = tracker->current;
        int check = (*comp)(max->element, cell->element);
        if (check < 0) {
            max = cell;
        }
        tracker = getNextTrackerOnXLList(tracker);
    }
    destroyTrackerOnXLList(tracker);
    return max->element;
}

bool isEmptyXLList(XLL_t *list) {
    if (list == NULL) return true;
    if (list->head == NULL) return true;
    return false;
}

XLLC_t *createCellOnXLList(void *element) {
    XLLC_t *cell = malloc(sizeof(XLLC_t));
    if (cell == NULL) return NULL;
    cell->element = element;
    cell->xorp = NULL;
    return cell;
}

XLL_TRACKER_t *getTrackerAtHeadOnXLList(XLL_t *list) {
    XLL_TRACKER_t *tracker = malloc(sizeof(XLL_TRACKER_t));
    if (tracker == NULL) return NULL;
    
    tracker->prev = NULL;
    tracker->current = list->head;
    if (tracker->current == NULL) {
        free(tracker);
        return NULL;
    }
    return tracker;
}

XLL_TRACKER_t *getTrackerAtTailOnXLList(XLL_t *list) {
    XLL_TRACKER_t *tracker = malloc(sizeof(XLL_TRACKER_t));
    if (tracker == NULL) return NULL;
    
    tracker->prev = NULL;
    tracker->current = list->tail;
    if (tracker->current == NULL) {
        free(tracker);
        return NULL;
    }
    return tracker;
}

XLL_TRACKER_t *getNextTrackerOnXLList(XLL_TRACKER_t *tracker) {
    // Block illegal parameters.
    if (tracker == NULL) return NULL;
    
    XLLC_t *temp = tracker->current;
    tracker->current = (XLLC_t *)xor(tracker->prev, tracker->current->xorp);
    tracker->prev = temp;
    if (tracker->current == NULL) {
        free(tracker);
        return NULL;
    }
    return tracker;
}

bool destroyTrackerOnXLList(XLL_TRACKER_t *tracker) {
    // Block illegal parameters.
    if (tracker == NULL) return false;
    
    free(tracker);
    return true;
}

void *getElementOnXLListByTracker(XLL_TRACKER_t *tracker) {
    // Block illegal parameters.
    if (tracker == NULL) return NULL;

    return tracker->current->element;
}
