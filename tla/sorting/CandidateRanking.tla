-------------------------- MODULE CandidateRanking --------------------------
EXTENDS Integers, Sequences, FiniteSets


(* this is the definition of sorted set and can be used to choose from *)
Sortings(S) ==
    LET D == 1..Cardinality(S)
    IN { seq\in [D -> S]:
            /\ S \subseteq { seq[i]:i\in D}
            /\ \A i,j \in D : (i < j) => (seq[i].key =< seq[j].key)} 

(* Generic sorting *)
KeyLeq(s, t) ==
    s.key =< t.key
    
GeneralSortings(S, LEQ(_,_)) ==
    LET D == 1..Cardinality(S)
    IN { seq\in [D -> S]:
            /\ S \subseteq { seq[i]:i\in D}
            /\ \A i,j \in D : (i < j) => (LEQ(seq[i], seq[j]))} 
                  
(* SortSet def, this is a recursive def *)           
RECURSIVE SortSet(_)            
SortSet(S) ==
        IF S = {} THEN << >>
                   ELSE LET ss == CHOOSE ss \in S: \A t \in S: ss.key =< t.key
                        IN <<ss>> \o SortSet(S \ {ss})
                        
(* 
   Generic SortSet def, this is a recursive def 
   Note that even the construct dose not allow for recursive high order operators
   we can still use LET to capture the context 
*)           
GeneralSortSet(S, LEQ(_, _)) ==
    LET RECURSIVE SetToSeq(_)            
                  SetToSeq(SS) == 
                    IF SS = {} THEN << >>
                               ELSE LET ss == CHOOSE s \in SS: \A t \in SS: LEQ(s, t)
                                    IN <<ss>> \o SetToSeq(SS\{ss})
    IN SetToSeq(S)
=============================================================================
\* Modification History
\* Last modified Sun Aug 20 17:32:25 PDT 2017 by junlongg
\* Created Sun Aug 20 15:29:31 PDT 2017 by junlongg
