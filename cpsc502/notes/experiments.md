Experimental Structure
========================

This is experimental research, so we need a way to reliably run and record the
results of experiments. This document describes the general principles of how
experiments are done in this repository.

What is an experiment?
------------------------

An experiment is a deterministic set of actions to take, given some input, that
produces some output (the output may be non-deterministic). Call the
deterministic actions the recipe for the experiment.

An experiment can change, but its recipe should be relatively static. Most
changes should be due to the same recipe being run on different inputs. Indeed,
the difference between the recipe and the input may be blurry.

Organizing Experiments
-----------------------

All experiments (unique recipies) are given their own folder in the
./experiements folder. The folder name should be descriptive of the experiment.
The directory name will be the experiment name. The experiment name should not
change once it is created.

Organization Within Experiments
--------------------------------

Inside each experiment's folder will be the following:

- `runs/`: Contains a history of experimental runs.
- `input/`: Contains the input for the next run of the experiment.
- `recipe.sh`: A script that runs the experiment.
- `testrun/`: An empty folder (containing just a .gitignore to ignore everything
  in it).

The `recipe.sh` file will:

1. Create a new directory in runs for this experiment. Directories in `runs/`
   will be named a 5-digit number corresponding to the run number. For example,
   `runs/XXXXX`.

2. Copy the `input/` directory to `runs/XXXXX/input/`.

3. Save system state information to `runs/XXXXX/state/`.

4. Save a copy o `recipe.sh` to `runs/XXXXX/recipe.sh`.

5. Run the experiment.

6. Save the experiment output to `runs/XXXXX/output/`.

7. Create an empty NOTES file in ~/runs/XXXXX/NOTES`.

7. `git add runs/XXXXX` (but not commit)

If `recipe.sh` is *not* passed the --save-this-run flag, then it will do the
same, except saving to `testrun/` instead of creating a new subdirectory of
runs.

The experimenter should *NEVER* copy a test run into the runs directory. That
would be cherry-picking the experiment. Re-run it (and if it's not an anomaly it
will work), or save it elsewhere (so that it's not marked as an experiment).

The experimenter should describe in the NOTES file why they ran the experiment
and any additional comments.

Analysis
---------

The biggest problem with the above is it requires enough space to store all of
the experiment runs. Git will de-duplicate on the file-level, so if the input is
large but unchanging it won't use too much space on remote clones. However, all
of the runs have to exist in the filesystem when checking out, so the local
machine still needs enough disk space to store all the copies of the experiment.
So if the input is 50MB (unchanging), after 1000 experiments, the repository
will be 50GB checked out. Cheecking out and changing branches will be incredibly
slow.

This desgin is good because whether or not an experiment is being saved is
decided before the experiment is run. This makes it hard to cherry-pick
experiements accidentally (intentionally is still possible, since you can fake
the entire repository, there's no good solution to that).

It's also good because all of the experiments are immediately available to be
examined just from one checkout, without needing any git-specific knowledge.

TODO: The general problem of storing the experiments is too expensive, so let's
not try to solve that here, but instead find the way that best works for
*attack* experiments, which ususally means:

1. Develop the attack, running the experiment lots of worthless times.
2. Once the attack works, run the experiment "for real" to demonstrate, save
   a log, that it is working.

This is fine since an attack is a constructive proof, and as you keep the failed
demonstrations, there's no way to be dishonest by omitting the run-up
this-is-just-an-attack-development-test-experiment experiments (since all you
need to show is tha the exploit works reliably).

So: Deleting an experiment that was supposed to be "for real" is dishonest. Not
including an experiment that wasn't supposed to be "for real" is *not*
dishonest. Changing a test experiment into a "for real" experiment, without
indicating that it was originally a test, is cherrypicking and *is* dishonest.
It's ok to save the results of test experiments for
creativity/debugging/collaborating purposes, as long as that experiment is never
relied upon when drawing conclusions (risky territory here, so avoid it as much
as possible).
