---- MODULE MC ----
EXTENDS AB, TLC

\* MV CONSTANT declarations@modelParameterConstants
CONSTANTS
d1, d2, d3
----

\* MV CONSTANT definitions Data
const_151415012227319000 == 
{d1, d2, d3}
----

\* CONSTRAINT definition @modelParameterContraint:0
constr_151415012227320000 ==
/\ Len(AtoB) <= 3
/\ Len(BtoA) <= 3
----
\* SPECIFICATION definition @modelBehaviorSpec:0
spec_151415012227421000 ==
Spec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_151415012227422000 ==
TypeOK
----
=============================================================================
\* Modification History
\* Created Sun Dec 24 13:15:22 PST 2017 by junlongg
