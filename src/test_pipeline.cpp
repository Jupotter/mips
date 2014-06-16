#include <iostream>
#include "tbb/pipeline.h"

class MyTest1 : public tbb::filter
{
    public:
        MyTest1()
            : tbb::filter(tbb::filter::serial_in_order)
        {
        };

        void* operator()(void* input)
        {
            static int count = 0;
            count++;
            std::cout << "Test1 " << count << std::endl;
            if (count >= 100)
                return NULL;
            return &count;
        };
};

class MyTest2 : public tbb::filter
{
    public:
        MyTest2()
            : tbb::filter(tbb::filter::serial_in_order)
        {
        }

        void* operator()(void* input)
        {
            std::cout << "Test2 " << *(int*)input << std::endl;
            return input;
        }
};

class MyTest3 : public tbb::filter
{
    public:
        MyTest3()
            : tbb::filter(tbb::filter::serial_in_order)
        {
        }

        void* operator()(void* input)
        {
            std::cout << "Test3 " << *(int*)input << std::endl;
            return input;
        }
};

int main()
{
    tbb::pipeline* pipeline = new tbb::pipeline();
    pipeline->add_filter(*(new MyTest1()));
    pipeline->add_filter(*(new MyTest2()));
    pipeline->add_filter(*(new MyTest3()));
    pipeline->run(5);
    return 0;
}

