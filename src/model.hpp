
#include "reference.hpp"

class User : memorydb::Item {
public:
    int         karma;
    memorydb::Reference parent;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, karma,     "karma");
        dbo::field(a, parent, "parent");
    }
};

