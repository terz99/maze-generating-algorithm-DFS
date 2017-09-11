#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 1000005;
const int MAX_LEN_WID = 1005;
int _len, _wid, _new_len, _new_wid, _num_nodes, _start_node, _end_node;
vector<int> _adj[MAX_NODES];
vector<int> _maze[MAX_NODES];
char _mat[MAX_LEN_WID][MAX_LEN_WID];
bool _vis[MAX_NODES];
stack<int> _stack;
int _dx[] = {0, 0, 1, -1};
int _dy[] = {1, -1, 0, 0};
int _ddx[] = {0, 0, 2, -2};
int _ddy[] = {2, -2, 0, 0};

int get_random_int(int x){
    return (int)(rand()%x);
}

void find_path(int curr_node){

    _vis[curr_node] = true;

    int cnt = 0;
    while(cnt < 4){

        cnt++;
        int next_idx = get_random_int(_adj[curr_node].size());
        int next_node = _adj[curr_node][next_idx];
        if(!_vis[next_node]){
            _stack.push(curr_node);
            _maze[curr_node].push_back(next_node);
            _maze[next_node].push_back(curr_node);
            find_path(next_node);
            break;
        }
    }

    if(cnt == 4 && !_stack.empty()){
        int next_node = _stack.top();
        _stack.pop();
        find_path(next_node);
    }
}

void find_direction(int x, int y){

    int sx = 2*(x/_wid)+1;
    int sy = 2*(x%_wid)+1;
    int ex = 2*(y/_wid)+1;
    int ey = 2*(y%_wid)+1;

    for(int i = 0; i < 4; i++){
        int nx = sx + _ddx[i];
        int ny = sy + _ddy[i];
        if(nx == ex && ny == ey){
            _mat[sx+_dx[i]][sy+_dy[i]] = (char)32;
        }
    }
}

void draw_maze(){

    for(int i = 0; i < _new_len; i++){
        for(int j = 0; j < _new_wid; j++){
            _mat[i][j] = '#';
        }
    }

    _mat[0][1] = (char)32;
    _mat[_new_len-1][_new_wid-2] = (char)32;



    for(int i = 0; i < _num_nodes; i++){
        for(int j = 0; j < _maze[i].size(); j++){
            find_direction(i, _maze[i][j]);
        }
    }

    for(int i = 1; i < _new_len; i += 2){
        for(int j = 1; j < _new_wid; j += 2){
            _mat[i][j] = (char)32;
        }
    }

    for(int i = 0; i < _new_len; i++){
        for(int j = 0; j < _new_wid; j++){
            cout << _mat[i][j];
        }
        cout << "\n";
    }
}

int main(){

    ios_base::sync_with_stdio(0);
    srand(time(NULL));

    cin >> _len >> _wid;
    _new_len = 2*_len+1;
    _new_wid = 2*_wid+1;
    _num_nodes = _len*_wid;

    int idx = 0;
    for(int i = 0; i < _len; i++){
        for(int j = 0; j < _wid; j++){

            if(j < _wid-1){
                _adj[idx].push_back(i*_wid+j+1);
                _adj[i*_wid+j+1].push_back(idx);
            }
            if(i < _len-1){
                _adj[idx].push_back((i+1)*_wid+j);
                _adj[(i+1)*_wid+j].push_back(idx);
            }
            idx++;
        }
    }

    _start_node = 0;
    _end_node = _num_nodes-1;

    find_path(get_random_int(_num_nodes));
    draw_maze();

    return 0;
}
