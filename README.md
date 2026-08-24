# Orbital Simulator

My orbital simulator calculates the positions of planets for a given total simulation time and numerical timestep. This is mainly to explore methods of numerical analysis. The two types of numerical analysis that have been implemented are Runge-Kutta 4 and Euler's method.

The project was built in C++ entirely, and includes a custom 3-dimensional vector class, celestial-body classes, gravitational calculations, and the numerical integration methods. Raylib was later added to provide a crude 3D visualization of the simulation.

## What it does

* Simulates gravitational interactions
* Supports Euler and RK4 numerical integration
* Models celestial bodies using C++
* Calculates the position, velocity, and acceleration of celestial bodies over time
* Uses a custom `PhysicsVector3` class for three-dimensional physics calculations
* Visualizes the simulation with Raylib
* Outputs the final positions of the celestial bodies and their displacement from their initial positions
* Allows the user to select the total simulation time, numerical timestep, and numerical integration method

## Physics

The primary physical model used by the simulator is Newtonian gravity.

The gravitational force between two celestial bodies is calculated using Newton's law of universal gravitation:

[
F = G\frac{m_1m_2}{r^2}
]

where `G` is the gravitational constant, `m1` and `m2` are the masses of the two bodies, and `r` is the distance between them.

The gravitational force is then used to calculate acceleration through Newton's second law:

[
F = ma
]

The resulting acceleration is used by the numerical integration method to update the velocity and position of each celestial body.

The simulator uses three-dimensional vectors for position, velocity, acceleration, and gravitational force, allowing the system to eventually support non-planar orbital motion.

The initial conditions for the planets are based on real-world values. For example, the initial velocity used for Mars was calculated using the vis-viva equation rather than simply assigning it an arbitrary velocity:

[
v^2 = GM\left(\frac{2}{r}-\frac{1}{a}\right)
]

where `M` is the mass of the central body, `r` is the current orbital distance, and `a` is the semi-major axis of the orbit.

The current simulation is a simplified Newtonian model, nothing too beyond AP Physics 1 with a bit of differential equations and calculus. It does not attempt to reproduce every factor involved in real planetary motion.

## Architecture

* **CelestialBody**

  * A class to store each planet/satellite
  * Contains name, mass, velocity, position, and acceleration
  * Contains the gravitational calculation function `CelestialBody::get_gravitational_force`
  * Allows the physical state of each celestial body to be updated independently
  * The same class can therefore represent objects such as the Sun, Earth, or Mars rather than requiring separate classes for each one

* **PhysicsVector3**

  * A class for a 3-dimensional mathematical vector.
  * Contains X, Y, Z, as well as units for verification between operations
  * The class is used to store physical quantities such as position, velocity, acceleration, and force
  * Contains overloaded arithmetic operators to make vector calculations more natural
  * Contains methods for operations such as finding the difference between vectors
  * It was renamed to `PhysicsVector3` due to the naming conflict with Raylib's `Vector3`
  * The unit system was originally included to help prevent incompatible physical quantities from being used in the same operation

* **PhysicsFunctions**

  * Contains functions that operate on the collection of celestial bodies and perform the actual simulation calculations
  * Contains the overall simulation `step` function
  * Handles the numerical integration methods used to advance the simulation
  * Keeps the overall simulation logic separate from the individual `CelestialBody` objects

* **RK4 variables**

  * A struct to hold variables necessary for the RK4 method.
  * RK4 requires several intermediate calculations during each timestep, so these values are stored separately rather than being placed directly into the `CelestialBody` class
  * This helps keep the permanent physical state of a body separate from the temporary values required during an RK4 calculation

* **Renderer**

  * Handles the Raylib window and 3D visualization
  * Creates and manages the camera
  * Receives the current celestial-body positions from the simulation
  * Draws the celestial bodies based on their current positions
  * The renderer does not perform the gravitational or numerical calculations itself; the physics engine remains responsible for determining the state of the simulation

## Numerical Methods

### Euler

* Euler's method is a simple numerical integration method that estimates the next state of a system using its current state and its derivative.
* In the orbital simulation, the current velocity and acceleration are used to estimate the position and velocity at the next timestep.
* It is relatively computationally inexpensive because it only requires one main evaluation per timestep.
* The disadvantage is that numerical error accumulates pretty quickly, and is further accentuated by larger timesteps or longer periods of time.
* Euler was useful as a baseline for this project because it provides a relatively simple method to compare against RK4.

In simplified form, Euler's method can be represented as:

[
y_{n+1}=y_n+h f(t_n,y_n)
]

where `h` is the timestep.

### RK4

* RK4, Runge-Kutta-4, is a much more accurate method of numerical analysis than Euler's method, and a more computationally expensive one.
* Instead of using only the current state of the system, RK4 makes four evaluations during each timestep.
* These evaluations estimate the behavior at the beginning, middle, and end of the timestep.
* The four estimates are then combined using different weights to produce the final update.
* The additional calculations make RK4 more expensive than Euler, but they significantly reduce the numerical error for many problems.
* Implementing RK4 was one of the most difficult parts of the project because the intermediate values must be calculated and applied correctly without accidentally modifying the actual state of the celestial bodies too early.
* RK4 also is susceptible to the same pitfalls of Euler's method (larger timesteps and longer periods of time can cause more error, as well as just inherent error in RK4 that gets accumulated), however the amount of error is much lower compared to Euler.

