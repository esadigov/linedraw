//I decided to use linked list with functions below
#include"vector.h"
typedef struct vectorList{
    Vector vec;
    struct vectorList *next;
}veclist;

veclist* VL_new(Vector vec);
veclist* VL_push(veclist* plist, Vector vec);
veclist* VL_pop(veclist *plist);
void VL_show(veclist *plist,char* label);
int VL_isEmpty(veclist *plist);
int VL_size(veclist *plist);
veclist *VL_previous(veclist *plist, veclist *pel);
void VL_removeByAddress(veclist **plist, veclist *pel);
veclist *VL_insertAfter(veclist *plist, veclist *pel, Vector vec);