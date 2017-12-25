---- MODULE MC ----
EXTENDS remove, TLC

\* Constant expression definition @modelExpressionEval
const_expr_151414221086313000 == 
(1..3) \X {"a", "b"}
----

\* Constant expression ASSUME statement @modelExpressionEval
ASSUME PrintT(<<"$!@$!@$!@$!@$!",const_expr_151414221086313000>>)
----

=============================================================================
\* Modification History
\* Created Sun Dec 24 11:03:30 PST 2017 by junlongg