The general RK4 process can be summarized as calculating four intermediate values, commonly referred to as `k1`, `k2`, `k3`, and `k4`, and then using a weighted combination of them to calculate the next state. This is covered a lot in my code, as I haven't cleaned up a lot of the comments that helped me understand and describe RK4.

## Visualization

The renderer runs on Raylib, an open-source library designed to provide relatively straightforward access to graphics, window management, input, and other multimedia functionality.

Raylib was added after the main physics engine had already been developed. Its purpose in this project is primarily to provide a visual representation of the numerical simulation.

The renderer creates a 3D perspective camera and draws the celestial bodies at positions determined by the physics engine.

The visualization also makes debugging the physics considerably easier. Before Raylib was added, an incorrect orbit could only be identified by examining numerical output. With the renderer, problems such as incorrect gravitational directions or obviously unstable orbits could be identified visually. However, I never had a chance to use this as I had already finished with the physics engine before starting with raylib.

The current renderer is intentionally fairly simple. It focuses on displaying the simulated positions rather than providing a complete interactive space simulator. This is partially by design, as the real purpose of the project is not to learn raylib or low-level 3D graphics, but learn about methods of numerical analysis and the C++ language.

## Challenges & Lessons Learned

* The last thing holding me back from finishing the physics engine was an accidental reversion of the gravitational force calculation function. This was particularly frustrating because the numerical integration code appeared to be the source of the problem at first.
* I learned about how RK4 and Euler work, as well as the numerical instability involved.
* RK4 was difficult to implement, as it took me many retries of writing out the outline before I had a sufficient understanding of how to implement RK4.
* Implementing my own vector class taught me about operator overloading, constructors, class design, and using mathematical abstractions in C++.
* Structs were some of the most interesting concepts I researched prior to the project - a class simply for storing other variables. I'm thankful I had the chance to implement a few useful ones.
* The project also forced me to think about the difference between a physical quantity such as position or velocity and the mathematical operations being performed on that quantity.
* Integrating Raylib with an existing physics engine was complicated because it forced me to think about the exact order and reliance of the two different aspects of the program with each other. I'm still not entirely happy with where it is right now, due to it showing a faster animation for a larger base step, but it works fine besides the cosmetic issue.
* More specifically, the current renderer displays the state of the simulation once each physics step. This means that changing the base timestep changes both how frequently the physics is calculated and how quickly the displayed simulation progresses. A future version could separate these two concepts using interpolation or a dedicated playback system.
* One thing that I had to focus on a lot was the difference between simulation time and real time. Real-life time is burdened by the raylib functions that lock down frames per second and when frames are triggered. Simulation time is much larger generally, always measured in seconds and refers to the time the physics engine works with.
* I also learned that integrating an external library into an existing project can introduce unexpected problems, such as the naming conflict between my original `Vector3` class and Raylib's `Vector3` structure.
* My first CS project at all. I learned a lot about proper project structure (CMake folders), importing libraries, and about the C++ language and structure. One big thing I learned from this was how much I'm capable of pushing myself in a week. I'm happy I was able to do it in my favorite language, C++!

## Known Limitations

* Renderer is relatively basic
* No orbital trails
* Simulation timestep affects visual speed
* Lack of optimization, including but not limited to some of the gravitational calculation structures
* Limited celestial-body presets
* The program is somewhat hard-coded, particularly during the initial creation of the Sun, Earth, and Mars
* No interpolation between physics states for smoother rendering
* Camera controls are currently limited
* Planet textures have not yet been integrated into the renderer
* The simulation currently uses a simplified Newtonian model and does not account for every real-world effect

## How to Build

The project uses CMake to build the C++ application.

By using `FetchContent` in the CMake configuration file, the project automatically includes raylib, instead of requiring a manual download.

The project can be built by configuring the CMake project and then building the generated Visual Studio/CMake project.

## How to Run

After running `Space_Simulator.exe`, a sample input I frequently use is `31556952`, the amount of seconds in a year for the time passed. Any number of seconds will do.

As the base step, I use `900` (15 minutes), but you can choose any number of seconds. Smaller timesteps generally require more calculations but can provide greater numerical accuracy.

Then, you can type `"Euler"` or `"RK4"` for your numerical analysis method. Euler will have more error but be faster than RK4.

After completing all this, have a look at the simulation window, and also check back in your terminal to see the final values for the planets, as well as the difference from their starting locations.

## Future Improvements

* Orbital trails to further visualize paths
* Camera controls for an immersive experience
* Planet textures, already collected in the assets folder, need to be added to the planets using Raylib
* Less hard-coded initialization, set up more opportunities to dynamically customize celestial bodies and simulation settings
* More celestial-body presets, such as a full Solar System, or perhaps Alpha Centauri's system
* Additional numerical integration methods
* Better separation between the physics simulation and renderer
* Interpolation between physics states to improve visual smoothness
* Comment clean-up
* Additional optimization of gravitational calculations
* More methods of numerical analysis to further educate myself in differential equations, and to further reduce error.

## Credits

**Project:** Orbital Simulator
**Author:** Ahsan Mohammed, computer science student in high school (as of 8/23/2026)

**Raylib:** Raylib is developed by Ramon Santamaria (@raysan5) and contributors.

**Earth texture:** ColourNess on DeviantArt — currently unused in the final renderer.

**Sun and Earth textures:** Originally sourced from NASA — currently unused in the final renderer.

Texture assets are included as references for potential future visualization improvements rather than being part of the current simulation itself.
