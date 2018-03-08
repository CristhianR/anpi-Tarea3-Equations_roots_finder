#include <functional>

template<typename T>
class Capsula{

public:

    mutable int contador;
    Capsula();
    T operator()(T entrada){

        //Llamar a las std::function

    }


};

Capsula::Capsula() {

    contador = 0;

}