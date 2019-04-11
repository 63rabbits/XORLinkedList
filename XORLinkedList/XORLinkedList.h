#ifndef XORLinkedList_h
#define XORLinkedList_h

#include <stdbool.h>

//////////////////////////////////////////////////
typedef enum XLLOption {
    XLL_OPTION_NONE,
    XLL_OPTION_WITH_ELEMENT
} XLL_OPTION_e;

#define xor(a, b) ((u_long)a ^ (u_long)b)

typedef struct XORLinkedList_Cell {
    void *element;
    struct XORLinkedList_Cell *xorp;
} XLLC_t;

typedef struct XORLinkedList {
    XLLC_t *head;
    XLLC_t *tail;
} XLL_t;

typedef struct XORLinkedList_Tracker {
    XLLC_t *prev;
    XLLC_t *current;
} XLL_TRACKER_t;

//////////////////////////////////////////////////
XLL_t *createXLList(void);
bool destroyXLList(XLL_t *list, XLL_OPTION_e option);
bool clearXLList(XLL_t *list, XLL_OPTION_e option);
bool insertXLList(XLL_t *list, void *element);
bool insertAtHeadOnXLList(XLL_t *list, void *element);
bool insertAtTailOnXLList(XLL_t *list, void *element);
void *pullXLList(XLL_t *list);
void *pullHeadOnXLList(XLL_t *list);
void *pullTailOnXLList(XLL_t *list);
void *findElementOnXLList(XLL_t *list, int (*comp)(void*, void*), void *element);
void *findMinOnXLList(XLL_t *list, int (*comp)(void*, void*));
void *findMaxOnXLList(XLL_t *list, int (*comp)(void*, void*));
bool isEmptyXLList(XLL_t *list);
XLLC_t *createCellOnXLList(void *element);
XLL_TRACKER_t *getTrackerHeadOnXLList(XLL_t *list);
XLL_TRACKER_t *getTrackerTailOnXLList(XLL_t *list);
XLL_TRACKER_t *getNextTrackerOnXLList(XLL_TRACKER_t *tracker);
bool destroyTrackerOnXLList(XLL_TRACKER_t *tracker);
void *getElementOnXLListByTracker(XLL_TRACKER_t *tracker);

#endif
