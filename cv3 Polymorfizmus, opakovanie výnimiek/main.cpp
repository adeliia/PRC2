#include "pbmimage.h"
#include <exception>

using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "The image could not be loaded";
  }
} myex;


int main() {
//    std::cout << "Hello, World!" << std::endl;
    PbmImage image;
    try {
         image.load("MARBLES.PBM");
         throw myex;
    } catch (exception& e) {
        cout << e.what()<< endl;
    }
    image.load("MARBLES.PBM");
    // image.setBit(1, 1, 0);
    image.seedFill4(1, 22, 0);
    image.printBits();
    image.save("MARBLES2.PBM");

    return 0;
}
