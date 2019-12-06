# libcoll

Collections implemented in ANSI C.

- [Linearity](#linearity)
  - [list](#list)
  - [vector](#vector)
  - [deque](#deque)
  - [seq](#seq)
  - [ring](#ring)
- [Association](#association)
  - [map](#map)
  - [dict](#dict)
  - [set](#set)
  - [pair](#pair)
- [Adapter](#adapter)
  - [stack](#stack)
  - [queue](#queue)
  - [heap](#heap)

## Linearity

### list

A doubly circular linked list.

Time complexity: 

| get | insert | remove | append | prepend |
| - | - | - | - |
| O(min(i, n-i)) | O(min(i, n-i)) | O(min(i, n-i)) | O(1) | O(1) |

### vector

A growable array.

### deque

A double end queue supporting random access.

### seq

A sequence implements a singly linked list.

### ring

A doubly circular linked list, without head.

## Association

### map

A map implemented with red-black tree.

### dict

A dictionary implemented with hash table.

### set

A set implemented with map.

### pair

A pair contains two pointers.

## Adapter

### stack

A stack implemented with list.

### queue

A queue implemented with list.

### heap

A binary heap implemented with vector.
