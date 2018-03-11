#include <vector>
using namespace std;
struct pezzo{
    int x;
    int y;
};
class Pipe
{
    private:
        int top;
        int bot;
        int speed;
    public:
        vector<pezzo> pezzi;
        void update();
        void show();
        bool isHit(Bird bird);
        Pipe();
};

/*bool Pipe::isHit(Bird)
{
    if(this)
}*/