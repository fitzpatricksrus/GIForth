//
// Created by Dad on 9/18/19.
//
/*
: interp
0       do
0         nextToken                  // -- stringAddr
1         findWord                   // stringAddr -- [ wordAddr true | stringAddr false ]
2         (jump_if_false)            // bool --
3         (7)
                                     // found the word.  Execute it
4             execute                // wordAddr --
5         (jump)
6         (19)
             // may be a number
7            parseNumber             // stringAddr -- [ value true | string addr false ]
8            (jump_if_false)
9            (12)
                                     // it's a number and it's on the stack.  We're done
10            (jump)
11            (19)
12                printString         // stringAddr
13                (push_next_cell)
14                '?'
15                printChar        // '?'
16                (push_next_cell)
17                '\n'
18                printChar        // '\n'
              endif
          endif
19      (push_next_cell)
20      (false)
21      (jump_if_false)
22      (0)

;
*/
#include <words/CoreForthWords.h>
#include <words/VocabWords.h>
#include <words/compiler/CompilerWords.h>
#include "runtime/PrimitiveForthWords.h"
#include "BootstrapInterp.h"
#include "BootstrapWords.h"
#include "runtime/ForthCell.h"
#include "runtime/utils/CompositeForthWordBuilder.h"

CompositeForthWord* BootstrapInterp::getInstance() {
	static PrimitiveForthWords pfw(nullptr);
	static CoreForthWords cfw(&pfw);
	static VocabWords cw(&cfw);
	static BootstrapWords bw(&cw);
	static CompilerWords compw(&bw);

    static CompositeForthWord INSTANCE(
		    CompositeForthWordBuilder("BootstrapInterp::INSTANCE")
		    		.compileConstant(static_cast<ForthCell::PTR_TYPE>(&compw))
		    		.compileCell(&VocabWords::CURRENT_VOCAB)
		    		.compileCell(&PrimitiveForthWords::CELL_PUT)
				    .compileRepeat()
						.compileCell(&BootstrapWords::NEXT_TOKEN)
						.compileCell(&BootstrapWords::FIND_WORD)
						.compileIf()
							.compileCell(&PrimitiveForthWords::EXECUTE)
						.compileElse()
							.compileCell(&CoreForthWords::PARSE_NUMBER)
							.compileCell(&PrimitiveForthWords::CONDITIONAL_NOT)
							.compileIf()
								.compileCell(&BootstrapWords::PRINT_STRING)
								.compileConstant(static_cast<ForthCell::INT_TYPE>('?'))
								.compileCell(&PrimitiveForthWords::PRINT_CHAR)
								.compileConstant(static_cast<ForthCell::INT_TYPE>('\n'))
								.compileCell(&PrimitiveForthWords::PRINT_CHAR)
							.compileEndIf()
						.compileEndIf()
					.compileForever()
            .build()
            );
    return &INSTANCE;
}
