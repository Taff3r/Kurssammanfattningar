# Code Reviewing in the trenches
* Developers appricate reviewer feedback and are more thorough when they know their code will be reviewed.
* The process increases confidence, both for developer and reviewer.

## Review process at Microsoft
1. *Preperation* (by the authors) of the code to be reviewed.
2. *Selection* of reviewers, with varying requirements for whom to select and how.
3. *Notification* of the selected reviewers and other stakeholders, with team policy dictation whom to inform and how.
4. *Feedback* provided by reviewers to authors and other stakeholders.
5. *Iteration* involving communication between authors and reviewers and further work by both.
6. *Check-in* of the code change to the target system (in some teams, before review)



### Motivations for code reviews
1. Improve code
2. Find defects
3. Transfer knowledge
4. Explore alternative solutions
5. Improve the development process
6. Avoid breaking builds
7. Increase team awareness
8. Share code ownership
9. Team assessment

## Main challenges
For authors: 
+ *Timely feedback*
+ *Insightful feedback*

For reviewers: 
+ *Large reviews*
+ *Bad documenation of the changes made*

## Best practices
For authors:
* Look for simple isses, such as code style
* Aim for small incremental changes that are easy to understand.
* Cluster related changes
* Document the motivation for changes
* Test the changes
* No tests? Create them
* Consider skipping review if small or trivial changes, like commenting or formatting.

For reviewers:
* Set aside dedicate, but bounded, time for reviewing.
* Review frequently, but review fewer changes at a time.
* Provide feedback ASAP.
* Focus on core issues first.
* Use a review checklist.
* Choose communication channels carefully.

For orgs:
* Establish a review policy.
* Make sure that time reviewing "counts" as important work.
* Use appropriate tools.

# An empirical study of the impact of modern code review practices on software quality

### Is there a relationship between code review coverage and post-release defects?
Review coverage is *negatively* associated with incidence of post-release defects in three of the four stuides released.
However it only provides a significant amount of explanatory power to two of the four studied releases, suggesting that review coverage alone does not guarantee a low incidence rate of post-release defects.

### Is there a relationship between code review participation and post-release defects?
It is associated. Review discussion metrics play a statically significant role in the explanatory power of all of the studies systems.

### Is there a relationship between code reviewer expertise and post-release defects?

Components with many changes that do not invlove a subject matter expert inthe authoring or reviewing process tend to be prone to post-release defects.


# What to look for in a code review

## Design

* Do the interations of various pieces of code in the CL make sense?
* Does this change belong in your codebase, or in a library?
* Does it integrate well with the rest of your system?
* Is now a good time to add this functionality?

## Functionality

* Does this change do what the devloper intended?
* Is the change good for the users of this code?
* Is the code tested?
* Can it cause dead locks or race conditions?

## Complexity
* Is the change more complex than it needs to be?
* Is it to generic, i.e. over-engineered?


## Tests
* Are there tests that test the changes?
* Are the tests included in the change?
* Are the tests sensible and useful?
* Will the tests fail when the code is broken?
* Are the tests to complex?

## Naming
* Did the developer pick good names for everything?
* Are the names to long?

## Comments
* Did the devloper write clear comments in understandable English?
* Are all of the comments necessary?
* Is there TODOs that need to be removed?

## Style
* Does it introduce major style changes?

## Consistency
* Does the code follow the style guide?

## Documentation
* If the change changes how the project is built, tested, etc.Check that it also includes documentation that how that is changed and how it now is done.
* If the change deletes or deprectas code, consider if the documentation should also be deleted.
* If documenations is missing, ask for it.

## Every line
* Read every line in human-written code.
* Make sure the code written is understandable.
* Make sure there is reviewer on the change that is qualified for the specific change.

## Context
* Look at the change in a broad context. E.g. the whole file.
* Don't accept changes that degrade the code health of the system, most systems become complex due to small changes that add up. Prevent small complexities.

## Good things
* If you see something nice, tell the developer.

