//
// Created by HP on 29.11.2015.
//

#include "tlist.h"

//      TListItem class
TListItem::TListItem ()
        : next(NULL), prev(NULL)
{

}



//
//      TList class
//
TList::TList ()
        : first(NULL), last(NULL)
        , counter(0)
{

}

TList::~TList ()
{
    Clear();
}

void TList::Clear()
{
    TListItem * pItem = Last();
    while (pItem) {
        TListItem * nextItem = pItem;
        pItem = pItem->Prev();
        delete nextItem;
    }

    first    = NULL;
    last     = NULL;
    counter  = 0;
}


void TList::Append (TListItem* ptItem)
{
    //Assert(ptItem->prev==NULL && ptItem->next==NULL); // not in list

    if (first==NULL) {                            // List is empty
        //Assert(last==NULL);
        first    = ptItem;
        last     = ptItem;
    }
    else {
        //Assert(last!=NULL);
        //Assert(last != ptItem); // already in list!!
        ptItem->prev = last;                      // Set previous link
        last->next = ptItem;
        last = ptItem;
    }
    counter++;
    //Assert(counter<=1 || first!=last);
}


void TList::InsertBefore (TListItem* ptBefore, TListItem* ptNewItem)
{
    if (ptBefore == NULL || ptNewItem == NULL) {
        //Assert(false);
        return;
    }
    if (IsEmpty()) {                            // List is empty
        //Assert(false);
        return;
    }

    //Assert(ptBefore!=ptNewItem);

    ptNewItem->prev = ptBefore->prev;

    if (ptBefore->prev==NULL) {               // Before is the  first item
        //Assert(ptBefore==first);
        first = ptNewItem;                      // Change the first item
    }
    else {
        //Assert(ptBefore!=first);
        ptBefore->prev->next = ptNewItem;
    }

    ptBefore->prev = ptNewItem;
    ptNewItem->next = ptBefore;

    counter++;
    //Assert(counter<=1 || first!=last);
}

void TList::InsertAfter (TListItem* ptAfter, TListItem* ptNewItem)
{
    if (ptAfter == NULL || ptNewItem == NULL) {
        //Assert(false);
        return;
    }
    if (IsEmpty()) {                            // List is empty
        //Assert(false);
        return;
    }

    //Assert(ptAfter!=ptNewItem);

    ptNewItem->next = ptAfter->next;

    if (ptAfter->next==NULL) {               // After the last item
        //Assert(ptAfter==last);
        last = ptNewItem;                      // Change the last item
    }
    else {
        //Assert(ptAfter!=last);
        ptAfter->next->prev = ptNewItem;
    }

    ptAfter->next = ptNewItem;
    ptNewItem->prev = ptAfter;

    counter++;
    //Assert(counter<=1 || first!=last);
}

void TList::DeleteItem (TListItem* ptItem)
{
    counter--;

    if (first == last) {                        // List consist of one item
        //Assert(ptItem==first);
        delete ptItem;
        first = last = NULL;
        //Assert(counter<=1 || first!=last);
        return;
    }

    if (ptItem != first && ptItem != last) {     // Delete the middle item
        TListItem* PrevItem = ptItem->Prev();
        TListItem* NextItem = ptItem->Next();
        PrevItem->next = NextItem;
        NextItem->prev = PrevItem;
        delete ptItem;
        //Assert(counter<=1 || first!=last);
        return;
    }

    if (ptItem == last) {                        // Delete last in the list ( >= 1 item)
        TListItem* PrevItem = ptItem->Prev();
        PrevItem->next = NULL;
        last = PrevItem;
        delete ptItem;
        //Assert(counter<=1 || first!=last);
        return;
    }
    if (ptItem == first) {                       // Delete first in the list ( >= 1 item)
        TListItem* NextItem = ptItem->Next();
        NextItem->prev = NULL;
        first = NextItem;
        delete ptItem;
    }
    //Assert(counter<=1 || first!=last);
}

TListItem* TList::operator[] (unsigned int index)
{
    if (index >= counter)
        return NULL;
    TListItem* pItem = First();
    for (unsigned int i = 0; i < index; i++, pItem = pItem->Next());
    return pItem;
}


void TList:: ReLink(TList *list)
{
    for(TListItem *ptItem; (ptItem=list->First()) != NULL; ) {
        list->ExtractItem (ptItem);
        Append(ptItem);
    }
}
void TList::ExtractItem (TListItem* ptItem)
{
    counter--;

    if (first == last) {                        // List consist of one item
        first = last = NULL;
        ptItem->prev = ptItem->next = NULL;
        //Assert(counter<=1 || first!=last);
        return;
    }

    if (ptItem != first && ptItem != last) {     // Delete the middle item
        TListItem* PrevItem = ptItem->Prev();
        TListItem* NextItem = ptItem->Next();
        PrevItem->next = NextItem;
        NextItem->prev = PrevItem;
        ptItem->prev = ptItem->next = NULL;
        //Assert(counter<=1 || first!=last);
        return;
    }

    if (ptItem == last) {                        // Delete last in the list ( >= 1 item)
        TListItem* PrevItem = ptItem->Prev();
        PrevItem->next = NULL;
        last = PrevItem;
        ptItem->prev = ptItem->next = NULL;
        //Assert(counter<=1 || first!=last);
        return;
    }
    if (ptItem == first) {                       // Delete first in the list ( >= 1 item)
        TListItem* NextItem = ptItem->Next();
        NextItem->prev = NULL;
        first = NextItem;
    }

    ptItem->prev = ptItem->next = NULL;
    //Assert(counter<=1 || first!=last);
}

