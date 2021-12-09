#pragma region Macros
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
typedef pair<ll,ll> pll;
typedef pair<pair<int, int>, int> ppi;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef bitset<60> Bitset;
const ll INFL = 1LL << 60;
const int INF = 1000000005;
const int MOD = 998244353;//1000000007;
ll GCD(ll a, ll b) { return b ? GCD(b, a % b) : a; }
ll LCM(ll a, ll b) { return (a * b) / GCD(a, b); }
bool range(int x,int y,int X,int Y){if(0<=x&&x<X&&0<=y&&y<Y){return true;} return false;}
#define CHOOSE(a) CHOOSE2 a
#define CHOOSE2(a0,a1,a2,a3,a4,x,...) x
#define debug_1(x1) cerr<<#x1<<": "<<x1<<endl
#define debug_2(x1,x2) cerr<<#x1<<": "<<x1<<", "#x2<<": "<<x2<<endl
#define debug_3(x1,x2,x3) cerr<<#x1<<": "<<x1<<", "#x2<<": "<<x2<<", "#x3<<": "<<x3<<endl
#define debug_4(x1,x2,x3,x4) cerr<<#x1<<": "<<x1<<", "#x2<<": "<<x2<<", "#x3<<": "<<x3<<", "#x4<<": "<<x4<<endl
#define debug_5(x1,x2,x3,x4,x5) cerr<<#x1<<": "<<x1<<", "#x2<<": "<<x2<<", "#x3<<": "<<x3<<", "#x4<<": "<<x4<<", "#x5<<": "<<x5<<endl
#ifdef _DEBUG
#define debug(...) CHOOSE((__VA_ARGS__,debug_5,debug_4,debug_3,debug_2,debug_1,~))(__VA_ARGS__)
#define debug_ar(v) do{cerr<<#v": ";for(auto x : v) cerr<<x<<' '; cerr<<endl;}while(0)
#else
#define debug(...)
#define debug_ar(v)
#endif
#pragma endregion
//------------------------------------------------------------------------------------------------------------------------------

const int SHAPE[][2][2]{
    { {1,0},{0,0} },
    { {1,0},{0,0} },
    { {1,0},{0,0} },
    { {1,0},{0,0} },

    { {1,0},{1,0} },

    { {1,1},{0,0} },
    { {1,1},{0,0} },
    { {1,1},{0,0} },
    { {1,1},{0,0} },

    { {1,1},{1,1} }
};
const int w[10] = {1,1,1,1,2,3,3,3,3,4};

unordered_map<ll,int> seen;

struct Crd{ int x,y; };
struct Procedure{ int mino,dir; };

vector<Procedure> ans;
vector<Procedure> proc;
vector<Crd> field = {
    Crd{0,4},
    Crd{1,3},
    Crd{2,3},
    Crd{3,4},
    Crd{1,2},
    Crd{0,0},
    Crd{0,2},
    Crd{3,0},
    Crd{3,2},
    Crd{1,0}
};
int dx[8] = {1,2,0,0,-1,-2,0,0};
int dy[8] = {0,0,1,2,0,0,-1,-2};

ll retFieldKey(const vector<Crd> &fld){
    ll key = 0;
    for(int mino = 0; mino < 10; mino++) {
        ll t = 1LL;
        for(int i = 0; i < 4*fld[mino].x+fld[mino].y; i++) t *= 5;
        key += t * w[mino];
    }
    return key;
}

bool canMove(int mino,int dir,const vector<Crd> &fld){
    int f[4][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    for(int mi = 0; mi < 10; mi++) {
        int x = fld[mi].x;
        int y = fld[mi].y;
        if(mi==mino){
            x += dx[dir];
            y += dy[dir];
        }
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                if(SHAPE[mi][i][j]==0) continue;
                if(x+i<0||x+i>=4||y+j<0||y+j>=5||f[x+i][y+j]+SHAPE[mi][i][j]>=2){
                    return false;
                }
                f[x+i][y+j] += SHAPE[mi][i][j];
            }
        }
    }

    return true;
}

void printField(const vector<Crd> &fld){
    int f[4][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    for(int mi = 0; mi < 10; mi++) {
        int x = fld[mi].x;
        int y = fld[mi].y;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                f[x+i][y+j] += SHAPE[mi][i][j];
            }
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            cout<<f[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
    int k;cin>>k;
}

void dfs(int depth){
    ll key = retFieldKey(field);
    //debug(key);
    if(depth==300 || seen[key]==1){
        //printField(field);
        return;
    }
    //cout<<"miria"<<endl;
    seen[key] = 1;
    

    if(field[9].x==1&&field[9].y==3){
        cout<<"Yeaaaaaaaaaaaaaaaah"<<endl;
        if(ans.size()==0||ans.size()>proc.size()) ans = proc;
        return;
    }

    for(int mino = 0; mino < 10; mino++) {
        for(int dir = 0; dir < 8; dir++) {
            if(canMove(mino,dir,field)){
                //cout<<"pre move"<<endl;
                //printField(field);
                proc.push_back(Procedure{mino,dir});
                int nowx = field[mino].x,nowy = field[mino].y;
                field[mino].x = nowx + dx[dir];
                field[mino].y = nowy + dy[dir];
                //cout<<"moved"<<endl;
                //printField(field);
                dfs(depth+1);
                proc.pop_back();
                field[mino].x = nowx;
                field[mino].y = nowy;
            }
            //if(ans.size()>0) return;
        }
    }    
}
string mino_jpn[10] = {"小","小","小","小","縦棒","横棒","横棒","横棒","横棒","大"};
string dir_jpn[8] = {"下","下","右","右","上","上","左","左"};
int dist[8] = {1,2,1,2,1,2,1,2};
int main(void) {
    dfs(0);
    cout<<ans.size()<<endl;
    for(auto p : ans){
        //cout<<p.mino<<' '<<p.dir<<endl;
        cout<<mino_jpn[p.mino]<<p.mino<<' '<<dir_jpn[p.dir]<<' '<<dist[p.dir]<<endl;
    }

}