#include <gtest/gtest.h>
#include <sealib/iterator.h>

#include <algorithm>
#include <array>
#include <random>

using Sealib::Iterator;

TEST(IteratorTest, iterator_integrity) {
    const unsigned long int size = 25000;
    const unsigned long int setSize = 5000;

    Sealib::ChoiceDictionary *c = new Sealib::ChoiceDictionary(size);
    Iterator *iterator = new Iterator(c);

    std::array<unsigned long int, setSize> set;

    unsigned int count = 0;
    unsigned long int num = 0;
    unsigned seed = 0;

    for (unsigned long int i = 0; i < setSize; i++) {
        set[i] = num;
        num += 5;
    }

    std::shuffle(set.begin(), set.end(), std::default_random_engine(seed));

    for (unsigned long int number : set) {
        c->insert(number);
    }

    iterator->init();
    while (iterator->more()) {
        unsigned long int index = iterator->next();
        for (unsigned long int number : set) {
            if (index == number) {
                count++;
                break;
            }
        }
    }
    // ASSERT_EQ(count, setSize);
    delete iterator;
    delete c;
}