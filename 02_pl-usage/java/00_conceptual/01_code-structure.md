# Structuring code in Java


## Composition

Composition is when a class definition includes one or more member variables that are object instances of existing classes.

e.g. the Dog class definition includes Leg object members (a dog is *composed of* legs).


## Inheritance

Inheritance (more specifically "class inheritance" / "implementation inheritance") is marked by the keyword `extends` and is when a class definition builds upon an existing non-`final` class definition. The "derived"/"child" class definition *inherits* members and methods from its "base"/"parent" class definition [according to access specifiers in the base class definition](https://docs.oracle.com/javase/tutorial/java/javaOO/accesscontrol.html). The derived class definition can include additional members/methods and can implement/override inherited methods, hence "extending" the base class definition.

Java merges the concept of implementation inheritance with the concept of subtyping, a category of [***polymorphism***](https://en.wikipedia.org/wiki/Polymorphism_(computer_science)). See [this lecture](https://courses.cs.washington.edu/courses/cse331/16wi/L12/L12-Subtyping.pdf) for details.

A few misc rules:

- A class can implementation-inherit from only one base class, i.e. a class can `extends` only one class.
- The child class constructor is responsible for calling the parent class constructor. If the desired parent class constructor takes no arguments, Java will do this implicitly. However, if the desired parent class constructor takes one or more arguments, the child class constructor must explicitly call `super(arg1, arg2, arg3)` (this calls the signature-matching parent class constructor).
- On overriding methods:
    - Over*loading* is when you have different functions with the same name (different parameter lists). Over*riding* is when you give an inherited function signature (same name and same parameter list) a different implementation.
    - Methods with the `final` keyword cannot be overriden.
    - Use the `@Override` tag when your intent is to override an inherited method. The Java compiler will throw warnings if you accidentally end up overloading instead of overriding.
    
***Implementation inheritance is generally considered a flaw in Java's language design because of its usage can cause complications down the road. Popular new languages like Go and Rust support polymorphism without supporting implementation inheritance. When writing Java, generally avoid using implementation inheritance and prefer using composition or interface inheritance.*** (see [James Gosling's comments](https://www.infoworld.com/article/2073649/why-extends-is-evil.html), the Design Patterns book, [Go's design](https://talks.golang.org/2012/splash.article#TOC_15.), [the Rust book](https://doc.rust-lang.org/stable/book/ch17-01-what-is-oo.html#inheritance-as-a-type-system-and-as-code-sharing), and [an article](https://okmij.org/ftp/Computation/Subtyping/Trouble.html) with [various references including John Ousterhout](https://okmij.org/ftp/Computation/Subtyping/References.html))


## Interfaces

An interface is a group of method signatures without any implementation (this means no instance member variables, but `static final` variables are allowed). Interfaces provide polymorphism without the potential inflexibility of implementation inheritance, and their usage faciliates multiple and/or evolving implementations of the same semantic interface.

e.g. the `Comparable<T>` interface includes one method signature: `compareTo(T other)`. For any type `A` that satisfies/`implements` the `Comparable<A>` interface, the library function `Collections.sort` can be used to sort a collection of items of type `A`. Note that because the only function we need for sorting is a way to compare any two items in the collection, the library only needs to write the sorting code once for the Comparable interface, and the code can be reused for any collection whose items are of a type that satisfies/`implements` the `Comparable<A>` interface. If we were defining a new class MyClass and wanted users to be able to use the `Collections.sort` function on a collection of items of type MyClass, we can simply add `implements Comparable<MyClass>` and implement the methods specified in the interface (in this case, just `compareTo(MyClass other)`). Additionally, MyClass can implement/satisfy the specification of other interfaces.

A few misc rules:

- Object instances of an interface itself are not allowed (because there are unimplemented methods).
- A class can implement multiple interfaces (recall that a class can extend only one base class).


## Abstract classes

An abstract class is a class with at least one `abstract` (unimplemented) method. Like with interfaces, object instances of an abstract class itself are not allowed.


## Inner classes


## Generics

### Basic usage

`ArrayList<T>` denotes an ArrayList holding (references to) objects of type T. T is called a "type parameter", and a generic type can have more than one type parameter (e.g. `HashMap<KeyType, ValueType>`).

With generics, you’re prevented, at compile time, from putting the wrong types of objects into a container (e.g. you can't insert a `Banana` into an `ArrayList<Apple>`). Subtyping is still present with type parameters (e.g. you can insert both `RedApple`s and `GreenApple`s into an `ArrayList<Apple>`).

