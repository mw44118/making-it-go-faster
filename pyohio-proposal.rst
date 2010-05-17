Making it go faster
===================

:Type: talk

:Presenter: W. Matthew Wilson <matt@tplus1.com>

:Python level: novice

Description
-----------

An introduction to profiling python code.

I'll use cProfile, pstats, and RunSnakeRun to find where code is getting
bogged down in a real-world example.  I'll measure the run-time cost
with timeit, refactor, and measure it again.

Finally, I'll talk about the limits of python optimization and show how
to replace python code with C.

Extended description
--------------------

I saw messages on the mailing list about not enough talks, and I've been
doing a lot of work in this area lately, so I put this proposal together.

Outline
-------

*   Trivial examples using cProfile and pstats
*   cProfile examples using code with some setup
*   Use runsnakerun to see a pretty picture of where code is spending
    time

*   Some trivial examples of timeit
*   Use timeit with code that requires some setup
*   Why minimum run time is more useful than mean run time

*   Use cProfile, pstats, and RunSnakeRun on some real code to find
    where it is getting bogged down
*   Use timeit to set the time to beat
*   Use cProfile to look at code execution just within the snippet we're
    timing, to find what to rewrite
*   Rewrite the python code
*   Record the new time with timeit
*   Use cProfile again to find the new slowest section of the code
*   Rewrite that section in C.
*   Talk about what you lose when you extend python with C
    *   People like me that are hooked on code inspection just get
        annoyed
    *   Code won't work in Jython, IronPython, etc
*   Rewrite that section with Cython instead

Bio
---

Dad, programmer, gardener, entrepeneur, internet crackpot.  Blogs at
http://blog.tplus1.com.

Recording release
-----------------

I will sign the recording release agreement (text at
http://wiki.python.org/moin/PyOhio/RecordingRelease).

.. Email to to cfp@pyohio.org by May 10, 2010
