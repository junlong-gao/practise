------------------------------- MODULE remove -------------------------------
EXTENDS Integers, Sequences

Remove(i, seq) ==
   [j \in 1..(Len(seq) - 1) |-> IF j < i THEN seq[j]
                                ELSE seq[j + 1]]
=============================================================================
\* Modification History
\* Last modified Sun Dec 24 10:59:43 PST 2017 by junlongg
\* Created Sun Dec 24 10:57:34 PST 2017 by junlongg
