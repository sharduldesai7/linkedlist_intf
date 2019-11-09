# Interfaces for double linked list and heap.

Interfaces for linked list and heap sort

### Running the example code in heap_intf.cpp

```
./heap_intf int1 int2
```

Example input:
```
./heap_intf 500 30
```

int1 = seed for randomiser (basically any reasonable number)

int2 = number of entries

The heapsort generates random inputs. You don't have to give them.

## Use as you want to

See the LICENSE file

## Limitation

Execution runs into infinite loop for certain random seed and number of entry values. 
The problem is not with the algorithm surely. I haven't been able to figure it out though - just been lazy about it.
Example for bug reproduction:
```
./heap_intf 500 100
```

* Do take a look at the bug
* Do contribute if you can improve

