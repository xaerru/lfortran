#ifndef LIBASR_PASS_REPLACE_ARRAY_PASSED_IN_FUNCTION_CALL_H
#define LIBASR_PASS_REPLACE_ARRAY_PASSED_IN_FUNCTION_CALL_H

#include <libasr/asr.h>
#include <libasr/utils.h>

namespace LCompilers {

    void pass_replace_array_passed_in_function_call(Allocator &al, ASR::TranslationUnit_t &unit,
                                const PassOptions &pass_options);

} // namespace LCompilers

#endif // LIBASR_PASS_REPLACE_ARRAY_PASSED_IN_FUNCTION_CALL_H
