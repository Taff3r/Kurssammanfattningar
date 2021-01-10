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

## Software Testing Lifecycle

Components in of themselves may very well work perfectly in isolation. However they may cause unwanted interference between each other when integrated into a system. Therfore integrationtests are needed.

### What VS When
Process models define conceptual workflow, one activity builds on the other. In pratice you can work in several iterations or parallel.

### Waterfall Model
The waterfall model is one of these conceptual workflows.
System Req -> Software Reqs -> Analysis -> Program design -> Coding -> Testing -> Operations.
Following this is risky and invites failure, even according to the author themselves.
Instead he proposed several iterations to refine the first.

### Incremental (RUP)
Do the requirements, design, implementation, and testing once frist, then redo the it once before first launch.
Repeat until product is finished.
Still very document driven process.
Very large increments.
### Agile, e.g. XP
Splits the functionality into smaller pieces. Cycles of weeks or days. Very small parts of the product is implemented in small stages.
The software is not necessary delivered after each cycle, instead there are set days of delivery.
The customer might also change their mind, and such the requirements are also changed in each cycle. 

### Continious Delivery
All stages are done continously and the product is continously released to the customer.

### Levels of testing (V-Model)

Requirements are tested by Acceptance tests
The high-level design is tested by the System tests
The detailed design is tested by the integration tests.
The code is tested by Unit tests.

All levels, except Acceptance tests are also regression tested, which make sure that no functionaliy goes missing.

### Benefits of the V-Model

* Intuitive and easy to explain
    + Makes a good model for training people
    + Shows how testing is related to other phases of the waterfall process
* Quite adaptabel to various situations
    + If the team is experioenced and understands the inherent limitations of the model
* Conceptual framework for some standards for safety critical systems.

### Weaknesses of the V-model
* Hard to follow in practice
* Document driven
    + Relies on the existence, accurarcy, and timeliness of the documentation
    + Asserts testing on each level is designed based on the deliverables of a single design phase
* Communcicates change poorly
    + Does not show how changes, fixes, and test rounds are handled.
* Testing windows get squeezed
* Based on simplistic waterfall model
* Does not fit into iterative development


## Levels, Types, and Phases - NOT THE SAME THING

* Test level - a test level is a group of test activities that focus into ceratin level of the test target
    + Test levels can be seen as levels of detail and abstraction
    + "How big part of the system are we testing?"


* Test Types - evaluate a system for a number of associated *quality goals*
    + Testing seleccted quality characteristics.
    + Testing to reveal ceratin types of problems
    + Testing to verify/validate types of problems
* Common test types:
    + Functional: Installation, Smoke, Concurrency testing
    + Non-Functional: Security, Usability, Performance
* A certain test type can be applied on several test levels and in different phases.

* Test Phases - Test phases are used to describe temporal parts in testing process
    + Test phases are phases in a development or testing project.
* Do not always match to the test levels or types
    + In iterative development the phases may not match the test levels
        - Often, there is unit testing but no unit test phase
        - You can have several integration phases, or integration testing without an integration phase
    + Phases *might* match the test levels
        - As depicted in the V-model

Test phases usually ask questions about:
* When? Test scheduling/process
* How? Automated vs. Manual
* What? New vs regression test
* Whom? Test organization


### Agile/Time paced development
Time is fixed, scope changes, e.g. Scrum
* 30 days to complete iteration or Sprint
* 90 days to complete alpha release
* 90 days to complete beta release
* 180 days for whole projects


### Testing in Time Paced Development
* Part of each development task
* Testing is not a phase
* Software is developed incrementally
    + Is has to be tested incrementally
* Rapid, time paced development
    + Time boxed releases and increments
    + Deadlines are not flexible
* Scope is flexible
    + Testing provides information for scoping

### Approaches to Testing in Time Paced Development
1. Automated regression testing
    * Automated unit testing
    * Test-driven development
    * Daily builds and automated tests
2. Stabilistation phase or increment
    * Feature freeze
    * Testing and debugging at the end of the increment or release
3. Separate system testing
    * Independent testing
    * Separate testers or testing team


## Organizing testing (Waterfall vs Agile)
* Waterfall
    + Division of labor
        - Different teams perform different tasks, design, dev, test, etc.
* Agile
    + Integrated Teams
        - Testing in collaboration, customer on site, etc.
        - **Hard to scale up as the organization grows**

### Scaling Agile
Core principles are easy, practice is complex.
Gets more complex as the organization and the amount of teams grows.

* Requirments change all the time
* Specifications are never final
    + Let them change, test design is part of each task
* Code is never "finished", never ready for testing
* Not enough time to test
    + Focus on development "finished" increments, tracking at the task level.
    + Testing is part of each development task.
* Need regression test everything in each increment
* Developers always break things again
* How can we trust?
    + Trust comes frombuilding in the quality, not from the external testing "safety net"
    + Automation is critical

       

### A/B Testing Continous Experimentation

* Run multiple versions - evalutae online
* Deployment strategies

* Canary Releases
* Dark Launches
* Gradual Rollouts
* A/B Testing 
