#include <iostream>
#include <utility>

#include <vector>

#include "UniquePointer.h"


int main() {


    kron::EncapsulatedPointer<int> x;
    
    if (!x)
    {
        std::cout << "here" << std::endl;
    }

    kron::EncapsulatedPointer<int> y(3);

    if (y)
    {
        std::cout << "and here got y " << *y << std::endl;
    }

    kron::EncapsulatedPointer<std::vector<int>> z(1,2);

    if (z)
    {
        std::cout << "and here got z[0] " << (*z)[0] << std::endl;

    }

    kron::UniquePointer<int>out;

    {
        kron::UniquePointer<int>w(new int(4));

        if (w)
        {
            std::cout << "and here got w" << *w << std::endl;

            auto q = std::move(w);

            std::cout << "moved w to q and got w" << *q << std::endl;

            if (!w)
            {
                std::cout << "w is empty now" << std::endl;

            }

            out = std::move(q);

        }
    }

    std::cout << "moved it out of scope " << *out << std::endl;

    //shared

    auto* x_s = new kron::SharedPointer<int>(new int(4));

    std::cout << "x_s made with " << **x_s << " with " << (*x_s).counter() << std::endl;

    auto* y_s = new kron::SharedPointer<int>(*x_s);

    std::cout << "made y_s so x_s has " << **x_s << " with " << (*x_s).counter() << std::endl;
    std::cout << "y_s has " << **y_s << " with " << (*y_s).counter() << std::endl;

    delete x_s;


    std::cout << "deleted x_s so now y_s" << **y_s << " with " << (*y_s).counter() << std::endl;

    {
        kron::SharedPointer<int>z_s(new int(37));

        std::cout << "stack z_s made with " << *z_s << " with " << (z_s).counter() << std::endl;

        z_s = *y_s;

        std::cout << "stack z_s was attributed so " << *z_s << " with " << (z_s).counter() << std::endl;
    }



    delete y_s; // check with debugger



    return 0;
}