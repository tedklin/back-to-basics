## The basic process

1. Understand the problem. What are we trying to solve? What is unknown and what is known? Try restating the problem in different ways, including drawing figures if applicable.
2. Make a plan, guided by the heuristics listed in the next section. This is the phase for the more carefree exploring/sketching of approaches/ideas. Don't be scared of trying anything that you think may be plausible/connected but are unsure whether it will directly lead you to a correct solution - even if what you try is ultimately off-base, it might give you insight towards a solution.
3. Carry out the plan. This is the phase for the more careful thorough/rigorous construction of your solution. Start from the major steps of your solution before going into minor details (but don't forget minor details altogether!).
4. Reflect on your work. (Taking some time on this is important for your learning!) What worked and what didn't? For what other problems might this solution or method be useful?


## Heuristics

### Analogy

Find and solve a simpler related problem (e.g. in a smaller dimension), then extend the result *and/or* method for that simpler related problem to the original problem.

- Related to the concept of [specialization](#auxiliary-problem).
- Examples of mathematically-precise forms of analogy include *isomorphism* and *homomorphism*.

### Auxiliary element

"Having recollected a formerly solved related problem and wishing to use it for our present one, we must often ask: Should we introduce some auxiliary element (e.g. a line, an unknown/variable, a theorem) in order to make its use possible?" Auxiliary elements are also used to reinforce definitions (e.g. when dealing with a circle we might draw out its radius), and they make the problem "fuller, more suggestive, and more familiar".

### Auxiliary problem

Equivalent/bilateral reduction
- e.g. to solve an algebraic equation, we often come up with a chain of equivalent equations (transformed by doing the same operation on both sides of the equation) until we get to the solution.

Unilateral reduction
- Say we have two problems A and B, such that if we knew how to solve A we could *directly* use that to fully solve B, but if we could only solve B we could not directly use that to fully solve A. (A is "more ambitious" than B. B is a specific case or set of cases of A. B considers a subset of the set of objects considered by A.)
- *Specialization*: a unilateral reduction from A to B.
    - For problem-solving:
        - e.g. Our original problem A is how to derive the diagonal of a rectangular prism with dimensions a b c. Our specialized problem B is how to derive the diagonal of a rectangle with dimensions a b.
            - B's solution (Pythagoras' theorem) doesn't *directly* give us A's solution, but B's solution might be useful as a *stepping stone* towards A's solution (*problem-solving by [analogy](#analogy)*).
            - On the other hand, A's solution would directly give us B's solution since B is just a specific case of A where c = 0.
        - e.g. Our original problem A is how to find the closest distance between two linearly moving ships given each ship's constant velocity and its position at a certain time. Our specialized problem B is an extreme case of A where one ship is at rest (zero velocity).
            - B's solution is obvious: it is the length of the perpendicular from the stationary ship to the line along which the other ship moves.
            - We can relate B back to A by observing that motion is relative. So any instance of the more general A can be reduced to a easily-solvable instance of B by adding velocity equal-but-opposite-to-one-of-the-ships to both ships. 
    - For proofs
        - When trying to prove/disprove a statement, specialization can lead to finding a counterexample (which disproves the statement).
    - **It is often useful to consider cases that are simple but extreme (e.g. setting one of the variables to zero or to infinity).**
- *Generalization*: a unilateral reduction from B to A.
    - e.g. If our original problem B is to find something given concrete values, it may be easier to substitute variables for the given values and manipulate the resulting algebraic equation (the more general problem A) to get to a solution.
    - Also see problem-solving under [Inventor's paradox](#inventors-paradox).


## Inductive reasoning and mathematical induction

*Inductive reasoning*: the process of discovering general laws by the observation and combination of particular instances.

*Mathematical induction*: the process of mathematically proving something by going from n to n+1.

These are two distinct processes, but they are often used together.

Example:


## Inventor's paradox

For problem-solving, the more ambitious (general) problem may be clearer/easier to solve.
- e.g. Our original problem B is how to find a plane that passes through a given line and bisects the volume of a *regular octohedron* for which the position is given. To solve B, we can consider a more ambitious/general problem A: how to find a plane that passes through a given line and bisects the volume of a *solid with a center of symmetry* for which the position is given.
    - Since B is a specific case of A (a regular octohedron is an instance of a solid with a center of symmetry), A's solution implies B's solution, i.e. A's solution is sufficient to fully solve B.
        - Notice the converse is not true (B's solution does not imply A's solution).
    - A is clearer/easier to solve (the solution is the plane defined by the line and the center of the symmetric solid), because it isolates the relevant property of a regular octohedron: that it has a center of symmetry. We can ignore trying to take into account the other properties of regular octohedrons.

For proving, the more ambitious (precise) statement may be clearer/easier to prove.
- e.g. Our original statement-to-prove is: the sum of the first n cubes is a square. It's unclear how to proceed directly from this "hazy" statement, but through [inductive reasoning](#inductive-reasoning-and-mathematical-induction), we might notice a potential pattern giving us a more ambitious/precise yet also more "tangible"/"manipulable" statement-to-prove: $1^3 + 2^3 + 3^3 + ... + n^3 = (1 + 2 + 3 + ... + n)^2$.
    - Proving the more ambitious/precise statement to be true implies the original statement is true.
        - Notice the converse is not true (the original statement being true does not directly imply the more ambitious/precise statement).
    - The more ambitious/precise statement is an obvious candidate for a familiar proof technique, [mathematical induction](#inductive-reasoning-and-mathematical-induction), that we can proceed with.




## Attitude

