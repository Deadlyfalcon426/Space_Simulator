# C++:
`friend`: grants a specific non-member function or class access to a class's private/protected members. A friend is not itself a member of the class.

`operator<<`: name of the function being overloaded; lets us define what << does when used with our class.

`std::ostream& os`: parameter representing the output stream (std::cout, a file stream, etc.). & means we work with the existing stream rather than making a copy.

`std::ostream&` before `operator<<`: return type. The function returns the same stream so << operations can be chained
# Physics:
mostly paper for now
# Mathematics:
will mostly stick to paper for now
# Project Design:
I Initially thought of using a position class that I could assign to different other classes. However after a second thought, I remembered some of my research before starting this project, and thought that a vector could also be a position, as well as just being a direction or a way to show velocity and magnitude. So now I'm using a vector instead of a Position class. I also thought about using inheritance/abstract/interfaces but then I realized I was just trying to force it in, because theres nothing horrible that could happen if I'm instantiating points randomly...
TL:DR of that is that instead of just a position class, we can use a vector class because its mathematical definition covers all the stuff we need.
