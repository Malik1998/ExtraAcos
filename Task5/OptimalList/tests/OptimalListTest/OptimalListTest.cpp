
#define DEBUG

#include <fcntl.h>
#include "OptimalListTest.h"
#include "gtest/gtest.h"
#include "iostream"
#include "../../List/Node.h"
#include "../../OptimalList/OptimalList.h"


TEST(OptimalListTest, SimpleTestOfUsing) {
    OptimalList<int> optimalList(-1, 10);


    Node<int> lement(nullptr, nullptr, 4);
    optimalList.pushFront(lement);

    lement.setData(3);
    optimalList.pushFront(lement);

    lement.setData(2);
    optimalList.pushFront(lement);

    lement.setData(1);
    optimalList.pushFront(lement);

    optimalList.popFront();
    optimalList.popFront();
    optimalList.popFront();
}


TEST(OptimalListTest, ChangeMemeoryWithLog) {
    OptimalList<int> optimalList(-1, 10);


    Node<int> lement(nullptr, nullptr, 4);
    optimalList.pushFront(lement);

    reinterpret_cast<int *>(&optimalList)[0] = 0;

    lement.setData(3);
    optimalList.pushFront(lement);

    return;

}

TEST(OptimalListTest, ChangeMemoryNoLog) {
    OptimalList<int> optimalList(-1, 10);


    Node<int> lement(nullptr, nullptr, 4);
    optimalList.pushFront(lement);

    reinterpret_cast<int *>(&optimalList)[0] = 0;

    lement.setData(3);
    optimalList.pushFront(lement);

    return;
}


TEST(OptimalListTest, FirstElement) {
    OptimalList<std::string> optimalList("FFF", 10);


    Node<std::string> lement(nullptr, nullptr, "first");
    optimalList.pushFront(lement);

    lement.setData("second");
    optimalList.pushBack(lement);

    lement.setData("third");
    optimalList.pushBack(lement);

    lement.setData("forth");
    optimalList.pushBack(lement);

    optimalList.popBack();
    optimalList.popBack();
    optimalList.popBack();

    ASSERT_EQ("first", optimalList.getFront()->getData());
}

TEST(OptimalListTest, Last) {
    OptimalList<std::string> optimalList("FFF", 10);


    Node<std::string> lement(nullptr, nullptr, "first");
    optimalList.pushFront(lement);

    lement.setData("second");
    optimalList.pushBack(lement);

    lement.setData("third");
    optimalList.pushBack(lement);

    lement.setData("forth");
    optimalList.pushBack(lement);

    optimalList.popBack();
    optimalList.popBack();
    optimalList.popBack();
    optimalList.popBack();

    ASSERT_EQ(nullptr, optimalList.getFront());
}

TEST(OptimalListTest, FirstElementAddAfter) {
    OptimalList<std::string> optimalList("FFF", 10);


    Node<std::string> lement(nullptr, nullptr, "first");
    optimalList.pushFront(lement);

    lement.setData("second");
    optimalList.pushBack(lement);

    lement.setData("third");
    optimalList.pushBack(lement);

    lement.setData("forth");
    optimalList.pushBack(lement);

    optimalList.popBack();
    optimalList.popBack();
    optimalList.popBack();

    ASSERT_EQ("first", optimalList.getBack()->getData());

    lement.setData("Last");
    optimalList.pushBack(lement);

    ASSERT_EQ("Last", optimalList.getBack()->getData());
}

TEST(OptimalListTest, AddWhereYouWant) {
    OptimalList<std::string> optimalList("FFF", 10);


    Node<std::string> lement(nullptr, nullptr, "first");
    optimalList.pushFront(lement);

    lement.setData("second");
    optimalList.pushBack(lement);

    lement.setData("third");
    optimalList.pushBack(lement);

    lement.setData("sec___third");

    optimalList.insert(optimalList.getFront()->getNext(), lement);


    ASSERT_EQ(optimalList.getBack()->getData(), "third");
    optimalList.popBack();

    ASSERT_EQ("sec___third", optimalList.getBack()->getData());
    optimalList.popBack();

    ASSERT_EQ("second", optimalList.getBack()->getData());
    optimalList.popBack();

    ASSERT_EQ("first", optimalList.getBack()->getData());
    optimalList.popBack();

}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}