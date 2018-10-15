cmake_minimum_required(VERSION 3.12)
project(Processor)

set(CMAKE_CXX_STANDARD 14)

include_directories(FullFileReader/ReadFullFile)

#add_executable(FullFileReader ../../../Task2/StringSortingCStyle/FullFileReader/FullFileReader.cpp ../../../Task2/StringSortingCStyle/FullFileReader/FullFileReader.h)

add_executable(Processor main.cpp Processor/Processor.cpp Processor/Processor.h
        Processor/SafeStack/SafeStack.h
        Processor/Converter/WordToCodeConverter/WordToCodeConverter.cpp Processor/Converter/WordToCodeConverter/WordToCodeConverter.h
        Processor/CommandService/CommandService.cpp Processor/CommandService/CommandService.h
        Processor/Converter/CodeToWordConverter/CodeToWordConverter.cpp Processor/Converter/CodeToWordConverter/CodeToWordConverter.h
        Processor/FullFileReader/ReadFullFile/FullFileReader.cpp Processor/FullFileReader/ReadFullFile/FullFileReader.h
        Processor/Converter/CodeToByteConverter/CodeToByteConverter.cpp Processor/Converter/CodeToByteConverter/CodeToByteConverter.h Processor/Converter/ByteToCodeConverter/ByteToCodeConverter.cpp Processor/Converter/ByteToCodeConverter/ByteToCodeConverter.h)


include_directories(

        External Libs/googletest-master/googletest/googlemock/gtest
)


add_executable(ProcessorTest tests/ProcessorTest/ProcessorTest.cpp tests/ProcessorTest/ProcessorTest.h
        Processor/Processor.cpp Processor/Processor.h
        Processor/Converter/WordToCodeConverter/WordToCodeConverter.cpp Processor/Converter/WordToCodeConverter/WordToCodeConverter.h
        Processor/CommandService/CommandService.cpp Processor/CommandService/CommandService.h
        Processor/Converter/CodeToWordConverter/CodeToWordConverter.cpp Processor/Converter/CodeToWordConverter/CodeToWordConverter.h
        Processor/FullFileReader/ReadFullFile/FullFileReader.cpp Processor/FullFileReader/ReadFullFile/FullFileReader.h
        Processor/Converter/CodeToByteConverter/CodeToByteConverter.cpp Processor/Converter/CodeToByteConverter/CodeToByteConverter.h
        Processor/Converter/ByteToCodeConverter/ByteToCodeConverter.cpp Processor/Converter/ByteToCodeConverter/ByteToCodeConverter.h)

#
target_link_libraries(
        ProcessorTest gtest gtest_main pthread)

enable_testing()