+++++++++++++++++++
Making it go faster
+++++++++++++++++++

Some slow code
==============

This takes a **long** time::

    >>> from pitz.project import Project
    >>> p = Project.from_pitzdir(Project.find_pitzdir())

That code does lots and lots of stuff.  What all does it do, and what is
taking so long?

How to speed up big chunks of code
==================================

1.  Use cProfile to build a file with information about all the calls made.

2.  Look at that file and and find where the code is getting hung up.

3.  Guess how to speed it up and rewrite some code.

4.  Rebuild the statistics file with cProfile again, and look for what
    is the new slowest part.


Using cProfile
==============

We can cProfile to run the code and write a file with lots of
statistics::

    >>> statement = "Project.from_pitzdir(Project.find_pitzdir())"
    >>> import cProfile
    >>> cProfile.runctx(statement, globals(), {}, "results.cprofile")

Then we can use pstats to look at those statistics::

    >>> import pstats
    >>> stats = pstats.Stats("results.cprofile")
    >>> stats.print_stats()

That was too much!  Print only the first 10 lines like this::

    >>> stats.print_stats(10)

Or print just the first 5% of rows like this::

    >>> stats.print_stats(0.05)

That's great, but what does this stuff really mean::

    >>> stats.print_stats(0.05)
    Sun Aug  1 13:41:45 2010    out.cprofile

             4643321 function calls (4615459 primitive calls) in 24.228 CPU seconds

       Random listing order was used
       List reduced from 264 to 13 due to restriction <0.050000000000000003>

       ncalls  tottime  percall  cumtime  percall filename:lineno(function)
         2482    0.034    0.000    0.144    0.000 build/bdist.linux-i686/egg/yaml/constructor.py:543(make_python_instance)
          668    0.009    0.000    0.015    0.000 pitz/entity/__init__.py:674(matches_dict)
          378    0.007    0.000    0.020    0.000 build/bdist.linux-i686/egg/yaml/scanner.py:430(fetch_flow_collection_start)
          670    0.015    0.000    0.015    0.000 {open}
         3214    0.047    0.000    0.144    0.000 pitz/bag.py:220(by_uuid)

From the standard documentation:

=========== ===========================================================
Column      Description
=========== ===========================================================

ncalls      for the number of calls

tottime     for the total time spent in the given function (and
            excluding time made in calls to sub-functions),

percall     is the quotient of tottime divided by ncalls

cumtime     is the total time spent in this and all subfunctions (from
            invocation till exit). This figure is accurate even for
            recursive functions.

percall     is the quotient of cumtime divided by primitive calls

=========== ===========================================================

I'll use a silly example to show what all these mean::

    >>> import time
    >>> def a_really_slow_function():
    ...     time.sleep(0.1)
    ...
    >>> def f():
    ...     for i in xrange(1, 1000):
    ...         a_really_slow_function()
    >>> cProfile.runctx("f()", globals(), locals(), "trivial.profile")
    >>> p2 = pstats.Stats("trivial.profile")

Sorting by cumulative will put f at the top::

    >>> p2.sort_stats('cumulative')
    <pstats.Stats instance at 0x9f5faac>
    >>> p2.print_stats(10)
    Sun Aug  1 15:05:28 2010    trivial.profile

             21 function calls in 0.902 CPU seconds

       Ordered by: cumulative time

       ncalls  tottime  percall  cumtime  percall filename:lineno(function)
            1    0.000    0.000    0.902    0.902 <string>:1(<module>)
            1    0.000    0.000    0.902    0.902 <ipython console>:1(f)
            9    0.000    0.000    0.902    0.100 <ipython console>:1(a_really_slow_function)
            9    0.902    0.100    0.902    0.100 {time.sleep}
            1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}

But sorting by time will put a_really_slow_function at the top::

    >>> p2.sort_stats('time')
    <pstats.Stats instance at 0x9f5faac>
    >>> p2.print_stats(10)
    Sun Aug  1 15:05:28 2010    trivial.profile

             21 function calls in 0.902 CPU seconds

       Ordered by: internal time

       ncalls  tottime  percall  cumtime  percall filename:lineno(function)
            9    0.902    0.100    0.902    0.100 {time.sleep}
            9    0.000    0.000    0.902    0.100 <ipython console>:1(a_really_slow_function)
            1    0.000    0.000    0.902    0.902 <ipython console>:1(f)
            1    0.000    0.000    0.902    0.902 <string>:1(<module>)
            1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}


Now look at runsnake
====================
