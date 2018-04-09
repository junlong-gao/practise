Theorem forward_induction :
   (forall A B C : Prop, A -> (A -> B) -> (A -> B -> C) -> C).
   Proof.

      intros A B C.
      intros proof_A A_imp_B A_imp_B_imp_C.
      pose (proof_B := A_imp_B proof_A).
      pose (proof_C := A_imp_B_imp_C proof_A proof_B).
      exact proof_C.

   Show Proof.

   Qed.

(* True is provable
In Coq, True is a Prop having only one proof, False is a Prop having no proof
*)

Theorem True_can_be_proven : True.
   Proof.
   (*
   There is no context. And no need for context as by def, True has one proof
   for it: I
   *)
   exact I.

   Show Proof.

   Qed.

(* To show something has no proof, that is, not provable, we can show that if
   there is a proof for it, we can have a proof for False:
   (forall proof_of_A : A, False)
   Short hand: A->False
   Or not A
   Or ~ A
   In particular, not False is provable (so always true)
*)

Theorem False_cannot_be_proven: not False.
   Proof.
   unfold not.
   intros proof_of_False.
   exact proof_of_False.
   Show Proof.
   Qed.

Require Import Bool.
Theorem eqb_is_reflixive : (forall a : bool, Is_true (eqb a a)).
Proof.
   intros a.
   case a.
   (* true *)
      simpl.
      exact I.
   (* false *)
      simpl.
      exact I.
   Show Proof.
Qed.

Theorem or_is_symmtry : (forall A B : Prop, A \/ B -> B \/ A).
Proof.
  intros A B proof_A_or_B.
  case proof_A_or_B.
     (* looking at def onf A \/ B, it
        has two cases(constructors)
      *)
     (* case 1: A -> B \/ A *)
     intros proof_A.
     pose (proof_of_B_or_A := (or_intror proof_A) : B \/ A).
     exact proof_of_B_or_A.

     (* case 2: B -> B \/ A *)
     intros proof_B.
     refine (or_introl _).
        exact proof_B.
  Show Proof.
Qed.

