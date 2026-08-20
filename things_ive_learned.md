# C++:
`friend`: grants a specific non-member function or class access to a class's private/protected members. A friend is not itself a member of the class.

`operator<<`: name of the function being overloaded; lets us define what << does when used with our class.

`std::ostream& os`: parameter representing the output stream (std::cout, a file stream, etc.). & means we work with the existing stream rather than making a copy.

`std::ostream&` before `operator<<`: return type. The function returns the same stream so << operations can be chained
# Physics:
mostly paper for now
we can find the approximate distance of earth from the sun by maybe using the apogee
well its actually aphelion apparently because the sun: just put in the value as one of the imensions, I chose X
BIG THING: EARTH HAS INITIAL VELOCITY, AS WELL AS OTHER PLANETS PLEASE ADD THIS IN AT SOME POINT
interesting read for later: https://www.quora.com/What-is-the-velocity-of-Earth-at-perihelion-and-aphelion-How-is-this-information-calculated
vis-viva equation!
# Mathematics:
will mostly stick to paper for now
for 3d vector V -> (3,5,8), with displacement -> d = sqrt( dx^2 + dy^2 + dx^2 ) = sqrt(9+25+64) = 98

# Project Design:
I Initially thought of using a position class that I could assign to different other classes. However after a second thought, I remembered some of my research before starting this project, and thought that a vector could also be a position, as well as just being a direction or a way to show velocity and magnitude. So now I'm using a vector instead of a Position class. I also thought about using inheritance/abstract/interfaces but then I realized I was just trying to force it in, because theres nothing horrible that could happen if I'm instantiating points randomly...
TL:DR of that is that instead of just a position class, we can use a vector class because its mathematical definition covers all the stuff we need.

I can find the force between the two bodies as a single number, the forcem and then I don't know how to split it. I also need to split it appropriately, meaning it must be in the direction of the other planetary body. Maybe we find the angle of them from each others positions, like relative to the origin somehow? Then we use some angle formula to split the full magnitude 3d-vector into 3 components, just like how you would do so with a 2d-vector. I thought I could get away without implementing an angle system because I couldn't figure it out, but I guess that's what we're doing!

So what kind of unit conversion or whatever are we thinking? perhaps... before every function we are going to use unit conversions... in main or in each function as like a check? im thinking check in main, make a unit translating function (gonna be a pain but seems a bit unavoidable for my purposes) then throw errors in the actual thing cause I dont want to return faulty vectors? error handling idk how it is in C++ probably not that bad to set up, probably not as simple as javas as we had to suffer a little bit just to have freaking class files

Random thought: order vector<CelestialBody> by something? mass?

maybe a overloaded vector3::adjust with Vector3 parameter

We can probably lower like time comp. because g force on two planets equals each other. this leads to less of an O(n^2) net gravity calculation and a faster one where we like do the same thing but we also use memoisation to keep running net forces of all planets, then keep adding to them instead of like using .adjust and doing them one by one.
WHOAH THIS IS SUPER COOL
I related that this would mean the amount of gravity calculations is equal to the amount of combinations of 2
so then using n choose r with n being n and r being 2(2 in each), i found that, after simplifying, the amount of calculations would have been (1/2) * (n^2 - n), which is better than n^2 by a lot!
its fun that i was able to apply discrete/statistics to a CS project, and I will definitely implement the new set up for net gravity calculations soon!
Actually it's still O(n^2) in both cases, however it nearly halves the computational work involved.