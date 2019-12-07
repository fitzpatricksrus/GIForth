#include "OuterInterp.h"

#include "BootstrapWords.h"
#include <runtime/ForthWord.h>
#include <runtime/PrimitiveForthWords.h>
#include <words/CoreForthWords.h>
#include <words/VocabWords.h>
#include <words/compiler/CompilerWords.h>
#include <runtime/utils/CompositeForthWordBuilder.h>
#include <runtime/NativeOSFunctions.hpp>

/*
: interp
    repeat
        nextToken
        str2Int not if
            findWord if
                execute
            else
                printString
                '?' printChar
                '\n' printChar
            endif
        endif
    forever
 */

CompositeForthWord* OuterInterp::getInstance() {
	static PrimitiveForthWords pfw(nullptr);
	static CoreForthWords cfw(&pfw);
	static VocabWords cw(&cfw);
	static BootstrapWords bw(&cw);
	static CompilerWords compw(&bw);
	static ForthVocab userVocab(&compw);
	PrimitiveForthWords::registers[PrimitiveForthWords::SOURCE_VOCAB_STATE] = static_cast<ForthCell::PTR_TYPE>(&userVocab);
	PrimitiveForthWords::registers[PrimitiveForthWords::DEST_VOCAB_STATE] = static_cast<ForthCell::PTR_TYPE>(&userVocab);

	static CompositeForthWord INSTANCE(
			CompositeForthWordBuilder("OuterInterp")
				.compileRepeat()
					.compileWord(&BootstrapWords::NEXT_TOKEN)
					.compileWord(&CoreForthWords::PARSE_NUMBER)
					.compileWord(&PrimitiveForthWords::CONDITIONAL_NOT)
					.compileIf()
						.compileWord(&BootstrapWords::FIND_WORD)
						.compileIf()
							.compileWord(&PrimitiveForthWords::EXECUTE)
						.compileElse()
							.compileWord(&BootstrapWords::PRINT_STRING)
							.compileConstant(static_cast<ForthCell::INT_TYPE>('?'))
							.compileWord(&PrimitiveForthWords::PRINT_CHAR)
							.compileConstant(static_cast<ForthCell::INT_TYPE>('\n'))
							.compileWord(&PrimitiveForthWords::PRINT_CHAR)
							.compileConstant(static_cast<ForthCell::INT_TYPE>('\r'))
							.compileWord(&PrimitiveForthWords::PRINT_CHAR)
							.compileWord(&PrimitiveForthWords::FLUSH_INPUT)
						.compileEndIf()
					.compileEndIf()
				.compileForever()
			.build()
	);
	return &INSTANCE;
}
