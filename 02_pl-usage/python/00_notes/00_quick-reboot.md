A quick list of basic reminders / things to review when coming from other programming languages (back) to Python(3.9).

For the rest of this document, "Python" implies "Python 3.9".

Intended to be gone through in order.

For a more-complete-yet-still-relatively-compact intro to Python, try e.g. *Python Distilled* by David Beazley. A list of notable sections to review is included at the end of this list.


### There are no "primitive/value types" - everything is an object, and everything is passed-by-object-reference.

This stands in contrast to a language like Java. However, in practice, behavior is similar since Python *immutable types* can't be modified by reference - they can only be reassigned.

Consider this Python example on a list (a mutable type):

```
def f(a: list[int]):
	a.append(1)

x1 = [0]
f(x1)
# x1 is now [0, 1]

def g(b: list[int]):
	b = [0, 1]

x2 = [0]
g(x2)
# x2 is still [0]
```

Note Java object types exhibit the same behavior as above.

Now consider this Python example on an integer (an immutable type):

```
def h(a: int):
	a = 1

x = 0
h(x)
# x is still 0
```

Note Java primitive types exhibit the same behavior as above. Even though integers are objects in Python, they are immutable and thus restricted to the above case.

For a list of immutable vs mutable built-in types in Python, refer to TOC of [this](https://realpython.com/python-mutable-vs-immutable-types/).


### Multiple variables can be assigned "in parallel"\*, and functions can return multiple values.

Under the hood: tuple packing/unpacking.

Examples:

```
a = 0
b = 1
a, b = b, a
# a is now 1; b is now 0
```

```
# unnecessarily complicated and verbose but illustrates mechanics.
def swap(a: int, b: int) -> tuple[int, int]:
	return b, a

a = 0
b = 1
a, b = swap(a, b)
# a is now 1; b is now 0
```

***\*Multiple assignment is not actually fully parallel under the hood, which can lead to subtle bugs***. What actually happens during multiple assignment:

1. The LHS values are evaluated one-by-one, sequentially from left to right.
2. The LHS values are packed into a temporary tuple.
3. The RHS names are assigned to the respective values in the temporary tuple one-by-one, sequentially from left to right (tuple unpacking).

**Takeaway: "write complex assignments** (e.g. when there are multiple levels of pointers and/or multiple ways to refer to the same pointer like when manipulating linked lists) **explicitly with temporary variables"** (refer to [this](https://stackoverflow.com/a/55369250)).


### Using an augmented assignment operator (e.g. +=) on a mutable object actually performs an *in-place* mutation.

In other words, it would be **incorrect** to think of ```lst += [1, 2]``` as ```temp = lst + [1, 2]; lst = temp```. **There is no new list instance being created and assigned**.

See Beazley section 2.4 for a more illustrative example.


### The equality operator ```==``` vs the identity operator ```is```.

```==``` in Python roughly corresponds to ```.equals``` on objects in Java (think of as comparing the contents of two objects in a well-defined way).

```is``` in Python roughly corresponds to ```==``` on objects in Java (think of as comparing whether two names refer to the same memory location).


### Don't rely on the "implicit truthiness" of values - be precise about condition checking (e.g. use ```is None```).

See Beazley section 2.7 (pg 44).


### Be careful when manipulating bits with the goal of meaningfully modifying integer values.

"Some care is required if you are working with raw bit patterns that are intended to map to native integers on the hardware. This is because Python does not truncate the bits or allow values to overflow — instead, the result will grow arbitrarily large in magnitude. It’s up to you to make sure the result is properly sized or truncated if needed." (Copied directly from Beazley section 1.4.)


### "Static"/"class" variables/methods in Python are subtly different from other languages like Java - it's probably best to just avoid them for the purposes of scripting/leetcode.

For reference (**not** recommended reading), see the various answers in this [thread](https://stackoverflow.com/questions/68645/class-static-variables-and-methods).


### *Python Distilled*, Distilled

Must-review sections/pages, by chapter:
- Ch1
	- pg10 : intro to string manipulation
	- 1.8-11 : standard collections
	- 1.16 : intro to classes and objects
	- 1.18 : intro to script writing
- Ch2
	- 2.1 : literals
	- 2.2 : expressions
	- 2.6 : ordered comparison operators (on sets and sequences including strings)
	- 2.9-14 : operations on standard collections
- Ch3
	- 


### [learnxinyminutes - Python](https://learnxinyminutes.com/docs/python/))

Speedrun of syntax / common operations by example.

Skip everything section 6 (Classes) and on - these are covered better by *Python Distilled*.
