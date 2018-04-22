#include <vector>
#include "bird.h"
using namespace std;
class Pipe
{
    public:
        int speed;
        int x;
        vector<int> y;
        int finishU;
        int startB;
        int spacing;
        void update();
        void show();
        bool isHit(Bird* bird);
        Pipe();
        Pipe(int);
};