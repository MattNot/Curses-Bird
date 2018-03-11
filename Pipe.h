#include <vector>
using namespace std;
struct pezzo{
    int x;
    int y;
};
class Pipe
{
    private:
        int x;
        int y;
        int speed;
    public:
        vector<pezzo> pezzi;
        void update();
        void show();
        bool isHit(Bird* bird);
        Pipe();
        Pipe(int);
};
Pipe::Pipe(){
    this->y=0;
    this->x=COLS;
}
Pipe::Pipe(int h)
{
    this->speed=1;
    //this->pezzi=new vector<pezzo>;
    for(int i=0; i<h; i++)
    {
        pezzi[i].x=COLS;
        pezzi[i].y=h-i;
    }
}

bool Pipe::isHit(Bird* b)
{

}