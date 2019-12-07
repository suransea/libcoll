# libcoll

Collections implemented in ANSI C.

- [Linearity](#linearity)
  - [List](#list)
  - [Vector](#vector)
  - [Deque](#deque)
  - [Seq](#seq)
  - [Ring](#ring)
- [Association](#association)
  - [Map](#map)
  - [Dict](#dict)
  - [Set](#set)
  - [Pair](#pair)
- [Adapter](#adapter)
  - [Stack](#stack)
  - [Queue](#queue)
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
* sort, reverse

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
* assign, sort*

### Deque

A double end queue supporting random access.

#### Time Complexity

get | insert(i) | remove(i) | append | prepend
--- | --------- | --------- | ------ | -------
O(1) | O(min(i, n-i)) | O(min(i, n-i)) | O(1) | O(1)

#### Operations

* new, free
* size, empty
* at, index_of*, find*, foreach
* append, prepend, insert_at*, insert_before*, insert_after*, insert_sorted*
* remove*, remove_all*, remove_if*, remove_first, remove_last, remove_at*, clear
* assign

### Seq

A sequence implements a singly linked list, without head.

#### Time Complexity

get(i) | insert(i) | remove(i) | append | prepend
------ | --------- | --------- | ------ | -------
O(i) | O(i) | O(i) | O(n) | O(1)

#### Operations

* free
* size
* at*, last, index_of*, find*, foreach
* append, prepend, insert_at*, insert_before*, insert_after*, insert_sorted
* remove*, remove_all*, remove_if*, next, remove_last, remove_at*
* reverse*

### Ring

A doubly circular linked list, without head.

#### Time Complexity

get(i) | insert(i) | remove(i) | append | prepend
------ | --------- | --------- | ------ | -------
O(abs(i)) | O(abs(i)) | O(abs(i)) | O(1) | O(1)

> "i" allow negative.

#### Operations

* new, free
* size
* index_of*, first*, last*, find*, foreach
* insert, insert_at*, insert_before*, insert_after*, insert_sorted*
* remove, remove_all, remove_if, remove_first*, remove_last*, remove_at*
* reverse*

## Association

### Map

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

### Dict

A dictionary implemented with hash table.

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

### Set

A set implemented with map.

#### Time Complexity

get | insert | remove
--- | ------ | ------
O(log n) | O(log n) | O(log n)

#### Operations

* new, new_custom, free
* size, empty
* foreach
* insert
* remove, clear
* contains

### Pair

A pair contains two pointers.

#### Operations

* new, free

## Adapter

### Stack

A stack implemented with list.

#### Operations

* new, free
* size, empty
* peek, foreach*
* push
* pop, clear

### Queue

A queue implemented with list.

#### Operations

* new, free
* size, empty
* front, back, foreach*
* push
* pop, clear*

### Heap

A binary heap implemented with vector.

#### Operations

* new, free
* size, empty
* top, foreach*
* push
* pop, clear
