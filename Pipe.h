#include "bird.h"
#include <vector>
using namespace std;
/*typedef struct pezzo{
    int x;
    int y;
};*/
class Pipe
{
    private:
        int top;
        int bot;
        int speed;
    public:
        vector<int> pezzi;
        void update();
        void show();
        bool isHit(Bird);
        Pipe();
};

/*bool Pipe::isHit(Bird)
{
    if(this)
}*/