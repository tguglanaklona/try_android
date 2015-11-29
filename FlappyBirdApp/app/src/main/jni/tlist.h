//
// if we go without STL library - create simple List
//

#ifndef FLAPPYBIRDAPP_TLIST_H
#define FLAPPYBIRDAPP_TLIST_H

#pragma once
#include <stddef.h>

//
// class TListItem
//
class TListItem
{
public:
    TListItem();               // Constructor of item
    virtual ~TListItem() {}
    virtual TListItem* Next() { return next; }
    virtual TListItem* Prev() { return prev; }
    virtual const TListItem* Next() const { return next; }
    virtual const TListItem* Prev() const { return prev; }
private:
    TListItem* next;           // Pointer on next item
    TListItem* prev;           // Pointer on prev item
    friend class TList;
};


typedef int  (*ConditionFunc)(TListItem *ptItem, void *par);
typedef void (*DoFunc)       (TListItem *ptItem, void *par);


class TList {
public:
    TList();
    ~TList();
    void Clear           ();                                        // Clears the list
    void ReLink          (TList *list);                             // Relink nodes to another list

    void Append          (TListItem* ptItem);                       // Add to list
    void DeleteItem      (TListItem* ptItem);                       // Delete item in list
    void ExtractItem     (TListItem* ptItem);                       // Extract item from list
    void ExchangeItems   (TListItem* ptOne, TListItem* ptTwo);
    void InsertBefore    (TListItem* ptBefore, TListItem* ptNew);   // Insert ptNew into list before ptBefore
    void InsertAfter     (TListItem* ptAfter,  TListItem* ptNew);   // Insert ptNew into list after ptAfter
    void Reverse         ();
    virtual TListItem* First     () { return first; }                       // Get first item in list
    virtual TListItem* Last      () { return last; }                        // Get last  item in list
    virtual TListItem* operator[](unsigned int);                            // Convert num to item
    virtual const TListItem* CFirst     () const { return first; }          // Get first item in list
    const TListItem* CLast       () const { return last; }                  // Get last  item in list
    //const TListItem* operator[](unsigned int index) const { return const_cast<TList *>(this)->operator[](index); }

    unsigned int Count   () const { return counter; }               // Get number of items
    int  IsEmpty         () const { return first==NULL; }

    TListItem *FirstThat (ConditionFunc func, void *par);
    void ForEach         (DoFunc func, void *par);

    void MoveToBegin(TListItem *ptItem);
    void MoveToEnd(TListItem *ptItem);

    void MovePrev(TListItem *ptItem);
    void MoveNext(TListItem *ptItem);

    int Index(const TListItem* ptItem) const;                       // Get node index in list
    int DeleteFrom(TListItem* ptItem);

private:
    TList& operator = (const TList& src);                           // declare but not define. To prevent incorrect copying
    TList(const TList& src);                                        // declare but not define. To prevent incorrect copying

    TListItem*     first;
    TListItem*     last;
    unsigned int counter;          // keeps the amount of items
};

///////////////////////////////////////////////////////////

#define DECLARE_ITEM_METHODS(itemclsname, base) \
  itemclsname* Next();\
  itemclsname* Prev();\
  const itemclsname* Next() const;\
  const itemclsname* Prev() const

#define DECLARE_BASIC_LIST_METHODS(itemclsname, base) \
  itemclsname *First();\
  itemclsname *Last ();\
  itemclsname *operator[](unsigned int index);\
  const itemclsname *First() const;\
  const itemclsname *Last () const;\
  const itemclsname *operator[](unsigned int index) const

#define DECLARE_MORE_LIST_METHODS(itemclsname, listclsname, base) \
  void ReLink       (listclsname *list);\
  void Append       (itemclsname* ptItem);\
  void DeleteItem   (itemclsname* ptItem);\
  void ExtractItem  (itemclsname* ptItem);\
  void ExchangeItems(itemclsname* ptOne, itemclsname* ptTwo);\
  void InsertBefore (itemclsname* ptBefore, itemclsname* ptNew);\
  void InsertAfter  (itemclsname* ptAfter,  itemclsname* ptNew)

#define DECLARE_LIST_METHODS(itemclsname, listclsname, base) \
  DECLARE_BASIC_LIST_METHODS(itemclsname, base); \
  DECLARE_MORE_LIST_METHODS(itemclsname, listclsname, base)

///////////////////////////////////////////////////////////

#define IMPLEMENT_ITEM_METHODS(itemclsname, base) \
  inline itemclsname* Next() { return static_cast<itemclsname *>(base::Next()); } \
  inline itemclsname* Prev() { return static_cast<itemclsname *>(base::Prev()); } \
  inline const itemclsname* Next() const { return static_cast<const itemclsname*>(base::Next()); } \
  inline const itemclsname* Prev() const { return static_cast<const itemclsname*>(base::Prev()); }

#define IMPLEMENT_BASIC_LIST_METHODS(itemclsname, prefix, base) \
  inline itemclsname *prefix##First() { return static_cast<itemclsname *>(base::First()); } \
  inline itemclsname *prefix##Last () { return static_cast<itemclsname *>(base::Last()); } \
  inline itemclsname *prefix##operator[](unsigned int index) { return static_cast<itemclsname *>(base::operator[](index)); } \
  inline const itemclsname *prefix##First() const { return static_cast<const itemclsname *>(base::First()); } \
  inline const itemclsname *prefix##Last () const { return static_cast<const itemclsname *>(base::Last()); } \
  inline const itemclsname *prefix##operator[](unsigned int index) const { return static_cast<const itemclsname *>(base::operator[](index)); }

