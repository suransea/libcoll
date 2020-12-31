# libcoll

Collections implemented in ANSI C.

- [Linearity](#linearity)
  - [List](#list)
  - [Vector](#vector)
  - [Array](#array)
  - [Deque](#deque)
  - [Seq](#seq)
  - [Tuple](#tuple)
- [Association](#association)
  - [TMap](#tmap)
  - [HMap](#hmap)
- [Adapter](#adapter)
  - [Stack](#stack)
  - [Queue](#queue)
  - [TSet](#tset)
  - [HSet](#hset)
  - [Heap](#heap)

## Linearity

### List

A doubly circular linked list.

#### Time Complexity

get(i) | insert(i) | remove(i) | append | prepend
------ | --------- | --------- | ------ | -------
O(min(i, n-i)) | O(min(i, n-i)) | O(min(i, n-i)) | O(1) | O(1)

#### Operations

* new, free
* size, empty
* at, first, last, index_of, find, foreach
* append, prepend, insert_at, insert_before, insert_after, insert_sorted
* remove, remove_all, remove_if, remove_first, remove_last, remove_at, clear
* assign, reverse

### Vector

A growable array.

#### Time Complexity

get | insert(i) | remove(i) | append | prepend
--- | --------- | --------- | ------ | -------
O(1) | O(n-i) | O(n-i) | O(1) | O(n)

#### Operations

* new, free
* size, empty
* at, first, last, index_of, find, foreach
* append, prepend, insert_at, insert_before, insert_after
* remove, remove_all, remove_if, remove_first, remove_last, remove_at, clear
* assign

### Array

A fixed array.

#### Time Complexity

| get | 
| --- | 
| O(1) |

#### Operations

* new, free
* size, empty
* at, first, last, index_of, find, foreach
* assign

### Deque

A double end queue supporting random access.

#### Time Complexity

get | insert(i) | remove(i) | append | prepend
--- | --------- | --------- | ------ | -------
O(1) | O(min(i, n-i)) | O(min(i, n-i)) | O(1) | O(1)

#### Operations

* new, free
* size, empty
* at, first, last, index_of, find, foreach
* append, prepend, insert_at, insert_before, insert_after
* remove, remove_all, remove_if, remove_first, remove_last, remove_at, clear
* assign

### Seq

A sequence implements a singly linked list.

#### Time Complexity

get(i) | insert(i) | remove(i) | append | prepend
------ | --------- | --------- | ------ | -------
O(i) | O(i) | O(i) | O(n) | O(1)

#### Operations

* new, free
* size, empty
* at, first, last, index_of, find, foreach
* append, prepend, insert_at, insert_before, insert_after, insert_sorted
* remove, remove_all, remove_if, remove_first, remove_last, remove_at, clear
* assign, reverse

### Tuple

Tuples with 2 to 5 elements.

## Association

### TMap

A map implemented with red-black tree.

#### Time Complexity

get | insert | remove
--- | ------ | ------
O(log n) | O(log n) | O(log n)

#### Operations

* new, new_custom, free
* size, empty
* value_of, foreach, keys, values
* insert
* remove, clear
* contains_key, contains_value

### HMap

A map implemented with hash table.

#### Time Complexity

get | insert | remove
--- | ------ | ------
O(1) ~ O(n) | O(1) ~ O(n) | O(1) ~ O(n)

#### Operations

* new, new_custom, free
* size, empty
* value_of, foreach, keys, values
* insert
* remove, clear
* contains_key, contains_value

## Adapter

### Stack

A stack implemented with vector.

#### Operations

* new, free
* size, empty
* peek, foreach
* push
* pop, clear

### Queue

A queue implemented with deque.

#### Operations

* new, free
* size, empty
* front, back, foreach
* push
* pop, clear

### TSet

A set implemented with tree map.

#### Time Complexity

insert | remove
------ | ------
O(log(n)) | O(log(n))

#### Operations

* new, new_custom, free
* size, empty
* foreach
* insert
* remove, clear
* contains

### HSet

A set implemented with hash map.

#### Time Complexity

insert | remove
------ | ------
O(1) ~ O(n) | O(1) ~ O(n)

#### Operations

* new, new_custom, free
* size, empty
* foreach
* insert
* remove, clear
* contains

### Heap

A binary heap implemented with vector.

#### Operations

* new, free
* size, empty
* top, foreach
* push
* pop, clear
