# libcoll

Collections implemented in ANSI C.

- [Linearity](#linearity)
  - [list](#list)
  - [vector](#vector)
  - [array](#array)
  - [deque](#deque)
  - [seq](#seq)
  - [tuple](#tuple)
- [Association](#association)
  - [tmap](#tmap)
  - [hmap](#hmap)
- [Adapter](#adapter)
  - [stack](#stack)
  - [queue](#queue)
  - [tset](#tset)
  - [hset](#hset)
  - [heap](#heap)

## Linearity

### list

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

### vector

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

### array

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

### deque

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

### seq

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

### tuple

Tuples with 2 to 5 elements.

## Association

### tmap

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

### hmap

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

### stack

A stack implemented with vector.

#### Operations

* new, free
* size, empty
* peek, foreach
* push
* pop, clear

### queue

A queue implemented with deque.

#### Operations

* new, free
* size, empty
* front, back, foreach
* push
* pop, clear

### tset

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

### hset

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

### heap

A binary heap implemented with vector.

#### Operations

* new, free
* size, empty
* top, foreach
* push
* pop, clear
