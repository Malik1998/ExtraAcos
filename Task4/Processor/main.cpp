#include <iostream>
#include "Processor/Converter/WordToCodeConverter/WordToCodeConverter.h"
#include "Processor/Converter/CodeToWordConverter/CodeToWordConverter.h"
#include "Processor/Processor.h"


int main() {
  //  WordToCodeConverter::convert((char *)"push 5\n end");

  //  CodeToWordConverter::convert((char *)"0 5\n 8");

    Processor processor = Processor("CommandCodeJump", Processor::WORD_COMMANDS);
    processor.execute();

}