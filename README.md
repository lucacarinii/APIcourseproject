# System for monitoring relations between users
University project for the API course (algorithms and principles of computer science)

### Technologies:
- C
- CLion

### Description:

Implementation in standard C language (with only libc) of a program that reads a sequence of commands from standard input, each corresponding to a change in the entities or in the relationships between entities and, when required, produces on standard output, for each type of relationship monitored, the identifier of the entity that is the recipient of the largest number of instances of that relationship, and the number of relationships that the entity receives.

More abstractly, the mechanism monitors the following phenomena:
- A new entity begins to be monitored
- A monitored entity stops being monitored
- A new relationship is established between 2 monitored entities
- A relationship existing between 2 monitored entities ceases to exist
