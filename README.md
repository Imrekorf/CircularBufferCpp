# CircularBufferCpp

Simple C++ Circular buffer.

Implemented as a linked list. Element 0 is the last added element.

Sample implementation:

```c++
size = 3 // indicates the amount of elements will be stored before older elements will be discarded.

CircularBufferNode<double>* CBNstart = new CircularBufferNode(size);
CircularBufferNode<double>::add(&CBNstart, 1.0);
CircularBufferNode<double>::add(&CBNstart, 2.0);
CircularBufferNode<double>::add(&CBNstart, 3.0);

std::cout << (*CBNstart)[0].val << std::endl;
std::cout << (*CBNstart)[1].val << std::endl;
std::cout << (*CBNstart)[2].val << std::endl;

/*
  outputs:
  3
  2
  1
*/

CircularBufferNode<double>::add(&CBNstart, 4.0);
std::cout << (*CBNstart)[0].val << std::endl;
std::cout << (*CBNstart)[1].val << std::endl;
std::cout << (*CBNstart)[2].val << std::endl;

/*
  outputs:
  4
  3
  2
*/

CircularBufferNode<double>::freeCircularBuffer(&CBNstart); // also turns the CBNstart to nullptr;

return 0;
```
