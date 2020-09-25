.name "spike"
.comment "useless"
		sti r1, %:l1, %1
		ld %0, r2
l1: 	live %1
        sti r1, %:l2, %1
        fork %:f1
		zjmp %:f1
f1:	    ld %0, r3
l2:     live %1
        zjmp %:f1
