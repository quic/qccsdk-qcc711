/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef GLINK_LIST_H
#define GLINK_LIST_H

/*=============================================================================

                   GLink List Header File

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

#define GLINK_LIST(type, name) \
  struct { \
    type *head; \
    type *tail; \
    unsigned int count; \
  } name

#define GLINK_LINK(type, link) \
  struct { \
    type *prev; \
    type *next; \
  } link

#define GLINK_LIST_INIT(list) do {  \
  (list).head = (list).tail = NULL; \
  (list).count = 0; \
} while(0)

#define GLINK_LINK_INIT(link) (link).next = (link).prev = NULL

#define GLINK_LIST_HEAD(list) (list.head)
#define GLINK_LIST_TAIL(list) (list.tail)
#define GLINK_LIST_CNT(list) (list.count)
#define GLINK_LIST_REMOVE(list, node, link) \
  do { \
    if((node)->link.prev) \
      (node)->link.prev->link.next = (node)->link.next; \
    else /* node at the front of the list */ \
      list.head = (node)->link.next; \
    if((node)->link.next) \
      (node)->link.next->link.prev = (node)->link.prev; \
    else /* node at the end of the list */ \
      list.tail = (node)->link.prev; \
    list.count--; \
  } while(0)

#define GLINK_LIST_ADD(list, node, link) \
  do { \
    if(!list.tail) \
    { \
      /* first node on the list */ \
      list.tail = list.head = node; \
    } \
    else \
    { \
      (node)->link.prev = list.tail; \
      list.tail->link.next = node; \
      list.tail = node; \
    } \
    list.count++; \
  } while(0)

#define GLINK_LIST_FIND(list, iter, link, test) do {  \
  iter = (list).head; \
  while(iter) { \
    if(test) {  \
      break;  \
    } \
    iter = (iter)->link.next;  \
  } \
} while(0)

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/

#endif /* GLINK_LIST_H */
