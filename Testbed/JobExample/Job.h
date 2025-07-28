#pragma once
#include <iostream>
#include "Core/Concurrency/JobSystem.h"

namespace hive {

    class PrintMessageJob : public IJob
    {
        int id;
        char* name;

    public:
        PrintMessageJob(int id, char *name)
            : id(id), name(name) {}

        void operator()() const override
        {
            std::cout << "JobDemo: " << id << " - " << name << std::endl;
        }
    };

    class CountJob : public IJob
    {
        int start, end;

    public:
        CountJob(int start, int end)
            : start(start), end(end) {}

        void operator()() const override
        {
            int j = 1;
            for(int i = start; i < end; i++) {
                j*= i;
            }
            std::cout << j << "Count job done with start=" << start << std::endl;
        }
    };

} // hive