#define IMPLEMENT_MORE_LIST_METHODS(itemclsname, listclsname, prefix, base) \
  inline void prefix##ReLink       (listclsname *list)                         { base::ReLink(list); } \
  inline void prefix##Append       (itemclsname* ptItem)                          { base::Append(ptItem); } \
  inline void prefix##DeleteItem   (itemclsname* ptItem)                          { base::DeleteItem(ptItem); } \
  inline void prefix##ExtractItem  (itemclsname* ptItem)                          { base::ExtractItem(ptItem); } \
  inline void prefix##ExchangeItems(itemclsname* ptOne, itemclsname* ptTwo)    { base::ExchangeItems(ptOne, ptTwo); } \
  inline void prefix##InsertBefore (itemclsname* ptBefore, itemclsname* ptNew) { base::InsertBefore(ptBefore, ptNew); } \
  inline void prefix##InsertAfter  (itemclsname* ptAfter,  itemclsname* ptNew) { base::InsertAfter (ptAfter,  ptNew); }

#define IMPLEMENT_LIST_METHODS(itemclsname, listclsname, base) \
  IMPLEMENT_BASIC_LIST_METHODS(itemclsname, , base) \
  IMPLEMENT_MORE_LIST_METHODS(itemclsname, listclsname, , base)

#define _IMPLEMENT_LIST_METHODS(itemclsname, listclsname, prefix, base) \
  IMPLEMENT_BASIC_LIST_METHODS(itemclsname, prefix, base) \
  IMPLEMENT_MORE_LIST_METHODS(itemclsname, listclsname, prefix, base)

#define IMPLEMENT_LIST(itemclsname, listclsname, base) \
class listclsname: public base \
{ \
  typedef base Inherited; \
 public: \
  listclsname() : Inherited() {} \
  IMPLEMENT_LIST_METHODS(itemclsname, listclsname, Inherited); \
private: \
  listclsname(const listclsname&); \
  void operator=(const listclsname&); \
}

///////////////////////////////////////////////////////////

/*template <class T>
class TListItemOf : public TListItem
{
    typedef TListItem Inherited;
public:
    T m_value;

    TListItemOf<T>(void) : m_value() {}

    IMPLEMENT_ITEM_METHODS(TListItemOf<T>, Inherited);
private:
    TListItemOf<T>(const TListItemOf<T>&);
    void operator=(const TListItemOf<T>&);
};*/


template <class T>
class TListItemOf : public TListItem {
    typedef TListItem Inherited;

public:
    T m_value;

    TListItemOf<T>(void) : m_value() {}

    //IMPLEMENT_ITEM_METHODS(TListItemOf<T>, Inherited);
    virtual TListItemOf<T>* Next() { return static_cast<TListItemOf<T> *>(Inherited::Next()); }
    virtual TListItemOf<T>* Prev() { return static_cast<TListItemOf<T> *>(Inherited::Prev()); }
    virtual const TListItemOf<T>* Next() const { return static_cast<const TListItemOf<T>*>(Inherited::Next()); }
    virtual const TListItemOf<T>* Prev() const { return static_cast<const TListItemOf<T>*>(Inherited::Prev()); }

private:
    TListItemOf<T>(const TListItemOf<T>&);
    void operator=(const TListItemOf<T>&);
};


/*template <class T>
class TListOf : public TList
{
    typedef TList Inherited;
public:
    TListOf<T>(void) {}

    IMPLEMENT_LIST_METHODS(TListItemOf<T>, TListOf<T>, Inherited);
private:
    TListOf<T>(const TListOf<T>&);
    void operator=(const TListOf<T>&);
};*/


template <class T>
class TListOf : public TList
{
    typedef TList Inherited;
public:
    TListOf<T>(void) {}

   //IMPLEMENT_LIST_METHODS(TListItemOf<T>, TListOf<T>, Inherited);
   virtual TListItemOf<T> * First() { return static_cast<TListItemOf<T> *>(Inherited::First()); }
   virtual TListItemOf<T> * Last () { return static_cast<TListItemOf<T> *>(Inherited::Last()); }
   virtual TListItemOf<T> * operator[](unsigned int index) { return static_cast<TListItemOf<T> *>(Inherited::operator[](index)); }
   virtual const TListItemOf<T> * CFirst() const { return static_cast<const TListItemOf<T> *>(Inherited::CFirst()); }
   virtual const TListItemOf<T> * CLast () const { return static_cast<const TListItemOf<T> *>(Inherited::CLast()); }
   //const TListItemOf<T> * operator[](unsigned int index) const { return static_cast<const TListItemOf<T> *>(Inherited::operator[](index)); }

   //void ReLink       (TListOf<T> *list)                                { Inherited::ReLink(list); }
   //void Append       (TListItemOf<T>* ptItem)                          { Inherited::Append(ptItem); }
   //void DeleteItem   (TListItemOf<T>* ptItem)                          { Inherited::DeleteItem(ptItem); }
   //void ExtractItem  (TListItemOf<T>* ptItem)                          { Inherited::ExtractItem(ptItem); }
   //void ExchangeItems(TListItemOf<T>* ptOne, TListItemOf<T>* ptTwo)    { Inherited::ExchangeItems(ptOne, ptTwo); }
   //void InsertBefore (TListItemOf<T>* ptBefore, TListItemOf<T>* ptNew) { Inherited::InsertBefore(ptBefore, ptNew); }
   //void InsertAfter  (TListItemOf<T>* ptAfter,  TListItemOf<T>* ptNew) { Inherited::InsertAfter (ptAfter,  ptNew); }

private:
    TListOf<T>(const TListOf<T>&);
    void operator=(const TListOf<T>&);
};


#endif //FLAPPYBIRDAPP_TLIST_H
