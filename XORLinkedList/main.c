#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "XORLinkedList.h"

//////////////////////////////////////////////////
typedef struct Element {
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);
int comp(void *elementA, void *elementB);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {

#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int testCount = 6;
    int numOfValue = 5;
    
    int s1 = 1;
    int s2 = INT_MAX;
    
    printf("=== start [%s] ===\n", __func__);
    
    XLL_t *list = createXLList();
    
    for (int r=0; r<testCount; r++) {
        printf("*** [Test #%d] ***\n", r+1);
        
        Element_t *element = NULL;
        switch (r) {
            case 0:
                for (int i=0; i<numOfValue; i++) {
                    element = createElement(i);
                    insertXLList(list, element);
                    printf("insert : %d\n", element->value);
                }
                while (!isEmptyXLList(list)) {
                    element = pullXLList(list);
                    printf("pull : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 1:
                for (int i=0; i<numOfValue; i++) {
                    element = createElement(i);
                    insertAtHeadOnXLList(list,  element);
                    printf("insert Head : %d\n", element->value);
                }
                while (!isEmptyXLList(list)) {
                    element = pullHeadOnXLList(list);
                    printf("pull Head : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 2:
                for (int i=0; i<numOfValue; i++) {
                    element = createElement(i);
                    insertAtHeadOnXLList(list, element);
                    printf("insert Head : %d\n", element->value);
                }
                while (!isEmptyXLList(list)) {
                    element = pullTailOnXLList(list);
                    printf("pull Tail : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 3:
                for (int i=0; i<numOfValue; i++) {
                    element = createElement(i);
                    insertAtTailOnXLList(list,  element);
                    printf("insert Tail : %d\n", element->value);
                }
                while (!isEmptyXLList(list)) {
                    element = pullHeadOnXLList(list);
                    printf("pull Head : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 4:
                for (int i=0; i<numOfValue; i++) {
                    element = createElement(i);
                    insertAtTailOnXLList(list,  element);
                    printf("insert Tail : %d\n", element->value);
                }
                while (!isEmptyXLList(list)) {
                    element = pullTailOnXLList(list);
                    printf("pull Tail : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 5:
                for (int i=0; i<numOfValue; i++) {
                    element = createElement(i);
                    insertXLList(list, element);
                    printf("insert : %d\n", element->value);
                }
                Element_t *e1 = createElement(s1);
                element = findElementOnXLList(list, comp, e1);
                if (element != NULL) {
                    printf("found value %d.\n", element->value);
                }
                else {
                    printf("could not found value %d. (T^T)\n", s1);
                }
                free(e1);
                
                Element_t *e2 = createElement(s2);
                element = findElementOnXLList(list, comp, e2);
                if (element != NULL) {
                    printf("found value %d.\n", element->value);
                }
                else {
                    printf("could not found value %d. (T^T)\n", s2);
                }
                free(e2);
                
                element = findMinOnXLList(list, comp);
                if (element != NULL) {
                    printf("found min value %d.\n", element->value);
                }
                else {
                    printf("could not found min value. (T^T)\n");
                }

                element = findMaxOnXLList(list, comp);
                if (element != NULL) {
                    printf("found max value %d.\n", element->value);
                }
                else {
                    printf("could not found max value. (T^T)\n");
                }

                // *************************************
                r = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
    }
    
    destroyXLList(list, XLL_OPTION_WITH_ELEMENT);
    
    printf("=== end [%s] ===\n", __func__);
}

Element_t *createElement(int value) {
    Element_t *element = malloc(sizeof(XLLC_t));
    if (element == NULL) return NULL;
    element->value = value;
    
    return element;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}

int comp(void *elementA, void *elementB) {
    int valueA = ((Element_t *)elementA)->value;
    int valueB = ((Element_t *)elementB)->value;
    return valueA - valueB;
}
