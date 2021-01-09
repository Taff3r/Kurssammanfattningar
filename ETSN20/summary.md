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


## Debugging

Distinct from testing.
Needs appropriate tool support
Must be done systemically.

According to surveys, people know, but don't use the the debugging features.

### Debugging process
* Reproduce, some bugs might appear in different environments. It might appear at the testers, but not the developers. Therefore be very specific in the defect reports.
* Reduce scope (find smallest test case that triggers the failure)
* Define fault hypothesis. Is it programming errors, faulty data, etc.
* Validate hypothesis.

### Monitoring

* Basic: `printf`
    + Quick start
    + Requires editing
    + Impacts performance
* Advanced: Debugging tools
    + No editing
    + Breakpoints, set, get
    + May impact performance

### Debugging Operations
* Breakpoints
* Single-stepping
* Resumer operation
* Temporary breakpoints
* Inspecting Variables
* Watchpoints 


### Debugging complex systems
* Reduce the configuration as much as possible, while still yielding the failure.
* Track back to earlier versions while still yielding the failure.
* Search web Q&A sites on others experience.

### Using binary search principles
* Assemble a list of potential problems and how to debug them
* Seperate changes of the environment and source code changes
    + Track down changes of the environment
    + Isolate source code changes via back-out builds.
* Zoom-in and conquer
    + Memory debugger
    + Conventional source code debugging
    + Side-by-side debugging.

### Change
* **ONLY CHANGE ONE THING AT A TIME**
* Keep and audit trail
* Regression test!


### Make the software easure to debug
* Predictability  - sychronous exection, single thread, fixed seed random generatios, minimize caches.
* Observability - logging, telemetry, high-level languages.
* Sources of information - revision control logs.


### Automated debugging?
* Delta dubugging - Takes small steps and analyzes them.
* Program slicing - Split the code into slices and analyze them.
* Spectra based - Explores a spectrum of execution.

Generally we can't automate debugging as of now.


## Code Reviews
* Review - activities to evalutate software artifact through manual scrutiny
    + Inspection - formally defined review
    + Walkthrough - author guided review
* Sometimes called static testing in contrast to dynamic (execution based) testing. (A bit misleading)


### Why review?

* Main objective
    - Detect faults
* Other objectives
    - Inform
    - Educate
    - Learn from (others) mistakes -> Improve!
* (Undetected) faults may affect software quality negatively - even duing the development process.


### Reviews complement testing
**REVIEWS ARE MANDATORY FOR E.G. SAFETY CRITICAL SOFTWARE**
You can review other things than code, such specifications, design, test plans, etc.

### Review in OS Communities

* Gate to getting code accepted
* Performed by experts
* Issues of triaging and priority (what to fix by whom?)
* Sometimes called "Modern code reviews"


### "Modern" Code Reviews
* Charatierized by fewer formal requirements
* Tool support for task distribution and conduct
* Strive to make reviews more efficient and less time-consuming.


### Code Review Process
* Criteria 
    + Readiness (Is it ready for review?)
    + Preparation (Invite reviewers)
    + Examination (Is there anything wrong? -> Change requests)
    + Rework
    + Validation (LGTM?)
    + Exit -> Report

### Usage-based reading
Does the code make the usecases possible?


### Getting the best from reviews
* The author
    + Is in the "hot seat"
    + How do you react?
* The dev tem
    + Better prepared
    + Feedback, both negative and postive.
    + Communication
* The Review team
    + Critical Thinking
    + Ability to detect omissions
    + Who should participate in the review?
* Cost-effective verification
    + Minimising cost of correction
    + Is it cost effective?
