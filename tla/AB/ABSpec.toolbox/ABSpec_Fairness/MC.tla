---- MODULE MC ----
EXTENDS ABSpec, TLC

\* CONSTANT definitions @modelParameterConstants:0Data
const_15141463586806000 == 
{"foo", "bar"}
----

\* SPECIFICATION definition @modelBehaviorSpec:0
spec_15141463586807000 ==
FairSpec
----
\* INVARIANT definition @modelCorrectnessInvariants:0
inv_15141463586808000 ==
Inv
----
\* PROPERTY definition @modelCorrectnessProperties:0
prop_15141463586809000 ==
\A v \in Data \X {0,1} : (AVar = v) ~> (BVar = v)
----
=============================================================================
\* Modification History
\* Created Sun Dec 24 12:12:38 PST 2017 by junlongg
