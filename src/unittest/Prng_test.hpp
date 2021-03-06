// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _PRNG_TEST_HPP_
#define _PRNG_TEST_HPP_

#include <petanqulator/Prng.hpp>
#include <cxxtest/TestSuite.h>

class Prng_test : public CxxTest::TestSuite 
{
    public:

        void test_prng_1() 
        {
            const int nbSamples = 1e6;
            const int N = 100;
            Prng prng;
            unsigned sum = 0;
            for (int i=0; i<nbSamples; i++) 
            {
                int s = prng.generate() * N;
                sum += s;
                TS_ASSERT(s >= 0);
                TS_ASSERT(s < N);
            }
            double mean = sum / (double)nbSamples;
            TS_ASSERT_DELTA(mean, N*0.5, 5);
        }

        void test_prng_2() 
        {
            const int nbSamples = 1e6;
            double sum = 0.0;
            Prng prng;
            for (int i=0; i<nbSamples; i++) 
            {
                double s = prng.generate();
                sum += s;
                TS_ASSERT(s >= 0);
                TS_ASSERT(s < 1);
            }
            double mean = sum / (double)nbSamples;
            TS_ASSERT_DELTA(mean, 0.5, 0.1);
        }

        void test_prng_3() 
        {
            const int nbSamples = 1e6;
            double sum = 0.0;
            Prng prng;
            for (int i=0; i<nbSamples; i++) 
            {
                double s = prng.generate(40.0, 44.0);
                sum += s;
                TS_ASSERT(s >= 40.0);
                TS_ASSERT(s < 44.0);
            }
            double mean = sum / (double)nbSamples;
            TS_ASSERT_DELTA(mean, 42.0, 0.1);
        }

};

#endif

