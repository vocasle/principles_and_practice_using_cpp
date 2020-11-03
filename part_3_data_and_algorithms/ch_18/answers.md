1. **What does "Caveat emptor!" mean?**

    According to Wikipedia, It is a short form of *Caveat emptor, quia ignorare non debuit quod jus alienum emit* ("Let a purchaser beware, for he ought not to be ignorant of the nature of the property which he is buying from another party.") I.e. the buyer should assure himself that the product is good and that the seller had the right to sell it, as opposed to receiving stolen property.

2. **What is the default meaning of copying for class objects?**

    Default meaning is to copy the reference to the object in memory, in other words it is a shallow copy.

3. **When is the default meaning of copying of class objects appropriate? When is inappropriate?**

    Shallow copy might be useful if class does not contain any dynamically allocated objects.

    Shallow copy probably is inappropriate for classes that allocate data on the heap store.

4. **What is a copy constructor?**

    A copy constructor has following signature:

    `MyClass(const MyClass&)`,

    and is used to perform deep copy of the objects.

5. **What is a copy assignment?**

    A copy assignment is an operator overload for custom class:

    `MyClass& operator=(const MyClass&)`,

    and is used to perform deep copy of the objects.

6. **What is the difference between copy assignment and copy initialization?**

    Copy assignment can be performed on the variable that is already initialized. Copy initialization is performed when variable is initialized via copy constructor.

7. **What is shallow copy? What is deep copy?**

    A shallow copy means that only a reference or pointer to the object is copied.

    A deep copy means that a reference or pointer is copied as well as the data that pointer or reference is pointing to.

8. **How does the copy of a vector compare to its source?**

    A copy of a vector contains same data as its source, but have different pointer to the data, because data was copied to new location.

9. **What are the five "essential operations" for a class?**

    1. Default constructor

    2. Copy constructor

    3. Copy assignment

    4. Move constructor

    5. Move assignment

    6. Destructor

10. **What is an explicit constructor? Where would you prefer one over the (default) alternative?**

    Explicit constructor takes a single argument and defines a conversion from its argument type to its class. Example: `std::vector<std::string> strings(10)`.

    Explicit constructor is preferable over default constructor in situations like when you need to create a `std::vector<std::string>` with 10 elements initialized with default constructor.

11. **What operations may be invoked implicitly for a class object?**

    Constructors and destructors of the class.

12. **What is an array?**

    An array is a contiguous block of memory of the same type.

13. **How do you copy an array?**

    Use `std::copy` or copy each element of the source array into the element of the target array.

14. **How do you initialize an array?**

    Stack allocated arrays are initialized with `int arr[10]` syntax, and heap allocated arrays are initialized with `int* arr = new int[10]` syntax.

15. **When should you prefer a pointer argument over a reference argument? Why?**

    Say function might return nullptr in this scenario it is a viable option to use pointer as a return type.

    According to [post on Stack Overflow](https://stackoverflow.com/a/7058373/3846281) it is best practice to use reference over pointers wherever is possible.

16. **What is a C-style string?**

    A zero terminated array of characters.

17. **What is a palindrome?**

    A word that if reversed is equals to original word, example: ana, bob, etc.
