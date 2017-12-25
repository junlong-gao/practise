---- MODULE MC ----
EXTENDS CandidateRanking, TLC

\* New definitions @modelParameterNewDefinitions
TestSet(n) == [key: 1..n, val: {"x", "y"}]
Sigma(n) == SUBSET TestSet(n)
----
\* Constant expression definition @modelExpressionEval
const_expr_150327555895118000 == 
\A S \in Sigma(7): GeneralSortSet(S, KeyLeq) \in GeneralSortings(S, KeyLeq)
----

\* Constant expression ASSUME statement @modelExpressionEval
ASSUME PrintT(<<"$!@$!@$!@$!@$!",const_expr_150327555895118000>>)
----

=============================================================================
\* Modification History
\* Created Sun Aug 20 17:32:38 PDT 2017 by junlongg
