---- MODULE MC ----
EXTENDS AB, TLC

\* MV CONSTANT declarations@modelParameterConstants
CONSTANTS
d1, d2, d3
----

\* MV CONSTANT definitions Data
const_151415095427328000 == 
{d1, d2, d3}
----

\* CONSTRAINT definition @modelParameterContraint:0
constr_151415095427329000 ==
/\ Len(AtoB) <= 3
/\ Len(BtoA) <= 3
----
\* SPECIFICATION definition @modelBehaviorSpec:0
spec_151415095427330000 ==
FairSpec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_151415095427331000 ==
TypeOK
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_151415095427332000 ==
ABS!FairSpec
----
=============================================================================
\* Modification History
\* Created Sun Dec 24 13:29:14 PST 2017 by junlongg
