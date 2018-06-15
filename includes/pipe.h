#include <vector>
#include "bird.h"
using namespace std;
class Pipe
{
    public:
        short int speed;
        short int x;
        vector<short int> y;
        short int finishU;
        short int startB;
        short int spacing;
        void update();
        void show();
        bool isHit(Bird* bird);
        Pipe();
        Pipe(int);
};