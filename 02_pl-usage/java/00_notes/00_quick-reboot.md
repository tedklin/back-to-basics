A quick list of basic reminders when coming from other programming languages (back) to Java.

Sampled from first few chapters of *Thinking in Java* by Bruce Eckel.


### All code goes inside classes.

- But not everything needs to be referenced through an object / instance of a class. When you say a class field/method is `static`, it means that particular field/method is not tied to any particular object instance (i.e. there is *one instance of that field/method* that's shared among all object instances of that class). These `static` members can be referenced directly through `ClassName.staticMember` (whereas non-static members need to be referenced through `createdObjectInstance.nonStaticMember`).
    - Accordingly, static methods don't have a `this` reference (the `this` reference in a method is a reference to the specific object instance that called the method).

- For each source file, you can have at most **one** public class, and that public class must be of the same name as the source file name.
    - But you may have "support" classes that are non-public, as well as public *internal classes* within the "main" public class.


### You always manipulate objects using references. Identifiers/variables that "contain" objects are really just references to those objects.

- When using `=` to assign an object variable to another object variable, you're pointing them to the same object in memory, **NOT copying their contents**.

- When passing an object to a function, you're passing a reference to that object (**the object itself is NOT copied**). Same with returning an object from a function.

- The `==` operator on two object variables checks if they reference the same object in memory, **NOT if their *contents* are the same**.
    - If you want to check if the contents of two objects are the same, use the `equals` method (after making sure it's overriden correctly).

- The `final` keyword used with an object variable indicates that the object *reference* stored is constant (i.e. you *can't rebind* that identifier to point to a different object, but the already-referred-to object itself can be modified).
    - There is no mechanism to make an object itself constant, other than designing the corresponding class that way.
    - Misc note about `final` member variables: they must be initialized at the point of declaration or in every constructor.


### The only way to create objects is to dynamically allocate them in heap memory.

- In general, use the `new` keyword to create objects (although some special objects like arrays support other convenient initialization syntax).

- All objects live on the heap and have their lifetimes managed automatically by Java's garbage collector.
    - Java programmers have no control over object lifetime.
    - This is in contrast to C where all heap memory must be explicitly allocated and freed by the programmer.

- Only primitive types and object references can live on the stack.
    - This is in contrast to C where structs themselves can exist on the stack.


### Arrays are (special) objects.

- This is in contrast to C where arrays are just simple blocks of memory.

- `int[] arr` declares a reference to an array object, which you can then initialize or assign using (for example) `= new int[4]` or `= new int[] { 2, 2, 2 }` or `= someOtherArray`.

- All arrays intrinsically maintain a `length` member you can query.


### Booleans have limited functionality.

- Casting is not allowed at all for booleans (whereas all other primitive types can be cast between each other).

- You can’t use a non-boolean as if it were a boolean in a logical expression.
    - i.e. there is no concept of "falsy" values like there is in other common languages.

```
// this is not valid Java
int i = 1;
if (i) {
    doSomething();
}

// you would have to do this instead
if (i != 0) {
    doSomething();
}
```


### There is no programmer-defined operator overloading.

- Note the `+` and `+=` operators are natively overloaded as concatenation for `String`s.

