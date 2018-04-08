(* BEGINNING OF EXAMPLE *)

(*
"forall A : Prop,...". In English,
this would be "For all A such that A is a Prop, ...".

"B -> C" really means "(forall something_of_type_B : B, C)".
which reads:
for all things that you can conclude B is true, you may
conclude C is true.

So (forall A : Prop, A -> A) means:
for all proposition A,
  for all things that you can conclude A is true, you may
  conclude A is true.
or:
for all proposition A,
   A is true implies A.
*)

Theorem my_first_proof : (forall A : Prop, A -> A).
Proof.
(*
One way to prove a statement like
"For all x such that x is an integer, ..."
is to assume we have an arbitrary integer x
and show that the rest of the statement holds
for x. The first tactic "intros" does exactly that.

Thus, every time I see "intros A.",
I think "assume A".
*)

(*
now:

1 subgoal
______________________________________(1/1)
forall A : Prop, A -> A

The tactic "intros" takes "forall" off
the front of the subgoal, changes its variable
into a hypothesis in the context,
and names the hypothesis.

Therefore, after this intros A:

1 subgoal
A : Prop
______________________________________(1/1)
A -> A

Recall, the context holds all things we've proven or,
as in this case, assumed to be proven.

RULE: If the subgoal starts with "(forall <name> : <type>, ..."
Then use tactic "intros <name>."
*)
   intros A.
(*
Now:

1 subgoal
A : Prop
______________________________________(1/1)
A -> A

The next tactic is "intros",
which we said works when "forall" is at the front of the subgoal.
It works here because "->" is actually shorthand for "forall".

"B -> C" really means "(forall something_of_type_B : B, C)".
So, "A->A" is "(forall something_of_type_A : A, A)".

The result is that "intros proof_of_A."
removes that hidden "forall" and moves the unnamed variable of type A
to the hypothesis named "proof_of_A":

1 subgoal
A : Prop
proof_of_A : A
______________________________________(1/1)
A

RULE: If the subgoal starts with "<type> -> ..." Then use tactic "intros <name>."
*)
   intros proof_of_A.
(*
After the second "intros" tactic,
our subgoal is "A", which means "we need something of type A" or,
because A is a proposition, "we need a proof of A".

1 subgoal
A : Prop
proof_of_A : A
______________________________________(1/1)
A

Now, the previous command moved a proof of A into the context and called it "proof_of_A".
So, hypothesis
   proof_of_A
in our context (which are all things we know to exist)
has a type that matches our subgoal (which is we want to create),
so we have an exact match.

RULE: If the subgoal matches an hypothesis, Then use tactic "exact <hyp_name>."
*)
   exact proof_of_A.
(*
The tactic "exact proof_of_A" solves the subgoal (and the proof).
*)
Qed.
(* END OF EXAMPLE *)

(* BEGINNING OF EXAMPLE *)
(*
Modus ponens
*)

Theorem forward_small : (forall A B : Prop, A -> (A->B) -> B).
Proof.
 intros A.
 intros B.
(* Now:
1 subgoal
A, B : Prop
______________________________________(1/1)
A -> (A -> B) -> B

Reads:
assume we have prop A, B,
we need to show:
forall proof_of_A  : A
andall A_implies_B : (forall some_proof_of_A: A, B),
B is true

*)
 intros proof_of_A.
(*
Now:
1 subgoal
A, B : Prop
proof_of_A : A
______________________________________(1/1)
(A -> B) -> B

reads:
assume we have prop A, B and a proof of A
we need to show:
forall A_implies_B : (forall some_proof_of_A: A, B),
B
*)
 intros A_implies_B.
(* Now:
1 subgoal
A, B : Prop
proof_of_A : A
A_implies_B : A -> B
______________________________________(1/1)
B
reads:
assume we have prop A, B and a proof of A and A_implies_B
we need to show:
B is true

So we use modus ponens to reduce the expression:
A_implies_B proof_of_A
into
proof_of_B

The command "pose" assigns the result of
"A_implies_B proof_of_A" to the new hypothesis
"proof_of_B".

And as a result of applying modus ponens, coq correctly deduced the
type of the result

proof_of_B := A_implies_B proof_of_A : B

which is of type B, reads:
we have a proof of B
or equavalently:
B is true.

RULE (modus ponens): If you have an hypothesis
"<hyp_name>: <type1> -> <type2> -> ... -> <result_type>"
OR an hypothesis
"<hyp_name>: (forall <obj1>:<type1>, (forall <obj2>:<type2>, ... <result_type> ...))"
OR any combination of "->" and "forall",
AND you have hypotheses of type "type1", "type2"...,
Then use tactic "pose" to create something of type "result_type".
*)
 pose (proof_of_B := A_implies_B proof_of_A).
(*
...which is exactly what we are to prove.
*)
 exact proof_of_B.
Qed.



