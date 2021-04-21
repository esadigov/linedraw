#include "LineStrip.h"
#include <stdio.h>
#include <stdlib.h>
veclist *VL_new(Vector vec)
{
    veclist *a = (veclist *)malloc(sizeof(veclist));
    a->vec = vec;
    a->next = NULL;
    return a;
}

veclist *VL_push(veclist *plist, Vector vec)
{
    veclist *new = (veclist *)malloc(sizeof(veclist));
    new->vec = vec;
    new->next = plist;
    return new;
}

veclist *VL_pop(veclist *plist)
{
    if (VL_isEmpty(plist))
        return plist;
    return plist->next;
}

void VL_show(veclist *plist, char *label)
{
    printf("----------%s-------------\n", label);
    if (VL_isEmpty(plist))
    {
        printf("List is empty");
    }
    else
    {
        veclist *temp ;
        int i = 0;
        for (temp = plist; temp != NULL; temp = temp->next)
        {
            printf("%d : %p  %p\n", i, temp, temp->next);
            V_show(temp->vec, "");
            i++;
        }
        printf("%d elements in all\n", i);
    }
}

int VL_isEmpty(veclist *plist)
{
    return plist == NULL;
}

int VL_size(veclist *plist)
{
    veclist *temp = plist;
    int i = 0;
    for (temp = plist; temp != NULL; temp = temp->next)
    {
        i++;
    }
    return i;
}

void VL_removeByAddress(veclist **plist, veclist *pel)
{
    veclist *prev = VL_previous((*plist), pel);
    if ((*plist) != pel)
    {
        prev->next = prev->next->next;
    }else{
        (*plist)=(*plist)->next;
    }
}

veclist *VL_previous(veclist *plist, veclist *pel)
{
    if (plist == pel)
    {
        return NULL;
    }
    veclist *temp = plist;
    for (temp; temp->next != NULL; temp = temp->next)
    {
        if (temp->next == pel)
        {
            return temp;
        }
    }
    return NULL;
}

veclist *VL_insertAfter(veclist *plist, veclist *pel, Vector vec)
{
    veclist *newone = VL_new(vec);
    veclist *temp = plist;
    for (temp; temp->next != NULL; temp = temp->next)
    {
        if (temp == pel)
        {
            newone->next = temp->next;
            temp->next = newone;
        }
    }
    return plist;
}


