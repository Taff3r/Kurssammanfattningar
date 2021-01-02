# ETSN20 Course Summary


### Terms
**Unit test** - Test that tests individual units of source code. Can be automated.
**System test** - Test that tests the integrated system to evaultae the system's compliance with its specified requirements. Can be automated. Can be used to test reliability.

**Reliability** - The defree to which the system is expected to perfom its required functions under stated conditions for a stated period of time. More specifically, the reliability is probabilty for failure free execution during the specified time.

**Fault** - It is an anamoly in the software that may cause it to behave incorrectly, and not accoding to its specification.

**Failure** - A deviation from expected behaviour in the outcome from the execution.

**Error state** - A state of the system, caused by the execution of a fault, but not yet manifested as a failure.

**Human Error** - Error introduced by a human.

**Test case** - Test case in a practical sense is a test-realted item which contains the following information:
1. A set of test inputs.
2. Exectuion conditions.
3. Expected outputs.

**McCabe Cyclomatic Complexity** - A theoretical measurment of the number of lineary independent paths in a CFG.
Can be calculated either with: MCC = #Decision nodes + 1 = #Edges - #Nodes + 2

**Equivalence (Class) Partioning** - Splitting the input into classes which are expected to behave similarly, minimizing the number of test cases that need to be written.
There are two major classes in EP, Valid-, and invalid classes.

**Boundrary Value Analysis** - Test inputs for testcases the edges between equivalence classes.

**Software Review** - Activies to evalute software artifact through manual scrutiny. Static. Applies to all types of artifacts, spreads knowledge, allows focus on coding standards.

**Modern Code Reviews** - Gate to getting code accpected as a contribution. Assuring quality and coding standards. Governing the development path for the community.

**Continous Delivery** - CD is a software engineering approach in which teams keep producing valueable software in short cycles and ensure the software can be reliably relase at any time.
    1. More and shorter iterations
    2. More benefit of automation
    3. More regression testing
    4. Increased speed of testing needed
    5. First of losing system focus.

**Test-Driven Development (TDD)** - Define the tests first, the write the code, the refactor, iterate. May be combined with with CD, but not necessarily.