void TList::ExchangeItems(TListItem *one, TListItem *two)
{
    TListItem *onePrev = one->prev;
    TListItem *oneNext = one->next;
    TListItem *twoPrev = two->prev;
    TListItem *twoNext = two->next;

    if (onePrev != two) {
        if (onePrev)
            onePrev->next = two;
        two->prev = onePrev;
    }
    else {
        two->prev = one;
    }

    if (oneNext != two) {
        if (oneNext)
            oneNext->prev = two;
        two->next = oneNext;
    }
    else {
        two->next = one;
    }

    if (twoPrev != one) {
        if (twoPrev)
            twoPrev->next = one;
        one->prev = twoPrev;
    }
    else {
        one->prev = two;
    }

    if (twoNext != one) {
        if (twoNext)
            twoNext->prev = one;
        one->next = twoNext;
    }
    else {
        one->next = two;
    }


// modify first and last pointers
    if (first == one)
        first = two;
    else if (first == two)
        first = one;

    if (last == one)
        last = two;
    else if (last == two)
        last = one;
}

TListItem* TList::FirstThat(ConditionFunc func, void *par)
{
    for (TListItem *ptItem = First(); ptItem; ptItem = ptItem->Next()) {
        if (func(ptItem, par))
            return ptItem;
    }
    return NULL;
}

void TList::ForEach (DoFunc func, void *par)
{
    for (TListItem *ptItem = First(); ptItem; ptItem = ptItem->Next()) {
        func(ptItem, par);
    }
}

void TList::Reverse()
{
    if (counter < 2) return;

    TListItem *ptItem = First();
    while (ptItem) {
        // exchange prev and next for ptItem
        TListItem *buff = ptItem->prev;
        ptItem->prev = ptItem->next;
        ptItem->next = buff;

        ptItem = ptItem->Prev();
    }

    // exchange first and last
    TListItem *buff = last;
    last = first;
    first = buff;
}

void TList::MoveToBegin(TListItem *ptItem)
{
    if(ptItem==first) return;

    TListItem *prev=ptItem->prev;
    TListItem *next=ptItem->next;
    // unlink
    if(next) next->prev=prev;
    prev->next=next;
    if(last==ptItem) last=prev;
    // link before first
    first->prev=ptItem;
    ptItem->next=first;
    // set the first
    first=ptItem;
    ptItem->prev=NULL;
    //Assert(first!=last);
}

void TList::MoveToEnd(TListItem *ptItem)
{
    if(ptItem==last) return;

    TListItem *next=ptItem->next;
    TListItem *prev=ptItem->prev;
    // unlink
    if(prev) prev->next=next;
    next->prev=prev;
    if(first==ptItem) first=next;
    // link after last
    last->next=ptItem;
    ptItem->prev=last;
    // set the last
    last=ptItem;
    ptItem->next=NULL;
    //Assert(first!=last);
}

void TList::MovePrev (TListItem *ptItem)
{
    TListItem * prev = ptItem->prev;
    if (!prev) return;

    ptItem->prev = prev->prev;
    if (ptItem->prev) {
        ptItem->prev->next = ptItem;
    }
    else {
        first = ptItem;
    }
    prev->next = ptItem->next;
    if (prev->next) {
        prev->next->prev = prev;
    }
    else {
        last = prev;
    }
    prev->prev = ptItem;
    ptItem->next = prev;
    //Assert(first!=last);
}

void TList::MoveNext (TListItem *ptItem)
{
    TListItem * next = ptItem->next;
    if (!next) return;

    ptItem->next = next->next;
    if (ptItem->next) {
        ptItem->next->prev = ptItem;
    }
    else {
        last = ptItem;
    }
    next->prev = ptItem->prev;
    if (next->prev) {
        next->prev->next = next;
    }
    else {
        first = next;
    }
    next->next = ptItem;
    ptItem->prev = next;
    //Assert(first!=last);
}

int TList::Index(const TListItem* ptItem) const
{
    int i=0;
    for(const TListItem *p=CFirst(); p; p=p->Next(), i++) {
        if(p==ptItem)
            return i;
    }
    return -1;
}

int TList::DeleteFrom(TListItem* ptItem)
{
    if ( IsEmpty() ) return 0;
    if ( Index(ptItem) < 0 ) return 0; //item doesn't belong to list

    unsigned int deleted_count = 0;

    if (First() == ptItem) { deleted_count = counter; Clear(); return deleted_count; }

    TListItem* prev = ptItem->Prev();
    prev->next = NULL;
    last = prev;

    do
    {
        TListItem* ptNext = ptItem->Next();
        delete ptItem;
        ++deleted_count;
        --counter;

        ptItem = ptNext;
    }
    while (ptItem);

    return deleted_count;
}

